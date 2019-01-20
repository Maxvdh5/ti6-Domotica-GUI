#ifndef NODE1_H
#define NODE1_H

#include <QWidget>
#include <QNetworkReply>




namespace Ui {
class node1;
}

class node1 : public QWidget
{
    Q_OBJECT

public:
    explicit node1(QWidget *parent = nullptr);
    ~node1();

public slots:
    void changeHeader(QString header);

    void changeStatus(int Status);

    void changeRole(int role);

    void changeGroup1(int G1);

    void changeGroup2(int G2);

    void changeMode(int M);

    void deleted();

    bool getDeleted();

    QString getHeader();

    QString getStatus();

    QString getRole();

    QString getGroup1();

    QString getGroup2();

    QString getMode();




private slots:
    void on_closeButton_clicked();

    void on_RoleButton_clicked();

    void on_ActivateButton_clicked();

    void on_SimulateButton_clicked();

    void onfinish(QNetworkReply*);

private:
    Ui::node1 *ui;

    int status;
    bool deleteMe = false;

};

#endif // NODE1_H
