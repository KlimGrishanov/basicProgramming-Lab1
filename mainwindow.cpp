#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <string>

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
    connect(ui->btn_plus, &QPushButton::clicked, this, &MainWindow::on_btn_plus_clicked);
    connect(ui->btn_minus, &QPushButton::clicked, this, &MainWindow::on_btn_minus_clicked);
    connect(ui->btn_multiply, &QPushButton::clicked, this, &MainWindow::on_btn_multiply_clicked);
    connect(ui->btn_divide, &QPushButton::clicked, this, &MainWindow::on_btn_divide_clicked);
    connect(ui->btn_equals, &QPushButton::clicked, this, &MainWindow::on_btn_equls_clicked);
    connect(ui->btn_change_sign, &QPushButton::clicked, this, &MainWindow::on_btn_change_sign_clicked);
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
    QString label = get_calc_label();
    if(label.length() == 1 && number == "0" && label == "0") {
        // except;
    } else if (isResult) {
        set_calc_label(number);
        isResult = false;
    } else if (label.length() == 1 && label == "0") {
        set_calc_label(number);
    } else if(label.length() < STR_LENGTH) {
        label = label + number;
        set_calc_label(label);
    }
}

void MainWindow::on_btn_clear_clicked(){
    set_calc_label("0");
    last_action = EMPTY;
    set_base_stylesheet();
    set_btn_dot_enabled(1);
    isResult = false;
}

void MainWindow::on_btn_dot_clicked(){
    QString new_label = get_calc_label();
    if(isResult){
        set_calc_label("0.");
        isResult = false;
    }else if(new_label.length() == 0){
        set_calc_label("0.");
    }else if(new_label.length() < STR_LENGTH){
        new_label = new_label + ".";
        set_calc_label(new_label);
        set_btn_dot_enabled(0);
    }
}

void MainWindow::on_btn_del_clicked(){
    QString new_label = get_calc_label();
    if(isResult){
        set_calc_label("0");
        set_btn_dot_enabled(1);
    } else {
        new_label.remove(-1, 1);
        set_calc_label(new_label);
    }
}

void MainWindow::action_in_calc_memory(double number) {
    if(last_action == PLUS) {
        //ui -> btn_plus -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
        calc_memory = calc_memory + number;
    } else if (last_action == MINUS) {
        //ui -> btn_minus -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
        calc_memory = calc_memory - number;
    } else if (last_action == MULTIPLY) {
        //ui -> btn_multiply -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
        calc_memory = calc_memory * number;
    } else if (last_action == DIVIDE){
        //ui -> btn_divide -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
        calc_memory = calc_memory / number;
    }
}

void MainWindow::set_base_stylesheet(){
    if(last_action == PLUS) {
        ui -> btn_plus -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
    } else if (last_action == MINUS) {
        ui -> btn_minus -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
    } else if (last_action == MULTIPLY) {
        ui -> btn_multiply -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
    } else if (last_action == DIVIDE){
        ui -> btn_divide -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
    } else {
        ui -> btn_plus -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
        ui -> btn_minus -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
        ui -> btn_multiply -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
        ui -> btn_divide -> setStyleSheet("QPushButton {background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;}QPushButton:hover {background-color: #FF7223;}");
    }
}

void MainWindow::on_btn_plus_clicked() {
    QString label = get_calc_label();
    ui->lbl_calc_line->setText("");
    ui->btn_plus->setStyleSheet("QPushButton {background: #808080; border-radius: 10px;color: #FFFFFF;font-weight: 600;}");
    double number = label.toDouble();
    if(last_action == PLUS && label != ""){
        action_in_calc_memory(number);
    } else if (last_action == PLUS && label == ""){
        // except
    } else if(label == "" && last_action != EMPTY) {
        set_base_stylesheet();
    } else if(last_action == EMPTY) {
        last_action = PLUS;
        calc_memory = number;
    } else {
        set_base_stylesheet();
        action_in_calc_memory(number);
    }
    set_btn_dot_enabled(1);
    printf("%lf", calc_memory);
    last_action = PLUS;
}

void MainWindow::on_btn_minus_clicked() {
    QString label = get_calc_label();
ui->lbl_calc_line->setText("");
    ui->btn_minus->setStyleSheet("QPushButton {background: #808080; border-radius: 10px;color: #FFFFFF;font-weight: 600;}");
    double number = label.toDouble();
    if(last_action == MINUS && label != ""){
        action_in_calc_memory(number);
    }else if ((last_action == MINUS && label == "")){
        // except
    } else if(label == "" && last_action != EMPTY) {
        set_base_stylesheet();
    } else if(last_action == EMPTY) {
        last_action = MINUS;
        calc_memory = number;
    } else {
        set_base_stylesheet();
        action_in_calc_memory(number);
    }
    printf("%lf", calc_memory);
    set_btn_dot_enabled(1);
    last_action = MINUS;
}

void MainWindow::on_btn_multiply_clicked() {
    QString label = get_calc_label();
    ui->lbl_calc_line->setText("");
    ui->btn_multiply->setStyleSheet("QPushButton {background: #808080; border-radius: 10px;color: #FFFFFF;font-weight: 600;}");
    double number = label.toDouble();
    if(last_action == MULTIPLY && label != ""){
        action_in_calc_memory(number);
    } else if((last_action == MULTIPLY && label == "")){
        // except
    } else if(label == "" && last_action != EMPTY) {
        set_base_stylesheet();
    } else if(last_action == EMPTY) {
        last_action = MULTIPLY;
        calc_memory = number;
    } else {
        set_base_stylesheet();
        action_in_calc_memory(number);
    }
    set_btn_dot_enabled(1);
    printf("%lf", calc_memory);
    last_action = MULTIPLY;
}

void MainWindow::on_btn_divide_clicked() {
    QString label = get_calc_label();
    ui->lbl_calc_line->setText("");
    ui->btn_divide->setStyleSheet("QPushButton {background: #808080; border-radius: 10px;color: #FFFFFF;font-weight: 600;}");
    double number = label.toDouble();
    if(last_action == DIVIDE && label != ""){
        action_in_calc_memory(number);
    }else if((last_action == DIVIDE && label == "")){
        // except
    } else if(label == "" && last_action != EMPTY) {
        set_base_stylesheet();
    } else if(last_action == EMPTY) {
        last_action = DIVIDE;
        calc_memory = number;
    } else {
        set_base_stylesheet();
        action_in_calc_memory(number);
    }
    printf("%lf", calc_memory);
    set_btn_dot_enabled(1);
    last_action = DIVIDE;
}

QString MainWindow::validation_label(QString str) {
    if(str == "inf") {
        str = "0";
        QMessageBox::critical(this, "Error Message", "Stop ignore math:\nDivide by zero");
    } else if(str == "nan") {
        str = "0";
    }
    return str;
}

void MainWindow::on_btn_equls_clicked() {
    QString label = get_calc_label();
    double number = label.toDouble();
    action_in_calc_memory(number);
    last_action = EMPTY;
    isResult = true;
    QString new_label = QString().setNum(calc_memory, 'g', PRECISION);
    new_label = validation_label(new_label);
    set_base_stylesheet();
    ui->lbl_calc_line->setText(new_label);
    if(get_calc_label().contains(".")) {
        set_btn_dot_enabled(0);
    } else {
        set_btn_dot_enabled(1);
    }
}

void MainWindow::on_btn_change_sign_clicked(){
    QString label = get_calc_label();
    QString new_label;
    if(label.contains("-")){
        new_label = label.remove(0, 1);
    } else if (label != "0"){
        new_label = "-" + label;
    } else {
        new_label = "-";
    }
    set_calc_label(new_label);
}


