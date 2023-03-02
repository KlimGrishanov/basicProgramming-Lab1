#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cssWork.h"
#include "bussinessLogic.h"

// Define const vars for Lab
#define STR_LENGTH 30
#define PRECISION 12

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

    Ui::MainWindow *ui;

    // Utlities
    QString get_calc_label();
    void set_calc_label(QString new_label);

    // Validation, catch errors
    QString validation_label(QString str);
    void error_handling (QString str);
    void validation_calc(action_obj temp);

    // Set CSS stylesheets
    void set_default_sign_css();
    void set_clicked_sign_css(int sign);

private slots:
    // SLOTS for clicked buttons (SIGNAL)
    void on_btn_sign_clicked(int sign);
    void on_btn_change_sign_clicked();
    void on_btn_numbers_clicked(QString number);
    void on_btn_clear_clicked();
    void on_btn_dot_clicked();
    void on_btn_del_clicked();
    void on_btn_equls_clicked();
};
#endif // MAINWINDOW_H
