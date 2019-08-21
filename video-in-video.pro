TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TOPDIR=$$PWD
SRCDIR=$${TOPDIR}/source
HDRDIR=$${SRCDIR}/includes

GENFOLDER =$${TOPDIR}/build/

UI_DIR =$${TOPDIR}/.uic
MOC_DIR=$${TOPDIR}/.moc
OBJ_DIR=$${TOPDIR}/.obj
RCC_DIR=$${TOPDIR}/.res

DEFINES += BUILDTIME=\\\"$$system(date '+%H:%M:%S')\\\"
DEFINES += BUILDDATE=\\\"$$system(date '+%Y-%m-%d')\\\"

INCLUDEPATH = \
    /usr/include \
    /usr/include/SDL \
    $${TOPDIR}/.uic

QMAKE_CXXFLAGS += \
    -fpermissive \
    -frtti -fexceptions  -std=c++17 \
    -D_GLIBCXX_USE_CXX11_ABI=0

LIBS += -L/usr/lib64 -lSDL -lSDL_ttf
LIBS += -L/usr/lib/vlc -lcompat -lvlc
LIBS += -L/usr/lib -lvlccore

SOURCES += \
    main.cc \
    tsurface.cc \
    tcontrol.cc \
    iinterfacecomponentreference.cc \
    tpoint.cc \
    tcomponent.cc \
    tapplication.cc \
    tfont.cc \
    tcolor.cc \
    tpainter.cc \
    tgraphicsitem.cc \
    ttimer.cc

FORMS +=

HEADERS += \
    tsurface.h \
    tcontrol.h \
    iinterfacecomponentreference.h \
    tpoint.h \
    tcomponent.h \
    tapplication.h \
    tfont.h \
    tcolor.h \
    tpainter.h \
    tgraphicsitem.h \
    ttimer.h \
    cam0_src.h \
    cam1_src.h

DISTFILES += \
    getwin.sh

