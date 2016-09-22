# Multibeam converter - creates PANGAEA and ODV import files from xyz-files
# Rainer Sieger
# Alfred Wegener Institute, Bremerhaven, Germany
# last change: 2014-10-04

macx {
    # creating cache file
    cache()

    # Set SDK
    QMAKE_MAC_SDK = macosx10.12

    # Only Intel binaries are accepted so force this
    CONFIG += x86_64

    # Minimum OS X version for submission is 10.7
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7

    # Icon
    ICON = ./Resources/icon/Application.icns

    # Replace default Info.plist
    QMAKE_INFO_PLIST = ./Resources/Info.plist

    QMAKE_CFLAGS += -gdwarf-2
    QMAKE_CXXFLAGS += -gdwarf-2
    QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
}

win32 {
    # Icon
    RC_FILE = ./Resources/Application.rc
}

linux-g++ {
}

TARGET = MultibeamConverter
TEMPLATE = app

QT += widgets network

INCLUDEPATH += ./Headers

HEADERS = ./Headers/Application.h \
    ./Headers/Globals.h \
    ./Forms/AboutDialog/AboutDialog.h \
    ./Forms/SetOptionsDialog/SetOptionsDialog.h \
    ./Forms/SetMultibeamOptionsDialog/SetMultibeamOptionsDialog.h

SOURCES = ./Sources/ApplicationInit.cpp \
    ./Sources/ApplicationMainWindow.cpp \
    ./Sources/ApplicationErrors.cpp \
    ./Sources/ApplicationPreferences.cpp \
    ./Sources/ApplicationCreateMenu.cpp \
    ./Sources/DeleteDoubleLines.cpp \
    ./Sources/MultibeamConverter.cpp \
    ./Sources/SaveFilelist.cpp \
    ./Forms/AboutDialog/AboutDialog.cpp \
    ./Forms/SetOptionsDialog/SetOptionsDialog.cpp \
    ./Forms/SetMultibeamOptionsDialog/SetMultibeamOptionsDialog.cpp

FORMS = ./Forms/AboutDialog/aboutdialog.ui \
    ./Forms/SetOptionsDialog/setoptionsdialog.ui \
    ./Forms/SetMultibeamOptionsDialog/setmultibeamoptionsdialog.ui
