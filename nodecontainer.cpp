#include "nodecontainer.h"
#include "node1.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

nodeContainer::nodeContainer()
{

}

nodeContainer::~nodeContainer()
{

}


void nodeContainer::deleteNodes(){
    for(int i = 0; i<counter;i++){
        delete container[i];
    }
    counter = 0;
}
node1 **nodeContainer::begin()
{
    return const_cast<node1**>( container );
}

node1 **nodeContainer::end()
{
    return const_cast<node1**>( container+counter );
}


void nodeContainer::addNode(){
    container[counter]= new node1;

}

void nodeContainer::readXML(QString xml)
{

    QXmlStreamReader reader(xml);
     while(!reader.atEnd() && !reader.hasError()) {
    if(reader.readNext() == QXmlStreamReader::StartElement && reader.name() == "node") {
    //node1 *node = new node1;
       addNode();
    qDebug()<<"node";
    reader.readNext();

    while(!(reader.tokenType()== QXmlStreamReader::EndElement && reader.name() == "node")){
        if(reader.tokenType() == QXmlStreamReader::StartElement){
            if(reader.name() == "eui64"){
                reader.readNext();
                qDebug()<<"eui64";
                 container[counter]->changeHeader(reader.text().toString());
            }
            else if(reader.name() == "status"){
                reader.readNext();
                qDebug()<<"status";
                 container[counter]->changeStatus(reader.text().toInt());

             }
            else if(reader.name() == "role"){
                reader.readNext();
                qDebug()<<"role";
                 container[counter]->changeRole(reader.text().toInt());


            }
            else if(reader.name() == "groups"){
                reader.readNext();
                qDebug()<<"groups";
                int groupSelect = 0;
                while(!(reader.tokenType()== QXmlStreamReader::EndElement && reader.name() == "groups")){
                    if(reader.tokenType() == QXmlStreamReader::StartElement){
                        if(reader.name() == "group"){
                            if(groupSelect == 0){
                                reader.readNext();
                                 qDebug()<<"group1";
                                 groupSelect++;
                                container[counter]->changeGroup1(reader.text().toInt());
                            }
                            else if (groupSelect == 1){
                                reader.readNext();
                                 qDebug()<<"group2";
                                 groupSelect++;
                                  container[counter]->changeGroup2(reader.text().toInt());

                            }
                        }
                        else{
                            reader.readNext();
                        }
                }
                    else{
                        reader.readNext();
                    }
                }
            }
            else if(reader.name() == "signal"){
                 reader.readNext();
                 qDebug()<<"signal";
                  container[counter]->changeMode(reader.text().toInt());
            }
            else{
                reader.readNext();
            }

        }
        else{
            reader.readNext();
        }
        }
        counter++;
    }

  }

}

QString nodeContainer::writeXML(){


    QString xml;
    QXmlStreamWriter xmlWriter( &xml );

    xmlWriter.writeStartElement("messagetype");
    xmlWriter.writeCharacters("setconfigs");
    xmlWriter.writeEndElement();


    for(int i=0; i<counter;i++){
        if(container[i]->getDeleted() != true){
    xmlWriter.writeStartElement("node");

    xmlWriter.writeStartElement("eui64");
    xmlWriter.writeCharacters(container[i]->getHeader());
    xmlWriter.writeEndElement();//eui64

    xmlWriter.writeStartElement("status");
    xmlWriter.writeCharacters(container[i]->getStatus());
    xmlWriter.writeEndElement();//Role

    xmlWriter.writeStartElement("role");
    xmlWriter.writeCharacters(container[i]->getRole());
    xmlWriter.writeEndElement();//Role

    xmlWriter.writeStartElement("groups");

    if(container[i]->getGroup1() != "None"){
    xmlWriter.writeStartElement("group");
    xmlWriter.writeCharacters(container[i]->getGroup1());
    xmlWriter.writeEndElement();//Group1
    }

    if(container[i]->getGroup2() != "None"){
    xmlWriter.writeStartElement("group");
    xmlWriter.writeCharacters(container[i]->getGroup2());
    xmlWriter.writeEndElement();//Group2
    }

    xmlWriter.writeEndElement();//Groups

    xmlWriter.writeStartElement("signal");
    xmlWriter.writeCharacters(container[i]->getMode());
    xmlWriter.writeEndElement();//signal

    xmlWriter.writeEndElement();//node
       }
    }
    qDebug()<<xml;
    xml = "xml="+xml;
    return(xml);
}

void nodeContainer::setHeader(){}
