QT += core gui serialport
QT += core gui
QT += sql
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camara.cpp \
    chosecamara.cpp \
    ilumicacion.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mysql.cpp \
    myvideocapture.cpp \
    riel.cpp \
    serialterminal.cpp \
    timer.cpp \
    user.cpp \
    usertype.cpp \
    viewtemperatura.cpp

HEADERS += \
    camara.h \
    chosecamara.h \
    ilumicacion.h \
    login.h \
    mainwindow.h \
    User.h \
    UserType.h \
    mysql.h \
    myvideocapture.h \
    riel.h \
    serialterminal.h \
    timer.h \
    viewtemperatura.h

FORMS += \
    chosecamara.ui \
    login.ui \
    mainwindow.ui \
    serialterminal.ui

#TARGET = SerialTerminal
#TEMPLATE = app

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

RC_ICONS = icono.ico

RESOURCES += \
    Imagenes.qrc

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += F:\Programs\opencv\release\install\include

LIBS += F:\Programs\opencv\release\bin\libopencv_core411.dll
LIBS += F:\Programs\opencv\release\bin\libopencv_highgui411.dll
LIBS += F:\Programs\opencv\release\bin\libopencv_imgproc411.dll

LIBS += F:\Programs\opencv\release\bin\libopencv_calib3d411.dll
LIBS += F:\Programs\opencv\release\bin\libopencv_dnn411.dll
LIBS += F:\Programs\opencv\release\bin\libopencv_flann411.dll
LIBS += F:\Programs\opencv\release\bin\libopencv_imgcodecs411.dll
LIBS += F:\Programs\opencv\release\bin\libopencv_ml411.dll
LIBS += F:\Programs\opencv\release\bin\libopencv_objdetect411.dll
LIBS += F:\Programs\opencv\release\bin\libopencv_photo411.dll
LIBS += F:\Programs\opencv\release\bin\libopencv_stitching411.dll
LIBS += F:\Programs\opencv\release\bin\libopencv_video411.dll
LIBS += F:\Programs\opencv\release\bin\libopencv_videoio411.dll
