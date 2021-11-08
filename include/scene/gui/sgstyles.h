/*
 * sgstyle.h
 *
 *  Created on: 16.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SGSTYLE_H_
#define SGSTYLE_H_

#include <core/component.h>
#include <scene/style.h>
#include <bt.h>

namespace csad {

using namespace bt;

class Material;

class SGStyle: public Component {
public:
	MEMDEFAULT(SGStyle)

	CSAD_API SGStyle();

	enum State {
		DEFAULT = 0,
		SELECT = 1,
		ACTION = 2,
		DISABLE = 3,
	};

	CSAD_API void setMaterialBack(char * name,int state);
	CSAD_API void setMaterialBack(Material * mat,int state);
	/// returns the substrate material corresponding to the state of the button.
	CSAD_API Material *getMaterialBack(int state);

	CSAD_API void setMaterialText(char * name,int state);
	CSAD_API void setMaterialText(Material * mat,int state);
	/// returns the material of the text corresponding to the state of the button.
	CSAD_API Material *getMaterialText(int state);

	CSAD_API void setMaterialKey(char * name,int state);
	CSAD_API void setMaterialKey(Material * mat,int state);
	/// returns the material of the text corresponding to the state of the button.
	CSAD_API Material *getMaterialKey(int state);

	CSAD_API void * set(unsigned _int32 ,void *);

	_FORCEINLINE static SGStyle * useStyle(Style *style,void *type) {return (SGStyle *)style->getComponent(type);}

	CSAD_API TYPEINFO_H

private:
	Material *materialBack[8];
	Material *materialText[4];
	Material *materialKey[2];
};

/**
 * @class SGButtonStyle
 *
 * @ingroup scenegui
 * @brief SGButtonStyle - component containing the settings button States.
 *
 * For description in the configuration:
 @verbatim
   <Style name="buttonstyle">
      <SGButtonStyle normal="butmatnormal" active="butmatactive" click="butmatclick"/>
	  <SGButtonStyle normal_text="textmatnormal" normal_text="textmatactive" normal_text="textmatclick"/>
   </Style>
 @endverbatim
 *
 * @see scenegui, SGButton
 */

class SGButtonStyle: public SGStyle {
public:
	MEMDEFAULT(SGButtonStyle)

	CSAD_API void * set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

};

/**
 * @class SGElementStyle
 *
 * @ingroup scenegui
 * @brief SGElementStyle - component containing the parameters of the item's state.
 *
 * @see scenegui
 */

class SGElementStyle: public SGStyle {
public:
	MEMDEFAULT(SGElementStyle)

	CSAD_API void * set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

};

/**
 * @class SGLineEditStyle
 *
 * @ingroup scenegui
 * @brief SGLineEditStyle - component containing the parameters of the line edit state.
 *
 * @see scenegui, SGLineEdit
 */

class SGLineEditStyle: public SGStyle {
public:
	MEMDEFAULT(SGLineEditStyle)

	CSAD_API void * set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

};

}

#endif /* SGSTYLE_H_ */
