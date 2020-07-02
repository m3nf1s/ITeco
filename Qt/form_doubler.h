#ifndef FORM_DOUBLER_H
#define FORM_DOUBLER_H

#include "doubler.h"
#include "states.h"

#include <QMainWindow>
#include <QWidget>
#include <QVector>
#include <QMessageBox>

namespace Ui {
class Form_Doubler;
}

class Form_Doubler : public QMainWindow
{
    Q_OBJECT

public:
    explicit Form_Doubler(QWidget *parent = nullptr);
    ~Form_Doubler();

signals:
    void ShowMainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_actionAbout_triggered();
    void on_actionEasy_triggered();
    void on_actionNormal_triggered();
    void on_actionHard_triggered();
    void on_pushButton_Add_clicked();
    void on_pushButton_Multiply_clicked();
    void on_pushButton_Reset_clicked();
    void on_pushButton_Cancel_clicked();

private:
    void StartGame(quint16 min_value, quint16 max_value);
    void SetButtonsFalse();
    void CheckCancelResetButtonsTrue();
    void UpdateLabels();
    void CheckGame();
    void CheckStackStates();

    Ui::Form_Doubler* ui                 { nullptr };
    QMessageBox*      result_message_box { nullptr };
    Doubler           doubler;
    QVector<States>   states;
};

#endif // FORM_DOUBLER_H
