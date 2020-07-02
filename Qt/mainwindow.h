#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "form_doubler.h"
#include "form_guessthenumber.h"
#include "form_vacation.h"
#include "form_believeornot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_pushButton_doubler_clicked();
    void on_pushButton_guessthenumber_clicked();
    void on_pushButton_Vacation_clicked();
    void on_pushButton_believe_or_not_clicked();

private:
    Ui::MainWindow*      ui                     { nullptr };
    Form_Doubler*        form_doubler           { nullptr };
    Form_GuessTheNumber* form_guess_the_number  { nullptr };
    Form_Vacation*       form_vacation          { nullptr };
    QMessageBox*         msg_box                { nullptr };
    Form_BelieveOrNot*   form_believe_or_not    { nullptr };
};
#endif // MAINWINDOW_H
