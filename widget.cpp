#include "widget.h"
#include "ui_widget.h"
#include <QTableWidget>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    if(!db.connection_open())
    {
        ui->statusLabel->setText("Failed");
    }
    else
    {
        ui->statusLabel->setText("Connected");
    }
}

Widget::~Widget()
{
    delete ui;
    db.connection_close();
}

void Widget::on_loginButton_clicked()
{
    QString txt, _name, _surname, _username, _balanceString;
    double _balance;
    username = ui->usernameEdit->text();
    password = ui->passwordEdit->text();
    //zmienic bool na int bo potrzebne wiele przypadkow
    int check = ci.dataLogin(username, password);

    if(check == 0)
    {
        ui->loginPage->hide();
        ui->mainPage->show();
        ui->stackedWidget->addWidget(ui->mainPage);
        ui->stackedWidget->setCurrentWidget(ui->mainPage);

        _name = ci.getName();
        _surname = ci.getSurname();
        txt = "Zalogowany jako: " + _name + " " + _surname;
        ui->clientLabel->setText(txt);
        _username = ci.getUsername();
        ui->idlabel->setText("Nr klienta: " + _username);
        _balance = ci.getBalance();
        _balanceString=QString::number(_balance);
        ui->balanceLabel->setText(_balanceString);

        QSqlQueryModel * modal = new QSqlQueryModel();
        QSqlQuery qry;
        qry.prepare("SELECT DATE, FROM_WHO, TITLE, KIND_OF_OPERATION, AMOUNT FROM transactions WHERE USERNAME='"+username+"'");
        qry.exec();
        modal->setQuery(qry);
        modal->setHeaderData(0,Qt::Horizontal,"Data");
        modal->setHeaderData(1,Qt::Horizontal,"Nadawca/ Odbiorca");
        modal->setHeaderData(2,Qt::Horizontal,"Tytuł");
        modal->setHeaderData(3,Qt::Horizontal,"Rodzaj operacji");
        modal->setHeaderData(4,Qt::Horizontal,"Kwota");
        ui->transactionTable->setModel(modal);
        ui->transactionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    }
    else if(check == -1)
    {
        ui->errorLabel->setText("Zły login lub hasło!");
        username = "";
        password = "";
        ui->usernameEdit->setText("");
        ui->passwordEdit->setText("");
    }
    else if(check==1)
    {
        ui->errorLabel->setText("Zbyt duża liczba błędnych logowań. Spróbuj później!");
        username = "";
        password = "";
        ui->usernameEdit->setText("");
        ui->passwordEdit->setText("");
    }
}


void Widget::on_logoutButton_clicked()
{

}

void Widget::on_transferButton_clicked()
{
    ui->mainPage->hide();
    ui->transferPage->show();
    ui->stackedWidget->addWidget(ui->transferPage);
    ui->stackedWidget->setCurrentWidget(ui->transferPage);

    double _balance = ci.getBalance();
    QString _balanceString = QString::number(_balance);
    int _transactionsLimit = ci.getTransactionsLimit();
    QString _transactionsLimitString = QString::number(_transactionsLimit);
    int _operationsLimit = ci.getOperationsLimit();
    QString _operationsLimitString = QString::number(_operationsLimit);
    ui->balanceLabel_2->setText(_balanceString);
    ui->limitHeightLabel->setText(_transactionsLimitString);
    ui->limitHeightLabel_2->setText(_operationsLimitString);
    QString currentDate = ti.getCurrentDate();
    ui->dateEdit->setText(currentDate);
}

void Widget::on_makeTransferButton_clicked()
{

}
