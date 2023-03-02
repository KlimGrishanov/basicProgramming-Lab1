#ifndef CSSWORK_H
#define CSSWORK_H
#include <QMainWindow>
#include <QPushButton>

const QString css_default_sign_btn = "QPushButton {"
                                     "background: #DF6521;border-radius: 10px;color: #FFFFFF;font-weight: 600;"
                                     "}QPushButton:hover {background-color: #FF7223;}";
const QString css_clicked_sign_btn = "QPushButton {"
                                     "background: #808080; border-radius: 10px;color: #FFFFFF;font-weight: 600;}";

void set_css_btn_sign_base(QPushButton *btn_sign);
void set_css_btn_sign_clicked(QPushButton *btn_sign);
void set_css_btn_dot_enabled(bool status, QPushButton *btn_dot);

#endif // CSSWORK_H
