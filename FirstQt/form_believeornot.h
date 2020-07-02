#ifndef FORM_BELIEVEORNOT_H
#define FORM_BELIEVEORNOT_H

#include "question.h"

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class Form_BelieveOrNot;
}

class Form_BelieveOrNot : public QWidget
{
    Q_OBJECT

public:
    explicit Form_BelieveOrNot(QWidget *parent = nullptr);
    ~Form_BelieveOrNot();

signals:
    void ShowMainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_Load_clicked();

    void on_pushButton_Next_clicked();

private:
    Ui::Form_BelieveOrNot*  ui                { nullptr };
    QVector<Question>       questions_;
    qint32                  current_question_ { 0 };
    qint32                  correct_answers_  { 0 };
};

#endif // FORM_BELIEVEORNOT_H
