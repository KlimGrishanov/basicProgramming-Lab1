#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

#define STR_LENGTH 30
#define EMPTY 0
#define PRECISION 7

#define PLUS 1
#define MINUS 2
#define MULTIPLY 3
#define DIVIDE 4


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    double calc_memory = EMPTY;
    int last_action = EMPTY;
    bool isResult = false;

    Ui::MainWindow *ui;

    QString get_calc_label();
    QString validation_label(QString str);
    void set_base_stylesheet();
    void action_in_calc_memory(double number);
    void set_calc_label(QString new_label);
    void set_btn_dot_enabled(bool status);
    void on_btn_change_sign_clicked();
    void on_btn_numbers_clicked(QString number);
    void on_btn_clear_clicked();
    void on_btn_dot_clicked();
    void on_btn_del_clicked();
    void on_btn_multiply_clicked();
    void on_btn_plus_clicked();
    void on_btn_divide_clicked();
    void on_btn_minus_clicked();
    void on_btn_equls_clicked();
};
#endif // MAINWINDOW_H
