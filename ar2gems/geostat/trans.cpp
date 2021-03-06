/* -----------------------------------------------------------------------------
** Copyright (c) 2012 Advanced Resources and Risk Technology, LLC
** All rights reserved.
**
** This file is part of Advanced Resources and Risk Technology, LLC (AR2TECH) 
** version of the open source software sgems.  It is a derivative work by 
** AR2TECH (THE LICENSOR) based on the x-free license granted in the original 
** version of the software (see notice below) and now sublicensed such that it 
** cannot be distributed or modified without the explicit and written permission 
** of AR2TECH.
**
** Only AR2TECH can modify, alter or revoke the licensing terms for this 
** file/software.
**
** This file cannot be modified or distributed without the explicit and written 
** consent of AR2TECH.
**
** Contact Dr. Alex Boucher (aboucher@ar2tech.com) for any questions regarding
** the licensing of this file/software
**
** The open-source version of sgems can be downloaded at 
** sourceforge.net/projects/sgems.
** ----------------------------------------------------------------------------*/



/**********************************************************************
** Author: Alexandre Boucher
** Copyright (C) 2002-2004 The Board of Trustees of the Leland Stanford Junior
**   University
** All rights reserved.
**
** This file is part of the "geostat" module of the Geostatistical Earth
** Modeling Software (GEMS)
**
** This file may be distributed and/or modified under the terms of the 
** license defined by the Stanford Center for Reservoir Forecasting and 
** appearing in the file LICENSE.XFREE included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.gnu.org/copyleft/gpl.html for GPL licensing information.
**
** Contact the Stanford Center for Reservoir Forecasting, Stanford University
** if any conditions of this licensing are not clear to you.
**
**********************************************************************/
#include "trans.h"
#include <grid/grid_model/geostat_grid.h>
#include <grid/grid_model/point_set.h>
#include <grid/grid_model/cartesian_grid.h>
#include <grid/grid_model/grid_property.h>
#include <grid/grid_model/grid_region.h>
#include <grid/grid_model/gval_iterator.h>
#include <GsTL/cdf/cdf_basics.h>
#include <GsTL/cdf/gaussian_cdf.h>
#include <GsTL/cdf/First2_moments_cdf.h>
#include <GsTL/cdf/non_param_cdf.h>
#include <GsTL/univariate_stats/build_cdf.h>
#include <utils/string_manipulation.h>
#include <utils/error_messages_handler.h>
#include <geostat/parameters_handler.h>
#include <grid/grid_model/property_copier.h>

#include <fstream>

#include <algorithm>



int trans::execute( GsTL_project* ) {

	for(int i=0; i<source_props_.size(); i++ ) {

    Grid_continuous_property* source_prop = source_props_[i];
		Grid_continuous_property* target_prop = 
			geostat_utils::add_property_to_grid( grid_, source_prop->name()+suffix_ );

    for(int i=0; i<grid_->size();++i) {
      if(region_ && !region_->is_inside_region(i)) continue;
      if( !source_prop->is_informed(i) ) continue;
      target_prop->set_value(source_prop->get_value(i),i);
    }

		if(is_local_cond_) cdf_transform_weighted(target_prop);
		else cdf_transform(target_prop);
    target_prop->set_parameters(parameters_);
	}

	return 0;
}

/*
Initialize the parameters
*/
bool trans::initialize( const Parameters_handler* parameters,
			Error_messages_handler* errors ) {
	std::cout << "initializing algorithm Trans \n";

	std::string grid_name = parameters->value( "grid.value" );
	errors->report( grid_name.empty(), 
			"grid", "No grid specified" );
	
	// Get the simulation grid from the grid manager
	if( !grid_name.empty() ) {
		bool ok = geostat_utils::create( grid_, grid_name,
				 "grid", errors );
		if( !ok ) return false;
	}
	else 
		return false;

  std::string region_name = parameters->value( "grid.region" );
  region_ = grid_->region(region_name);

	std::vector< std::string > prop_names = String_Op::decompose_string( 
						parameters->value( "props.value" ), ";" );
	errors->report( prop_names.empty(), "props", "No property specified" );
	suffix_ = parameters->value( "out_suffix.value" );
  if( !errors->empty() ) return false;


  cdf_source_ = get_cdf( parameters,errors, "source");
  cdf_target_ = get_cdf( parameters,errors, "target");
  if(cdf_source_.raw_ptr()==NULL || cdf_target_.raw_ptr() == NULL) return false;

 
	is_local_cond_ = ( parameters->value( "is_cond.value" ) == "1" );
	if(is_local_cond_) {
		std::string cond_prop_str = parameters->value( "cond_prop.value" );
		errors->report( cond_prop_str.empty(),"cond_prop", "No property specified" );
		std::string wgt_factor_str = parameters->value( "weight_factor.value" );
		errors->report( wgt_factor_str.empty(),"weight_factor", "No weight factor specified" );
		float wgt_factor = String_Op::to_number< float >( wgt_factor_str );

		Grid_continuous_property* cond_prop = grid_->property( cond_prop_str );

		//weights_.insert(weights_.begin(), cond_prop->begin(),cond_prop->end() );
    for (int i=0; i<cond_prop->size(); i++)
    {
      if(region_ && !region_->is_inside_region(i)) continue;
      if ( cond_prop->is_informed(i) )
          weights_.push_back( cond_prop->get_value(i) );
      else
          weights_.push_back( -999 );
    }

		wgth_iterator it_max  = std::max_element(weights_.begin(),weights_.end());
		for(wgth_iterator it = weights_.begin() ; it!= weights_.end(); ++it )
        {
            if ( *it<0.0 )
                *it = 1.0;
            else
                *it = std::pow( (*it)/(*it_max) ,wgt_factor);
            //*it = std::pow( *it*(*it_max) ,wgt_factor);
        }
	}
  if(!errors->empty()) return false;

// Set up the property Copier 
//	Property_copier* prop_copier;
//	Point_set* pset = dynamic_cast< Point_set* >( grid_ );
//    Cartesian_grid* cgrid = dynamic_cast< Cartesian_grid* >( grid_ );
//	if( pset ) prop_copier = new Pset_to_pset_copier();
//	else if(cgrid) prop_copier = new Cgrid_to_cgrid_copier();

	for(int j=0; j<prop_names.size() ; j++ ) {
		Grid_continuous_property* sourceProp = grid_->property( prop_names[j] );
    if( sourceProp== 0 ) {
		  errors->report( "props", "Non existing properties" );
      return false;
    }
    source_props_.push_back(sourceProp);

  }

  if(!errors->empty()) {
    return false;
  }

  this->extract_parameters(parameters);
	return true;
}

SmartPtr<Continuous_distribution> trans::get_cdf( const Parameters_handler* parameters,
		Error_messages_handler* errors, std::string suffix )
{
	SmartPtr<Continuous_distribution> cdist;
  std::string cdf_type = parameters->value( "ref_type_"+suffix+".value" );

	//bool is_nonparam = ( parameters->value( "ref_type_"+suffix+".value" ) == "Non Parametric" );
	//bool is_Gaussian = ( parameters->value( "ref_type_"+suffix+".value" ) == "Gaussian" );

  if( cdf_type == "Non Parametric" ) {
    bool ok = distribution_utils::get_continuous_cdf(cdist,parameters,
              errors,"nonParamCdf_"+suffix);
  }
	else if(cdf_type == "Gaussian")
	{
		std::string mean_str = parameters->value( "G_mean_"+suffix+".value" );
	    std::string var_str = parameters->value( "G_variance_"+suffix+".value" );
		errors->report( mean_str.empty()|| var_str.empty(), "GaussianBox_"+suffix, 
				"No mean or variance provided" );

    float mean = String_Op::to_number<float>(mean_str);
    float variance = String_Op::to_number<float>(var_str);

    cdist = SmartPtr<Continuous_distribution>(new Gaussian_distribution(mean, std::sqrt(variance) ) );
	} 
	else if(cdf_type == "Uniform")
	{
		std::string unif_min = parameters->value( "Unif_min_"+suffix+".value" );
	  std::string unif_max = parameters->value( "Unif_max_"+suffix+".value" );
		errors->report( unif_min.empty()|| unif_max.empty(), "UniformBox_"+suffix, 
				"No minimum or maximum provided" );

    cdist = SmartPtr<Continuous_distribution>(new Uniform_distribution(String_Op::to_number<float>(unif_min),
                                                                        String_Op::to_number<float>(unif_max) ));
	} 

	else if(cdf_type == "Log Normal")
	{
		std::string mean_str = parameters->value( "LN_mean_"+suffix+".value" );
	    std::string var_str = parameters->value( "LN_variance_"+suffix+".value" );
		errors->report( mean_str.empty()|| var_str.empty(), "logNormalBox_"+suffix, 
				"No mean or variance provided" );

    float mean = String_Op::to_number<float>(mean_str);
    float variance = String_Op::to_number<float>(var_str);

    cdist = SmartPtr<Continuous_distribution>(new LogNormal_distribution(mean, std::sqrt(variance) ));
	} 

	return cdist;
}

void  trans::cdf_transform( Grid_continuous_property* prop )
{
	grid_->select_property( prop->name() );
	for( Geostat_grid::iterator it = grid_->begin(); it != grid_->end(); ++it )
	{
    if(region_ && !region_->is_inside_region(it->node_id()) ) continue;
		if( it->is_informed() ) {
			double p = cdf_source_->prob(it->property_value());
      if(p > 0 && p < 1.0) {
			  it->set_property_value( cdf_target_->inverse(p) );
      }
      else {
        it->set_not_informed();
      }
		}
	}
}


void  trans::cdf_transform_weighted( Grid_continuous_property* prop  )
{
	grid_->select_property( prop->name() );
	wgth_iterator it_wt = weights_.begin();
	for( Geostat_grid::iterator it = grid_->begin(); it != grid_->end(); ++it, ++it_wt )
	{
    if(region_ && !region_->is_inside_region(it->node_id()) ) continue;
		if( it->is_informed() ) {
			float val = it->property_value();
			float zval = cdf_target_->inverse( cdf_source_->prob( val ) );
			it->set_property_value( val - *it_wt*(val-zval) );
		}
	}
}

Named_interface* trans::create_new_interface( std::string& ) {
  return new trans;
}
