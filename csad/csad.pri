
HEADERS+= \
include/csad.h \
include/format.h \
include/platform.h \
include/gen3.h

SOURCES+= \
csad/btext/tesselator/dict.cpp \
csad/btext/tesselator/geom.cpp \
csad/btext/tesselator/memalloc.cpp \
csad/btext/tesselator/normal.cpp \
csad/btext/tesselator/priorityq-heap.cpp \
csad/btext/tesselator/priorityq.cpp \
csad/btext/tesselator/sweep.cpp \
csad/btext/tesselator/tessrender.cpp \
csad/btext/tesselator/tessmono.cpp \
csad/btext/tesselator/tessmesh.cpp \
csad/btext/tesselator/tess.cpp

HEADERS+= \
csad/btext/tesselator/xglues.h \
csad/btext/tesselator/dict.h \
csad/btext/tesselator/geom.h \
csad/btext/tesselator/memalloc.h \
csad/btext/tesselator/normal.h \
csad/btext/tesselator/priorityq-heap.h \
csad/btext/tesselator/priorityq-sort.h \
csad/btext/tesselator/priorityq.h \
csad/btext/tesselator/sweep.h \
csad/btext/tesselator/tessrender.h \
csad/btext/tesselator/tessmono.h \
csad/btext/tesselator/tessmesh.h \
csad/btext/tesselator/tess.h

SOURCES+= \
csad/btext/jpg/jpge.cpp \
csad/btext/jpg/jpgd.cpp

HEADERS+= \
csad/btext/jpg/jpge.h \
csad/btext/jpg/jpgd.h

SOURCES+= \
csad/core/base/stringconsts.cpp
csad/core/base/basecontainer.cpp

HEADERS+= \
csad/core/base/stringconsts.h
csad/core/base/baseapi.h
csad/core/base/basecontainer.h

SOURCES+= \
csad/core/application.cpp \
csad/core/corefunctions.cpp \
csad/core/csadclassmanager.cpp \
csad/core/component.cpp \
csad/core/containercomponents.cpp \
csad/core/graph.cpp \
csad/core/input.cpp \
csad/core/csadcore.cpp \
csad/core/config.cpp \
csad/core/system.cpp \
csad/core/interfacedatasystem.cpp \
csad/core/interfacethreadsystem.cpp \
csad/core/objectmanager.cpp \
csad/core/module.cpp

HEADERS+= \
csad/core/config.h \
csad/core/csadcore.h \
csad/core/csadclassmanager.h

HEADERS+= \
include/core/csadapi.h \
include/core/types.h \
include/core/baseobject.h \
include/core/application.h \
include/core/corefunctions.h \
include/core/classmanager.h \
include/core/component.h \
include/core/containercomponents.h \
include/core/graph.h \
include/core/input.h \
include/core/core.h \
include/core/system.h \
include/core/systemobject.h \
include/core/interfacedatasystem.h \
include/core/interfacethreadsystem.h \
include/core/objectmanager.h \
include/core/module.h

SOURCES+= \
csad/gen3/genfunctions.cpp \
csad/gen3/cputriangulator.cpp \
csad/gen3/modellerpath.cpp \
csad/gen3/modellermesh.cpp \
csad/gen3/modellerraster.cpp \
csad/gen3/rasterscript.cpp \
csad/gen3/meshscript.cpp \
csad/gen3/base/baseraster.cpp \
csad/gen3/base/baseface.cpp \
csad/gen3/base/basesampler.cpp \
csad/gen3/base/basemodeller.cpp

HEADERS+= \
csad/gen3/base/baseraster.h \
csad/gen3/base/baseface.h \
csad/gen3/base/basesampler.h \
csad/gen3/base/basemodeller.h

HEADERS+= \
include/gen3/genapi.h \
include/gen3/genfunctions.h \
include/gen3/types.h \
include/gen3/cputriangulator.h \
include/gen3/modellerpath.h \
include/gen3/modellermesh.h \
include/gen3/modellerraster.h \
include/gen3/rasterscript.h \
include/gen3/meshscript.h

SOURCES+= \
csad/format/formatxml.cpp \
csad/format/formattga.cpp \
csad/format/formatjpg.cpp \
csad/format/formatpak.cpp \
csad/format/format3ds.cpp

HEADERS+= \
include/format/formatxml.h \
include/format/formattga.h \
include/format/formatjpg.h \
include/format/formatpak.h \
include/format/format3ds.h

SOURCES+= \
csad/platform/win/winglextension.cpp \
csad/platform/win/winfile.cpp \
csad/platform/win/winlog.cpp \
csad/platform/win/winthread.cpp \
csad/platform/win/winlibrary.cpp \
csad/platform/win/wintimer.cpp \
csad/platform/win/winnetconnection.cpp \
csad/platform/win/wininterfaceeventsystem.cpp \
csad/platform/win/wininterfacerendersystem.cpp \
csad/platform/win/winkeyboard.cpp \
csad/platform/win/winos.cpp \
csad/platform/win/winmouse.cpp \
csad/platform/win/winrender.cpp \
csad/platform/win/winrenderer.cpp \
csad/platform/win/windisplay.cpp \
csad/platform/win/winglcontext.cpp \
csad/platform/win/winfont.cpp \
csad/platform/win/winfontserver.cpp

SOURCES+= \
csad/platform/qnx/qnxglextension.cpp \
csad/platform/qnx/qnxfile.cpp \
csad/platform/qnx/qnxlog.cpp \
csad/platform/qnx/qnxthread.cpp \
csad/platform/qnx/qnxlibrary.cpp \
csad/platform/qnx/qnxtimer.cpp \
csad/platform/qnx/qnxnetconnection.cpp \
csad/platform/qnx/qnxinterfaceeventsystem.cpp \
csad/platform/qnx/qnxinterfacerendersystem.cpp \
csad/platform/qnx/qnxkeyboard.cpp \
csad/platform/qnx/qnxos.cpp \
csad/platform/qnx/qnxmouse.cpp \
csad/platform/qnx/qnxrender.cpp \
csad/platform/qnx/qnxrenderer.cpp \
csad/platform/qnx/qnxdisplay.cpp \
csad/platform/qnx/qnxglcontext.cpp \
csad/platform/qnx/qnxfont.cpp \
csad/platform/qnx/qnxfontserver.cpp

SOURCES+= \
csad/platform/linux/linuxglextension.cpp \
csad/platform/linux/linuxfile.cpp \
csad/platform/linux/linuxlog.cpp \
csad/platform/linux/linuxthread.cpp \
csad/platform/linux/linuxlibrary.cpp \
csad/platform/linux/linuxtimer.cpp \
csad/platform/linux/linuxnetconnection.cpp \
csad/platform/linux/linuxinterfaceeventsystem.cpp \
csad/platform/linux/linuxinterfacerendersystem.cpp \
csad/platform/linux/linuxkeyboard.cpp \
csad/platform/linux/linuxos.cpp \
csad/platform/linux/linuxmouse.cpp \
csad/platform/linux/linuxrender.cpp \
csad/platform/linux/linuxrenderer.cpp \
csad/platform/linux/linuxdisplay.cpp \
csad/platform/linux/linuxglcontext.cpp \
csad/platform/linux/linuxfont.cpp \
csad/platform/linux/linuxfontserver.cpp

SOURCES+= \
csad/platform/osx/osxglextension.cpp \
csad/platform/osx/osxfile.cpp \
csad/platform/osx/osxlog.cpp \
csad/platform/osx/osxthread.cpp \
csad/platform/osx/osxlibrary.cpp \
csad/platform/osx/osxtimer.cpp \
csad/platform/osx/osxnetconnection.cpp \
csad/platform/osx/osxinterfaceeventsystem.cpp \
csad/platform/osx/osxinterfacerendersystem.cpp \
csad/platform/osx/osxkeyboard.cpp \
csad/platform/osx/osxos.cpp \
csad/platform/osx/osxmouse.cpp \
csad/platform/osx/osxrender.cpp \
csad/platform/osx/osxrenderer.cpp \
csad/platform/osx/osxdisplay.cpp \
csad/platform/osx/osxglcontext.cpp \
csad/platform/osx/osxfont.cpp \
csad/platform/osx/osxfontserver.cpp

SOURCES+= \
csad/platform/platformfunctions.cpp \
csad/platform/glextension.cpp \
csad/platform/keyboard.cpp \
csad/platform/render.cpp \
csad/platform/renderer.cpp \
csad/platform/localdisplay.cpp \
csad/platform/glcontext.cpp \
csad/platform/interfacerendersystem.cpp \
csad/platform/font.cpp \
csad/platform/fontserver.cpp \
csad/platform/base/basenetconnection.cpp \
csad/platform/base/basesoftrender.cpp

HEADERS+= \
csad/platform/glextension.h \
csad/platform/localdisplay.h \
csad/platform/base/basenetconnection.h \
csad/platform/base/basesoftrender.h \
csad/platform/win/winglextension.h \
csad/platform/qnx/qnxglextension.h \
csad/platform/linux/linuxglextension.h \
csad/platform/osx/osxglextension.h

HEADERS+= \
include/platform/types.h \
include/platform/platformapi.h \
include/platform/platformfunctions.h \
include/platform/file.h \
include/platform/log.h \
include/platform/thread.h \
include/platform/library.h \
include/platform/timer.h \
include/platform/netconnection.h \
include/platform/interfaceeventsystem.h \
include/platform/interfacerendersystem.h \
include/platform/keyboard.h \
include/platform/mouse.h \
include/platform/render.h \
include/platform/renderer.h \
include/platform/display.h \
include/platform/glcontext.h \
include/platform/font.h \
include/platform/os.h \
include/platform/fontserver.h \
include/platform/base/baselog.h \
include/platform/base/baseinterfaceeventsystem.h \
include/platform/base/basekeyboard.h \
include/platform/base/basemouse.h

HEADERS+= \
include/platform/win/winlog.h \
include/platform/win/wininterfaceeventsystem.h

HEADERS+= \
include/platform/qnx/qnxlog.h \
include/platform/qnx/qnxinterfaceeventsystem.h

HEADERS+= \
include/platform/linux/linuxlog.h \
include/platform/linux/linuxinterfaceeventsystem.h

HEADERS+= \
include/platform/osx/osxlog.h \
include/platform/osx/osxinterfaceeventsystem.h

SOURCES+= \
csad/scene/scene.cpp \
csad/scene/scenecomponent.cpp \
csad/scene/sceneresender.cpp \
csad/scene/shader.cpp \
csad/scene/localtransform.cpp \
csad/scene/camera.cpp \
csad/scene/viewport.cpp \
csad/scene/meshfilter.cpp \
csad/scene/material.cpp \
csad/scene/text3d.cpp \
csad/scene/texture2d.cpp \
csad/scene/style.cpp \
csad/scene/textstyle.cpp \
csad/scene/fonttext.cpp \
csad/scene/light.cpp \
csad/scene/lightingmodel.cpp \
csad/scene/mesh.cpp \
csad/scene/groupmesh.cpp

HEADERS+= \
csad/scene/localtransform.h \

HEADERS+= \
include/scene/scene.h \
include/scene/scenecomponent.h \
include/scene/sceneresender.h \
include/scene/shader.h \
include/scene/transform.h \
include/scene/camera.h \
include/scene/viewport.h \
include/scene/meshfilter.h \
include/scene/material.h \
include/scene/text3d.h \
include/scene/texture2d.h \
include/scene/style.h \
include/scene/textstyle.h \
include/scene/fonttext.h \
include/scene/light.h \
include/scene/lightingmodel.h \
include/scene/mesh.h \
include/scene/groupmesh.h

SOURCES+= \
csad/scene/gui/sgbaseelement.cpp \
csad/scene/gui/sgbutton.cpp \
csad/scene/gui/sgelement.cpp \
csad/scene/gui/sglayout.cpp \
csad/scene/gui/sglineedit.cpp \
csad/scene/gui/sgmenu.cpp \
csad/scene/gui/sgmouse.cpp \
csad/scene/gui/sgscroll.cpp \
csad/scene/gui/sgstyles.cpp \
csad/scene/gui/sgtable.cpp \
csad/scene/gui/sgtabcontroll.cpp

HEADERS+= \
include/scene/gui/sggui.h \
include/scene/gui/sgbaseelement.h \
include/scene/gui/sgbutton.h \
include/scene/gui/sgelement.h \
include/scene/gui/sglayout.h \
include/scene/gui/sglineedit.h \
include/scene/gui/sgmouse.h \
include/scene/gui/sgmenu.h \
include/scene/gui/sgscroll.h \
include/scene/gui/sgstyles.h \
include/scene/gui/sgtable.h \
include/scene/gui/sgtabcontroll.h

SOURCES+= \
csad/components/resender.cpp

HEADERS+= \
include/components/resender.h 