#ifndef NODECONTAINER_H
#define NODECONTAINER_H
#include <QNetworkReply>
#include "node1.h"

class node1;

class nodeContainer
{
public:
    nodeContainer();
    virtual ~nodeContainer();

    node1** begin();
    node1** end();

    node1 * container[999];
public:
    void addNode();

    void readXML(QString xml);

    void setHeader();

    QString writeXML();

    void deleteNodes();

private:
    int counter = 0;

};

#endif // NODECONTAINER_H
