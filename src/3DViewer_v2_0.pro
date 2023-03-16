QT       += core gui opengl openglwidgets
win32 {
    LIBS += -lopengl32 -lglu32
}
include(QTGifimage-master/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common/settings.cc \
    controller/controller.cc \
    model/affine.cc \
    model/memento.cc \
    model/obj_data.cc \
    view/glview.cc \
    main.cc \
    view/view.cc

HEADERS += \
    common/settings.h \
    common/viewer_exception.h \
    controller/controller.h \
    model/affine.h \
    model/memento.h \
    model/obj_data.h \
    model/vertex.h \
    model/edge.h \
    view/glview.h \
    view/view.h

FORMS += \
    view/ui/view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource.qrc

ICON = common/3d.icns
