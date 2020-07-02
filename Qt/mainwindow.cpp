#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , form_doubler(new Form_Doubler)
    , form_guess_the_number(new Form_GuessTheNumber)
    , form_vacation(new Form_Vacation)
    , msg_box(new QMessageBox)
    , form_believe_or_not(new Form_BelieveOrNot)
{
    ui->setupUi(this);    
    this->setFixedSize(this->width(), this->height());

    connect(form_doubler, &Form_Doubler::ShowMainWindow, this, &MainWindow::show);
    connect(form_guess_the_number, &Form_GuessTheNumber::ShowMainWindow, this, &MainWindow::show);
    connect(form_vacation, &Form_Vacation::ShowMainWindow, this, &MainWindow::show);
    connect(form_believe_or_not, &Form_BelieveOrNot::ShowMainWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete form_doubler;
    delete form_guess_the_number;
    delete form_vacation;
    delete msg_box;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_pushButton_doubler_clicked()
{
    msg_box->setText("Компьютер загадал случайное число.\n"
                    "Вам необходимо его достичь за минимальное количество шагов.");
    msg_box->setWindowTitle("Doubler");

    msg_box->show();
    form_doubler->show();
    this->close();
}

void MainWindow::on_pushButton_guessthenumber_clicked()
{
    msg_box->setText("Компьютер загадал случайное число.\n"
                    "Вам необходимо его отгадать.");
    msg_box->setWindowTitle("Guess the Number");

    msg_box->show();
    form_guess_the_number->show();
    this->close();
}

void MainWindow::on_pushButton_Vacation_clicked()
{
    msg_box->setText("Заявление на отпуск");
    msg_box->setWindowTitle("Vacation");

    msg_box->show();
    form_vacation->show();
    this->close();
}

void MainWindow::on_pushButton_believe_or_not_clicked()
{
    msg_box->setText("Верю - не Верю");
    msg_box->setWindowTitle("Believe or not");

    msg_box->show();
    form_believe_or_not->show();
    this->close();
}
