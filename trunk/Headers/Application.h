/* Application.h              */
/* 2013-05-15                 */
/* Dr. Rainer Sieger          */

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QTextEdit>
#include <QTextCodec>
#include <QTextStream>
#include <QStringListModel>
#include <QListView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>
#include <QProcess>
#include <QTimer>
#include <QMimeData>
#include <QDesktopServices>
#include <QMessageBox>
#include <QProgressBar>
#include <QProgressDialog>
#include <QStatusBar>
#include <QSettings>

#include "Globals.h"
#include "Webfile.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QAction;
class QLabel;
class QProgressDialog;
class QProgressBar;
class QTimer;
class QDateTime;
class QUrl;
class QTextEdit;
class QStringListModel;
class QListView;
class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_CLASSINFO( "author", "Rainer Sieger" )
    Q_CLASSINFO( "url", "https://pangaea.de" )

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    int         gi_EOL;                          //!< End-of-Line Zeichen fuer die Outputdateien
    int         gi_Codec;                        //!< Zeichenkodierung
    int         gi_Extension;                    //!< Dateierweiterung fuer Ausgabedateien
    int         gi_ActionNumber;                 //!< Die ActionNumber wird bei jedem angewandenten Tool um 1 erhoeht.
    int         gi_NumOfProgramStarts;           //!< Anzahl der Programmstarts
    int         gi_PosDigits;                    //!< Anzahl der Nachkommastellen fuer die Position
    int         gi_DepthDigits;                  //!< Anzahl der Nachkommastellen fuer die Depth

    QStringList gsl_FilenameList;                //!< Liste aller Dateinamen incl. Pfad.

    QString		gs_FilenameFormat;               //!< Bestimmt in die Form des automatisch erzeugten neuen Dateinamens. \%a = aktuelle Actionnumber, \%N = Dateiname.
    QString		gs_Path;                         //!< Der zuletzt verwendete Pfad.
    QString     gs_Version;                      //!< Aktuelle Version des Programms.
    QString     gs_lastDate;                     //!< Datum des letzten Downloads

    bool        gb_showProgressBar;              //!< Soll der ProgressBar im Fenster unten rechts angezeigt werden?

    QString     gs_ExportFilename;
    QString     gs_ShipName;
    QString     gs_CruiseLabel;
    QString     gs_EventLabel;
    QString     gs_AuthorID;
    QString     gs_ReferenceID;
    QString     gs_ProjectID;
    QString     gs_InstituteID;
    QString     gs_MethodID;

    bool        gb_LatLong;

    int DeleteDoubleLines( const QString &FilenameIn, const QString &FilenameOut, const int NumOfFiles );
    int ExtractColumns( const QString &FilenameIn, const QString &FilenameOut, const int NumOfFiles );
    int SaveFilelist( const QString &FilenameOut, const QStringList &FilenameList );

    QString buildOutputStr( const bool LatLong, const QString InputStr, const int i_PosDigits, const int i_DepthDigits );

    int MultibeamConverter( const QString &FilenameIn, const QString &FilenameOut, const int SkipNLines, const int NumOfFiles );

    int MultibeamImportConverter( const QString &FilenameIn, const QString &FilenameOut, const int FileNo, const QString &ExportFilename, const QString &CruiseLabel, const QString &EventLabel,
                                  const QString &AuthorID, const QString &ReferenceID, const QString &ShipName, const QString &ProjectID, const QString &InstituteID, const QString &MethodID,
                                  const bool LatLong, const int PosDigits, const int DepthDigits, const int NumOfFiles );

    void doMultibeamConverter( const int n );
    int doSetMultibeamOptionsDialog();

protected:
    void dragEnterEvent( QDragEnterEvent *event );
    void dropEvent( QDropEvent *event );
    void closeEvent( QCloseEvent *event );
    void onError( const int err );

signals:
    void finishedBuildFilelist( bool );

private slots:
    int  chooseFile();
    int  chooseFiles();
    int  chooseFolder( const QString &Folder = "" );
    int  saveFile();
    int  saveFileAs();

    void exitApplication();
    void hideWindow();
    void newWindow();
    void displayHelp();
    void about();
    void clearStatusMessage();

    void doDeleteDoubleLines();
    void doSaveFilelist();

    void doMultibeamConverterAll();
    void doMultibeamConverter10();
    void doMultibeamConverter100();
    void doMultibeamConverterImport();

    int doSetOptionsDialog();

private:
    QStringList expandCommandline();
    QStringList renameFiles( const QStringList &Filename, const QString &searchStr, const QString &replaceStr );
    bool buildFilename( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QString &Filename, QString &FilenameIn, QString &FilenameOut );
    bool containsBinaryFile( const QStringList &FilenameList );
    bool existsFirstFile( const int ActionNumber, const QString &FilenameFormat, const int Extension, QStringList &FilenameList );
    bool isEmptyLine( const QString &String );
    QString findZip( const int mode = 1 );
    QString findUnzip( int const mode = 1 );
    int NumOfSections( const QString &String );
    int addToFilenameList( QStringList &FilenameList, const QString &Filename, const bool showAllFiles = true, const bool decompressFile = false );
    int calcFileSizeClass( const QString &FilenameIn, const int NumOfFiles, const int lowerLimit = 100, const int upperLimit = 1000 );
    int copyStringList( const QStringList &InStringList, QStringList &OutStringList, const QString &s_Pattern = "*" );
    int emptyDir( const QString &Dir );
    int decompressFile( const QString &Filename, const bool delZipFile = false, const int mode = 1, const QString &Program = "zip" );
    int incFileProgress( const int NumOfFiles, const int FileNumber );
    int incProgress( const int NumOfFiles, const int Step );
    int readFile( const QString &FilenameIn, QStringList &Input, const int Codec = -1, const int NumOfFiles = 0, const qint64 Bytes = 0 );
    int removeFile( const QString &Filename );
    int downloadFile( const QString &Url, const QString &absoluteFilePath );
    unsigned int incProgress( const int NumOfFiles, const unsigned int filesize, const unsigned int length, const QString &InputStr );
    void appendItem( QStringList &List, const QString &Item, const QString &SS = "", const QString &RS = "" );
    void compressFolder( const QString &Program, const QString &Folder );
    void compressFile( const QString &FilenameIn, const int mode = 1, const QString &Program = "zip" );
    void clearFilenameList( int &ActionNumber, QStringList &FilenameList );
    void clearList( QStringList &List );
    void clearMessage();
    void createActions();
    void createMenus();
    void createStatusBar( const bool showProgressBar );
    void enableMenuItems( const QStringList &FilenameList );
    void endTool( const int err, const int stopProgress, int &ActionNumber, const QString &FilenameFormat, const int Extension, QStringList &FilenameList, const QString &doneMessage = "Done", const QString &canceledMessage = "Converter was canceled", const bool clearList = false, const bool incActionNumber = true );
    void initFileProgress( const int NumOfFiles, const QString &FilenameIn, const QString &MessageText );
    void initProgress( const int NumOfFiles, const QString &Filename, const QString &MessageText, const int totalNumberOfSteps );
    void initProgress( const int totalNumberOfSteps );
    void listDir( QStringList &Filename, const QString &Directory, const bool showAllFiles = true, const bool decompressFile = false );
    void loadPreferences();
    void resetFileProgress( const int NumOfFiles );
    void resetProgress( const int NumOfFiles = 0 );
    void savePreferences();
    void setNormalCursor();
    void setStatusBar( const QString &Message = "", const int seconds = 0 );
    void setStatusBarFileInProgress( const QString &Filename, const QString &Message = "", const int i_seconds = 0 );
    void setWTitle( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QStringList &FilenameList );
    void setWaitCursor();
    void showFilenameList( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QStringList &FilenameList );
    void showList( const QStringList &List );
    void showMessage( const QString &Message, QStringList &MessageList );
    void wait( const int msec );

    QString getApplicationName( const bool replaceUnderline = false );
    QString getDataLocation();
    QString getDocumentDir();
    QString getPreferenceFilename();
    QString getVersion();
    QString setEOLChar( const int EOL );
    QString setExtension( const int Extension );
    QString getFileChecksum( const QString &FilenameIn );

    QMenu	*fileMenu;
    QMenu   *basicToolsMenu;
    QMenu	*specialToolsMenu;
    QMenu	*helpMenu;

    QAction *newWindowAction;
    QAction *openFileAction;
    QAction *openFolderAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *hideWindowAction;
    QAction *setOptionsAction;
    QAction *exitAction;
    QAction *deleteDoubleLinesAction;
    QAction *extractColumnsAction;
    QAction *saveFilelistAction;
    QAction *CliwocConverterAction;
    QAction *CreateDoiXmlAction;
    QAction *MultibeamConverterImportAction;
    QAction *MultibeamConverterAllAction;
    QAction *MultibeamConverter10Action;
    QAction *MultibeamConverter100Action;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *showHelpAction;

    QProgressDialog *ProgressDialog;
    QProgressDialog *FileProgressDialog;
    QProgressBar    *ProgressBar;
    QLabel			*StatusMessage;

    QStringListModel	*Model;
    QListView			*ListView;
    QTextEdit			*textViewer;

    QPoint	posWindow;              //!< Position des Programmfensters.
    QSize	sizeWindow;             //!< Groesse des Programmfensters.

    QPoint	posDialog;              //!< Position der Dialoge.
    QSize	sizeParameterDialog;	//!< Groesse der Parameterdialogs.
};

#endif
