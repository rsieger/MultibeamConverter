/* 2013-05-17                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-05-10

int MainWindow::MultibeamImportConverter( const QString& s_FilenameIn, const QString& s_FilenameOut, const int i_FileNo, const QString& s_ExportFilename,
                                          const QString& s_CruiseLabel, const QString& s_EventLabel, const QString& s_AuthorID, const QString& s_ReferenceID,
                                          const QString& s_ShipName, const QString& s_ProjectID, const QString& s_InstituteID, const QString& s_MethodID,
                                          const bool b_LatLong, const int i_PosDigits, const int i_DepthDigits, const int i_NumOfFiles )
{
    QString         InputStr        = "";

    unsigned int	ui_length		= 1;
    unsigned int	ui_filesize		= 1;

// **********************************************************************************************
// open input file

    QFile fin( s_FilenameIn );

    if ( fin.open( QIODevice::ReadOnly | QIODevice::Text ) == false )
        return( -10 );

    ui_filesize = fin.size();

    QTextStream tin( &fin );

// **********************************************************************************************
// open output file

    QFile fout( s_FilenameOut );

    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tout( &fout );

// **********************************************************************************************

    initProgress( i_NumOfFiles, s_FilenameIn, tr( "Converting..." ), 100 );

// **********************************************************************************************
// read file

// Header

    if ( i_FileNo == 0 )
    {
        tout << "/* DATA DESCRIPTION:" << eol;

        QString s_Author  = s_AuthorID;
        QString s_Method  = s_MethodID;
        QString s_Project = s_ProjectID;
        QString s_Event   = s_EventLabel;

        if ( s_Author.isEmpty() == true )
            s_Author = "506";

        if ( s_Method.isEmpty() == true )
            s_Method = "43";

        if ( s_Project.isEmpty() == true )
            s_Project = "15";

        if ( s_Event.isEmpty() == true )
            s_Event = "not_given";

        tout << "Author:\t" << s_Author << eol;

        tout << "Title:\tMultibeam survey (latitude, longitude, depth) from " << s_ShipName << " cruise " << s_CruiseLabel << eol;

        if ( s_InstituteID.isEmpty() == false )
            tout << "Source:\t" << s_InstituteID << eol;

        if ( s_ReferenceID.isEmpty() == false )
            tout << "Reference:\t" << s_ReferenceID << eol;

        if ( s_ExportFilename.isEmpty() == false )
            tout << "Export Filename:\t" << s_ExportFilename << eol;

        tout << "Event:\t" << s_EventLabel << eol;

        tout << "PI:\t" << s_Author << eol;

        tout << "Parameter:\t1600 * FORMAT: ###0.000000" << eol;
        tout <<           "\t1601 * FORMAT: ###0.000000" << eol;

        tout << "\t2268 * PI: " << s_Author << " * METHOD: " << s_Method << " * FORMAT: ####0.0" << eol;

        tout << "Project:\t" << s_Project << eol;

        tout << "Topologic Type:\t6" << eol;
        tout << "Status:\t4" << eol;
        tout << "Login:\t3" << eol;
        tout << "*/" << eol;

        tout << "Event label" << "\t" << "1600" << "\t" << "1601" << "\t" << "2268" << eol;

        tout << s_Event;
    }

    while ( ( tin.atEnd() == false ) && ( ui_length != (unsigned int) _APPBREAK_ ) )
    {
        InputStr  = tin.readLine();
        ui_length = incProgress( i_NumOfFiles, ui_filesize, ui_length, InputStr );

        while ( InputStr.contains( "  " ) == true )
            InputStr.replace( "  ", " " );

        tout << "\t" << buildOutputStr( b_LatLong, InputStr, i_PosDigits, i_DepthDigits ) << eol;
    }

    resetProgress( i_NumOfFiles );

    fin.close();
    fout.close();

// **********************************************************************************************

    if ( ui_length == (unsigned int) _APPBREAK_ )
        return( _APPBREAK_ );

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-05-10

QString MainWindow::buildOutputStr(const bool b_LatLong, const QString InputStr, const int i_PosDigits, const int i_DepthDigits )
{
    double          d_Depth         = 0.;
    double          d_Latitude      = 0.;
    double          d_Longitude     = 0.;

// **********************************************************************************************

    if ( InputStr.contains( "\t" ) == true )
    {
       d_Depth = InputStr.section( "\t", 2, 2 ).toDouble();

       if ( b_LatLong == true )
       {
           d_Latitude  = InputStr.section( "\t", 0, 0 ).toDouble();
           d_Longitude = InputStr.section( "\t", 1, 1 ).toDouble();
       }
       else
       {
           d_Latitude  = InputStr.section( "\t", 1, 1 ).toDouble();
           d_Longitude = InputStr.section( "\t", 0, 0 ).toDouble();
       }
    }
    else
    {
        if ( InputStr.startsWith( " " ) == true )
        {
            d_Depth = InputStr.section( " ", 3, 3 ).toDouble();

            if ( b_LatLong == true )
            {
                d_Latitude  = InputStr.section( " ", 1, 1 ).toDouble();
                d_Longitude = InputStr.section( " ", 2, 2 ).toDouble();
            }
            else
            {
                d_Latitude  = InputStr.section( " ", 2, 2 ).toDouble();
                d_Longitude = InputStr.section( " ", 1, 1 ).toDouble();
            }
        }
        else
        {
            d_Depth = InputStr.section( " ", 2, 2 ).toFloat();

            if ( b_LatLong == true )
            {
                d_Latitude  = InputStr.section( " ", 0, 0 ).toDouble();
                d_Longitude = InputStr.section( " ", 1, 1 ).toDouble();
            }
            else
            {
                d_Latitude  = InputStr.section( " ", 1, 1 ).toDouble();
                d_Longitude = InputStr.section( " ", 0, 0 ).toDouble();
            }
        }
    }

    if ( d_Longitude < -180. )
        d_Longitude += 360.;

    if ( d_Depth < 0 )
      d_Depth = -d_Depth;

    return( QString( "%1\t%2\t%3" ).arg( d_Latitude, 0, 'f', i_PosDigits ).arg( d_Longitude, 0, 'f', i_PosDigits ).arg( d_Depth, 0, 'f', i_DepthDigits ) );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-04-07

int MainWindow::MultibeamConverter( const QString& s_FilenameIn, const QString& s_FilenameOut, const int i_SkipNLines, const int i_NumOfFiles )
{
    int             k               = 0;
    int             n               = 0;

    int             i_posLatitude   = -1;
    int             i_posLongitude  = -1;
    int             i_posBathyDepth = -1;

    QString         InputStr        = "";

    unsigned int	ui_length       = 1;
    unsigned int	ui_filesize     = 1;

// **********************************************************************************************
// open input file

    QFile fin( s_FilenameIn );

    if ( fin.open( QIODevice::ReadOnly | QIODevice::Text ) == false )
        return( -10 );

    ui_filesize = fin.size();

    QTextStream tin( &fin );

// **********************************************************************************************
// open output file

    QFile fout( s_FilenameOut );

    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tout( &fout );

// **********************************************************************************************

    initProgress( i_NumOfFiles, s_FilenameIn, tr( "Converting..." ), 100 );

// **********************************************************************************************
// read file

// Header
    InputStr  = tin.readLine();
    ui_length = incProgress( i_NumOfFiles, ui_filesize, ui_length, InputStr );

    if ( InputStr.startsWith( "/* DATA DESCRIPTION:" ) == true )
    {
        while ( ( tin.atEnd() == false ) && ( ui_length != (unsigned int) _APPBREAK_ ) && ( InputStr != "*/" ) )
        {
            InputStr  = tin.readLine();
            ui_length = incProgress( i_NumOfFiles, ui_filesize, ui_length, InputStr );
        }

        InputStr  = tin.readLine();
        ui_length = incProgress( i_NumOfFiles, ui_filesize, ui_length, InputStr );
    }

    n = NumOfSections( InputStr );

    if ( n > 1 )
    {
        for ( int i=0; i<n; i++ )
            if ( ( InputStr.section( "\t", i, i ).toLower() == "latitude" ) || ( InputStr.section( "\t", i, i ) == "1600" ) )
                i_posLatitude = i;

        for ( int i=0; i<n; i++ )
            if ( ( InputStr.section( "\t", i, i ).toLower() == "longitude" ) || ( InputStr.section( "\t", i, i ) == "1601" ) )
                i_posLongitude = i;

        for ( int i=0; i<n; i++ )
        {
            if ( ( InputStr.section( "\t", i, i ).toLower() == "depth, bathymetric [m]" )
                 || ( InputStr.section( "\t", i, i ).toLower() == "depth, bathymetric, gridded [m]" )
                 || ( InputStr.section( "\t", i, i ).toLower() == "bathy depth [m]" )
                 || ( InputStr.section( "\t", i, i ).toLower() == "bathy depth grid [m]" )
                 || ( InputStr.section( "\t", i, i ) == "2268" )
                 || ( InputStr.section( "\t", i, i ) == "104179" ) )
            {
                i_posBathyDepth = i;
            }
        }

        if ( ( i_posLatitude > -1 ) && ( i_posLongitude > -1 ) && ( i_posBathyDepth > -1 ) )
        {
            tout << "Station" << "\t" << "Latitude [degress_north]" << "\t" << "Longitude [degress_east]" << "\t" << "Depth, water [m]" << "\t" << "Bathy depth [m]" << eol;

            while ( ( tin.atEnd() == false ) && ( ui_length != (unsigned int) _APPBREAK_ ) )
            {
                InputStr  = tin.readLine();
                ui_length = incProgress( i_NumOfFiles, ui_filesize, ui_length, InputStr );

                tout << QString( "%1" ).arg( ++k ) << "\t" << InputStr.section( "\t", i_posLatitude, i_posLatitude ) << "\t";
                tout << InputStr.section( "\t", i_posLongitude, i_posLongitude ) << "\t" << "0";
                tout << "\t" << InputStr.section( "\t", i_posBathyDepth, i_posBathyDepth ) << eol;

                for ( int j=1; j<i_SkipNLines; j++ )
                {
                    InputStr  = tin.readLine();
                    ui_length = incProgress( i_NumOfFiles, ui_filesize, ui_length, InputStr );
                }
            }
        }
    }

    resetProgress( i_NumOfFiles );

    fin.close();
    fout.close();

// **********************************************************************************************

    if ( ui_length == (unsigned int) _APPBREAK_ )
        return( _APPBREAK_ );

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-04-07

void MainWindow::doMultibeamConverter( const int n )
{
    int         i                   = 0;
    int         k                   = 0;
    int         err                 = 0;
    int         stopProgress        = 0;

    QStringList sl_FilenameOut;

// **********************************************************************************************

    gi_ActionNumber = 1;

    if ( existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList ) == true )
    {
        if ( n < 0 )
        {
          if ( doSetMultibeamOptionsDialog() != QDialog::Accepted )
              err = _CHOOSEABORTED_;
        }

        if ( err == _NOERROR_ )
        {
            initFileProgress( gsl_FilenameList.count(), gsl_FilenameList.at( 0 ), tr( "Multibeam converter working..." ) );

            while ( ( i < gsl_FilenameList.count() ) && ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) )
            {
                QFileInfo fi( gsl_FilenameList.at( i ) );

                if ( fi.exists() == true )
                {
                    sl_FilenameOut.append( fi.absolutePath() + "/" + fi.completeBaseName() + "_imp.txt" );

                    if ( n < 0 )
                        err = MultibeamImportConverter( fi.absoluteFilePath(), sl_FilenameOut.at( i ), i, gs_ExportFilename, gs_CruiseLabel, gs_EventLabel, gs_AuthorID,
                                                        gs_ReferenceID, gs_ShipName, gs_ProjectID, gs_InstituteID, gs_MethodID, gb_LatLong, gi_PosDigits, gi_DepthDigits,
                                                        gsl_FilenameList.count() );
                    else
                        err = MultibeamConverter( fi.absoluteFilePath(), fi.absolutePath() + "/" + fi.completeBaseName() + "_odv.txt", n, gsl_FilenameList.count() );

                    stopProgress = incFileProgress( gsl_FilenameList.count(), ++i );
                }
                else
                {
                    err = _FILENOTEXISTS_;
                }
            }

            resetFileProgress( gsl_FilenameList.count() );
        }
    }
    else
    {
        err = _CHOOSEABORTED_;
    }

    if ( ( n < 0 ) && ( sl_FilenameOut.count() > 1 ) && ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) )
    {
        i = 0;

        initFileProgress( sl_FilenameOut.count(), sl_FilenameOut.at( 0 ), tr( "Concatenating multibeam files..." ) );

        QFileInfo fi_out( sl_FilenameOut.at( 0 ) );

        QFile fout( fi_out.absolutePath() + "/" + gs_ExportFilename + "_imp.txt" );

        if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
            return;

        QTextStream tout( &fout );

        while ( ( i < sl_FilenameOut.count() ) && ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) )
        {
            QFileInfo fi_in( sl_FilenameOut.at( i ) );

            if ( fi_in.exists() == true )
            {
                QFile fin( sl_FilenameOut.at( i ) );

                if ( fin.open( QIODevice::ReadOnly | QIODevice::Text ) == false )
                {
                    fout.close();
                    return;
                }

                QTextStream tin( &fin );

                while ( tin.atEnd() == false )
                {
                    ++k;
                    tout << tin.readLine() << eol;
                }

                fin.close();
                fin.remove();

                stopProgress = incFileProgress( sl_FilenameOut.count(), ++i );
            }
            else
            {
                err = _FILENOTEXISTS_;
            }
        }

        resetFileProgress( sl_FilenameOut.count() );

        fout.close();
    }

// **********************************************************************************************

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Multibeam converter was canceled" ), false, false );

    if ( ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) && ( k > 0 ) )
        QMessageBox::information( this, "Multibeam converter", QString( "Number of data points: %1" ).arg( k-17 ), "OK" );

    onError( err );
}


// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doMultibeamConverterImport()
{
   doMultibeamConverter( -1 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doMultibeamConverterAll()
{
   doMultibeamConverter( 0 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doMultibeamConverter10()
{
   doMultibeamConverter( 10 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doMultibeamConverter100()
{
   doMultibeamConverter( 100 );
}
