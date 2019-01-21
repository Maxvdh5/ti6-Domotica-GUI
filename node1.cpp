#include "node1.h"
#include "ui_node1.h"
#include "mainwindow.h"
#include <QPixmap>
#include <QXmlStreamWriter>

node1::node1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::node1)
{
    ui->setupUi(this);

    QPixmap Close("D:/ProjectBLK6/GUI_Domotica/close.png");
    ui->closeButton->setIcon(Close);
}

node1::~node1()
{
    delete ui;
}

void node1::on_closeButton_clicked()
{
deleted();
}

void node1::deleted(){
    ui->DeletedLbl->setText("(deleted)");
    deleteMe = true;
}

void node1::changeHeader(QString header){
    ui->Header->setText(header);

}

void node1::changeStatus(int status){
    //TODO hier code voor een node die standby staat
    if(status == 1){
        this->status = 1;
        ui->ActivateButton->setText("deactivated");
    }
    if(status == 2){
        this->status = 2;
         ui->ActivateButton->setText("Activated");
    }

}

void node1::changeRole(int role){
        if(role == 2){
            ui->PhotoLbl->setText("Sensor");
            ui->RoleButton->setText("Sensor");
        }
        else if(role == 1){
            ui->PhotoLbl->setText("Actuator");
            ui->RoleButton->setText("Actuator");
            ui->ModeCB->setEnabled(false);
            ui->SimulateButton->setEnabled(false);
        }
}

void node1::changeGroup1(int G1){
       ui->Group1CB->setCurrentText(QString::number(G1));
}

void node1::changeGroup2(int G2){
       ui->Group2CB->setCurrentText(QString::number(G2));
}

void node1::changeMode(int M){
    if  (M==1){
        ui->ModeCB->setCurrentText("None");
    }
    else if(M == 2){
         ui->ModeCB->setCurrentText("Off");
    }
    else if(M == 3){
        ui->ModeCB->setCurrentText("Red");
    }
    else if(M==4){
        ui->ModeCB->setCurrentText("Green");
    }
    else if(M==5){
        ui->ModeCB->setCurrentText("Blue");
    }

}

void node1::on_RoleButton_clicked()
{
    if(ui->RoleButton->text()=="Sensor"){
        ui->PhotoLbl->setText("Actuator");
        ui->RoleButton->setText("Actuator");
        ui->ModeCB->setEnabled(false);
        ui->SimulateButton->setEnabled(false);
    }
    else if(ui->RoleButton->text()=="Actuator"){
        ui->PhotoLbl->setText("Sensor");
        ui->RoleButton->setText("Sensor");
        ui->ModeCB->setEnabled(true);
        ui->SimulateButton->setEnabled(true);
    }
}

QString node1::getHeader(){
    return( ui->Header->text());
}

QString node1::getStatus(){
    return( QString::number(this->status));
}

bool node1::getDeleted(){
    return ( deleteMe);
}

QString node1::getRole(){
   if(ui->RoleButton->text() == "Actuator") {
       return("1");
   }
   else if(ui->RoleButton->text() == "Sensor") {
       return("2");
   }

}

QString node1::getGroup1(){
    return(ui->Group1CB->currentText());
}

QString node1::getGroup2(){
    return( ui->Group2CB->currentText());
}

QString node1::getMode(){
    if(ui->ModeCB->currentText()== "None"){
       return("1");
       }
       else if(ui->ModeCB->currentText()== "Off"){
       return("2");
       }
       else if(ui->ModeCB->currentText()== "Red"){
       return("3");
       }
       else if(ui->ModeCB->currentText()== "Green"){
       return("4");
       }
       else if(ui->ModeCB->currentText()== "Blue"){
       return("5");
    }
}

//QString node1::setadres(QString adres)
//{
  //  adres = adres;
//}

void node1::on_ActivateButton_clicked()
{
    if(this->status == 1){
        changeStatus(2);
    }
    else if(this->status == 2){
        changeStatus(1);
    }
}

void node1::on_SimulateButton_clicked()
{
    QString xml;
    QXmlStreamWriter xmlWriter( &xml );

    xmlWriter.writeStartElement("messagetype");
    xmlWriter.writeCharacters("sendsignal");
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("groups");

    if(getGroup1() != "None"){
    xmlWriter.writeStartElement("group");
    xmlWriter.writeCharacters(getGroup1());
    xmlWriter.writeEndElement();//Group1
    }

    if(getGroup2() != "None"){
    xmlWriter.writeStartElement("group");
    xmlWriter.writeCharacters(getGroup2());
    xmlWriter.writeEndElement();//Group2
    }

    xmlWriter.writeEndElement();//Groups

    xmlWriter.writeStartElement("signal");
    xmlWriter.writeCharacters(getMode());
    xmlWriter.writeEndElement();//signal


    xml = "xml="+xml;
    qDebug()<<xml;

        QUrl serviceUrl = QUrl(this->adres);
          QString postData = (xml);

          QNetworkRequest request(serviceUrl);
          QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);

          connect(networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));
          connect(networkManager,SIGNAL(finished(QNetworkReply*)),networkManager,SLOT(deleteLater()));

          networkManager->post(request, postData.toUtf8());



}

void node1::onfinish(QNetworkReply *reply)
{
    qDebug()<<reply->readAll();
}
