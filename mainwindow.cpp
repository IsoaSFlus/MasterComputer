#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qtcomm = new QTComm(this);

    mcus = MCUs::mcus();

    mcus->mcu[0] = new MCU(this, 1);
    mcus->mcu[1] = new MCU(this, 2);
    mcus->mcu[2] = new MCU(this, 3);
    mcus->mcu[3] = new MCU(this, 4);
    mcus->mcu[0]->setName(QString("设备1"));
    mcus->mcu[1]->setName(QString("设备2"));
    mcus->mcu[2]->setName(QString("设备3"));
    mcus->mcu[3]->setName(QString("设备4"));
    this->updateLabel();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->comboBox->addItem(info.portName());
    }

    setNameAction = new QAction(QString("修改设备"),this);
    QMenu *mSetName = menuBar()->addMenu(QString("设置"));
    mSetName->addAction(setNameAction);

    connect(setNameAction, &QAction::triggered, this, &MainWindow::setName);
    connect(qtcomm->mSerialPort, &QSerialPort::readyRead, this, &MainWindow::showLog);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete qtcomm;
    delete mcus;
}

void MainWindow::on_pushButton_clicked()
{
    qtcomm->openSerialPort(ui->comboBox->currentText());
}

void MainWindow::showLog()
{
    bool ok;
    int getInfo = qtcomm->read().toInt(&ok, 10);
    if((getInfo % 11 == 0) && (ok == true) && getInfo <= 33)
    {
        QString log;
        log = QString("  发出警报\n");
        QDateTime  time = QDateTime::currentDateTime();
        QString current_date = time.toString("yyyy-MM-dd hh:mm  ");
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + current_date + mcus->mcu[getInfo/11]->getName() +log);
        ui->textBrowser->moveCursor(QTextCursor::End);
    }
}

void MainWindow::updateLabel()
{
    ui->label->setText(mcus->mcu[0]->getName());
    ui->label_2->setText(mcus->mcu[1]->getName());
    ui->label_3->setText(mcus->mcu[2]->getName());
    ui->label_4->setText(mcus->mcu[3]->getName());
}

void MainWindow::setName()
{
    SetNameDialog *dialog = new SetNameDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("修改设备名称"));
    dialog->exec();
    updateLabel();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QFile data("log.txt");
    if (data.open(QFile::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&data);
        out << ui->textBrowser->toPlainText();
    }
    data.close();
}
