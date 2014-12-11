// ***********************************************************************************************
// *                                                                                             *
// * SetMultibeamOptionsDialog.cpp                                                               *
// *                                                                                             *
// * Dr. Rainer Sieger - 2013-05-17                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtWidgets>

#include "Application.h"
#include "SetMultibeamOptionsDialog.h"

int MainWindow::doSetMultibeamOptionsDialog()
{
    int i_DialogResult = QDialog::Rejected;

    SetMultibeamOptionsDialog dialog( this );

    dialog.ExportFilename_lineEdit->setText( gs_ExportFilename );
    dialog.ShipName_lineEdit->setText( gs_ShipName );
    dialog.CruiseLabel_lineEdit->setText( gs_CruiseLabel );
    dialog.EventLabel_lineEdit->setText( gs_EventLabel );
    dialog.AuthorID_lineEdit->setText( gs_AuthorID );
    dialog.ReferenceID_lineEdit->setText( gs_ReferenceID );
    dialog.ProjectID_lineEdit->setText( gs_ProjectID );
    dialog.InstituteID_lineEdit->setText( gs_InstituteID );
    dialog.MethodID_lineEdit->setText( gs_MethodID );
    dialog.Position_spinBox->setValue( gi_PosDigits );
    dialog.Depth_spinBox->setValue( gi_DepthDigits );

    if ( gb_LatLong == true )
        dialog.LatLong_radioButton->setChecked( true );
    else
        dialog.LongLat_radioButton->setChecked( true );

    dialog.OK_pushButton->setWhatsThis( "Start process" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.move( posDialog );
    dialog.resize( dialog.sizeHint() );
    dialog.show();

// ******************************************************************************************************

    switch ( dialog.exec() )
    {
    case QDialog::Accepted:
        gs_ExportFilename   = dialog.ExportFilename_lineEdit->text();
        gs_ShipName         = dialog.ShipName_lineEdit->text();
        gs_CruiseLabel      = dialog.CruiseLabel_lineEdit->text();
        gs_EventLabel       = dialog.EventLabel_lineEdit->text();
        gs_AuthorID         = dialog.AuthorID_lineEdit->text();
        gs_ReferenceID      = dialog.ReferenceID_lineEdit->text();
        gs_ProjectID        = dialog.ProjectID_lineEdit->text();
        gs_InstituteID      = dialog.InstituteID_lineEdit->text();
        gs_MethodID         = dialog.MethodID_lineEdit->text();
        gi_PosDigits        = dialog.Position_spinBox->value();
        gi_DepthDigits      = dialog.Depth_spinBox->value();

        if ( dialog.LatLong_radioButton->isChecked() )
            gb_LatLong = true;
        else
            gb_LatLong = false;

        i_DialogResult = QDialog::Accepted;
        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    posDialog = dialog.pos();

    return( i_DialogResult );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

SetMultibeamOptionsDialog::SetMultibeamOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
}

