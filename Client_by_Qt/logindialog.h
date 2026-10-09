#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include"global.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;
    QMap<TipErr, QString> _tip_errs;
    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    void showTip(QString str,bool b_ok);
    bool checkUserValid();
    bool checkPwdValid();
    void initHttpHandlers();
public slots:
    void slot_forget_pwd();
    void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);
signals:
    void sigSwitchRegister();
    void sigSwitchReset();

private slots:
    void on_pushButton_clicked();
};

#endif // LOGINDIALOG_H
