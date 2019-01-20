#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "node1.h"
#include "nodecontainer.h"

#include <QHBoxLayout>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int nodes = 0;
    int first = 0;
    QHBoxLayout * scroll;

private slots:
    void on_ApplyButton_clicked();

    void on_Syncbutton_clicked();

    void setTime();

    void onfinish(QNetworkReply *reply);

    void onConfirm(QNetworkReply *reply);

    void Readhttp(QString Header,QString Body);

    void WriteHttp();

//    void on_Synctijd_windowIconTextChanged(const QString &iconText);

//    void on_Netwerkactief_windowIconTextChanged(const QString &iconText);

private:
    Ui::MainWindow *ui;
    node1 node;
    nodeContainer cont;

};

#endif // MAINWINDOW_H
