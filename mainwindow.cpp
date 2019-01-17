#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDomDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QString>

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

void MainWindow::on_pushButton_clicked()
{
    QUrl serviceUrl = QUrl("http://pellevangils.nl/post.php");

      QString postData = ("xml=<messagetype>getconfigs</messagetype>");

      QNetworkRequest request(serviceUrl);
      QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
      connect(networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));
      connect(networkManager,SIGNAL(finished(QNetworkReply*)),networkManager,SLOT(deleteLater()));

      networkManager->post(request, postData.toUtf8());
}

void MainWindow::onfinish(QNetworkReply *reply)
{
    qDebug()<<reply->readAll();
//    qDebug()<<"1------------------------------------------------------------------------";
//    QDomDocument* doc = new QDomDocument();
//    doc->setContent(reply);
//    QDomElement docElem = doc->documentElement();
//    QDomNode n = docElem.firstChild();

//    int i = 0;
//    int j = 0;

//    while(!n.isNull()) {
//        QDomElement e = n.toElement(); // try to convert the node to an element.
//        qDebug()<<i;
//        i++;
//        if(!e.isNull()) {
//            qDebug() << qPrintable(e.tagName()) << endl; // the node really is an element.
//            qDebug()<<j;
//            j++;
//        }
//        n = n.nextSibling();
//    }

//    qDebug()<< "end";
}
