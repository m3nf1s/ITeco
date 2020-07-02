#include "form_vacation.h"
#include "ui_form_vacation.h"
#include "element.h"

#include <QFile>
#include <QMessageBox>

Form_Vacation::Form_Vacation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Vacation)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());
}

Form_Vacation::~Form_Vacation()
{
    delete ui;
}

void Form_Vacation::on_pushButton_clicked()
{
    QVector<Element> elements =
    {
        { "name1", ui->lineEdit_company_name->text()      },
        { "name2", ui->lineEdit_direct_name->text()       },
        { "name3", ui->lineEdit_position->text()          },
        { "name4", ui->lineEdit_full_name_gentive->text() },
        { "name5", ui->lineEdit_full_name->text()         },
        { "data1", ui->dateEdit->date().toString()        },
        { "data2", ui->dateEdit_2->date().toString()      },
        { "data3", ui->dateEdit_3->date().toString()      }
    };

    QFile file("..\\FirstQt\\pattern.txt");
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, "Warning", "Файл не открыт");
    }
    QString data = file.readAll();

    QRegExp reg;
    for(const Element& element : elements)
    {
        reg.setPattern("<" + element.tag + ">");
        data.replace(reg, element.string);
    }

    ui->textEdit->setText(data);
    file.close();
}
