#ifndef SETNAMEDIALOG_H
#define SETNAMEDIALOG_H

#include <QDialog>
#include "mcu.h"

namespace Ui {
class SetNameDialog;
}

class SetNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetNameDialog(QWidget *parent = 0);
    ~SetNameDialog();

    void accept();

private:
    Ui::SetNameDialog *ui;
    MCUs *mcus;
};

#endif // SETNAMEDIALOG_H
