/* 2013-05-17                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2008-04-07

int MainWindow::SaveFilelist( const QString &s_FilenameOut, const QStringList sl_FilenameList )
{
    QDateTime   CreationDateTime;

// **********************************************************************************************
// open output file

    QFileInfo fi( s_FilenameOut );

    QFile fout( s_FilenameOut );

    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text) == false )
        return( -20 );

    QTextStream tout( &fout );

// **********************************************************************************************

    for ( int i=0; i<sl_FilenameList.count(); i++ )
    {
        fi.setFile( sl_FilenameList.at( i ) );

        CreationDateTime.setDate( fi.created().date() );
        CreationDateTime.setTime( fi.created().time() );

        tout << QDir::toNativeSeparators( fi.absoluteFilePath() ) << "\t";
        tout << QDir::toNativeSeparators( fi.absolutePath() ) << "\t";
        tout << fi.fileName() << "\t" << fi.baseName() << "\t";
        tout << fi.completeSuffix() << "\t" << fi.size() << "\t" << CreationDateTime.toString( "yyyy-MM-ddThh:mm:ss" ) << eol;
    }

    fout.close();

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2008-04-07

void MainWindow::doSaveFilelist()
{
    int         err				= 0;
    int         stopProgress	= 0;

    QString     s_FilenameOut   = "";

// **********************************************************************************************

    if ( existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList ) == true )
    {
        QFileInfo fi( gsl_FilenameList.at( 0 ) );

        s_FilenameOut = QFileDialog::getSaveFileName( this, tr( "Save list of files to" ), fi.absolutePath() + tr( "_filelist.txt" ), tr( "Text (*.txt)" ), 0, QFileDialog::DontUseNativeDialog );

        if ( s_FilenameOut.isEmpty() == false )
            err = SaveFilelist( s_FilenameOut, gsl_FilenameList );
        else
            err = _CHOOSEABORTED_;
    }
    else
    {
        err = _CHOOSEABORTED_;
    }

// **********************************************************************************************

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Save list of files was canceled" ), false, false );

    onError( err );
}


