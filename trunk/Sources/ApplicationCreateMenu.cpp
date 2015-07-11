// ***********************************************************************************************
// *                                                                                             *
// * createMenu.cpp - creates application menus                                                  *
// *                                                                                             *
// * Dr. Rainer Sieger - 2013-05-17                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Erstellen der Menue-Aktionen. */

void MainWindow::createActions()
{
// File menu
    newWindowAction = new QAction(tr("&New window"), this);
    newWindowAction->setShortcut(tr("Ctrl+N"));
    connect(newWindowAction, SIGNAL(triggered()), this, SLOT(newWindow()));

    openFileAction = new QAction(tr("&Open..."), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(chooseFiles()));

    openFolderAction = new QAction(tr("Select &Folder..."), this);
    openFolderAction->setShortcut(tr("Ctrl+F"));
    connect(openFolderAction, SIGNAL(triggered()), this, SLOT(chooseFolder()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveAsAction = new QAction(tr("Save &As..."), this);
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveFileAs()));

    hideWindowAction = new QAction(tr("&Close window"), this);
    hideWindowAction->setShortcut(tr("Ctrl+W"));
    connect(hideWindowAction, SIGNAL(triggered()), this, SLOT(hideWindow()));

    setOptionsAction = new QAction(tr("General options..."), this);
    setOptionsAction->setShortcut(tr("Ctrl+,"));
    connect(setOptionsAction, SIGNAL(triggered()), this, SLOT(doSetOptionsDialog()));

    exitAction = new QAction(tr("&Quit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    // Basic tools
    saveFilelistAction = new QAction(tr("Save list of files"), this);
    connect(saveFilelistAction, SIGNAL(triggered()), this, SLOT(doSaveFilelist()));

    deleteDoubleLinesAction = new QAction(tr("Delete double lines"), this);
    connect(deleteDoubleLinesAction, SIGNAL(triggered()), this, SLOT(doDeleteDoubleLines()));

    // Special tools
    MultibeamConverterImportAction = new QAction(tr("Create multibeam PANGAEA import file"), this);
    connect(MultibeamConverterImportAction, SIGNAL(triggered()), this, SLOT(doMultibeamConverterImport()));

    MultibeamConverter100Action = new QAction(tr("Multibeam dataset -> ODV import file (1 % resolution)"), this);
    connect(MultibeamConverter100Action, SIGNAL(triggered()), this, SLOT(doMultibeamConverter100()));

    MultibeamConverter10Action = new QAction(tr("Multibeam dataset -> ODV import file (10 % resolution)"), this);
    connect(MultibeamConverter10Action, SIGNAL(triggered()), this, SLOT(doMultibeamConverter10()));

    MultibeamConverterAllAction = new QAction(tr("Multibeam dataset -> ODV import file (full resolution)"), this);
    connect(MultibeamConverterAllAction, SIGNAL(triggered()), this, SLOT(doMultibeamConverterAll()));

    // Help menu
    aboutAction = new QAction(tr("&About ") + getApplicationName( true ), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    showHelpAction = new QAction(getApplicationName( true ) + tr(" &Help"), this);
    showHelpAction->setShortcut(tr("F1"));
    connect(showHelpAction, SIGNAL(triggered()), this, SLOT(displayHelp()));

#if defined(Q_OS_WIN)
    newWindowAction->setStatusTip(tr("Create a new file"));
    openFileAction->setStatusTip(tr("Choose an existing file"));
    openFolderAction->setStatusTip(tr("Choose an existing folder"));
    saveAction->setStatusTip(tr("Save the document to disk"));
    saveAsAction->setStatusTip(tr("Save the document under a new name"));
    exitAction->setStatusTip(tr("Exit the application"));
    aboutAction->setStatusTip(tr("Show the application's About box"));
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    showHelpAction->setStatusTip(tr("Show the application's help"));
#endif

}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Verbindet Menues mit Aktionen. */

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu( tr( "&File" ) );
    fileMenu->addAction( openFileAction );
    fileMenu->addAction( openFolderAction );
    fileMenu->addSeparator();

#if defined(Q_OS_LINUX)
    ;
#endif

#if defined(Q_OS_MAC)
    fileMenu->addAction( newWindowAction );
    newWindowAction->setEnabled( false );
    fileMenu->addAction( hideWindowAction );
#endif

#if defined(Q_OS_WIN)
    fileMenu->addAction( hideWindowAction );
#endif

    fileMenu->addSeparator();
    fileMenu->addAction( setOptionsAction );

#if defined(Q_OS_LINUX)
    fileMenu->addSeparator();
    fileMenu->addAction( exitAction );
#endif

#if defined(Q_OS_WIN)
    fileMenu->addSeparator();
    fileMenu->addAction( exitAction );
#endif

// **********************************************************************************************

    basicToolsMenu = menuBar()->addMenu( tr( "Basic tools" ) );

    basicToolsMenu->addAction( deleteDoubleLinesAction );
    basicToolsMenu->addAction( saveFilelistAction );

// **********************************************************************************************

    specialToolsMenu = menuBar()->addMenu( tr( "Converter tools" ) );
    specialToolsMenu->addAction( MultibeamConverterImportAction );
    specialToolsMenu->addSeparator();
    specialToolsMenu->addAction( MultibeamConverter100Action );
    specialToolsMenu->addAction( MultibeamConverter10Action );
    specialToolsMenu->addAction( MultibeamConverterAllAction );

// **********************************************************************************************

    helpMenu = menuBar()->addMenu( tr( "&Help" ) );
    helpMenu->addAction( aboutAction );
    helpMenu->addAction( aboutQtAction );
    helpMenu->addSeparator();
    helpMenu->addAction( showHelpAction );
}
