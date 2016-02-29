#include <QApplication>
#include <QRegExp>
#include <QRegExpValidator>
#include <QLineEdit>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QDialog>
#include <QPushButton>
#include <QObject>
#include "iplineedit.h"


// source : http://stackoverflow.com/questions/23166283/how-to-set-input-mask-and-qvalidator-to-a-qlineedit-at-a-time-in-qt

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    //QRegExpValidator *pValidator = new QRegExpValidator(regExp);
    //QLineEdit *lineEdit = new QLineEdit();
    //lineEdit->setValidator(new QRegExpValidator(pValidator));
    //lineEdit->setInputMask("000.000.000.000;_");

    //QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    // You may want to use QRegularExpression for new code with Qt 5 (not mandatory).
    //QRegExp ipRegex ("^" + ipRange
    //                 + "\\." + ipRange
    //                 + "\\." + ipRange
    //                 + "\\." + ipRange + "$");
    //QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex);
    //lineEdit->setValidator(ipValidator);
    //lineEdit->show();

    //ipline.show();

    //CustomLineEdit cle;
    //cle.show()gg;

    QDialog dlg;

    QHBoxLayout* layout = new QHBoxLayout;
    CustomIpEditor * ipline = new CustomIpEditor;
    QPushButton* btn = new QPushButton("&Connect");

    layout->addWidget(ipline);
    layout->addWidget(btn);

    QObject::connect(btn, SIGNAL(clicked()), ipline, SLOT(getIp()));

    dlg.setLayout(layout);
    dlg.show();


    return a.exec();
}

