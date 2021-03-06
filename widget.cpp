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

    int check = ci.getLoginData(username, password);

    if(check == 0)
    {
        ui->loginPage->hide();
        ui->mainPage->show();
        ui->stackedWidget->addWidget(ui->mainPage);
        ui->stackedWidget->setCurrentWidget(ui->mainPage);

        _username = ci.getUsername();
        ci.getPersonalInformation(_username);
        _name = ci.getName();
        _surname = ci.getSurname();
        QString txt = "Zalogowany jako: " + _name + " " + _surname;
        ui->clientLabel->setText(txt);
        ui->idlabel->setText("Nr klienta: " + _username);
        _balance = ci.getBalance();
        ui->balanceLabel->setNum(_balance);

        QSqlQueryModel * modal = new QSqlQueryModel();
        QSqlQuery qry;
        qry.prepare("SELECT DATE, PERSON, ACCNUMBER, TITLE, KINDOFOPER, AMOUNT FROM transactions WHERE USERNAME='"+username+"' ORDER BY DATE DESC");
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

        ci.getCurrentDate();
        QString loginDate = ci.getLastLoginDate();
        QString finalLoginDate = "Ostatnio zalogowany " + loginDate;
        ui->lastLoginLabel->setText(finalLoginDate);

        ci.udpatelastLoginDate(_username);
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

    _balance = ci.getBalance();
    transactionsLimit = ci.getTransactionsLimit();
    transactions = ci.getTransactions();
    operations = ci.getOperations();
    operationsLimit = ci.getOperationsLimit();
    _accountNumber = ci.getAccountNumber();

    possibleTransactions = transactionsLimit - transactions;
    possibleOperations = operationsLimit - operations;

    currentDate = ti.getCurrentDate();
    ui->balanceLabel_2->setNum(_balance);
    ui->limitHeightLabel->setNum(transactionsLimit);
    ui->limitHeightLabel_2->setNum(operationsLimit);
    ui->limitHeightTranLabel->setNum(possibleTransactions);
    ui->limitHeightOperLabel->setNum(possibleOperations);
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

    transactions = ci.getTransactions();
    operations = ci.getOperations();

    bool check = ti.checkAccountBalance(_balance, amount);

    bool check1 = ti.checkAmount(amountString);
    bool check2 = ti.checkRecipient(recipientString);
    bool check3 = ti.checkRecipient(recipientString);
    bool check4 = ti.checkAccNumber(recipientAccountNumber);

    if(check1 == true && check2 == true && check3 == true && check4 == true)
    {

        if(check == true)
        {
            if(operations < operationsLimit && amount <= possibleTransactions)
            {
                ti.getRecipientData(recipientAccountNumber);
                ti.getSenderData(_name, _username, _surname, _accountNumber, _balance, transactions, operations);
                ti.updateRecipient(amount, recipientAccountNumber);
                ti.updateSender(amount, _accountNumber);
                ti.updateRecipientTransactions(amount, title);
                ti.updateSenderTransactions(amount, title, recipientString);
                ti.updateTransactions(_username, amount);
                ti.updateOperations(_username);

                ui->transferStatusLabel->setText("Przelew wykonany pomyślnie!");
                ui->amountEdit->setText("");
                ui->recipientEdit->setText("");
                ui->titleEdit->setText("");
                ui->accountEdit->setText("");
                amount = 0.0;
                amountString = "";
                recipientString = "";
                title = "";
                recipientAccountNumber = "";

                ci.getPersonalInformation(_username);
                _balance = ci.getBalance();
                transactionsLimit = ci.getTransactionsLimit();
                transactions = ci.getTransactions();
                operations = ci.getOperations();
                operationsLimit = ci.getOperationsLimit();
                _accountNumber = ci.getAccountNumber();

                possibleTransactions = transactionsLimit - transactions;
                possibleOperations = operationsLimit - operations;

                currentDate = ti.getCurrentDate();
                ui->balanceLabel_2->setNum(_balance);
                ui->limitHeightLabel->setNum(transactionsLimit);
                ui->limitHeightLabel_2->setNum(operationsLimit);
                ui->limitHeightTranLabel->setNum(possibleTransactions);
                ui->limitHeightOperLabel->setNum(possibleOperations);
                ui->accountSenderLabel->setText(_accountNumber);
                ui->dateEdit->setText(currentDate);

            }
            else
            {
                ui->transferStatusLabel->setText("Przekroczono dzienny limit wysokości transakcji lub operacji");
                ui->amountEdit->setText("");
                ui->recipientEdit->setText("");
                ui->titleEdit->setText("");
                ui->accountEdit->setText("");
                amount = 0.0;
                amountString = "";
                recipientString = "";
                title = "";
                recipientAccountNumber = "";
            }
        }
        else
        {
            ui->transferStatusLabel->setText("Nie masz wystarczających środków na koncie!");
            ui->amountEdit->setText("");
            ui->recipientEdit->setText("");
            ui->titleEdit->setText("");
            ui->accountEdit->setText("");
            amount = 0.0;
            amountString = "";
            recipientString = "";
            title = "";
            recipientAccountNumber = "";
        }
    }
    else
    {
        ui->transferStatusLabel->setText("Nieodpowiednia wartość w którymś z pól!");
    }

}

void Widget::on_backButton_clicked()
{
    ui->amountEdit->setText("");
    ui->recipientEdit->setText("");
    ui->titleEdit->setText("");
    ui->accountEdit->setText("");
    ui->loginPage->hide();
    ui->mainPage->show();
    ui->stackedWidget->addWidget(ui->mainPage);
    ui->stackedWidget->setCurrentWidget(ui->mainPage);

    ci.getPersonalInformation(_username);
    _balance = ci.getBalance();
    ui->balanceLabel->setNum(_balance);

    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT DATE, PERSON, ACCNUMBER, TITLE, KINDOFOPER, AMOUNT FROM transactions WHERE USERNAME='"+username+"' ORDER BY DATE DESC");
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

void Widget::on_settingsButton_clicked()
{
    ui->mainPage->hide();
    ui->settingsPage->show();
    ui->stackedWidget->addWidget(ui->settingsPage);
    ui->stackedWidget->setCurrentWidget(ui->settingsPage);

    ci.getPersonalInformation(_username);
    _balance = ci.getBalance();
    ui->balanceLabel->setNum(_balance);

    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT DATE, PERSON, ACCNUMBER, TITLE, KINDOFOPER, AMOUNT FROM transactions WHERE USERNAME='"+username+"' ORDER BY DATE DESC");
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

void Widget::on_backSettingsButton_clicked()
{
    ui->passwordStatusLabel->setText("");
    ui->transactionsStatusLabel->setText("");
    ui->operationsStatusLabel->setText("");
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
        ui->transactionsStatusLabel->setText("");
        ui->operationsStatusLabel->setText("");
    }
    else
    {
        ui->passwordStatusLabel->setText("Zmiana hasła nieudana. Spróbuj ponownie!");
        oldPassword="";
        newPassword="";
        ui->oldPasswordEdit->setText("");
        ui->newPasswordEdit->setText("");
        ui->transactionsStatusLabel->setText("");
        ui->operationsStatusLabel->setText("");
    }

}

void Widget::on_limitChangeButton_clicked()
{
    oldLimit = ui->oldTransactionLimitEdit->text();
    newLimit = ui->newTransactionLimitEdit->text();

    bool check = ci.changeTransactionsLimit(_username, oldLimit, newLimit);

    if(check==true)
    {
        ui->transactionsStatusLabel->setText("Pomyślnie zmieniono limit transakcji!");
        oldLimit="";
        newLimit="";
        ui->oldTransactionLimitEdit->setText("");
        ui->newTransactionLimitEdit->setText("");
        ui->passwordStatusLabel->setText("");
        ui->operationsStatusLabel->setText("");
    }
    else
    {
        ui->transactionsStatusLabel->setText("Zmiana limitu transakcji nieudana. Spróbuj ponownie!");
        oldLimit="";
        newLimit="";
        ui->oldTransactionLimitEdit->setText("");
        ui->newTransactionLimitEdit->setText("");
        ui->passwordStatusLabel->setText("");
        ui->operationsStatusLabel->setText("");
    }
}

void Widget::on_limitOperationChangeButton_clicked()
{
    oldOperLimit = ui->oldOperationLimitEdit->text();
    newOperLimit = ui->newOperationLimitEdit->text();

    bool check = ci.changeOperationsLimit(_username, oldOperLimit, newOperLimit);

    if(check==true)
    {
        ui->operationsStatusLabel->setText("Pomyślnie zmieniono limit operacji!");
        oldOperLimit="";
        newOperLimit="";
        ui->oldOperationLimitEdit->setText("");
        ui->newOperationLimitEdit->setText("");
        ui->passwordStatusLabel->setText("");
        ui->transactionsStatusLabel->setText("");
    }
    else
    {
        ui->operationsStatusLabel->setText("Zmiana limitu operacji nieudana. Spróbuj ponownie!");
        oldOperLimit="";
        newOperLimit="";
        ui->oldOperationLimitEdit->setText("");
        ui->newOperationLimitEdit->setText("");
        ui->passwordStatusLabel->setText("");
        ui->transactionsStatusLabel->setText("");
    }
}
