#include <QtGui>

#include "Application.h"
#include "Globals.h"
#include "SetGlobalOptionsDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetGlobalOptionsDialog()
{
    int i_DialogResult = QDialog::Rejected;

    SetGlobalOptionsDialog *dialog	= new SetGlobalOptionsDialog();

// ***********************************************************************************************************************

    dialog->OKPushButton->setWhatsThis( "Set new parameter title orientation" );
    dialog->CancelPushButton->setWhatsThis( "Cancel dialog" );

// ***********************************************************************************************************************
// Options

    dialog->LastDownloadDate_dateEdit->setDate( QDate::fromString( gs_lastDate, Qt::ISODate ) );
    dialog->DownloadDirectory_lineEdit->setText( gs_DownloadDirectory );
    dialog->ThumbnailDirectory_lineEdit->setText( gs_ThumbnailDirectory );
    dialog->EasyThumbnailsProgram_lineEdit->setText( gs_EasyThumbnails );
    dialog->wgetProgram_lineEdit->setText( gs_wget );
    dialog->psftpProgram_lineEdit->setText( gs_psftp );
    dialog->UrlDownload_lineEdit->setText( gs_UrlDownload );
    dialog->UserUpdateList_lineEdit->setText( gs_UserUpdateList );
    dialog->PasswordUpdateList_lineEdit->setText( gs_PasswordUpdateList );
    dialog->UrlUpload_lineEdit->setText( gs_UrlUpload );
    dialog->UserUpload_lineEdit->setText( gs_UserUpload );
    dialog->PasswordUpload_lineEdit->setText( gs_PasswordUpload );
    dialog->PathUpdateList_lineEdit->setText( ( gs_PathUpdateList ) );

    dialog->adjustSize();
    dialog->move( posDialog );

// ******************************************************************************************************

    i_DialogResult = dialog->exec();

    posDialog = dialog->pos();

    switch ( i_DialogResult )
    {
    case QDialog::Accepted:
        gs_lastDate             = dialog->LastDownloadDate_dateEdit->date().toString( Qt::ISODate );
        gs_DownloadDirectory    = dialog->DownloadDirectory_lineEdit->text();
        gs_ThumbnailDirectory   = dialog->ThumbnailDirectory_lineEdit->text();
        gs_EasyThumbnails       = dialog->EasyThumbnailsProgram_lineEdit->text();
        gs_wget                 = dialog->wgetProgram_lineEdit->text();
        gs_psftp                = dialog->psftpProgram_lineEdit->text();
        gs_UrlDownload          = dialog->UrlDownload_lineEdit->text();
        gs_UserUpdateList       = dialog->UserUpdateList_lineEdit->text();
        gs_PasswordUpdateList   = dialog->PasswordUpdateList_lineEdit->text();
        gs_UrlUpload            = dialog->UrlUpload_lineEdit->text();
        gs_UserUpload           = dialog->UserUpload_lineEdit->text();
        gs_PasswordUpload       = dialog->PasswordUpload_lineEdit->text();
        gs_PathUpdateList       = dialog->PathUpdateList_lineEdit->text();

        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    delete dialog;
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

SetGlobalOptionsDialog::SetGlobalOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OKPushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(CancelPushButton, SIGNAL(clicked()), this, SLOT(reject()));

    connect(browseDownloadDirectory_pushButton, SIGNAL(clicked()), this, SLOT( browseDownloadDirectoryDialog() ));
    connect(browseThumbnailDirectory_pushButton, SIGNAL(clicked()), this, SLOT( browseThumbnailDirectoryDialog() ));

    connect(browseEasyThumbnailsProgram_pushButton, SIGNAL(clicked()), this, SLOT( browseEasyThumbnailsProgramDialog() ));
    connect(browseWgetProgram_pushButton, SIGNAL(clicked()), this, SLOT( browseWgetProgramDialog() ));
    connect(browsePSftpProgram_pushButton, SIGNAL(clicked()), this, SLOT( browsePSftpProgramDialog() ));
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void SetGlobalOptionsDialog::browseDownloadDirectoryDialog()
{
    QString Path		= this->DownloadDirectory_lineEdit->text();
    QString startPath   = getPersonalDir();
    QString	resultPath  = "";

// ***********************************************************************************************************************

    startPath.replace( "://", ":/" );

    if ( Path.isEmpty() == FALSE )
        startPath = Path;

    resultPath = QFileDialog::getExistingDirectory( this, tr( "Choose a folder" ), startPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    if ( resultPath.isEmpty() == TRUE )
        resultPath = startPath;

    this->DownloadDirectory_lineEdit->setText( QDir::toNativeSeparators( resultPath ) );

    DownloadDirectory_lineEdit->setFocus();
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void SetGlobalOptionsDialog::browseThumbnailDirectoryDialog()
{
    QString Path		= this->ThumbnailDirectory_lineEdit->text();
    QString startPath   = getPersonalDir();
    QString	resultPath  = "";

// ***********************************************************************************************************************

    startPath.replace( "://", ":/" );

    if ( Path.isEmpty() == FALSE )
        startPath = Path;

    resultPath = QFileDialog::getExistingDirectory( this, tr( "Choose a folder" ), startPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    if ( resultPath.isEmpty() == TRUE )
        resultPath = startPath;

    this->ThumbnailDirectory_lineEdit->setText( QDir::toNativeSeparators( resultPath ) );

    ThumbnailDirectory_lineEdit->setFocus();
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void SetGlobalOptionsDialog::browseEasyThumbnailsProgramDialog()
{
    QString	fn			= "";
    QString file		= this->EasyThumbnailsProgram_lineEdit->text();
    QString fileStart	= getProgramDir();

// ***********************************************************************************************************************

    fileStart.replace( "://", ":/" );

    if ( file.isEmpty() == FALSE )
        fileStart = file;

    fn = QFileDialog::getOpenFileName( this, tr( "Select the EasyThumbnails program (*.exe)" ), fileStart, tr( "EXE file (*.exe)" ) );

    if ( fn.isEmpty() == TRUE )
        fn = file;

    this->EasyThumbnailsProgram_lineEdit->setText( QDir::toNativeSeparators( fn ) );

    EasyThumbnailsProgram_lineEdit->setFocus();
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void SetGlobalOptionsDialog::browseWgetProgramDialog()
{
    QString	fn			= "";
    QString file		= this->wgetProgram_lineEdit->text();
    QString fileStart	= getProgramDir();

// ***********************************************************************************************************************

    fileStart.replace( "://", ":/" );

    if ( file.isEmpty() == FALSE )
        fileStart = file;

    fn = QFileDialog::getOpenFileName( this, tr( "Select the wget program (*.exe)" ), fileStart, tr( "EXE file (*.exe)" ) );

    if ( fn.isEmpty() == TRUE )
        fn = file;

    this->wgetProgram_lineEdit->setText( QDir::toNativeSeparators( fn ) );

    wgetProgram_lineEdit->setFocus();
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void SetGlobalOptionsDialog::browsePSftpProgramDialog()
{
    QString	fn			= "";
    QString file		= this->psftpProgram_lineEdit->text();
    QString fileStart	= getProgramDir();

// ***********************************************************************************************************************

    fileStart.replace( "://", ":/" );

    if ( file.isEmpty() == FALSE )
        fileStart = file;

    fn = QFileDialog::getOpenFileName( this, tr( "Select the psftp program (*.exe)" ), fileStart, tr( "EXE file (*.exe)" ) );

    if ( fn.isEmpty() == TRUE )
        fn = file;

    this->psftpProgram_lineEdit->setText( QDir::toNativeSeparators( fn ) );

    psftpProgram_lineEdit->setFocus();
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

QString SetGlobalOptionsDialog::getPersonalDir()
{
    QString s_PersonalDir	= QDir::homePath();
    QString s_HomeDir		= QDir::homePath();

    #if defined(Q_WS_WIN)
        QSettings settings( "Microsoft", "Windows" );
        s_PersonalDir = settings.value( "/CurrentVersion/Explorer/Shell Folders/Personal" ).toString();
    #endif

    #if defined(Q_WS_MACX)
        s_PersonalDir = s_HomeDir;
    #endif

    return( QDir::toNativeSeparators( s_PersonalDir ) );
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

QString SetGlobalOptionsDialog::getProgramDir()
{
    QString     s_ProgramDir   = "";

    #if defined(Q_WS_WIN)
        int         i              = 0;
        QStringList sl_Environment = QProcess::systemEnvironment();
        while ( ( s_ProgramDir.isEmpty() == TRUE ) && ( ++i < sl_Environment.count() ) )
            if ( sl_Environment.at( i ).startsWith( "PROGRAMFILES=", Qt::CaseInsensitive ) == TRUE )
                s_ProgramDir = sl_Environment.at( i ).section( "=", 1, 1 );
    #endif

    #if defined(Q_WS_MACX)
        s_ProgramDir = QDir::homePath();
    #endif

    return( QDir::toNativeSeparators( s_ProgramDir ) );
}

