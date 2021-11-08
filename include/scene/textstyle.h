/*
 * textstyle.h
 *
 *  Created on: 03.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef TEXTSTYLE_H_
#define TEXTSTYLE_H_

#include <core/component.h>

namespace csad {

class Font;
class Material;

/**
 * @class TextStyle
 *
 * @ingroup scene
 * @brief TextStyle - component describing the parameters of the text.
 *
 * 
 * For description in the configuration:
 @verbatim
   <Style name="the name of the style">
      <TextStyle font="server/font" material="textMaterial" charsize="0.0005" kerning="1.0" />
   </Style>
 @endverbatim
 *
 * @see scene
 */

class TextStyle: public Component {
public:
	MEMDEFAULT(TextStyle)

	CSAD_API TextStyle();

	enum Anchor {
		/// on top
		Top = 0x010,
		/// on center
		Center = 0x000,
		/// relative to the bottom
		Bottom = 0x020,
		/// относительно лева
		Left = 0x100,
		/// относительно права
		Right = 0x001,
		/// относительно левого верхнего угла
		Left_Top = 0x110,
		/// относительно лева по центру
		Left_Center = 0x100,
		/// относительно левого нижнего угла
		Left_Bottom = 0x120,
		/// относительно правого верхнего угла
		Right_Top = 0x011,
		/// относительно права по центру
		Right_Center = 0x001,
		/// относительно правого нижнего угла
		Right_Bottom = 0x021
	};

	/// Sets the font for the server name and font
	CSAD_API TextStyle& setFont(char *path);
	/// Sets the font for the server name and font
	_FORCEINLINE TextStyle& setFont(const char *path) {setFont((char *)path);return *this;}
	/// Specifies the font object
	CSAD_API TextStyle& setFont(Font *font);
	/// Returns a font object
	/// @return Font.
	_FORCEINLINE Font * getFont() {return p_font;}
	/// Specifies the scale of the image characters
	CSAD_API TextStyle& setCharSize(float val);
	/// Returns the scale of the image characters
	_FORCEINLINE float getCharSize() {return p_charSize;}
	/// Specifies the scale of the distance between characters
	CSAD_API TextStyle& setKerning(float val);
	/// Returns the scale of the character spacing
	_FORCEINLINE float getKerning() {return p_kerning;}
	/// Specifies the orientation of the text by name
	CSAD_API TextStyle& setAnchor(char *name);
	/// Specifies the orientation of the text
	CSAD_API TextStyle& setAnchor(int val);
	/// Returns the orientation of the text
	_FORCEINLINE int getAnchor() {return p_anchor;}
	/// Specifies the material by name
	CSAD_API TextStyle& setMaterial(char *name);
	/// Sets the object's material
	CSAD_API TextStyle& setMaterial(Material *mat);
	/// Returns an object of material
	_FORCEINLINE Material* getMatrial() {return p_material;}

	CSAD_API void *set(unsigned _int32 ,void *);

	CSAD_API const char *getPath();

	CSAD_API TYPEINFO_H
private:
	Font* p_font;
	float p_charSize;
	float p_kerning;
	int p_anchor;
	Material *p_material;

	friend class Text3D;
	friend class ModellerMesh;
};

}

#endif /* TEXTSTYLE_H_ */
