#ifndef SETGLOBALOPTIONSDIALOG_H
#define SETGLOBALOPTIONSDIALOG_H

#include <QDialog>

#include "ui_setglobaloptionsdialog.h"

class SetGlobalOptionsDialog : public QDialog, public Ui::SetGlobalOptionsDialog
{
    Q_OBJECT

public:
    SetGlobalOptionsDialog( QWidget *parent = 0 );

    QString getPersonalDir();
    QString getProgramDir();

private slots:
    void browseDownloadDirectoryDialog();
    void browseThumbnailDirectoryDialog();
    void browseEasyThumbnailsProgramDialog();
    void browseWgetProgramDialog();
    void browsePSftpProgramDialog();
};

#endif
