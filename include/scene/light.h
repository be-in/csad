/*
 * light.h
 *
 *  Created on: 06.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <scene/scenecomponent.h>
#include <bt.h>

OPTIMIZE_ON;

namespace csad {

/**
 * @class Light
 *
 * @ingroup scene
 * @brief Light - компонент определ€ющий источник света.
 *
 * For description in the configuration:
 @verbatim
   <Transform>
      <Light mode="режим" direction="направление"/>
   </Transform>
 @endverbatim
 *
 * @see Transform, scene
 */

class Light:public SceneComponent {
public:
	MEMMANAGER(Light)

	CSAD_API Light();
	CSAD_API ~Light();

	/// Light mode
	enum Mode {
		/// Ranged light from point
		Spot,
		/// Light from point
		Point,
		/// Linear light.
		Direct,
	};

	/// Define light mode
	CSAD_API void setMode(unsigned int mode);
	/// Define light mode
	CSAD_API void setMode(char *mode);
	/// Define light mode
	_FORCEINLINE void setMode(const char *mode) { setMode((const char*)mode); }
	/// Return light mode
	_FORCEINLINE unsigned int mode() { return p_mode; }
	/// Set light direction
	CSAD_API void setDirection(vector3f *dir);
	/// Return light direction
	_FORCEINLINE vector3f &direction() { return mdirec; }

	///
	CSAD_API void setAmbient(vector4f *val);
	/// Ambient color
	_FORCEINLINE bt::vector4f &ambient() { return fambient; }
	///
	CSAD_API void setDiffuse(vector4f *val);
	///  Diffuse color
	_FORCEINLINE bt::vector4f &diffuse() { return fdiffuse; }
	///
	CSAD_API void setSpecular(vector4f *val);
	/// Specular color
	_FORCEINLINE bt::vector4f &specular() { return fspecular; }

	/// Set spot angle
	CSAD_API void setCutoff(float val);
	/// Return spot angle
	_FORCEINLINE float cutoff() { return fcutoff; }

	CSAD_API void *set(unsigned _int32,void*);

	CSAD_API TYPEINFO_H

private:
	vector3f mdirec;
	unsigned int p_mode;
	vector4f fambient;
	vector4f fdiffuse;
	vector4f fspecular;
	float fcutoff;
};

}

OPTIMIZE_OFF;

#endif /* LIGHT_H_ */
