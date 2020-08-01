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


SOURCES += \
    AddSubButton.cpp \
    CameraController.cpp \
    CameraManager.cpp \
    CommentToolBar.cpp \
    HTitleButton.cpp \
    ImageButton.cpp \
    MediaController.cpp \
    SettingDialog.cpp \
    TitleButton.cpp \
    ToolBar.cpp \
    main.cpp \
    mainwindow.cpp \
    RenderWidget.cpp \
    Util.cpp \
    mypaint.cpp \
    myrender.cpp \
    playpausebutton.cpp \
    vlcwrapper.cpp

HEADERS += \
    AddSubButton.h \
    CameraController.h \
    CameraManager.h \
    CommentToolBar.h \
    HTitleButton.h \
    ImageButton.h \
    MediaController.h \
    SettingDialog.h \
    TitleButton.h \
    ToolBar.h \
    common.h \
    mainwindow.h \
    RenderWidget.h \
    Util.h \
    mypaint.h \
    myrender.h \
    playpausebutton.h \
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
    mainwindow.ui


QT += opengl network widgets

win32{
VLC_PATH = $$PWD/win32/vlc-2.2.2/sdk
}
win64{
VLC_PATH = $$PWD/win64/vlc-2.2.2/sdk
}
INCLUDEPATH += $${VLC_PATH}/include
LIBS += -L$${VLC_PATH}/lib -lvlc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
