#include "cssWork.h"

// Set base css stylesheet for sign buttons (another lib)
void set_css_btn_sign_base(QPushButton *btn_sign) {
    btn_sign->setStyleSheet(css_default_sign_btn);
}

// Set clicked css stylesheet for sign buttons (another lib)
void set_css_btn_sign_clicked(QPushButton *btn_sign) {
    btn_sign->setStyleSheet(css_clicked_sign_btn);
}

// Set css stylesheet for dot buttons by status (another lib)
void set_css_btn_dot_enabled (bool status, QPushButton *btn_dot) {
    btn_dot->setEnabled(status);
    if (status) {
        btn_dot->setStyleSheet("QPushButton{ "
                               "background: #2C2C2C; border-radius: 10px;color: white;"
                               "} QPushButton:hover{"
                               "background: #5C5C5C;}");
    } else {
        btn_dot->setStyleSheet("color: black; background-color: #2C2C2C; border-radius: 10px;");
    }
}
