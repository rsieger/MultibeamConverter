/****************************************************************
**
** Preferences of MultibeamConverter
** 2011-04-06, Dr. Rainer Sieger
** last change: 2011-04-06
**
****************************************************************/

#include "Application.h"

const QString PrefDate = "MultibeamConverter, 2011-04-05";

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 11.3.2004

/*! @brief Sichern der Programmeinstellungen */

void MainWindow::savePreferences()
{
    #if defined(Q_OS_LINUX)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    #if defined(Q_OS_MAC)
        QSettings settings( getPreferenceFilename(), QSettings::NativeFormat );
    #endif

    #if defined(Q_OS_WIN)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    settings.beginGroup( QCoreApplication::applicationName() );

    settings.setValue( "NumOfProgramStarts", gi_NumOfProgramStarts );

    settings.setValue( "WindowX", x() );
    settings.setValue( "WindowY", y() );
    settings.setValue( "WindowHeight", height() );
    settings.setValue( "WindowWidth", width() );

    settings.setValue( "DialogX", posDialog.x() );
    settings.setValue( "DialogY", posDialog.y() );
    settings.setValue( "DialogHeight", sizeParameterDialog.height() );
    settings.setValue( "DialogWidth", sizeParameterDialog.width() );

    settings.setValue( "Path", gs_Path );
    settings.setValue( "FilenameFormat", gs_FilenameFormat );
    settings.setValue( "ExportFilename", gs_ExportFilename );
    settings.setValue( "CruiseLabel", gs_CruiseLabel );
    settings.setValue( "EventLabel", gs_EventLabel );
    settings.setValue( "AuthorID", gs_AuthorID );
    settings.setValue( "ReferenceID", gs_ReferenceID );
    settings.setValue( "ShipName", gs_ShipName );
    settings.setValue( "ProjectID", gs_ProjectID );
    settings.setValue( "InstituteID", gs_InstituteID );
    settings.setValue( "MethodID", gs_MethodID );
    settings.setValue( "LatLong", gb_LatLong );
    settings.setValue( "PositionDigits", gi_PosDigits );
    settings.setValue( "DepthDigits", gi_DepthDigits );

    settings.endGroup();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 21.11.2007

/*! @brief Laden der Programmeinstellungen */

void MainWindow::loadPreferences()
{
    #if defined(Q_OS_LINUX)
        gi_Codec = _UTF8_; // UTF-8
        gi_EOL   = _UNIX_;
    #endif

    #if defined(Q_OS_MAC)
        gi_Codec = _APPLEROMAN_; // Mac Roman
        gi_EOL   = _UNIX_;
    #endif

    #if defined(Q_OS_WIN)
        gi_Codec = _LATIN1_; // Latin-1 = ISO 8859-1
        gi_EOL   = _WIN_;
    #endif

    #if defined(Q_OS_LINUX)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    #if defined(Q_OS_MAC)
        QSettings settings( getPreferenceFilename(), QSettings::NativeFormat );
    #endif

    #if defined(Q_OS_WIN)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    settings.beginGroup( QCoreApplication::applicationName() );

    gi_NumOfProgramStarts = settings.value( "NumOfProgramStarts", 0 ).toInt();

    posWindow.setX( settings.value( "WindowX", 100 ).toInt() );
    posWindow.setY( settings.value( "WindowY", 100 ).toInt() );
    sizeWindow.setHeight( settings.value( "WindowHeight", 250 ).toInt() );
    sizeWindow.setWidth( settings.value( "WindowWidth", 600 ).toInt() );

    posDialog.setX( settings.value( "DialogX", 110 ).toInt() );
    posDialog.setY( settings.value( "DialogY", 110 ).toInt() );
    sizeParameterDialog.setHeight( settings.value( "DialogHeight", 100 ).toInt() );
    sizeParameterDialog.setWidth( settings.value( "DialogWidth", 100 ).toInt() );

    gs_Path               = settings.value( "Path", getDocumentDir() ).toString();
    gs_FilenameFormat     = settings.value( "FilenameFormat", "zz%a_%N.txt" ).toString();

    gs_ExportFilename     = settings.value( "ExportFilename", "ANT-III_1_bathy" ).toString();
    gs_CruiseLabel        = settings.value( "CruiseLabel", "ANT-III/1" ).toString();
    gs_EventLabel         = settings.value( "EventLabel", "PS06/1-track" ).toString();
    gs_AuthorID           = settings.value( "AuthorID", "883" ).toString();
    gs_ReferenceID        = settings.value( "ReferenceID", "9" ).toString();
    gs_ShipName           = settings.value( "ShipName", "POLARSTERN" ).toString();
    gs_ProjectID          = settings.value( "ProjectID", "1" ).toString();
    gs_InstituteID        = settings.value( "InstituteID", "32" ).toString();
    gs_MethodID           = settings.value( "MethodID", "7143" ).toString();
    gb_LatLong            = settings.value( "LatLong", false ).toBool();
    gi_PosDigits          = settings.value( "PositionDigits", 6 ).toInt();
    gi_DepthDigits        = settings.value( "DepthDigits", 1 ).toInt();

    settings.endGroup();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Ermitteln des Dateinamens fuer die Programmeinstellungen.
*   @return Name der Datei fuer die Programmeinstellungen. Dateiname ist gleich "_ERROR_",
*   wenn Betriebssystem ungleich Windows, Mac OS oder Unix ist.
*/

QString MainWindow::getPreferenceFilename()
{
    QString s_PrefFilename = "";

    #if defined(Q_OS_LINUX)
        s_PrefFilename = QDir::homePath() + QLatin1String( "/.config/" ) + QCoreApplication::organizationName() + "/" + QCoreApplication::applicationName() + "/" + QCoreApplication::applicationName() + QLatin1String( ".conf" );
    #endif

    #if defined(Q_OS_MAC)
        s_PrefFilename = QDir::homePath() + QLatin1String( "/Library/Preferences/" ) + QCoreApplication::organizationDomain().section( ".", 1, 1 ) + "." + QCoreApplication::organizationDomain().section( ".", 0, 0 ) + "." + QCoreApplication::applicationName() + QLatin1String( ".plist" );
    #endif

    #if defined(Q_OS_WIN)
        if ( QCoreApplication::applicationName().toLower().endsWith( "portable" ) )
        {
            s_PrefFilename = QCoreApplication::applicationDirPath() + "/" + QCoreApplication::applicationName() + QLatin1String( ".ini" );
        }
        else
        {
            QSettings cfg( QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName() );
            s_PrefFilename = QFileInfo( cfg.fileName() ).absolutePath() + "/" + QCoreApplication::applicationName() + "/" + QCoreApplication::applicationName() + QLatin1String( ".ini" );
        }
    #endif

    return( s_PrefFilename );
}
