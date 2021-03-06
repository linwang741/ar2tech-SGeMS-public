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
** Author: Ting Li
** Copyright (C) 2002-2004 The Board of Trustees of the Leland Stanford Junior
**   University
** All rights reserved.
**
** This file is part of the "grid" module of the Geostatistical Earth
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

#ifndef MGRID_NEIGHBORHOOD_H
#define MGRID_NEIGHBORHOOD_H

#include <grid/grid_model/rgrid_neighborhood.h>
#include <grid/grid_model/rgrid.h>
#include <grid/maskedgridcursor.h>

class GRID_DECL MgridNeighborhood : public Rgrid_ellips_neighborhood
{
public:
	MgridNeighborhood( RGrid* grid, 
		Grid_continuous_property* property, 
		GsTLInt max_radius, GsTLInt mid_radius, GsTLInt min_radius, 
		double x_angle, double y_angle, double z_angle, 
		int max_neighbors = 20, 
		const Covariance<GsTLPoint>* cov = 0,
    const Grid_region* region=0); 
	~MgridNeighborhood() {}
	 virtual void find_neighbors( const Geovalue& center ); 
protected:
	 MaskedGridCursor * _mcursor;

};

class GRID_DECL MgridWindowNeighborhood : public Rgrid_window_neighborhood
{
public:
	 MgridWindowNeighborhood( const Grid_template& geom, RGrid* grid=0, 
			     Grid_continuous_property* prop = 0 );
	 ~MgridWindowNeighborhood(){}
	 virtual void find_neighbors( const Geovalue& center ); 
	 virtual void set_grid(RGrid *);
     virtual void find_all_neighbors( const Geovalue& center );

protected:
	 MaskedGridCursor * _mcursor;
};

class GRID_DECL MgridNeighborhood_hd : public Rgrid_ellips_neighborhood_hd
{
public:
	MgridNeighborhood_hd( RGrid* grid, 
		Grid_continuous_property* property, 
		GsTLInt max_radius, GsTLInt mid_radius, GsTLInt min_radius, 
		double x_angle, double y_angle, double z_angle, 
		int max_neighbors = 20, 
		const Covariance<GsTLPoint>* cov = 0,
    const Grid_region* region=0); 
	~MgridNeighborhood_hd() {}
	virtual void find_neighbors( const Geovalue& center ); 
protected:
	MaskedGridCursor * _mcursor;
};
#endif