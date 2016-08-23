#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("IsoaSFlus");
    QCoreApplication::setOrganizationDomain("isoasflus.me");
    QCoreApplication::setApplicationName(tr("智能安防系统"));

    qtcomm = new QTComm(this);

    mcus = MCUs::mcus();

    mcus->mcu[0] = new MCU(this, 1);
    mcus->mcu[1] = new MCU(this, 2);
    mcus->mcu[2] = new MCU(this, 3);
    mcus->mcu[3] = new MCU(this, 4);
//    mcus->mcu[0]->setName(QString("设备1"));
//    mcus->mcu[1]->setName(QString("设备2"));
//    mcus->mcu[2]->setName(QString("设备3"));
//    mcus->mcu[3]->setName(QString("设备4"));
    readSettings();
    this->updateLabel();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->comboBox->addItem(info.portName());
    }

    setNameAction = new QAction(QString("修改设备"),this);
    QMenu *mSetName = menuBar()->addMenu(QString("设置"));
    mSetName->addAction(setNameAction);

    //安装事件过滤器
    ui->label_5->installEventFilter(this);
    ui->label_6->installEventFilter(this);
    ui->label_7->installEventFilter(this);
    ui->label_8->installEventFilter(this);

    fade[0] = new FadeAnimation(this, ui->label_5);
    fade[1] = new FadeAnimation(this, ui->label_6);
    fade[2] = new FadeAnimation(this, ui->label_7);
    fade[3] = new FadeAnimation(this, ui->label_8);

    QFile data(QApplication::applicationDirPath()+"\/log.txt");
    if (data.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&data);
        QString str;
        str = in.readAll();
        ui->textBrowser->setText(str);
        ui->textBrowser->moveCursor(QTextCursor::End);
    }
    data.close();

    connect(setNameAction, &QAction::triggered, this, &MainWindow::setName);
    connect(qtcomm->mSerialPort, &QSerialPort::readyRead, this, &MainWindow::showLog);
//    ui->label_5->setPixmap(QPixmap().fromImage(QImage(":/img/red")));
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
        this->buf += current_date + mcus->mcu[getInfo/11]->getName() +log;
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + current_date + mcus->mcu[getInfo/11]->getName() +log);
        ui->textBrowser->moveCursor(QTextCursor::End);
        setAlert(getInfo/11 +1);

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
    QFile data(QApplication::applicationDirPath()+"\/log.txt");
    if (data.open(QFile::ReadWrite | QIODevice::Append)) {
        QTextStream out(&data);
//        out << ui->textBrowser->toPlainText();
        out << buf;
        qDebug()<<"write success";
    }
    data.close();
    writeSettings();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(obj == ui->label_5)
        {
//            ui->label_5->setPixmap(QPixmap().fromImage(QImage(":/img/gray")));
            fade[0]->stop();
            qDebug()<<"success";
            return true;
        }
        if(obj == ui->label_6)
        {
//            ui->label_6->setPixmap(QPixmap().fromImage(QImage(":/img/gray")));
            fade[1]->stop();
            qDebug()<<"success";
            return true;
        }
        if(obj == ui->label_7)
        {
//            ui->label_7->setPixmap(QPixmap().fromImage(QImage(":/img/gray")));
            fade[2]->stop();
            qDebug()<<"success";
            return true;
        }
        if(obj == ui->label_8)
        {
//            ui->label_8->setPixmap(QPixmap().fromImage(QImage(":/img/gray")));
            fade[3]->stop();
            qDebug()<<"success";
            return true;
        }
        return false;
    }
    else
        return QMainWindow::eventFilter(obj, event);

}

void MainWindow::setAlert(int n)
{
    switch (n) {
    case 1:
//        ui->label_5->setPixmap(QPixmap().fromImage(QImage(":/img/red")));
        fade[0]->start();
        break;
    case 2:
//        ui->label_6->setPixmap(QPixmap().fromImage(QImage(":/img/red")));
        fade[1]->start();
        break;
    case 3:
//        ui->label_7->setPixmap(QPixmap().fromImage(QImage(":/img/red")));
        fade[2]->start();
        break;
    case 4:
//        ui->label_8->setPixmap(QPixmap().fromImage(QImage(":/img/red")));
        fade[3]->start();
        break;
    default:
        break;
    }
}

void MainWindow::writeSettings()
{
    mcus = MCUs::mcus();
    QSettings settings;

    settings.beginGroup("DeviceName");
    settings.setValue("1", mcus->mcu[0]->getName());
    settings.setValue("2", mcus->mcu[1]->getName());
    settings.setValue("3", mcus->mcu[2]->getName());
    settings.setValue("4", mcus->mcu[3]->getName());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    mcus = MCUs::mcus();
    QSettings settings;

    settings.beginGroup("DeviceName");
    mcus->mcu[0]->setName(settings.value("1", "设备1").toString());
    mcus->mcu[1]->setName(settings.value("2", "设备2").toString());
    mcus->mcu[2]->setName(settings.value("3", "设备3").toString());
    mcus->mcu[3]->setName(settings.value("4", "设备4").toString());
    settings.endGroup();
}
