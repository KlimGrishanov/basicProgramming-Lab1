#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect all ui buttons
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

//    connect(ui->btn_clear, &QPushButton::clicked, this, &MainWindow::on_btn_clear_clicked);
//    connect(ui->btn_dot, &QPushButton::clicked, this, &MainWindow::on_btn_dot_clicked);
//    connect(ui->btn_del, &QPushButton::clicked, this, &MainWindow::on_btn_del_clicked);
//    connect(ui->btn_change_sign, &QPushButton::clicked, this, &MainWindow::on_btn_change_sign_clicked);

    connect(ui->btn_plus, &QPushButton::clicked, this, [this]{MainWindow::on_btn_sign_clicked(PLUS);});
    connect(ui->btn_minus, &QPushButton::clicked, this, [this]{MainWindow::on_btn_sign_clicked(MINUS);});
    connect(ui->btn_multiply, &QPushButton::clicked, this, [this]{MainWindow::on_btn_sign_clicked(MULTIPLY);});
    connect(ui->btn_divide, &QPushButton::clicked, this, [this]{MainWindow::on_btn_sign_clicked(DIVIDE);});

    connect(ui->btn_equals, &QPushButton::clicked, this, &MainWindow::on_btn_equls_clicked);
}

// Ui descriptor
MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::get_calc_label () {
    return ui->lbl_calc_line->text();
}

void MainWindow::set_calc_label (QString new_label) {
    ui->lbl_calc_line->setText(new_label);
}

// Validate values, catch error
QString MainWindow::validation_label (QString str) {
    if (str == "inf" || str == "-inf") {
        str = "0";
        QMessageBox::critical(this, "Error Message", "Stop ignore math:\nDivide by zero"); // except this
    } else if (str == "nan") {
        str = "0";
    }
    return str;
}

// Launch post action by sign (another lib)
void MainWindow::action_in_calc_memory (double number) {
    if (last_action == PLUS) {
        calc_memory = calc_memory + number;
    } else if (last_action == MINUS) {
        calc_memory = calc_memory - number;
    } else if (last_action == MULTIPLY) {
        calc_memory = calc_memory * number;
    } else if (last_action == DIVIDE){
        calc_memory = calc_memory / number;
    }
}

// Set base css stylesheet for sign buttons (another lib)
void MainWindow::set_css_btn_sign_base () {
    if (last_action == PLUS) {
        ui -> btn_plus -> setStyleSheet(css_default_sign_btn);
    } else if (last_action == MINUS) {
        ui -> btn_minus -> setStyleSheet(css_default_sign_btn);
    } else if (last_action == MULTIPLY) {
        ui -> btn_multiply -> setStyleSheet(css_default_sign_btn);
    } else if (last_action == DIVIDE){
        ui -> btn_divide -> setStyleSheet(css_default_sign_btn);
    } else {
        ui -> btn_plus -> setStyleSheet(css_default_sign_btn);
        ui -> btn_minus -> setStyleSheet(css_default_sign_btn);
        ui -> btn_multiply -> setStyleSheet(css_default_sign_btn);
        ui -> btn_divide -> setStyleSheet(css_default_sign_btn);
    }
}

// Set clicked css stylesheet for sign buttons (another lib)
void MainWindow::set_css_btn_sign_clicked (int sign) {
    if (sign == PLUS) {
        ui->btn_plus->setStyleSheet(css_clicked_sign_btn);
    } else if (sign == MINUS) {
        ui->btn_minus->setStyleSheet(css_clicked_sign_btn);
    } else if (sign == MULTIPLY) {
        ui->btn_multiply->setStyleSheet(css_clicked_sign_btn);
    } else if (sign == DIVIDE) {
        ui->btn_divide->setStyleSheet(css_clicked_sign_btn);
    } else {
        // except
    }
}

// Set css stylesheet for dot buttons by status (another lib)
void MainWindow::set_css_btn_dot_enabled (bool status) {
    ui->btn_dot->setEnabled(status);
    if (status) {
        ui->btn_dot->setStyleSheet("QPushButton{ background: #2C2C2C; border-radius: 10px;color: white;} QPushButton:hover{background: #5C5C5C;}");
    } else {
        ui->btn_dot->setStyleSheet("color: black; background-color: #2C2C2C; border-radius: 10px;");
    }
}

// SLOT for clicked numbers buttons
void MainWindow::on_btn_numbers_clicked (QString number) {
    QString label = get_calc_label();

    if ((number == "0" && label == "0") || (isResult && label.contains("e"))) { // !except in else
        // except
    } else if (label == "0") {
        set_calc_label(number);
    } else if (label.length() < STR_LENGTH) {
        label = label + number;
        set_calc_label(label);
    }
}

// SLOT for clicked clear (C) button
void MainWindow::on_btn_clear_clicked () {
    set_calc_label("0");
    isResult = false;
    last_action = EMPTY;
    set_css_btn_sign_base();
    set_css_btn_dot_enabled(1);
}

// SLOT for clicked dot (.) button
void MainWindow::on_btn_dot_clicked () {
    QString new_label = get_calc_label();
    if (new_label.length() == 0) {
        set_calc_label("0.");
    } else if (new_label.length() < STR_LENGTH) {
        new_label = new_label + ".";
        set_calc_label(new_label);
        set_css_btn_dot_enabled(0); // !change if/else
    } else {
        //except
    }
}

// SLOT for clicked del button
void MainWindow::on_btn_del_clicked () {
    QString new_label = get_calc_label();

    if(new_label.contains("e")){ // !change if/else
        // except
    } else if(!new_label.contains(".") ){
        set_css_btn_dot_enabled(1);
        new_label.remove(-1, 1);
    }

    set_calc_label(new_label);
}

// SLOT for clicked sign buttons
void MainWindow::on_btn_sign_clicked (int sign) {
    QString label = get_calc_label();
    double number = label.toDouble();

    ui->lbl_calc_line->setText("");
    set_css_btn_sign_clicked(sign);

    if (last_action == sign && label != "") {
        action_in_calc_memory(number);
    } else if (last_action == sign && label == ""){ // !change if/else
        // except
    } else if (label == "" && last_action != EMPTY) {
        set_css_btn_sign_base();
    } else if (last_action == EMPTY) {
        last_action = sign;
        calc_memory = number;
    } else {
        set_css_btn_sign_base();
        action_in_calc_memory(number);
    }

    set_css_btn_dot_enabled(1);
    last_action = sign;
}

// SLOT for clicked equals (=) button
void MainWindow::on_btn_equls_clicked () {
    QString label = get_calc_label();
    double number = label.toDouble();

    action_in_calc_memory(number);
    QString new_label = QString().setNum(calc_memory, 'g', PRECISION);
    new_label = validation_label(new_label);
    set_css_btn_sign_base();
    ui->lbl_calc_line->setText(new_label);

    if (get_calc_label().contains(".")) {
        set_css_btn_dot_enabled(0);
    } else {
        set_css_btn_dot_enabled(1);
    }

    last_action = EMPTY;
    isResult = true;
}

// SLOT for clicked change sign (+/-) button
void MainWindow::on_btn_change_sign_clicked () {
    QString label = get_calc_label();
    QString new_label;

    if(label.contains("-")) {
        new_label = label.remove(0, 1);
    } else if (label != "0"){
        new_label = "-" + label;
    } else {
        new_label = "-";
    }

    set_calc_label(new_label);
}
