QT       += core gui
QT += opengl network widgets svg xml quickwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#msvc:QMAKE_CXXFLAGS += -execution-charset:utf-8
#msvc:QMAKE_CXXFLAGS += -source-charset:utf-8
#QMAKE_CXXFLAGS_WARN_ON += -wd4819

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    AddSubButton.cpp \
    ArnetWrapper.cpp \
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
    activatewidget.cpp \
    assist.cpp \
    cameracontroller1.cpp \
    cameraview.cpp \
    common.cpp \
    deviceinfo.cpp \
    ffdecoder.cpp \
    ffplayer.cpp \
    freedrawing.cpp \
    freedrawingmenu.cpp \
    glvideowidget.cpp \
    iconbutton.cpp \
    imagedisplay.cpp \
    jyplayer.cpp \
    linestate.cpp \
    main.cpp \
    mainwindow.cpp \
    Util.cpp \
    mainwindowv12.cpp \
    model/Device.cpp \
    model/DeviceModel.cpp \
    mp4encoder.cpp \
    mypaint.cpp \
    navigator.cpp \
    pensettingdialog.cpp \
    penstate.cpp \
    penstyle.cpp \
    playpausebutton.cpp \
    primewindow.cpp \
    progressbar.cpp \
    recordindicator.cpp \
    recordlabel.cpp \
    scaler.cpp \
    settingdialogv2.cpp \
    ui/CameraControllerV2.cpp \
    ui/CameraPreview.cpp \
    ui/CameraViewWidget.cpp \
    ui/FlowLayout.cpp \
    ui/MainUI.cpp \
    ui/MenuDialog.cpp \
    ui/TestViewController.cpp \
    ui/TouchButton.cpp \
    ui/VideoGLRender.cpp \
    ui/homev2_2.cpp \
    utils/ThemeUtils.cpp \
    videorender.cpp \
    vlcplayer.cpp \
    vlcplayercontroller.cpp \
    vlctest.cpp \
    vlcworker.cpp \
    vlcwrapper.cpp \
    yuv2jpg.cpp

HEADERS += \
    AddSubButton.h \
    ArnetWrapper.h \
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
    activatewidget.h \
    assist.h \
    cameracontroller1.h \
    cameraview.h \
    common.h \
    deviceinfo.h \
    ffdecoder.h \
    ffplayer.h \
    freedrawing.h \
    freedrawingmenu.h \
    glvideowidget.h \
    iconbutton.h \
    imagedisplay.h \
    jyplayer.h \
    linestate.h \
    mainwindow.h \
    Util.h \
    mainwindowv12.h \
    model/Device.h \
    model/DeviceModel.h \
    mp4encoder.h \
    mypaint.h \
    navigator.h \
    pensettingdialog.h \
    penstate.h \
    penstyle.h \
    playpausebutton.h \
    primewindow.h \
    progressbar.h \
    recordindicator.h \
    recordlabel.h \
    scaler.h \
    settingdialogv2.h \
    ui/CameraControllerV2.h \
    ui/CameraPreview.h \
    ui/CameraViewWidget.h \
    ui/FlowLayout.h \
    ui/MainUI.h \
    ui/MenuDialog.h \
    ui/TestViewController.h \
    ui/TouchButton.h \
    ui/VideoGLRender.h \
    ui/homev2_2.h \
    utils/ThemeUtils.h \
    videorender.h \
    vlcplayer.h \
    vlcplayercontroller.h \
    vlctest.h \
    vlcworker.h \
    vlcwrapper.h \
    yuv2jpg.h

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
    mainwindowv12.ui \
    navigator.ui \
    primewindow.ui \
    recordlabel.ui \
    vlcplayer.ui \
    vlcplayercontroller.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_FILE = resources.rc

win32{
    equals(QT_ARCH, x86_64) {
        DESTDIR = $${PWD}/bin64
        FFMPEG_DIR = $$PWD/contrib/ffmpeg/win64
        VLC_DIR = $$PWD/contrib/vlc/win64
    }

    equals(QT_ARCH, i386) {
        DESTDIR = $${PWD}/bin32
        FFMPEG_DIR = $$PWD/contrib/ffmpeg/win32
        VLC_DIR = $$PWD/contrib/vlc/win32
    }

    LIBS += -L$${FFMPEG_DIR}/bin -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale
    INCLUDEPATH += $${FFMPEG_DIR}/include
    DEPENDPATH += $${FFMPEG_DIR}/bin

    LIBS += -L$${VLC_DIR}/sdk/lib -llibvlc
    INCLUDEPATH += $${VLC_DIR}/sdk/include
    DEPENDPATH +=$${VLC_DIR}
}
