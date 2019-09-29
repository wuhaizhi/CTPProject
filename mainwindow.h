#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TradeApi/win32/ThostFtdcTraderApi.h"
#include "TradeApi/win32/ThostFtdcMdApi.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public CThostFtdcTraderSpi, public CThostFtdcMdSpi
{
    Q_OBJECT

private:
    CThostFtdcTraderApi* m_ptraderapi;
    TThostFtdcBrokerIDType	m_BrokerID;
    TThostFtdcUserIDType	m_UserID;
    TThostFtdcInvestorIDType m_InvestorID;
    TThostFtdcPasswordType	m_Password;
    TThostFtdcAuthCodeType	m_AuthCode;
    TThostFtdcAppIDType	m_AppID;

    void InitCTP();

    int UserLogin();
    int Authenticate();


    // 重写CThostFtdcTraderSpi方法
    void OnFrontConnected();
    void OnFrontDisconnected(int nReason);
    void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast);
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast);
    void OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast);
    void OnRspOrderInsert(CThostFtdcInputOrderField * pInputOrder, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast);
    void OnRtnOrder(CThostFtdcOrderField * pOrder);
    void OnRtnTrade(CThostFtdcTradeField * pTrade);
    void OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast);
    void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField* pSettlementInfo, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
    void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
    void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
    void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);



    int ReqQryTradingAccount();
    int qryInstrument(QString sInstrumentID);
    int qryInvestorPositon();
    int QryOrder();
    int CancelOrder(CThostFtdcOrderField AOrder);
    void ReqSettlementInfoConfirm();


    void AppendLog(QString msg);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_login_clicked();

    void on_btn_qry_Order_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_AppendMsg(QString msg);

signals:
    void send_AppendMsg(QString msg);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
