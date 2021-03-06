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



#include <actions/unary_action.h>
#include <utils/error_messages_handler.h>
#include <grid/grid_model/gval_iterator.h>
#include <utils/string_manipulation.h>
#include <actions/defines.h>
#include <geostat/utilities.h>
#include <appli/manager_repository.h>

bool Unary_action::init(std::string& _parameters, GsTL_project* _proj, Error_messages_handler* _errors) {
	this->proj_ = _proj;
	this->errors_ = _errors;

	std::vector<std::string> params = String_Op::decompose_string(_parameters, Actions::separator, Actions::unique);

	// check for correct number of parameters
	if (params.size() <2) {
		return false;
	}

	// extract the parameters
	grid_name_ = params[0];
	property_name_ = params[1];
	if(params.size()==3)
		new_property_name_ = params[2];
	else
		new_property_name_ = this->name()+"("+params[1]+")";

	// get reference to the grid
//	bool ok = geostat_utils::create(this->grid_, this->grid_name_, "", _errors);
  grid_ = dynamic_cast<Geostat_grid*>(
		Root::instance()->interface( 
					    gridModels_manager + "/" + this->grid_name_
					    ).raw_ptr() );
	if (!grid_) {
		_errors->report("Illegal grid name specified");
		return false;
	}

	Grid_continuous_property* property = grid_->property(property_name_);
	if (property == 0) {
		_errors->report("Illegal property specified");
		return false;
	}

	Grid_continuous_property* new_property = grid_->property(new_property_name_);
	if (new_property != 0) {
		_errors->report("New Property already exists in specified grid");
		return false;
	}

	return true;
}

bool Unary_action::exec() {
	// set the active property to reading property
	this->grid_->select_property(this->property_name_);

	// add new property to the grid
//	Grid_continuous_property* newProperty = 
 //   geostat_utils::add_property_to_grid(this->grid_, this->new_property_name_);
  Grid_continuous_property* newProperty = this->grid_->property( this->new_property_name_ );
  if( !newProperty ) 
    newProperty = this->grid_->add_property( this->new_property_name_ );

	// get iterators for the original property and the new property
	Geostat_grid::iterator property_begin = this->grid_->begin();
	Geostat_grid::iterator property_end = this->grid_->end();
	Geostat_grid::iterator new_property_begin = this->grid_->begin(newProperty);
	Geostat_grid::iterator new_property_end = this->grid_->end(newProperty);
	for (; property_begin != property_end; ++property_begin, ++new_property_begin) {
		if(!property_begin->is_informed()) continue;
		Geovalue::property_type new_prop_value = 0.0;
    bool ok = this->transform(property_begin->property_value(), new_prop_value);
		if ( ok ) 
      new_property_begin->set_property_value(new_prop_value);
    else 
			new_property_begin->set_not_informed();
	}
	return true;
}



bool Standardize_transform_action::transform(
		const Geovalue::property_type& _val,
		Geovalue::property_type& _new_val){
//	if(!is_initialized_) compute_moment();
	_new_val = (_val -mean_)/stdev_;
	return true;
}

bool Standardize_transform_action::init(std::string& _parameters, GsTL_project* _proj,
										Error_messages_handler* _errors) {
	bool ok = Unary_action::init(_parameters,_proj,_errors);
	if(!ok) return false;

	this->grid_->select_property(this->property_name_);
	Geovalue::property_type sum=0.;
	Geovalue::property_type sum2=0.;
	int n = 0;
	Geostat_grid::iterator property_begin = this->grid_->begin();
	Geostat_grid::iterator property_end = this->grid_->end();
	for (; property_begin != property_end; ++property_begin) {
		if(!property_begin->is_informed()) continue;
		Geovalue::property_type val = property_begin->property_value();
		sum += val;
		sum2 += val*val;
		n++;

	}
	if(n==0) return false;
	mean_ = sum/n;
	stdev_ = std::sqrt(sum2/n - mean_*mean_);
	return true;
}



bool Unit_scaling_transform_action::transform(
		const Geovalue::property_type& _val,
		Geovalue::property_type& _new_val){
//	if(!is_initialized_) compute_moment();
	_new_val = (_val -min_)/(max_ - min_);
	return true;
}

bool Unit_scaling_transform_action::init(std::string& _parameters, GsTL_project* _proj,
										Error_messages_handler* _errors) {
	bool ok = Unary_action::init(_parameters,_proj,_errors);
	if(!ok) return false;

  Grid_continuous_property* prop = this->grid_->select_property(this->property_name_);

  Grid_continuous_property::const_iterator it = prop->begin();
  min_ = 9e20;
  max_ = -9e20;
  for( ; it != prop->end(); ++it ){
    if(*it < min_) min_ = *it;
    else if(*it > max_) max_ = *it;
  }

//  min_ = *( std::min_element(prop->begin(), prop->end()) );
//  max_ = *( std::max_element(prop->begin(), prop->end()) );

  if(min_ == max_) return false;

  return true;

}



