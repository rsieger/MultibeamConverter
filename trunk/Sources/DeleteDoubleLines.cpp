/* 2013-05-17                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2008-04-07

int MainWindow::DeleteDoubleLines( const QString& s_FilenameIn, const QString& s_FilenameOut, const int i_NumOfFiles )
{
    int         i               = 0;
    int         n               = 0;

    int			stopProgress	= 0;

    QStringList sl_Input;

// **********************************************************************************************
// read data file

    if ( ( n = readFile( s_FilenameIn, sl_Input ) ) < 1 ) // System encoding
        return( n );

// **********************************************************************************************
// open output file

    QFile fout( s_FilenameOut );

    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text) == false )
        return( -20 );

    QTextStream tout( &fout );

// **********************************************************************************************

    initProgress( i_NumOfFiles, s_FilenameIn, tr( "Deleting double lines..." ), sl_Input.count() );

// **********************************************************************************************

    tout << sl_Input.at( i++ ) << eol;

    while ( ( i<sl_Input.count() ) && ( stopProgress != _APPBREAK_ ) )
    {
        if ( sl_Input.at( i ) != sl_Input.at( i-1) )
            tout << sl_Input.at( i ) << eol;

        stopProgress = incProgress( i_NumOfFiles, ++i );
    }

    fout.close();

    resetProgress( i_NumOfFiles );

    if ( stopProgress == _APPBREAK_ )
        return( _APPBREAK_ );

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2008-04-07

void MainWindow::doDeleteDoubleLines()
{
    int         i				= 0;
    int         err				= 0;
    int         stopProgress	= 0;

    QString s_FilenameIn    = "";
    QString s_FilenameOut   = "";

// **********************************************************************************************

    if ( existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList ) == true )
    {
        initFileProgress( gsl_FilenameList.count(), gsl_FilenameList.at( 0 ), tr( "Deleting double lines..." ) );

        while ( ( i < gsl_FilenameList.count() ) && ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) )
        {
            if ( buildFilename( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList.at( i ), s_FilenameIn, s_FilenameOut ) == true )
            {
                err = DeleteDoubleLines( s_FilenameIn, s_FilenameOut, gsl_FilenameList.count() );

                stopProgress = incFileProgress( gsl_FilenameList.count(), ++i );
            }
            else
            {
                err = _FILENOTEXISTS_;
            }
        }

        resetFileProgress( gsl_FilenameList.count() );
    }
    else
    {
        err = _CHOOSEABORTED_;
    }

// **********************************************************************************************

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Deleting double lines was canceled" ) );

    onError( err );
}

