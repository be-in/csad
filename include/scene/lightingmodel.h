/*
 * @file lightingmodel.h
 *
 *  Created on: 06.12.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef LIGHTINGMODEL_H_
#define LIGHTINGMODEL_H_

#include <core/baseobject.h>
#include <core/csadapi.h>
#include <bt.h>

OPTIMIZE_ON;

namespace csad {

class Scene;
class Light;

typedef VoidVector<Light> ListLightings;

/**
 * @class LightingModel
 *
 * @ingroup scene
 * @brief LightingModel - группа освещения.
 *
 * For description in the configuration:
 @verbatim
   <Scene>
      <Transform name="name of light">
         <Light />
	  </Transform>
      <LightingModel name="name mode" light0="name of light"/>
   </Scene>
 @endverbatim
 *
 * @see Scene, scene
 */

class LightingModel: public BaseObject {
public:
	MEMDEFAULT(LightingModel)

	CSAD_API LightingModel(Scene *,char*name);
	CSAD_API ~LightingModel();

	/// use light in lighting model
	CSAD_API LightingModel& setLight(unsigned int id,char *name);
	/// use light in lighting model
	_FORCEINLINE LightingModel& setLight(unsigned int id,const char *name) { setLight(id,(char *)name); return *this; }
	/// use light in lighting model
	CSAD_API LightingModel& setLight(unsigned int id,Light*light);

	/// lights in lighting model
	ListLightings &lights() { return flist; }

	CSAD_API void *set(unsigned _int32,void*);

	CSAD_API TYPEINFO_H

private:
	ListLightings flist;
	Scene *fscene;

friend class Scene;
};

}

OPTIMIZE_OFF;

#endif /* LIGHTINGMODEL_H_ */
