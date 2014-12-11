#ifndef SETMULTIBEAMOPTIONSDIALOG_H
#define SETMULTIBEAMOPTIONSDIALOG_H

#include <QDialog>

#include "ui_setmultibeamoptionsdialog.h"

class SetMultibeamOptionsDialog : public QDialog, public Ui::SetMultibeamOptionsDialog
{
    Q_OBJECT

public:
    SetMultibeamOptionsDialog( QWidget *parent = 0 );
};

#endif
