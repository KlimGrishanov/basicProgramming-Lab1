#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Define const vars for Lab
#define STR_LENGTH 30
#define EMPTY 0
#define PRECISION 7

// Define const int for sign (like-enum)
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
    // Calc memory
    double calc_memory = EMPTY;
    int last_action = EMPTY;
    bool isResult = false;

    // CSS Stylesheets
    QString css_default_sign_btn = "QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}";
    QString css_clicked_sign_btn = "QPushButton {background: #808080; border-radius: 10px;color: #FFFFFF;font-weight: 600;}";

    Ui::MainWindow *ui;

    // Utlities
    QString get_calc_label();
    void set_calc_label(QString new_label);

    // Validation, catch errors
    QString validation_label(QString str);

    // Set CSS stylesheets
    void set_css_btn_sign_base();
    void set_css_btn_sign_clicked(int sign);
    void set_css_btn_dot_enabled(bool status);

    // Math function
    void action_in_calc_memory(double number);

    // SLOTS for clicked buttons (SIGNAL)
    void on_btn_sign_clicked(int sign);
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
