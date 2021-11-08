/*
 * csad.h
 *
 *  Created on: 26.11.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef CSAD_H_
#define CSAD_H_

/**
 * @mainpage Complex software application developer (Комплекс программного обеспечения разработчика приложений)
 * Developer Documentation.
 *
 * The basis of software system is a toolkit modules and classes language C / C ++,
 * which allow to control the display , input devices and output devices other internal equipment.
 * The purpose software package to simplify development and improve application performance.
 * Basic algorithms and data structures processed software complex are specified with @ref bt.
 *
 *
 * @ref page1
 */

/*
 * ==================================
 *           Для старта программы необходимо иметь конфигурационный файл, который должен находится в каталоге программы.
 *           Также конфигурационный файл можно указать в командной строке запуска первым параметром.
 *
 *           Архитектура:
 *           Конструкция объектов построенна на четырех базовых элементах BaseObject, ConteinerComponents, Conteiner, memManager.
 *           Взаимосвязь объектов и архитектурная часть приложения строится при помощи ObjectManager.
 *
 *           Устройство путей объектов:
*/

#include <bt.h>
#include <gen3.h>
#include <platform.h>
#include <format.h>
#include <core/application.h>
#include <core/baseobject.h>
#include <core/component.h>
#include <core/containercomponents.h>
#include <core/module.h>
#include <core/core.h>
#include <core/graph.h>
#include <core/input.h>
#include <core/objectmanager.h>
#include <components/resender.h>
#include <scene/gui/sggui.h>
#include <scene/scene.h>
#include <scene/scenecomponent.h>
#include <scene/sceneresender.h>
#include <scene/transform.h>
#include <scene/camera.h>
#include <scene/texture2d.h>
#include <scene/text3d.h>
#include <scene/style.h>
#include <scene/textstyle.h>
#include <scene/fonttext.h>
#include <scene/meshfilter.h>
#include <scene/material.h>
#include <scene/lightingmodel.h>
#include <scene/light.h>
#include <scene/mesh.h>
#include <scene/groupmesh.h>
#include <scene/shader.h>

/**
 * @namespace csad
 *
 * @brief Complex software application developer
 *
 * @see core, platform, format, input, scene, scenegui
 */

namespace csad {

/**
 * @defgroup core csad: core
 * @brief classes architecture.
 * @see csad, Core.
 *
 */
	
/**
 * @defgroup input csad: input
 * @brief the object management controllers input.
 * @see csad, Input.
 */

}

#endif /* CSAD_H_ */
