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
    AddSubButton.cpp \
    CameraController.cpp \
    CameraManager.cpp \
    CommentToolBar.cpp \
    Configure.cpp \
    HTitleButton.cpp \
    ImageButton.cpp \
    Loading/Loading.cpp \
    MediaController.cpp \
    Resolution.cpp \
    SettingDialog.cpp \
    TitleButton.cpp \
    ToolBar.cpp \
    aboutdialog.cpp \
    cameracontroller1.cpp \
    cameraview.cpp \
    common.cpp \
    ffdecoder.cpp \
    ffplayer.cpp \
    freedrawing.cpp \
    freedrawingmenu.cpp \
    glvideowidget.cpp \
    imagedisplay.cpp \
    jyplayer.cpp \
    linestate.cpp \
    main.cpp \
    mainwindow.cpp \
    Util.cpp \
    mp4encoder.cpp \
    mypaint.cpp \
    navigator.cpp \
    playpausebutton.cpp \
    primewindow.cpp \
    recordindicator.cpp \
    recordlabel.cpp \
    scaler.cpp \
    videorender.cpp \
    vlcplayer.cpp \
    vlcplayercontroller.cpp \
    vlcworker.cpp \
    vlcwrapper.cpp

HEADERS += \
    AddSubButton.h \
    CameraController.h \
    CameraManager.h \
    CommentToolBar.h \
    Configure.h \
    HTitleButton.h \
    ImageButton.h \
    Loading/Loading.h \
    MediaController.h \
    Resolution.h \
    SettingDialog.h \
    TitleButton.h \
    ToolBar.h \
    VideoRenderCallback.h \
    aboutdialog.h \
    cameracontroller1.h \
    cameraview.h \
    common.h \
    ffdecoder.h \
    ffplayer.h \
    freedrawing.h \
    freedrawingmenu.h \
    glvideowidget.h \
    imagedisplay.h \
    jyplayer.h \
    linestate.h \
    mainwindow.h \
    Util.h \
    mp4encoder.h \
    mypaint.h \
    navigator.h \
    playpausebutton.h \
    primewindow.h \
    recordindicator.h \
    recordlabel.h \
    scaler.h \
    videorender.h \
    vlcplayer.h \
    vlcplayercontroller.h \
    vlcworker.h \
    vlcwrapper.h

FORMS += \
    AddSubButton.ui \
    CameraController.ui \
    CameraManager.ui \
    CommentToolBar.ui \
    HTitleButton.ui \
    MediaController.ui \
    SettingDialog.ui \
    TitleButton.ui \
    ToolBar.ui \
    freedrawing.ui \
    freedrawingmenu.ui \
    imagedisplay.ui \
    linestate.ui \
    mainwindow.ui \
    navigator.ui \
    primewindow.ui \
    recordlabel.ui \
    vlcplayer.ui \
    vlcplayercontroller.ui


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
