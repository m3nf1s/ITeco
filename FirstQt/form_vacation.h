#ifndef FORM_VACATION_H
#define FORM_VACATION_H

#include <QWidget>

namespace Ui {
class Form_Vacation;
}

class Form_Vacation : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Vacation(QWidget *parent = nullptr);
    ~Form_Vacation();

signals:
   void ShowMainWindow();

private slots:
   void on_pushButton_clicked();

private:
    Ui::Form_Vacation* ui { nullptr };
};

#endif // FORM_VACATION_H
