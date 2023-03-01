#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cssWork.h"
#include "bussinessLogic.h"
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

// Auto-connected by names
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

void MainWindow::error_handling (QString str) {
    if (str.contains("e")) {
        QMessageBox::critical(this, "Error Message", "You cant add numbers for e. Push AC or use sign buttons");
    } else if (str.length() == STR_LENGTH){
        QMessageBox::critical(this, "Error Message", "Limit quantity of numbers");
    }
}

// Set base css stylesheet for sign buttons
void MainWindow::set_default_sign_css () {
    if (last_action == PLUS) {
        set_css_btn_sign_base(ui->btn_plus);
    } else if (last_action == MINUS) {
        set_css_btn_sign_base(ui->btn_minus);
    } else if (last_action == MULTIPLY) {
        set_css_btn_sign_base(ui->btn_multiply);
    } else if (last_action == DIVIDE){
        set_css_btn_sign_base(ui->btn_divide);
    } else {
        set_css_btn_sign_base(ui->btn_plus);
        set_css_btn_sign_base(ui->btn_minus);
        set_css_btn_sign_base(ui->btn_multiply);
        set_css_btn_sign_base(ui->btn_divide);
    }
}

// Set clicked css stylesheet for sign buttons
void MainWindow::set_clicked_sign_css (int sign) {
    if (sign == PLUS) {
        set_css_btn_sign_clicked(ui->btn_plus);
    } else if (sign == MINUS) {
        set_css_btn_sign_clicked(ui->btn_minus);
    } else if (sign == MULTIPLY) {
        set_css_btn_sign_clicked(ui->btn_multiply);
    } else {
        set_css_btn_sign_clicked(ui->btn_divide);
    }
}

// SLOT for clicked numbers buttons
void MainWindow::on_btn_numbers_clicked (QString number) {
    QString label = get_calc_label();

    if ((number != "0" || label != "0") && !label.contains("e")) {
        if(label == "0") {
            set_calc_label(number);
        } else if (label.length() < STR_LENGTH) {
            label = label + number;
            set_calc_label(label);
        } else {
            error_handling(label);
        }
    } else {
        error_handling(label);
    }
}

// SLOT for clicked clear (C) button
void MainWindow::on_btn_clear_clicked () {
    set_calc_label("0");
    last_action = EMPTY;
    set_default_sign_css();
    set_css_btn_dot_enabled(1, ui->btn_dot);
}

// SLOT for clicked dot (.) button
void MainWindow::on_btn_dot_clicked () {
    QString new_label = get_calc_label();
    if (new_label.length() == 0) {
        set_calc_label("0.");
    } else if (new_label.length() < STR_LENGTH && !new_label.contains("e")) {
        new_label = new_label + ".";
        set_calc_label(new_label);
        set_css_btn_dot_enabled(0, ui->btn_dot);
    } else {
        error_handling(new_label);
    }
}

// SLOT for clicked del button
void MainWindow::on_btn_del_clicked () {
    QString new_label = get_calc_label();

    if(!new_label.contains("e")){
        new_label.remove(-1, 1);
        if(!new_label.contains(".")) {
            set_css_btn_dot_enabled(1, ui->btn_dot);
        }
    } else {
        error_handling(new_label);
    }

    set_calc_label(new_label);
}

// SLOT for clicked sign buttons
void MainWindow::on_btn_sign_clicked (int sign) {
    QString label = get_calc_label();
    double number = label.toDouble();

    ui->lbl_calc_line->setText("");
    set_clicked_sign_css(sign);

    action_obj temp;
    temp.memory = MainWindow::calc_memory;
    temp.sign = MainWindow::last_action;
    temp.number = number;

    if (last_action == sign && label != "") {
         MainWindow::calc_memory = action_in_calc_memory(temp);
    } else if (label == "" && last_action != EMPTY && last_action != sign) {
        set_default_sign_css();
    } else if (last_action == EMPTY) {
        last_action = sign;
        calc_memory = number;
    } else {
        set_default_sign_css();
        MainWindow::calc_memory = action_in_calc_memory(temp);
    }

    set_css_btn_dot_enabled(1, ui->btn_dot);
    last_action = sign;
}

// SLOT for clicked equals (=) button
void MainWindow::on_btn_equls_clicked () {
    QString label = get_calc_label();
    double number = label.toDouble();

    action_obj temp;
    temp.memory = MainWindow::calc_memory;
    temp.sign = MainWindow::last_action;
    temp.number = number;

    MainWindow::calc_memory = action_in_calc_memory(temp);
    QString new_label = QString().setNum(calc_memory, 'g', PRECISION);
    new_label = validation_label(new_label);
    set_default_sign_css();
    ui->lbl_calc_line->setText(new_label);

    if (get_calc_label().contains(".")) {
        set_css_btn_dot_enabled(0, ui->btn_dot);
    } else {
        set_css_btn_dot_enabled(1, ui->btn_dot);
    }

    last_action = EMPTY;
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
