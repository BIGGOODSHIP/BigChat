#ifndef MAINWINDOW_H
#define MAINWINDOW_H


/************************************************************************************
*
*
*   @file:          mainwindow.h
*   @brief:         实现一个窗口，基础qt
*   @author:         BAOHAOFAN  3320335083@qq.com
*   @date:              2026/8/10
*   @information:       XXXXX
*
*
************************************************************************************/
#include <QMainWindow>
#include"logindialog.h"
#include"registerdialog.h"
#include"resetdialog.h"
#include"chatdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;



public slots:
    void SlotSwitchReg();
    void SlotSwitchLogin();//从registerdialog返回
    void SlotSwitchLogin2();//从resetdialog返回
    void SlotSwitchReset();
    void SlotSwitchChat();//跳转到chat界面
private:
    Ui::MainWindow *ui;
    LoginDialog* _login_dlg;
    RegisterDialog* _reg_dlg;
    ResetDialog* _reset_dlg;
    ChatDialog* _chat_dlg;
};
#endif // MAINWINDOW_H
