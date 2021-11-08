/*
 * glextension.h
 *
 *  Created on: 12.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 *
 * Compatible OpenLG Version: 1.2.4
 *
 *  
 */

#ifndef GLEXTENSION_H_
#define GLEXTENSION_H_

#include <platform/platformapi.h>

extern char *GLErrorString[];

// *********************************** OpenGL *****************************************

#ifndef GL_BGRA
#define GL_BGRA                                    0x080E1
#endif
#ifndef GL_BGR
#define GL_BGR                                     0x080E0
#endif
#ifndef GL_DOUBLE
#define GL_DOUBLE                                  0x0140A
#endif

#ifndef GL_TEXTURE_MAX_LOD
#define GL_TEXTURE_MAX_LOD                         0x0813B
#endif
#ifndef GL_TEXTURE_MIN_LOD
#define GL_TEXTURE_MIN_LOD                         0x0813A
#endif

#define GL_MAX_MULTITEXTURE_UNITS                  0x084E2
#define GL_MULTITEXTURE0                           0x084C0

#ifndef GL_COMPRESSED_ALPHA
#define GL_COMPRESSED_ALPHA                        0x084E9
#endif
#ifndef GL_COMPRESSED_LUMINANCE
#define GL_COMPRESSED_LUMINANCE                    0x084EA
#endif
#ifndef GL_COMPRESSED_LUMINANCE_ALPHA
#define GL_COMPRESSED_LUMINANCE_ALPHA              0x084EB
#endif
#ifndef GL_COMPRESSED_INTENSITY
#define GL_COMPRESSED_INTENSITY                    0x084EC
#endif
#ifndef GL_COMPRESSED_RGB
#define GL_COMPRESSED_RGB                          0x084ED
#endif
#ifndef GL_COMPRESSED_RGBA
#define GL_COMPRESSED_RGBA                         0x084EE
#endif
#ifndef GL_TEXTURE_COMPRESSION_HINT
#define GL_TEXTURE_COMPRESSION_HINT                0x084EF
#endif
#ifndef GL_TEXTURE_COMPRESSED_IMAGE_SIZE
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE           0x086A0
#endif
#ifndef GL_TEXTURE_COMPRESSED
#define GL_TEXTURE_COMPRESSED                      0x086A1
#endif

#define GL_MAX_VERTEX_UNITS                        0x086A4
#define GL_VERTEX_BLEND                            0x086A7
#define GL_BLEND_MODELVIEW0                        0x01700

#define GL_PROGRAM_ERROR_POSITION_ARB               0x864B
#define GL_PROGRAM_BINDING_ARB                      0x8677
#define GL_PROGRAM_ERROR_STRING_ARB                 0x8874
#define GL_FRAGMENT_SHADER                          0x8B30
#define GL_VERTEX_SHADER                            0x8B31
#define GL_SHADER_TYPE                              0x8B4F
#define GL_COMPILE_STATUS                           0x8B81
#define GL_LINK_STATUS                              0x8B82
#define GL_INFO_LOG_LENGTH                          0x8B84
#define GL_ATTACHED_SHADERS                         0x8B85
#define GL_CURRENT_PROGRAM                          0x8B8D
#define GL_GEOMETRY_SHADER                          0x8DD9

// *********************************** GL_TEXTURE_3D **********************************

#ifndef GL_TEXTURE_3D
#define GL_TEXTURE_3D                              0x0806F
#endif
#ifndef GL_TEXTURE_BINDING_3D
#define GL_TEXTURE_BINDING_3D                      0x0806A
#endif

// *********************************** FUNCTIONS **********************************

namespace csad {

class Module;

Module* glLib();

}

#if defined (OS_QNX)
#include "qnx/qnxglextension.h"
#elif defined (OS_WIN)
#include "win/winglextension.h"
#elif defined (OS_LINUX)
#include "linux/linuxglextension.h"
#elif defined (OS_OSX)
#include "osx/osxglextension.h"
#else
#include "unknow/unknowglextension.h"
#endif

#endif /* GLEXTENSION_H_ */
