QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#DESTDIR=$$PWD/bin/
contains(QT_ARCH, i386) {
    message("32-bit")
    DESTDIR = $${PWD}/bin32
} else {
    message("64-bit")
    DESTDIR = $${PWD}/bin64
}


SOURCES += \
    ArnetWrapper.cpp \
    Configure.cpp \
    ImageButton.cpp \
    Resolution.cpp \
    SettingDialog.cpp \
    cameracontroller1.cpp \
    common.cpp \
    ffdecoder.cpp \
    ffplayer.cpp \
    firstwindow.cpp \
    glvideowidget.cpp \
    main.cpp \
    Util.cpp \
    mp4encoder.cpp \
    progressbar.cpp \
    recordindicator.cpp \
    scaler.cpp \
    sockettest.cpp \
    yuv2jpg.cpp

HEADERS += \
    ArnetWrapper.h \
    Configure.h \
    ImageButton.h \
    Resolution.h \
    SettingDialog.h \
    cameracontroller1.h \
    common.h \
    ffdecoder.h \
    ffplayer.h \
    firstwindow.h \
    glvideowidget.h \
    Util.h \
    mp4encoder.h \
    progressbar.h \
    recordindicator.h \
    scaler.h \
    sockettest.h \
    yuv2jpg.h


QT += opengl network widgets

THRIDPARTIES_PATH = $$PWD/thirdparties

contains(QT_ARCH, i386) {
    VLC_PATH = $$PWD/win32/vlc-2.2.2/sdk
#    ARNET_LIB_PATH = $${THRIDPARTIES_PATH}/arnet/lib/win32
#    LIBS += -L$${ARNET_LIB_PATH} -lARNET_SDK
    LIBS += -L$${THRIDPARTIES_PATH}/ffmpeg/lib/win32 -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample -lswscale
} else {
    VLC_PATH = $$PWD/x86_64/vlc-2.2.2/sdk
#    ARNET_LIB_PATH = $${THRIDPARTIES_PATH}/arnet/lib/x86_64
#    LIBS += -L$${ARNET_LIB_PATH} -lARNET_SDK
    LIBS += -L$${THRIDPARTIES_PATH}/ffmpeg/lib/win64 -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample -lswscale
}

#INCLUDEPATH += $${THRIDPARTIES_PATH}/arnet/inc
INCLUDEPATH += $${THRIDPARTIES_PATH}/ffmpeg/include
INCLUDEPATH += $${VLC_PATH}/include

LIBS += -L$${VLC_PATH}/lib -lvlc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_FILE = resources.rc
