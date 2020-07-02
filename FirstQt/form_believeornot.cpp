#include "form_believeornot.h"
#include "ui_form_believeornot.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QFile>
#include <QtXml>

Form_BelieveOrNot::Form_BelieveOrNot(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form_BelieveOrNot)

{
    ui->setupUi(this);
    ui->checkBox->setChecked(false);
    ui->pushButton_Next->setEnabled(false);
}

Form_BelieveOrNot::~Form_BelieveOrNot()
{
    delete ui;
}

void Form_BelieveOrNot::closeEvent(QCloseEvent *event)
{
    questions_.clear();
    correct_answers_  = 0;
    current_question_ = 0;
    ui->textBrowser->setText("");
    ui->checkBox->setChecked(false);
    ui->pushButton_Next->setEnabled(false);
    emit ShowMainWindow();
    event->accept();
}

void Form_BelieveOrNot::on_pushButton_Load_clicked()
{
    questions_.clear();
    QString filename = QFileDialog::getOpenFileName(this, tr("Open xml"), tr("*.xml"));

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Warning", "File not open");
    }

    QXmlStreamReader xml;
    xml.setDevice(&file);
    while(!xml.atEnd())
    {
        QXmlStreamReader::TokenType type = xml.readNext();
        switch (type)
        {
            case QXmlStreamReader::StartElement:
            {
                if(xml.name().toString() == "Text")
                {
                    xml.readNext();
                    questions_.push_back( {xml.text().toString(), false} );
                }

                if(xml.name().toString() == "Answer")
                {
                    xml.readNext();
                    questions_.back().answer = xml.text().toString() == "true";
                }
                break;
            }
        }
    }

    if(!questions_.isEmpty())
    {
        current_question_ = 0;
        correct_answers_  = 0;
        ui->pushButton_Next->setEnabled(true);
        ui->textBrowser->setText(questions_.at(current_question_).question);
    }
}

void Form_BelieveOrNot::on_pushButton_Next_clicked()
{
    if(ui->checkBox->isChecked() == questions_.at(current_question_).answer)
    {
        ++correct_answers_;
    }

    if(questions_.size() - 1 != current_question_)
    {
        ++current_question_;
        ui->textBrowser->setText(questions_.at(current_question_).question);
        ui->checkBox->setChecked(false);
    }

    if(questions_.size() - 1 == current_question_)
    {
        ui->textBrowser->setText("");
        ui->checkBox->setChecked(false);
        ui->pushButton_Next->setEnabled(false);
        QMessageBox::information(this, "End", "Вы набрали: " + QString::number(correct_answers_) + " верных ответов");
    }
}
