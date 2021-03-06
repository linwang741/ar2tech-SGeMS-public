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
** Author: Nicolas Remy
** Copyright (C) 2002-2004 The Board of Trustees of the Leland Stanford Junior
**   University
** All rights reserved.
**
** This file is part of the "math" module of the Geostatistical Earth
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

#ifndef __GSTLAPPLI_MATH_GSTLPOINT_H__ 
#define __GSTLAPPLI_MATH_GSTLPOINT_H__ 
 
#include <math/common.h>
#include <utils/gstl_types.h> 
#include <math/gstlvector.h> 
 
#include <iostream> 
#include <cmath>
 

/** GsTLTripletTmpl represents any triplet of numbers. 

* One of its purposes is to represent a location in 3D space.

*/
template <class R > 
class GsTLTripletTmpl { 
public: 
    // Requirements for GsTL : 
    typedef R coordinate_type; 
    typedef GsTLVector<R> difference_type; 
    static const int dimension = 3; 



    //KD tree requirements
public: 

  typedef R ScalarType;

  static int get_dim() { return GsTLTripletTmpl<R>::dimension; }

  R length() const { 
    return std::sqrt( coords_[0]*coords_[0]+
                      coords_[1]*coords_[1]+
                      coords_[2]*coords_[2]  );
  }

  R distance2(const GsTLTripletTmpl<R>& gp) const { 
    R dx =  coords_[0] - gp[0];
    R dy =  coords_[1] - gp[1];
    R dz =  coords_[2] - gp[2];
    return dx*dx + dy*dy + dz*dz;
  }

  void normalize() {
    R l=length();
    coords_[0] /= l;
    coords_[1] /= l;
    coords_[2] /= l;
  }

  GsTLTripletTmpl( const GsTLVector<R>& gp )  { 
    coords_[0] = gp.x(); 
    coords_[1] = gp.y(); 
    coords_[2] = gp.z(); 
  } 

   GsTLTripletTmpl<R>& operator = ( const GsTLVector<R>& t ) { 
     if( this != &t ) { 
       coords_[0] = t.x(); 
       coords_[1] = t.y();
       coords_[2] = t.z();
     } 
     return *this; 
   } 

     
public:
    GsTLTripletTmpl() { 
        coords_[0] = 0; 
        coords_[1] = 0; 
        coords_[2] = 0; 
    } 
 
    GsTLTripletTmpl( 
        R x, R y, R z 
    )  { 
        coords_[0] = x; 
        coords_[1] = y; 
        coords_[2] = z; 
    } 
     
    GsTLTripletTmpl( 
        const GsTLTripletTmpl<R>& gp 
    )  { 
        coords_[0] = gp.coords_[0]; 
        coords_[1] = gp.coords_[1]; 
        coords_[2] = gp.coords_[2]; 
    } 
     
    ~GsTLTripletTmpl() {} 
     
     
     
    R& x() { return coords_[0]; } 
    R& y() { return coords_[1]; } 
    R& z() { return coords_[2]; } 
     
    const R& x() const { return coords_[0]; } 
    const R& y() const { return coords_[1]; } 
    const R& z() const { return coords_[2]; } 
 
    GsTLTripletTmpl<R> operator + (const difference_type& v ) const { 
        return (GsTLTripletTmpl<R>(coords_[0]+v[0], coords_[1]+v[1], coords_[2]+v[2])); 
    } 
     
    // Requirements GsTL : 
 
    R& operator [] (GsTLInt i) { 
        return coords_[i]; 
    } 
     
    const R& operator [] (GsTLInt i) const { 
        return coords_[i]; 
    } 
     
     
    GsTLVector<R> operator - (const GsTLTripletTmpl<R>& t1 ) const { 
        return (GsTLVector<R>( 
                coords_[0] - t1.coords_[0], 
                coords_[1] - t1.coords_[1], 
                coords_[2] - t1.coords_[2] 
            ) 
        ); 
    } 
     
     
    GsTLTripletTmpl<R> operator + (const GsTLTripletTmpl<R>& t1 ) const { 
        return (GsTLTripletTmpl<R>( 
                coords_[0] + t1.coords_[0], 
                coords_[1] + t1.coords_[1], 
                coords_[2] + t1.coords_[2] 
            ) 
        ); 
    } 
 

    
    GsTLTripletTmpl<R> operator / (R r ) const { 
        return (GsTLTripletTmpl<R>( 
                coords_[0]/r, 
                coords_[1]/r, 
                coords_[2]/r 
            ) 
        ); 
    }

    void operator /= ( R r ) {

      coords_[0] /= r;

      coords_[1] /= r;

      coords_[2] /=r;

    }


    GsTLTripletTmpl<R> operator * (R r ) const { 
        return (GsTLTripletTmpl<R>( 
                coords_[0]*r, 
                coords_[1]*r, 
                coords_[2]*r 
            ) 
        ); 
    }

    void operator *= (R r ) const { 
        coords_[0]*=r;
        coords_[1]*=r;
        coords_[2]*=r;
    }

    void operator -= ( const GsTLTripletTmpl<R>& t ) {

      coords_[0] -= t.coords_[0];

      coords_[1] -= t.coords_[1];

      coords_[2] -= t.coords_[2];

    }

    void operator += ( const GsTLTripletTmpl<R>& t ) {

      coords_[0] += t.coords_[0];

      coords_[1] += t.coords_[1];

      coords_[2] += t.coords_[2];

    }


    GsTLTripletTmpl<R>& operator = ( const GsTLTripletTmpl<R>& t ) { 
        if( this != &t ) { 
            coords_[0] = t.coords_[0]; 
            coords_[1] = t.coords_[1]; 
            coords_[2] = t.coords_[2]; 
        } 
        return *this; 
    } 
     
    bool operator == (const GsTLTripletTmpl<R>& t ) const { 
        if( (coords_[0] == t.coords_[0]) &&  (coords_[1] == t.coords_[1]) &&  (coords_[2] == t.coords_[2]) ) { 
            return true; 
        } 
        return false; 
    } 
 
    bool operator != (const GsTLTripletTmpl<R>& t ) const { 
        if( (coords_[0] != t.coords_[0]) ||  (coords_[1] != t.coords_[1]) ||  (coords_[2] != t.coords_[2]) ) { 
            return true; 
        } 
        return false; 
    } 

    const R* raw_access() const { return coords_; }
    R* raw_access() { return coords_; }

     
protected: 
    R coords_[3]; 
}; 
 
template <class R> 
std::ostream& operator << ( std::ostream& o,  const GsTLTripletTmpl<R>& t ) { 
        o << t[0] << " " << t[1] << " " << t[2] ; 
        return o; 
} 
 

template<class R>

inline R dot( const GsTLTripletTmpl<R>& t1, const GsTLTripletTmpl<R>& t2 ) {

  return ( t1.x()*t2.x() + 

           t1.y()*t2.y() + 

           t1.z()*t2.z() );

}


/*
template<class R>
inline GsTLTripletTmpl<R> operator * (R r, const GsTLTripletTmpl<R>& t ) const { 
  return t*r;
}
*/


typedef GsTLTripletTmpl<GsTLCoord> GsTLPoint; 
typedef GsTLTripletTmpl<GsTLInt> GsTLGridNode; 
typedef GsTLTripletTmpl<double> GsTLTriplet; 
 
 
#endif 
