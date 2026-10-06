#ifndef RESETDIALOG_H
#define RESETDIALOG_H

#include <QDialog>
#include"global.h"

namespace Ui {
class ResetDialog;
}

class ResetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResetDialog(QWidget *parent = nullptr);
    ~ResetDialog();

private:
    Ui::ResetDialog *ui;
    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;
    QMap<TipErr, QString> _tip_errs;

private:
    bool checkUserValid();
    bool checkEmailValid();
    bool checkPassValid();
    bool checkConfirmValid();
    bool checkVarifyValid();

    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    void initHandlers();
    void showTip(QString str,bool b_ok);

signals:
    void switchLogin();

public slots:
    void slot_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
    void on_sure_btn_clicked();
    void on_varify_btn_clicked();
    void on_cancel_btn_clicked();





};

#endif // RESETDIALOG_H
