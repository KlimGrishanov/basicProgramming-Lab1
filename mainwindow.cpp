#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_one, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("1");});
    connect(ui->btn_two, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("2");});
    connect(ui->btn_three, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("3");});
    connect(ui->btn_four, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("4");});
    connect(ui->btn_five, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("5");});
    connect(ui->btn_six, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("6");});
    connect(ui->btn_seven, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("7");});
    connect(ui->btn_eight, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("8");});
    connect(ui->btn_nine, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("9");});
    connect(ui->btn_zero, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("0");});
    connect(ui->btn_clear, &QPushButton::clicked, this, &MainWindow::on_btn_clear_clicked);
    connect(ui->btn_dot, &QPushButton::clicked, this, &MainWindow::on_btn_dot_clicked);
    connect(ui->btn_del, &QPushButton::clicked, this, &MainWindow::on_btn_del_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::get_calc_label(){
    return ui->lbl_calc_line->text();
}

void MainWindow::set_calc_label(QString new_label){
    ui->lbl_calc_line->setText(new_label);
}

void MainWindow::set_btn_dot_enabled(bool status){
    ui->btn_dot->setEnabled(status);
    if(!status){
        ui->btn_dot->setStyleSheet("color: black; background-color: #2C2C2C; border-radius: 10px;");
    } else {
        ui->btn_dot->setStyleSheet("QPushButton{ background: #2C2C2C; border-radius: 10px;color: white;}QPushButton:hover{background: #5C5C5C;}");
    }
}

void MainWindow::on_btn_numbers_clicked(QString number){
    QString new_label = get_calc_label();
    new_label = new_label + number;
    set_calc_label(new_label);
}

void MainWindow::on_btn_clear_clicked(){
    set_calc_label("");
    set_btn_dot_enabled(1);
}

void MainWindow::on_btn_dot_clicked(){
    QString new_label = get_calc_label();
    new_label = new_label + ".";
    set_calc_label(new_label);
    set_btn_dot_enabled(0);
}

void MainWindow::on_btn_del_clicked(){
    QString new_label = get_calc_label();
    if((new_label.toStdString())[new_label.length()-1] == '.'){
        set_btn_dot_enabled(1);
    }
    new_label.remove(-1, 1);
    set_calc_label(new_label);
}
