QT += quick
QT += charts
QT += quickcontrols2
QT += network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/api.cpp \
        src/api_caller.cpp \
        src/api_ilmatieteenlaitos.cpp \
        src/backend.cpp \
        src/controller.cpp \
        src/data.cpp \
        src/datamodel.cpp \
        src/main.cpp \
        src/weatherdata.cpp

RESOURCES += \
    src/GUI/qml.qrc




# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \

HEADERS += \
    src/DataRequest.h \
    src/api.hh \
    src/api_caller.h \
    src/api_ilmatieteenlaitos.hh \
    src/backend.h \
    src/controller.hh \
    src/data.hh \
    src/datamodel.hh \
    src/weatherdata.hh


