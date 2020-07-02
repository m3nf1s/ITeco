#include "form_doubler.h"
#include "ui_form_doubler.h"

#include <QCloseEvent>


Form_Doubler::Form_Doubler(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Form_Doubler)
    , result_message_box(new QMessageBox)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());
    SetButtonsFalse();
}

Form_Doubler::~Form_Doubler()
{
    delete ui;
    delete result_message_box;
}

void Form_Doubler::closeEvent(QCloseEvent* event)
{
    ui->label_current_value_number->setNum(0);
    ui->label_final_value_number->setNum(0);
    ui->label_current_steps_number->setNum(0);
    ui->label_minimal_steps_number->setNum(0);
    SetButtonsFalse();

    emit ShowMainWindow();

    event->accept();
}

void Form_Doubler::StartGame(quint16 min_value, quint16 max_value)
{
    doubler.GenerateNewValues(min_value, max_value);

    ui->label_current_value_number->setNum(doubler.GetCurrentValue());
    ui->label_final_value_number->setNum(doubler.GetFinalValue());
    ui->label_current_steps_number->setNum(doubler.GetCurrentCountSteps());
    ui->label_minimal_steps_number->setNum(doubler.GetFinalCountSteps());

    ui->pushButton_Add->setEnabled(true);
    ui->pushButton_Multiply->setEnabled(true);
}

void Form_Doubler::SetButtonsFalse()
{
    ui->pushButton_Add->setEnabled(false);
    ui->pushButton_Multiply->setEnabled(false);
    ui->pushButton_Reset->setEnabled(false);
    ui->pushButton_Cancel->setEnabled(false);
}

void Form_Doubler::CheckCancelResetButtonsTrue()
{
    if(!ui->pushButton_Cancel->isEnabled() || !ui->pushButton_Reset->isEnabled())
    {
        ui->pushButton_Reset->setEnabled(true);
        ui->pushButton_Cancel->setEnabled(true);
    }
}

void Form_Doubler::UpdateLabels()
{
    ui->label_current_value_number->setNum(doubler.GetCurrentValue());
    ui->label_current_steps_number->setNum(doubler.GetCurrentCountSteps());
}

void Form_Doubler::CheckGame()
{
    if(doubler.GetCurrentValue() == doubler.GetFinalValue())
    {
        if(doubler.GetCurrentCountSteps() == doubler.GetFinalCountSteps())
        {
            result_message_box->setWindowTitle("Win");
            result_message_box->setText("Молодец! Вы справились!");
        }
        else
        {
            result_message_box->setWindowTitle("Win");
            result_message_box->setText("Вы справились.");
        }
        SetButtonsFalse();
        result_message_box->show();
    }

    if(doubler.GetCurrentValue() > doubler.GetFinalValue())
    {
        result_message_box->setWindowTitle("Lose");
        result_message_box->setText("Вы проиграли :(");
        SetButtonsFalse();
        result_message_box->show();
    }

}

void Form_Doubler::CheckStackStates()
{
    if(states.empty())
    {
        ui->pushButton_Cancel->setEnabled(false);
        ui->pushButton_Reset->setEnabled(false);
    }
}

void Form_Doubler::on_actionAbout_triggered()
{
    result_message_box->setWindowTitle("Author");
    result_message_box->setText("Derevyanko Andrey");
    result_message_box->show();
}

void Form_Doubler::on_actionEasy_triggered()
{
    StartGame(0, 100);
}

void Form_Doubler::on_actionNormal_triggered()
{
    StartGame(0, 256);
}

void Form_Doubler::on_actionHard_triggered()
{
    StartGame(0, 512);
}

void Form_Doubler::on_pushButton_Add_clicked()
{
    ++doubler.GetCurrentValue();
    ++doubler.GetCurrentCountSteps();
    UpdateLabels();
    states.push_back(States::ADD);
    CheckCancelResetButtonsTrue();
    CheckGame();
}

void Form_Doubler::on_pushButton_Multiply_clicked()
{
    doubler.GetCurrentValue() *= 2;
    ++doubler.GetCurrentCountSteps();
    UpdateLabels();
    states.push_back(States::MULTIPLY);
    CheckCancelResetButtonsTrue();
    CheckGame();
}

void Form_Doubler::on_pushButton_Reset_clicked()
{
    doubler.GetCurrentValue() = 1;
    ++doubler.GetCurrentCountSteps();
    states.clear();
    UpdateLabels();
    CheckStackStates();
}

void Form_Doubler::on_pushButton_Cancel_clicked()
{
    if(states.back() == States::ADD)
    {
        --doubler.GetCurrentValue();
        ++doubler.GetCurrentCountSteps();
        UpdateLabels();
    }

    if(states.back() == States::MULTIPLY)
    {
        doubler.GetCurrentValue() /= 2;
        ++doubler.GetCurrentCountSteps();
        UpdateLabels();
    }

    states.pop_back();
    CheckStackStates();
}
