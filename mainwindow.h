#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QStringList>
#include <QStringListIterator>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QLineEdit>
#include <QFile>
#include <QKeyEvent>
#include <QTextCodec>
#include <QMediaPlayer>
#include <QElapsedTimer>
#include <QTimer>
#include <QLabel>

#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QMediaPlayer* player;
    QTimer* bgtimer = new QTimer(this);
    //QElapsedTimer* caltimer = new QElapsedTimer;

    //void timerEvent(QTimerEvent* t);
//    int id1 = 0;
//    int id2 = 0;
    int flag = 0;
    int BPM = 0;
    int key_num = 0;
    int current_beat = 0;
    QString nameofsong;
    QString notes;

    void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
