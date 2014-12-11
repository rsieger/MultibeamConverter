#ifndef SETOPTIONSDIALOG_H
#define SETOPTIONSDIALOG_H

#include <QDialog>

#include "ui_setoptionsdialog.h"

class SetOptionsDialog : public QDialog, public Ui::SetOptionsDialog
{
Q_OBJECT

public:
    SetOptionsDialog( QWidget *parent = 0 );
};

#endif
