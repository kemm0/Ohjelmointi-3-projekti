QT += quick
QT += charts
QT += quickcontrols2
QT += network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/apicaller.cpp \
        src/apicallerfingrid.cpp \
        src/apicallerfmi.cpp \
        src/apicallmanager.cpp \
        src/appcontroller.cpp \
        src/backend.cpp \
        src/data.cpp \
        src/datamanager.cpp \
        src/main.cpp

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
    src/apicallerfingrid.hh \
    src/apicallerfmi.hh \
    src/apicallmanager.hh \
    src/appcontroller.hh \
    src/backend.hh \
    src/datamanager.hh \
    src/apicaller.hh \
    src/data.hh \
    src/datarequest.hh


