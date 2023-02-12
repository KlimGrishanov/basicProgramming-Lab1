#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    Ui::MainWindow *ui;
    QString get_calc_label();
    void set_calc_label(QString new_label);
    void set_btn_dot_enabled(bool status);
    void on_btn_numbers_clicked(QString number);
    void on_btn_clear_clicked();
    void on_btn_dot_clicked();
    void on_btn_del_clicked();
};
#endif // MAINWINDOW_H
