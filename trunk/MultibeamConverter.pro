# Multibeam converter - creates PANGAEA and ODV import files from xyz-files
# Rainer Sieger
# Alfred Wegener Institute, Bremerhaven, Germany
# last change: 2014-10-04

macx {
    message( "MacOS X" )

    # creating cache file
    cache()

    # Set SDK
    QMAKE_MAC_SDK = macosx10.9

    # Only Intel binaries are accepted so force this
    CONFIG += x86_64

    # Minimum OS X version for submission is 10.6.6
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6

    # Icon
    ICON = ./Resources/icon/Application.icns

    # Replace default Info.plist
    QMAKE_INFO_PLIST = ./Resources/Info.plist

    QMAKE_CFLAGS += -gdwarf-2
    QMAKE_CXXFLAGS += -gdwarf-2
    QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_OBJECTIVE_CFLAGS_RELEASE =  $$QMAKE_OBJECTIVE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
}

win32 {
    message( "Windows" )

    # Icon
    RC_FILE = ./Resources/Application.rc
}

linux-g++ {
    message( "Linux" )
}

TARGET = MultibeamConverter
TEMPLATE = app

QT += widgets network

INCLUDEPATH += ./Headers

HEADERS = ./Headers/Application.h \
    ./Headers/Globals.h \
    ./Headers/Webfile.h \
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
    ./Sources/Webfile.cpp \
    ./Forms/AboutDialog/AboutDialog.cpp \
    ./Forms/SetOptionsDialog/SetOptionsDialog.cpp \
    ./Forms/SetMultibeamOptionsDialog/SetMultibeamOptionsDialog.cpp

FORMS = ./Forms/AboutDialog/aboutdialog.ui \
    ./Forms/SetOptionsDialog/setoptionsdialog.ui \
    ./Forms/SetMultibeamOptionsDialog/setmultibeamoptionsdialog.ui
