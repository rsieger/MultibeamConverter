// ***********************************************************************************************
// *                                                                                             *
// * SetOptionsDialog.cpp - Sets program options                                                 *
// *                                                                                             *
// * Dr. Rainer Sieger - 2010-07-10                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtWidgets>

#include "Application.h"
#include "SetOptionsDialog.h"

SetOptionsDialog::SetOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

int MainWindow::doSetOptionsDialog()
{
    int i_DialogResult = QDialog::Rejected;

// ***********************************************************************************************************************

    SetOptionsDialog dialog( this );

    dialog.FilenameFormat_lineEdit->setText( QDir::toNativeSeparators( gs_FilenameFormat ) );

    dialog.FilenameFormat_lineEdit->selectAll();

    dialog.OK_pushButton->setWhatsThis( "Close dialog" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.move( posDialog );
    dialog.resize( dialog.sizeHint() );
    dialog.show();

// ******************************************************************************************************

    switch ( dialog.exec() )
    {
    case QDialog::Accepted:
        gs_FilenameFormat = dialog.FilenameFormat_lineEdit->text();

        i_DialogResult    = QDialog::Accepted;
        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    posDialog = dialog.pos();

    return( i_DialogResult );
}
