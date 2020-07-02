#include "form_guessthenumber.h"
#include "ui_form_guessthenumber.h"

#include <QCloseEvent>
#include <QRandomGenerator>
#include <random>
#include <QErrorMessage>

Form_GuessTheNumber::Form_GuessTheNumber(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form_GuessTheNumber)
    , msg(new QMessageBox)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());
    ui->pushButton_Apply->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    msg->setWindowTitle("Win");
    msg->setText("Поздравлаю. Ты угадал число!");
}

Form_GuessTheNumber::~Form_GuessTheNumber()
{
    delete ui;
    delete msg;
}

void Form_GuessTheNumber::closeEvent(QCloseEvent *event)
{
    ui->lineEdit->setText("");
    ui->pushButton_Apply->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    count_attempts_ = 0;
    ui->label_current_attempts->setNum(count_attempts_);
    ui->label_advice->setText("Начни игру :)");

    emit ShowMainWindow();
    event->accept();
}

void Form_GuessTheNumber::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter)
    {
        on_pushButton_Apply_clicked();
    }
}
void Form_GuessTheNumber::on_pushButton_New_Game_clicked()
{
    std::uniform_int_distribution dis(0, 100);
    number_ = dis(*QRandomGenerator::global());

    ui->lineEdit->setText("");
    ui->lineEdit->setEnabled(true);
    ui->pushButton_Apply->setEnabled(true);
    ui->label_advice->setText("А ты не плох ;)");
}

void Form_GuessTheNumber::on_pushButton_Apply_clicked()
{
    bool isConvert = true;
    quint16 value = ui->lineEdit->text().toUShort(&isConvert);

    if(!isConvert)
    {
        QMessageBox::warning(this, "Warning", "Входная строка имела неверный формат");
        ui->label_advice->setText("Что-то пошло не так");
    }
    else
    {
        if(number_ < value)
        {
            ui->label_advice->setText("Число меньше");
        }
        else if(number_ > value)
        {
            ui->label_advice->setText("Число больше");
        }

        ++count_attempts_;
        ui->label_current_attempts->setNum(count_attempts_);

        if(number_ == value)
        {
            ui->label_advice->setText("В точку");
            ui->pushButton_Apply->setEnabled(false);
            ui->lineEdit->setEnabled(false);
            count_attempts_ = 0;
            ui->label_current_attempts->setNum(count_attempts_);

            msg->show();
        }
    }
    ui->lineEdit->setText("");
}
