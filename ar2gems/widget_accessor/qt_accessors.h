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
** This file is part of the "extra" module of the Geostatistical Earth
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

#ifndef __GSTLAPPLI_MISC_QT_ACCESSORS_H__
#define __GSTLAPPLI_MISC_QT_ACCESSORS_H__

#include <widget_accessor/common.h>
#include <gui/utils/qwidget_value_accessor.h>

#include <string>

class GridSelectorBasic;
class PropertySelectorNoRegion;
class SinglePropertySelector;
class MultiPropertySelector;
class OrderedPropertySelector;
class OrderedCategoricalPropertySelector;
class FileChooser;
class VariogramInput;
class KrigingTypeSelector;
class TrendComponents;
class EllipsoidInput;
class NonParamCdfInput;
class TailCdfInput;
class OctantSearchInput;
class AdvancedNeighborhoodInput;
class GridSelector;
class PropertySelector;
class HardDataKrigingPropertySelector;
class SingleWeightPropertySelector;
class SinglePropertyGroupSelector;
class MultiPropertyGroupSelector;
class MultiRegionSelector;

class EXTRAGUI_DECL GridSelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  GridSelector_accessor( QWidget* widget = 0 );
  virtual ~GridSelector_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  GridSelectorBasic* selector_;

};



class EXTRAGUI_DECL PropertySelectorNoRegion_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  PropertySelectorNoRegion_accessor( QWidget* widget = 0 );
  virtual ~PropertySelectorNoRegion_accessor() {}
  
  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  PropertySelectorNoRegion* selector_;

};


class EXTRAGUI_DECL PropertySelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  PropertySelector_accessor( QWidget* widget = 0 );
  virtual ~PropertySelector_accessor() {}
  
  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  PropertySelector* selector_;

};


class EXTRAGUI_DECL SinglePropertySelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  SinglePropertySelector_accessor( QWidget* widget = 0 );
  virtual ~SinglePropertySelector_accessor() {}
  
  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  SinglePropertySelector* selector_;

};

class EXTRAGUI_DECL SingleWeightPropertySelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  SingleWeightPropertySelector_accessor( QWidget* widget = 0 );
  virtual ~SingleWeightPropertySelector_accessor() {}
  
  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  SingleWeightPropertySelector* selector_;

};


class EXTRAGUI_DECL MultiPropertySelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  MultiPropertySelector_accessor( QWidget* widget = 0 );
  virtual ~MultiPropertySelector_accessor() {}
  
  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  MultiPropertySelector* selector_;

};


class EXTRAGUI_DECL OrderedPropertySelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  OrderedPropertySelector_accessor( QWidget* widget = 0 );
  virtual ~OrderedPropertySelector_accessor() {}
  
  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  OrderedPropertySelector* selector_;

};



class EXTRAGUI_DECL OrderedCategoricalPropertySelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  OrderedCategoricalPropertySelector_accessor( QWidget* widget = 0 );
  virtual ~OrderedCategoricalPropertySelector_accessor() {}
  
  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  OrderedCategoricalPropertySelector* selector_;

};



class EXTRAGUI_DECL SinglePropertyGroupSelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  SinglePropertyGroupSelector_accessor( QWidget* widget = 0 );
  virtual ~SinglePropertyGroupSelector_accessor() {}
  
  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  SinglePropertyGroupSelector* selector_;

};

class EXTRAGUI_DECL MultiPropertyGroupSelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  MultiPropertyGroupSelector_accessor( QWidget* widget = 0 );
  virtual ~MultiPropertyGroupSelector_accessor() {}
  
  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  MultiPropertyGroupSelector* selector_;

};


class EXTRAGUI_DECL MultiRegionSelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  MultiRegionSelector_accessor( QWidget* widget = 0 );
  virtual ~MultiRegionSelector_accessor() {}
  
  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  MultiRegionSelector* selector_;

};

class EXTRAGUI_DECL FileChooser_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  FileChooser_accessor( QWidget* widget = 0 );
  virtual ~FileChooser_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return file_chooser_ != 0; }
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();
  
 private:
  FileChooser* file_chooser_;

};



class EXTRAGUI_DECL VariogramInput_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  VariogramInput_accessor( QWidget* widget = 0 );
  virtual ~VariogramInput_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return varg_input_ != 0; }
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();
  
 private:
  VariogramInput* varg_input_;

};



class EXTRAGUI_DECL KrigingTypeSelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  KrigingTypeSelector_accessor( QWidget* widget = 0 );
  virtual ~KrigingTypeSelector_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; }
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();
  
 private:
  KrigingTypeSelector* selector_;

};


class EXTRAGUI_DECL TrendComponents_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  TrendComponents_accessor( QWidget* widget = 0 );
  virtual ~TrendComponents_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; }
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();
  
 private:
  TrendComponents* selector_;

};
/*
class EXTRAGUI_DECL Drift_components_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  Drift_components_accessor( QWidget* widget = 0 );
  virtual ~Drift_components_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; }
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();

 private:
  Drift_components* selector_;

};
*/
class EXTRAGUI_DECL EllipsoidInput_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  EllipsoidInput_accessor( QWidget* widget = 0 );
  virtual ~EllipsoidInput_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return input_ != 0; }
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();
  
 private:
  EllipsoidInput* input_;

};


class EXTRAGUI_DECL nonParamCdfInput_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  nonParamCdfInput_accessor( QWidget* widget = 0 );
  virtual ~nonParamCdfInput_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return input_ != 0; }
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();
  
 private:
  NonParamCdfInput* input_;

};

class EXTRAGUI_DECL tailCdfInput_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  tailCdfInput_accessor( QWidget* widget = 0 );
  virtual ~tailCdfInput_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return input_ != 0; }
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();
  
 private:
  TailCdfInput* input_;
};


class EXTRAGUI_DECL lowerTailCdfInput_accessor : public tailCdfInput_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  lowerTailCdfInput_accessor( QWidget* widget = 0 );
  virtual ~lowerTailCdfInput_accessor() {}

//  virtual bool initialize( QWidget* widget = 0 );
//  virtual bool is_valid() const { return input_ != 0; }
//  virtual std::string value() const;
//  virtual bool set_value( const std::string& str );
//  virtual void clear();
  
// protected:
//  TailCdfInput* input_;
};


class EXTRAGUI_DECL upperTailCdfInput_accessor : public tailCdfInput_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  upperTailCdfInput_accessor( QWidget* widget = 0 );
  virtual ~upperTailCdfInput_accessor() {}
  
};


class EXTRAGUI_DECL OctantSearch_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  OctantSearch_accessor( QWidget* widget = 0 );
  virtual ~OctantSearch_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return input_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();
    
 private:
  OctantSearchInput* input_;

};

class EXTRAGUI_DECL AdvancedSearch_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  AdvancedSearch_accessor( QWidget* widget = 0 );
  virtual ~AdvancedSearch_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return input_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();
    
 private:
  AdvancedNeighborhoodInput *input_;

};


class EXTRAGUI_DECL GridRegionSelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  GridRegionSelector_accessor( QWidget* widget = 0 );
  virtual ~GridRegionSelector_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  GridSelector* selector_;

};


class EXTRAGUI_DECL PropertyRegionSelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  PropertyRegionSelector_accessor( QWidget* widget = 0 );
  virtual ~PropertyRegionSelector_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; } 
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}
    
 private:
  PropertySelector* selector_;

};

class EXTRAGUI_DECL HardDataKrigingPropertyRegionSelector_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  HardDataKrigingPropertyRegionSelector_accessor( QWidget* widget = 0 );
  virtual ~HardDataKrigingPropertyRegionSelector_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return selector_ != 0; }
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear() {}

 private:
  HardDataKrigingPropertySelector* selector_;

};
/*
class EXTRAGUI_DECL lowerTailCdfInput_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  lowerTailCdfInput_accessor( QWidget* widget = 0 );
  virtual ~lowerTailCdfInput_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return input_ != 0; }
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();
  
 private:
  TailCdfInput* input_;
};


class EXTRAGUI_DECL upperTailCdfInput_accessor : public QWidget_value_accessor {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
  upperTailCdfInput_accessor( QWidget* widget = 0 );
  virtual ~upperTailCdfInput_accessor() {}

  virtual bool initialize( QWidget* widget = 0 );
  virtual bool is_valid() const { return input_ != 0; }
  virtual std::string value() const;
  virtual bool set_value( const std::string& str );
  virtual void clear();
  
 private:
  TailCdfInput* input_;
};
*/

#endif 
