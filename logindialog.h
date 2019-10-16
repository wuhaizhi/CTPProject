#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "traderapi.h"
#include "traderspi.h"
#include "TradeApi/win32/ThostFtdcTraderApi.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog, CThostFtdcTraderSpi
{
    Q_OBJECT

private:
    CTraderApi *m_tradeApi;
    CTraderSpi *m_TradeSpi;

    void OnFrontConnected();
    void OnFrontDisconnected(int nReason);
    void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast);


    int UserLogin();
    int Authenticate();

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    void setTradeApi(CTraderApi *TradeApi, CTraderSpi *ATradeSpi);

private slots:
    void on_but_login_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
