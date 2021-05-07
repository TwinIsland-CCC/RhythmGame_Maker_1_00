#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    connect(ui->pushButton,&QPushButton::clicked,[=](){

//        QString path = QFileDialog::getOpenFileName(this,"打开");

//        ui->lineEdit->setText(path);

//        QFile file(path);

//        file.open(QIODevice::ReadWrite);

//        QTextCodec* codec = QTextCodec::codecForName("ansi");

//        QByteArray array = file.readAll();
//        //ui->textEdit->setText(array);
//        ui->textEdit->setText(codec->toUnicode(array));
//    });

        player = new QMediaPlayer;
        player->setVolume(50);

    connect(ui->ChooseMusBtn,&QPushButton::clicked,[=](){
        QString path = QFileDialog::getOpenFileName(this,"打开");
        qDebug()<<path;
        ui->lineEdit_2->setText(path);
        player->setMedia(QUrl(path));
        //nameofsong = path;
    });

    connect(ui->BPMSetBtn,&QPushButton::clicked,[=](){
        BPM = (ui->BPMInput->text()).toInt();
    });

    connect(ui->PlayMusBtn,&QPushButton::clicked,[=](){
        player->play();
    });



    connect(ui->PauseMusBtn,&QPushButton::clicked,[=](){
        player->pause();
    });

    connect(ui->StartBtn,&QPushButton::clicked,[=](){
        player->stop();
        player->play();
        bgtimer->start(1);
        //caltimer->start();
    });

    connect(ui->PauseBtn,&QPushButton::clicked,this,[=](){
        bgtimer->stop();
        player->pause();


    });

    connect(ui->ResumeBtn,&QPushButton::clicked,[=]()
    {
        player->play();
        bgtimer->start(1);

    });

    connect(bgtimer,&QTimer::timeout,[=]()
    {
        ui->label2->setText(QString::number(flag++));
    });

    connect(player,&QMediaPlayer::stateChanged,[=](){
        if(player->state() == QMediaPlayer::StoppedState)
        {
            ui->label3->setText("打谱结束~");
            bgtimer->stop();
        }
    });

    connect(ui->ReStartBtn,&QPushButton::clicked,[=](){
        player->stop();
        player->play();
        flag = 0;
        key_num = 0;
        ui->label2->setText(QString::number(0));
        bgtimer->start(1);
        //caltimer->start();
    });

    connect(ui->StopBtn,&QPushButton::clicked,[=](){
        player->stop();
        bgtimer->stop();
        flag = 0;
        key_num = 0;
        ui->label2->setText(QString::number(0));
    });

    connect(ui->OutBtn,&QPushButton::clicked,[=](){
        QString filename="../table/"+nameofsong+".txt";
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly))
            {
                ui->label3->setText("导出中...");
                QTextStream stream(&file);
                for (QString :: iterator it = notes.begin(); it != notes.end();++it){
                    qDebug()<<"正在导出";
                    stream << *it;
                }
                file.close();
            }
        ui->label3->setText("导出成功！");
    });



//           m_file.setFileName(QString("%1").arg(m_udpconfig.SavePath)+QString("/%1.txt").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz")));   //文件的保存路径   按照年月日时分秒格式
//            if(!m_file.open(QIODevice::WriteOnly|QIODevice::Text))
//            {
//                QMessageBox::critical(NULL,"提示","无法创建文件");
//                return;
//            }else{
//                QTextStream stream( &m_file );//开始写入文本
//                stream<<"radarStatus:"<<dataInfo.RadarStatus.radarStatus<<endl;
//                //你的写入操作
//                m_file.flush();
//            }
//            m_file.close();

//    });




}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        switch(event->key())
        {
        case Qt::Key_Z:
            ui->label3->setText("有效");
            key_num++;
            notes+=(QString::number(key_num)+" Z "+QString::number(flag)+"\n");
            ui->textEdit->setText(notes);

            break;

        case Qt::Key_X:
            ui->label3->setText("有效");
            key_num++;
            notes+=(QString::number(key_num)+" X "+QString::number(flag)+"\n");
            ui->textEdit->setText(notes);
            break;

        case Qt::Key_C:
            ui->label3->setText("有效");
            key_num++;
            notes+=(QString::number(key_num)+" C "+QString::number(flag)+"\n");
            ui->textEdit->setText(notes);
            break;

        case Qt::Key_V:
            ui->label3->setText("有效");
            key_num++;
            notes+=(QString::number(key_num)+" V "+QString::number(flag)+"\n");
            ui->textEdit->setText(notes);
            break;

        default:
            ui->label3->setText("无效");
            break;
        }
    }
}


//void MainWindow::timerEvent(QTimerEvent* t){
//    static int num1 = 1,num2 = 1;
//    //判断
//    if(t->timerId() == id1)ui->label2->setText(QString::number(num1++));
//    if(t->timerId() == id2)ui->label3->setText(QString::number(num2++));
//}
