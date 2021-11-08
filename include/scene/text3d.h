/*
 * text3d.h
 *
 *  Created on: 28.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef TEXT3D_H_
#define TEXT3D_H_

#include <scene/scenecomponent.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

class Style;
class TextStyle;
class Mesh;
class GlContext;

/**
 * @class Text3D
 *
 * @ingroup scene
 * @brief Text3D - component, is suitable for construction of geometry text. Build output is saved in a Mesh situated in the component MeshFilter.
 *
 * @see scene MeshFilter Mesh
 */

class Text3D: public SceneComponent {
public:
	MEMMANAGER(Text3D)

	CSAD_API Text3D();

	/// Sets the style of the text style name
	CSAD_API Text3D& setStyle(char *name);
	/// Sets the style of the text style name
	CSAD_API Text3D& setStyle(const char *name);
	/// Sets the style
	CSAD_API Text3D& setStyle(Style *style);
	/// Returns the text style
	_FORCEINLINE TextStyle *textStyle() {return p_style;}
	/// Sets the text
	CSAD_API Text3D& setText(char *text);
	/// Sets the text
	CSAD_API Text3D& setText(const char *text);
	/// Restores text
	_FORCEINLINE const char* text() {return p_text.str();}
	/// Returns the position of the text
	CSAD_API vector3d textCenter();
	_FORCEINLINE vector3d &textSize() {return p_meshSize;}
	/// To set the offset into the depth
	CSAD_API void setOffset(float offset);

	/// sets the object receiving the event from the text
	CSAD_API void setResiver(BaseObject *);

	CSAD_API void start();
	CSAD_API void update();
	CSAD_API void quit();

	int changes() {return p_changes;}

	CSAD_API void *set(unsigned _int32 ,void *);

	CSAD_API TYPEINFO_H

private:
	TextStyle *p_style;
	ShortString p_text;
	bool p_isBuild;
	float p_zoffset;
	vector3d p_meshSize;
	int p_changes;
	BaseObject *p_resiver;

	Mesh* createMesh(const char *name="");

	/// Перещет модели текста
	void _buildMesh();
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* TEXT3D_H_ */
