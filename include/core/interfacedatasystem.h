/*
 * interfacedatasystem.h
 *
 *  Created on: 09.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef INTERFACEDATASYSTEM_H_
#define INTERFACEDATASYSTEM_H_

#include <core/objectmanager.h>
//#include <core/conteiner.h>
#include <gen3.h>

namespace csad {

class Texture2D;

/*class ObjectPriority {
	void upObjectPriority(void *key);
	void **getLowObject();

	void *list;
	_voidint maxPriority;
	_voidint maxSize;
};*/

/**
 * @class InterfaceDataSystem
 *
 * @ingroup scene
 * @brief InterfaceDataSystem - system data manager.
 *
 * 
 *
 *
 * @see core
 */

class InterfaceDataSystem {
public:
	CSAD_API InterfaceDataSystem();
	CSAD_API ~InterfaceDataSystem();

	CSAD_API bool registerFormat(BaseObject * obj);
	CSAD_API void setAvailSize(int size);
	_FORCEINLINE void removeData(char *dataName) {p_objects.removeObject(dataName);}

	/// отложенная загрузка ресурса двухмерного изображеня
	CSAD_API void loadRaster(char *filename,gen::Raster **raster);
	_FORCEINLINE void loadRaster(const char *filename,gen::Raster **raster) { loadRaster((char*)filename,raster); }

	/// отложенная загрузка ресурса двухмерного изображеня в текстуру
	CSAD_API void loadRasterToTexture2D(char *filename,Texture2D *text);
	_FORCEINLINE void loadRasterToTexture2D(const char *filename,Texture2D *text) { loadRasterToTexture2D((char*)filename,text); }

private:
	ObjectManager p_objects;
	void *list;
	_voidint maxPriority;
	_voidint maxSize;
	_voidint lockSize;

	_voidint addRasterAlloc(Raster *raster);

	void upObjectPriority(void *key);
	void **getLowObject();

	static void _APICALL _loadRaster(ParametersList *param);
	static void _APICALL _Raster(ParametersList *param);
};

}

#endif /* INTERFACEDATASYSTEM_H_ */
