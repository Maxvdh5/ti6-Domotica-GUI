#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodecontainer.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QtGui>
#include <QString>
#include <QPixmap>
#include <QTextDocument>
#include <QXmlStreamReader>
#include <QTemporaryFile>
#include <QDomDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ApplyButton_clicked()
{
   Readhttp("setConfig",cont.writeXML());

}

void MainWindow::on_Syncbutton_clicked()
{

    Readhttp("getConfig","xml=<messagetype>getconfigs</messagetype>");
    setTime();

}

void MainWindow::setTime()
{
    QDateTime local(QDateTime::currentDateTime());
    QString time = local.toString("dd:MM:yyyy hh:mm:ss");
    ui->Synctijd_2->setText(time);
}

void MainWindow::WriteHttp(){
    QLayoutItem *child;
    while((child = scroll->takeAt(0))!= 0) {
        delete child->widget();
        delete child;
    }
    delete scroll;
}

void MainWindow::Readhttp(QString Header,QString Body){
    QUrl serviceUrl = QUrl(this->adres);
        qDebug()<<this->adres;
        qDebug()<<Header;
        QString postHeader = (Header);
      QString postData = (Body);


      if(postHeader == "getConfig"){
      QNetworkRequest request(serviceUrl);
      QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);

      connect(networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));
      connect(networkManager,SIGNAL(finished(QNetworkReply*)),networkManager,SLOT(deleteLater()));

      networkManager->post(request, postData.toUtf8());
      }
      else if(postHeader == "setConfig"){
          QNetworkRequest request(serviceUrl);
          QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);

          connect(networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onConfirm(QNetworkReply*)));
          connect(networkManager,SIGNAL(finished(QNetworkReply*)),networkManager,SLOT(deleteLater()));

          networkManager->post(request, postData.toUtf8());
          qDebug()<<postData;
          }
 }


void MainWindow::onfinish(QNetworkReply *reply)
{

    QTextDocument doc;
    doc.setHtml(reply->readAll());
    QString test = doc.toPlainText();
    QString noFile = "<xml><messagetype>nodeconfigs</messagetype> <node> <eui64>1385214629631229487</eui64> <status>1</status> <role>1</role> <groups> <group>2</group> </groups> <signal>0</signal> </node> <node> <eui64>1234214629631223412</eui64> <status>2</status> <role>2</role> <groups> <group>1</group> <group>2</group> </groups> <signal>3</signal> </node> <node> <eui64>1234567891234567890</eui64> <status>2</status> <role>1</role> <groups> <group>0</group> </groups> <signal>2</signal> </node></xml>";
    qDebug()<<test;

    //test = "<xml>"+test+"</xml>";

    if (first != 0){
        QLayoutItem *child;
        cont.deleteNodes();
        while((child = scroll->takeAt(0))!= 0) {
            delete child->widget();
            delete child;
        }
        delete scroll;
    }
    first++;

     scroll = new QHBoxLayout(this);
     cont.readXML(noFile);

     for (node1* nodes : cont) {
         scroll->addWidget(nodes);
     }

     ui->scrollAreaWidgetContents->setLayout(scroll);

 }

void MainWindow::onConfirm(QNetworkReply *reply){
    qDebug()<<reply->readAll();
}


void MainWindow::on_pushButton_clicked()
{
    this->adres = ui->adresInput->text();

}
