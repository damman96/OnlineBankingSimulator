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
    username = ui->usernameEdit->text();
    password = ui->passwordEdit->text();

    int check = ci.dataLogin(username, password);

    if(check == 0)
    {
        ui->loginPage->hide();
        ui->mainPage->show();
        ui->stackedWidget->addWidget(ui->mainPage);
        ui->stackedWidget->setCurrentWidget(ui->mainPage);

        _name = ci.getName();
        _surname = ci.getSurname();
        QString txt = "Zalogowany jako: " + _name + " " + _surname;
        ui->clientLabel->setText(txt);
        _username = ci.getUsername();
        ui->idlabel->setText("Nr klienta: " + _username);
        _balance = ci.getBalance();
        QString _balanceString=QString::number(_balance);
        ui->balanceLabel->setText(_balanceString);

        QSqlQueryModel * modal = new QSqlQueryModel();
        QSqlQuery qry;
        qry.prepare("SELECT DATE, PERSON, ACCNUMBER, TITLE, KINDOFOPER, AMOUNT FROM transactions WHERE USERNAME='"+username+"' ORDER BY DATE ASC");
        qry.exec();
        modal->setQuery(qry);
        modal->setHeaderData(0,Qt::Horizontal,"Data");
        modal->setHeaderData(1,Qt::Horizontal,"Nadawca/ Odbiorca");
        modal->setHeaderData(2,Qt::Horizontal,"Nr konta");
        modal->setHeaderData(3,Qt::Horizontal,"Tytuł");
        modal->setHeaderData(4,Qt::Horizontal,"Rodzaj operacji");
        modal->setHeaderData(5,Qt::Horizontal,"Kwota");
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
    ui->mainPage->hide();
    ui->loginPage->show();
    ui->stackedWidget->addWidget(ui->loginPage);
    ui->stackedWidget->setCurrentWidget(ui->loginPage);

    ui->errorLabel->setText("Wylogowano pomyślnie!");
    username = "";
    password = "";
    ui->usernameEdit->setText("");
    ui->passwordEdit->setText("");

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
    _accountNumber = ci.getAccountNumber();

    currentDate = ti.getCurrentDate();
    ui->balanceLabel_2->setText(_balanceString);
    ui->limitHeightLabel->setText(_transactionsLimitString);
    ui->limitHeightLabel_2->setText(_operationsLimitString);
    ui->accountSenderLabel->setText(_accountNumber);
    ui->dateEdit->setText(currentDate);    
}

void Widget::on_makeTransferButton_clicked()
{
    amountString = ui->amountEdit->text();
    amount = amountString.toDouble();
    recipientString = ui->recipientEdit->text();
    title = ui->titleEdit->text();
    recipientAccountNumber = ui->accountEdit->text();

    ti.getRecipientData(recipientAccountNumber);
    ti.getSenderData(_name, _username, _surname, _accountNumber, _balance);
    ti.updateRecipient(amount, recipientAccountNumber);
    ti.updateSender(amount, _accountNumber);
    ti.updateRecipientTransactions(amount, title);
    ti.updateSenderTransactions(amount, title, recipientString);
}

void Widget::on_backButton_clicked()
{
    ui->transferPage->hide();
    ui->mainPage->show();
    ui->stackedWidget->addWidget(ui->mainPage);
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

void Widget::on_settingsButton_clicked()
{
    ui->mainPage->hide();
    ui->settingsPage->show();
    ui->stackedWidget->addWidget(ui->settingsPage);
    ui->stackedWidget->setCurrentWidget(ui->settingsPage);
}

void Widget::on_backSettingsButton_clicked()
{
    ui->settingsPage->hide();
    ui->mainPage->show();
    ui->stackedWidget->addWidget(ui->mainPage);
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

void Widget::on_passwordChangeButton_clicked()
{
    oldPassword = ui->oldPasswordEdit->text();
    newPassword = ui->newPasswordEdit->text();

    bool check = ci.changePassword(password, oldPassword, newPassword);

    if(check==true)
    {
        ui->passwordStatusLabel->setText("Pomyślnie zmieniono hasło!");
        oldPassword="";
        newPassword="";
        ui->oldPasswordEdit->setText("");
        ui->newPasswordEdit->setText("");
    }
    else
    {
        ui->passwordStatusLabel->setText("Zmiana hasła nieudana. Spróbuj ponownie!");
        oldPassword="";
        newPassword="";
        ui->oldPasswordEdit->setText("");
        ui->newPasswordEdit->setText("");
    }

}
