#ifndef FORM_GUESSTHENUMBER_H
#define FORM_GUESSTHENUMBER_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class Form_GuessTheNumber;
}

class Form_GuessTheNumber : public QWidget
{
    Q_OBJECT

public:
    explicit Form_GuessTheNumber(QWidget *parent = nullptr);
    ~Form_GuessTheNumber();

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void ShowMainWindow();

private slots:
    void on_pushButton_New_Game_clicked();

    void on_pushButton_Apply_clicked();

private:
    Ui::Form_GuessTheNumber* ui              { nullptr };
    QMessageBox*             msg             { nullptr };
    quint16                  number_         { 0 };
    quint16                  count_attempts_ { 0 };
};

#endif // FORM_GUESSTHENUMBER_H
