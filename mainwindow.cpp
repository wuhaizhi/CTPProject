#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>
#include <Windows.h>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, SIGNAL(send_AppendMsg(QString)), this, SLOT(on_AppendMsg(QString)));
}


void MainWindow::InitCTP(){
    QDir* aDir = new QDir();
    if (!aDir->exists("flow\\Trade"))
    {
        aDir->mkdir("flow\\Trade");
    }


    strcpy_s(m_BrokerID, "9999");
    strcpy_s(m_InvestorID, "142162");
    strcpy_s(m_UserID,  "142162");
    strcpy_s(m_Password, "wu64117467");
    strcpy_s(m_AppID, "simnow_client_test");
    strcpy_s(m_AuthCode, "0000000000000000");

    m_ptraderapi = CThostFtdcTraderApi::CreateFtdcTraderApi("flow\\Trade\\");
    qDebug("%s\n", m_ptraderapi->GetApiVersion());
    m_ptraderapi->RegisterSpi(this);
    m_ptraderapi->SubscribePublicTopic(THOST_TERT_QUICK);
    m_ptraderapi->SubscribePrivateTopic(THOST_TERT_QUICK);
    m_ptraderapi->RegisterFront(const_cast<char *>("tcp://180.168.146.187:10130"));
    m_ptraderapi->Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_login_clicked()
{
InitCTP();
}

int MainWindow::UserLogin(){
   qDebug() << "用户登陆" << endl;

   CThostFtdcReqUserLoginField reqUserLogin;
   memset(&reqUserLogin, 0, sizeof(reqUserLogin));

   strcpy_s(reqUserLogin.BrokerID, m_BrokerID);
   strcpy_s(reqUserLogin.UserID, m_UserID);
   strcpy_s(reqUserLogin.Password, m_Password);
   return m_ptraderapi->ReqUserLogin(&reqUserLogin, 1);
}

int MainWindow::Authenticate(){
    CThostFtdcReqAuthenticateField field;
    memset(&field, 0, sizeof(field));
    strcpy_s(field.BrokerID, m_BrokerID);
    strcpy_s(field.UserID, m_UserID);
    strcpy_s(field.AppID, m_AppID);
    strcpy_s(field.AuthCode, m_AuthCode);
    return m_ptraderapi->ReqAuthenticate(&field, 2);
}


void MainWindow::OnFrontConnected(){
    qDebug("OnFrontConnected");
    qDebug("%s\n", m_ptraderapi->GetApiVersion());

    //如果连接成功就进行认证
    Authenticate();
}

void MainWindow::OnFrontDisconnected(int nReason){

}

void MainWindow::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    if(pRspAuthenticateField){
        if (pRspInfo->ErrorID == 0){

            AppendLog("OnRspAuthenticate:" +QString::fromLocal8Bit(pRspInfo->ErrorMsg));
            UserLogin();
        }else {

            AppendLog("OnRspAuthenticate:" +QString::fromLocal8Bit(pRspInfo->ErrorMsg));
        }

    }
}

void MainWindow::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
    AppendLog("<OnRspUserLogin>");
        if (pRspUserLogin)
        {
            AppendLog("\tTradingDay" + QString::fromLocal8Bit(pRspUserLogin->TradingDay));
            AppendLog("\tLoginTime " + QString::fromLocal8Bit( pRspUserLogin->LoginTime));
            AppendLog("\tBrokerID "+ QString::fromLocal8Bit( pRspUserLogin->BrokerID));
            AppendLog("\tUserID "+ QString::fromLocal8Bit( pRspUserLogin->UserID));
            AppendLog("\tSystemName "+ QString::fromLocal8Bit( pRspUserLogin->SystemName));
            AppendLog("\tMaxOrderRef "+ QString::fromLocal8Bit( pRspUserLogin->MaxOrderRef));
            AppendLog("\tSHFETime "+ QString::fromLocal8Bit( pRspUserLogin->SHFETime));
            AppendLog("\tDCETime "+ QString::fromLocal8Bit( pRspUserLogin->DCETime));
            AppendLog("\tCZCETime "+ QString::fromLocal8Bit( pRspUserLogin->CZCETime));
            AppendLog("\tFFEXTime "+ QString::fromLocal8Bit( pRspUserLogin->FFEXTime));
            AppendLog("\tINETime "+ QString::fromLocal8Bit( pRspUserLogin->INETime));
            AppendLog("\tFrontID "+ QString::number(pRspUserLogin->FrontID));
            AppendLog("\tSessionID "+ QString::number( pRspUserLogin->SessionID));
        }
        if (pRspInfo)
        {
            AppendLog("\tErrorMsg "+ QString::fromLocal8Bit(pRspInfo->ErrorMsg));
            AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
        }
        AppendLog("\tnRequestID "+ QString::number( nRequestID));
        AppendLog("\tbIsLast "+ QString::number( bIsLast));
        AppendLog("</OnRspUserLogin>");
}


void MainWindow::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
    AppendLog("<OnRspSettlementInfoConfirm>");
        if (pSettlementInfoConfirm)
        {
            AppendLog("\tBrokerID" + QString::fromLocal8Bit( pSettlementInfoConfirm->BrokerID));
            AppendLog("\tInvestorID" + QString::fromLocal8Bit( pSettlementInfoConfirm->InvestorID));
            AppendLog("\tConfirmDate" + QString::fromLocal8Bit( pSettlementInfoConfirm->ConfirmDate));
            AppendLog("\tConfirmTime" + QString::fromLocal8Bit( pSettlementInfoConfirm->ConfirmTime));
            AppendLog("\tAccountID" + QString::fromLocal8Bit( pSettlementInfoConfirm->AccountID));
            AppendLog("\tCurrencyID" + QString::fromLocal8Bit( pSettlementInfoConfirm->CurrencyID));
            AppendLog("\tSettlementID "+ QString::number( pSettlementInfoConfirm->SettlementID));
        }
        if (pRspInfo)
        {
            AppendLog("\tErrorMsg" + QString::fromLocal8Bit( pRspInfo->ErrorMsg));
            AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
        }
        AppendLog("\tnRequestID "+ QString::number( nRequestID));
        AppendLog("\tbIsLast "+ QString::number( bIsLast));
        AppendLog("</OnRspSettlementInfoConfirm>");

}
void MainWindow::OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
    AppendLog("<OnRspQryInstrument>");
        if (pInstrument)
        {
            AppendLog("\tInstrumentID" + QString::fromLocal8Bit( pInstrument->InstrumentID));
            AppendLog("\tExchangeID" + QString::fromLocal8Bit( pInstrument->ExchangeID));
            AppendLog("\tInstrumentName" + QString::fromLocal8Bit( pInstrument->InstrumentName));
            AppendLog("\tExchangeInstID" + QString::fromLocal8Bit( pInstrument->ExchangeInstID));
            AppendLog("\tProductID" + QString::fromLocal8Bit( pInstrument->ProductID));
            AppendLog("\tCreateDate" + QString::fromLocal8Bit( pInstrument->CreateDate));
            AppendLog("\tOpenDate" + QString::fromLocal8Bit( pInstrument->OpenDate));
            AppendLog("\tExpireDate" + QString::fromLocal8Bit( pInstrument->ExpireDate));
            AppendLog("\tStartDelivDate" + QString::fromLocal8Bit( pInstrument->StartDelivDate));
            AppendLog("\tEndDelivDate" + QString::fromLocal8Bit( pInstrument->EndDelivDate));
            AppendLog("\tUnderlyingInstrID" + QString::fromLocal8Bit( pInstrument->UnderlyingInstrID));
            AppendLog("\tDeliveryYear "+ QString::number( pInstrument->DeliveryYear));
            AppendLog("\tDeliveryMonth "+ QString::number( pInstrument->DeliveryMonth));
            AppendLog("\tMaxMarketOrderVolume "+ QString::number( pInstrument->MaxMarketOrderVolume));
            AppendLog("\tMinMarketOrderVolume "+ QString::number( pInstrument->MinMarketOrderVolume));
            AppendLog("\tMaxLimitOrderVolume "+ QString::number( pInstrument->MaxLimitOrderVolume));
            AppendLog("\tMinLimitOrderVolume "+ QString::number( pInstrument->MinLimitOrderVolume));
            AppendLog("\tVolumeMultiple "+ QString::number( pInstrument->VolumeMultiple));
            AppendLog("\tIsTrading "+ QString::number( pInstrument->IsTrading));
            AppendLog("\tProductClass "+ QString( pInstrument->ProductClass));
            AppendLog("\tInstLifePhase "+ QString( pInstrument->InstLifePhase));
            AppendLog("\tPositionType "+ QString( pInstrument->PositionType));
            AppendLog("\tPositionDateType "+ QString( pInstrument->PositionDateType));
            AppendLog("\tMaxMarginSideAlgorithm "+ QString( pInstrument->MaxMarginSideAlgorithm));
            AppendLog("\tOptionsType "+ QString( pInstrument->OptionsType));
            AppendLog("\tCombinationType "+ QString( pInstrument->CombinationType));
            AppendLog("\tPriceTick "+ QString::number( pInstrument->PriceTick));
            AppendLog("\tLongMarginRatio "+ QString::number( pInstrument->LongMarginRatio));
            AppendLog("\tShortMarginRatio "+ QString::number( pInstrument->ShortMarginRatio));
            AppendLog("\tStrikePrice "+ QString::number( pInstrument->StrikePrice));
            AppendLog("\tUnderlyingMultiple "+ QString::number( pInstrument->UnderlyingMultiple));
        }
        if (pRspInfo)
        {
            AppendLog("\tErrorMsg" + QString::fromLocal8Bit( pRspInfo->ErrorMsg));
            AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
        }
        AppendLog("\tnRequestID "+ QString::number( nRequestID));
        AppendLog("\tbIsLast "+ QString::number( bIsLast));
        AppendLog("</OnRspQryInstrument>");
}


void MainWindow::OnRspOrderInsert(CThostFtdcInputOrderField * pInputOrder, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
    AppendLog("<OnRspOrderInsert>");
    if (pInputOrder)
    {
        AppendLog("\tBrokerID" + QString::fromLocal8Bit( pInputOrder->BrokerID));
        AppendLog("\tInvestorID" + QString::fromLocal8Bit( pInputOrder->InvestorID));
        AppendLog("\tInstrumentID" + QString::fromLocal8Bit( pInputOrder->InstrumentID));
        AppendLog("\tOrderRef" + QString::fromLocal8Bit( pInputOrder->OrderRef));
        AppendLog("\tUserID" + QString::fromLocal8Bit( pInputOrder->UserID));
        AppendLog("\tCombOffsetFlag" + QString::fromLocal8Bit( pInputOrder->CombOffsetFlag));
        AppendLog("\tCombHedgeFlag" + QString::fromLocal8Bit( pInputOrder->CombHedgeFlag));
        AppendLog("\tGTDDate" + QString::fromLocal8Bit( pInputOrder->GTDDate));
        AppendLog("\tBusinessUnit" + QString::fromLocal8Bit( pInputOrder->BusinessUnit));
        AppendLog("\tExchangeID" + QString::fromLocal8Bit( pInputOrder->ExchangeID));
        AppendLog("\tInvestUnitID" + QString::fromLocal8Bit( pInputOrder->InvestUnitID));
        AppendLog("\tAccountID" + QString::fromLocal8Bit( pInputOrder->AccountID));
        AppendLog("\tCurrencyID" + QString::fromLocal8Bit( pInputOrder->CurrencyID));
        AppendLog("\tClientID" + QString::fromLocal8Bit( pInputOrder->ClientID));
        AppendLog("\tIPAddress" + QString::fromLocal8Bit( pInputOrder->IPAddress));
        AppendLog("\tMacAddress" + QString::fromLocal8Bit( pInputOrder->MacAddress));
        AppendLog("\tVolumeTotalOriginal "+ QString::number( pInputOrder->VolumeTotalOriginal));
        AppendLog("\tMinVolume "+ QString::number( pInputOrder->MinVolume));
        AppendLog("\tIsAutoSuspend "+ QString::number( pInputOrder->IsAutoSuspend));
        AppendLog("\tRequestID "+ QString::number( pInputOrder->RequestID));
        AppendLog("\tUserForceClose "+ QString::number( pInputOrder->UserForceClose));
        AppendLog("\tIsSwapOrder "+ QString::number( pInputOrder->IsSwapOrder));
        AppendLog("\tOrderPriceType " + QString( pInputOrder->OrderPriceType));
        AppendLog("\tDirection " + QString( pInputOrder->Direction));
        AppendLog("\tTimeCondition " + QString( pInputOrder->TimeCondition));
        AppendLog("\tVolumeCondition " + QString( pInputOrder->VolumeCondition));
        AppendLog("\tContingentCondition " + QString( pInputOrder->ContingentCondition));
        AppendLog("\tForceCloseReason " + QString( pInputOrder->ForceCloseReason));
        AppendLog("\tLimitPrice "+ QString::number( pInputOrder->LimitPrice));
        AppendLog("\tStopPrice "+ QString::number( pInputOrder->StopPrice));
    }
    if (pRspInfo)
    {
        AppendLog("\tErrorMsg" + QString::fromLocal8Bit( pRspInfo->ErrorMsg));
        AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
    }
    AppendLog("\tnRequestID "+ QString::number( nRequestID));
    AppendLog("\tbIsLast "+ QString::number( bIsLast));
    AppendLog("</OnRspOrderInsert>");
}
void MainWindow::OnRtnOrder(CThostFtdcOrderField * pOrder){
    AppendLog("<OnRtnOrder>");
    if (pOrder)
    {
        AppendLog("\tBrokerID" + QString::fromLocal8Bit( pOrder->BrokerID));
        AppendLog("\tInvestorID" + QString::fromLocal8Bit( pOrder->InvestorID));
        AppendLog("\tInstrumentID" + QString::fromLocal8Bit( pOrder->InstrumentID));
        AppendLog("\tOrderRef" + QString::fromLocal8Bit( pOrder->OrderRef));
        AppendLog("\tUserID" + QString::fromLocal8Bit( pOrder->UserID));
        AppendLog("\tCombOffsetFlag" + QString::fromLocal8Bit( pOrder->CombOffsetFlag));
        AppendLog("\tCombHedgeFlag" + QString::fromLocal8Bit( pOrder->CombHedgeFlag));
        AppendLog("\tGTDDate" + QString::fromLocal8Bit( pOrder->GTDDate));
        AppendLog("\tBusinessUnit" + QString::fromLocal8Bit( pOrder->BusinessUnit));
        AppendLog("\tOrderLocalID" + QString::fromLocal8Bit( pOrder->OrderLocalID));
        AppendLog("\tExchangeID" + QString::fromLocal8Bit( pOrder->ExchangeID));
        AppendLog("\tParticipantID" + QString::fromLocal8Bit( pOrder->ParticipantID));
        AppendLog("\tClientID" + QString::fromLocal8Bit( pOrder->ClientID));
        AppendLog("\tExchangeInstID" + QString::fromLocal8Bit( pOrder->ExchangeInstID));
        AppendLog("\tTraderID" + QString::fromLocal8Bit( pOrder->TraderID));
        AppendLog("\tTradingDay" + QString::fromLocal8Bit( pOrder->TradingDay));
        AppendLog("\tOrderSysID" + QString::fromLocal8Bit( pOrder->OrderSysID));
        AppendLog("\tInsertDate" + QString::fromLocal8Bit( pOrder->InsertDate));
        AppendLog("\tInsertTime" + QString::fromLocal8Bit( pOrder->InsertTime));
        AppendLog("\tActiveTime" + QString::fromLocal8Bit( pOrder->ActiveTime));
        AppendLog("\tSuspendTime" + QString::fromLocal8Bit( pOrder->SuspendTime));
        AppendLog("\tUpdateTime" + QString::fromLocal8Bit( pOrder->UpdateTime));
        AppendLog("\tCancelTime" + QString::fromLocal8Bit( pOrder->CancelTime));
        AppendLog("\tActiveTraderID" + QString::fromLocal8Bit( pOrder->ActiveTraderID));
        AppendLog("\tClearingPartID" + QString::fromLocal8Bit( pOrder->ClearingPartID));
        AppendLog("\tUserProductInfo" + QString::fromLocal8Bit( pOrder->UserProductInfo));
        AppendLog("\tStatusMsg" + QString::fromLocal8Bit( pOrder->StatusMsg));
        AppendLog("\tActiveUserID" + QString::fromLocal8Bit( pOrder->ActiveUserID));
        AppendLog("\tRelativeOrderSysID" + QString::fromLocal8Bit( pOrder->RelativeOrderSysID));
        AppendLog("\tBranchID" + QString::fromLocal8Bit( pOrder->BranchID));
        AppendLog("\tInvestUnitID" + QString::fromLocal8Bit( pOrder->InvestUnitID));
        AppendLog("\tAccountID" + QString::fromLocal8Bit( pOrder->AccountID));
        AppendLog("\tCurrencyID" + QString::fromLocal8Bit( pOrder->CurrencyID));
        AppendLog("\tIPAddress" + QString::fromLocal8Bit( pOrder->IPAddress));
        AppendLog("\tMacAddress" + QString::fromLocal8Bit( pOrder->MacAddress));
        AppendLog("\tVolumeTotalOriginal "+ QString::number( pOrder->VolumeTotalOriginal));
        AppendLog("\tMinVolume "+ QString::number( pOrder->MinVolume));
        AppendLog("\tIsAutoSuspend "+ QString::number( pOrder->IsAutoSuspend));
        AppendLog("\tRequestID "+ QString::number( pOrder->RequestID));
        AppendLog("\tInstallID "+ QString::number( pOrder->InstallID));
        AppendLog("\tNotifySequence "+ QString::number( pOrder->NotifySequence));
        AppendLog("\tSettlementID "+ QString::number( pOrder->SettlementID));
        AppendLog("\tVolumeTraded "+ QString::number( pOrder->VolumeTraded));
        AppendLog("\tVolumeTotal "+ QString::number( pOrder->VolumeTotal));
        AppendLog("\tSequenceNo "+ QString::number( pOrder->SequenceNo));
        AppendLog("\tFrontID "+ QString::number( pOrder->FrontID));
        AppendLog("\tSessionID "+ QString::number( pOrder->SessionID));
        AppendLog("\tUserForceClose "+ QString::number( pOrder->UserForceClose));
        AppendLog("\tBrokerOrderSeq "+ QString::number( pOrder->BrokerOrderSeq));
        AppendLog("\tZCETotalTradedVolume "+ QString::number( pOrder->ZCETotalTradedVolume));
        AppendLog("\tIsSwapOrder "+ QString::number( pOrder->IsSwapOrder));
        AppendLog("\tOrderPriceType " + QString( pOrder->OrderPriceType));
        AppendLog("\tDirection " + QString( pOrder->Direction));
        AppendLog("\tTimeCondition " + QString( pOrder->TimeCondition));
        AppendLog("\tVolumeCondition " + QString( pOrder->VolumeCondition));
        AppendLog("\tContingentCondition " + QString( pOrder->ContingentCondition));
        AppendLog("\tForceCloseReason " + QString( pOrder->ForceCloseReason));
        AppendLog("\tOrderSubmitStatus " + QString( pOrder->OrderSubmitStatus));
        AppendLog("\tOrderSource " + QString( pOrder->OrderSource));
        AppendLog("\tOrderStatus " + QString( pOrder->OrderStatus));
        AppendLog("\tOrderType " + QString( pOrder->OrderType));
        AppendLog("\tLimitPrice "+ QString::number( pOrder->LimitPrice));
        AppendLog("\tStopPrice "+ QString::number( pOrder->StopPrice));
    }
    AppendLog("</OnRtnOrder>");
}
void MainWindow::OnRtnTrade(CThostFtdcTradeField * pTrade){
    AppendLog("<OnRtnTrade>");
    if (pTrade)
    {
        AppendLog("\tBrokerID" + QString::fromLocal8Bit( pTrade->BrokerID));
        AppendLog("\tInvestorID" + QString::fromLocal8Bit( pTrade->InvestorID));
        AppendLog("\tInstrumentID" + QString::fromLocal8Bit( pTrade->InstrumentID));
        AppendLog("\tOrderRef" + QString::fromLocal8Bit( pTrade->OrderRef));
        AppendLog("\tUserID" + QString::fromLocal8Bit( pTrade->UserID));
        AppendLog("\tExchangeID" + QString::fromLocal8Bit( pTrade->ExchangeID));
        AppendLog("\tTradeID" + QString::fromLocal8Bit( pTrade->TradeID));
        AppendLog("\tOrderSysID" + QString::fromLocal8Bit( pTrade->OrderSysID));
        AppendLog("\tParticipantID" + QString::fromLocal8Bit( pTrade->ParticipantID));
        AppendLog("\tClientID" + QString::fromLocal8Bit( pTrade->ClientID));
        AppendLog("\tExchangeInstID" + QString::fromLocal8Bit( pTrade->ExchangeInstID));
        AppendLog("\tTradeDate" + QString::fromLocal8Bit( pTrade->TradeDate));
        AppendLog("\tTradeTime" + QString::fromLocal8Bit( pTrade->TradeTime));
        AppendLog("\tTraderID" + QString::fromLocal8Bit( pTrade->TraderID));
        AppendLog("\tOrderLocalID" + QString::fromLocal8Bit( pTrade->OrderLocalID));
        AppendLog("\tClearingPartID" + QString::fromLocal8Bit( pTrade->ClearingPartID));
        AppendLog("\tBusinessUnit" + QString::fromLocal8Bit( pTrade->BusinessUnit));
        AppendLog("\tTradingDay" + QString::fromLocal8Bit( pTrade->TradingDay));
        AppendLog("\tInvestUnitID" + QString::fromLocal8Bit( pTrade->InvestUnitID));
        AppendLog("\tVolume "+ QString::number( pTrade->Volume));
        AppendLog("\tSequenceNo "+ QString::number( pTrade->SequenceNo));
        AppendLog("\tSettlementID "+ QString::number( pTrade->SettlementID));
        AppendLog("\tBrokerOrderSeq "+ QString::number( pTrade->BrokerOrderSeq));
        AppendLog("\tDirection " + QString( pTrade->Direction));
        AppendLog("\tTradingRole " + QString( pTrade->TradingRole));
        AppendLog("\tOffsetFlag " + QString( pTrade->OffsetFlag));
        AppendLog("\tHedgeFlag " + QString( pTrade->HedgeFlag));
        AppendLog("\tTradeType " + QString( pTrade->TradeType));
        AppendLog("\tPriceSource " + QString( pTrade->PriceSource));
        AppendLog("\tTradeSource " + QString( pTrade->TradeSource));
        AppendLog("\tPrice "+ QString::number( pTrade->Price));
    }
    AppendLog("</OnRtnTrade>");
}
void MainWindow::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
    AppendLog("<OnRspError>");
    if (pRspInfo)
    {
        AppendLog("\tErrorMsg" + QString::fromLocal8Bit( pRspInfo->ErrorMsg));
        AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
    }
    AppendLog("\tnRequestID "+ QString::number( nRequestID));
    AppendLog("\tbIsLast "+ QString::number( bIsLast));
    AppendLog("</OnRspError>");
}
void MainWindow::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField* pSettlementInfo, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){
    AppendLog("<OnRspQrySettlementInfo>");
    if (pSettlementInfo)
    {
        AppendLog("\tTradingDay" + QString::fromLocal8Bit( pSettlementInfo->TradingDay));
        AppendLog("\tBrokerID" + QString::fromLocal8Bit( pSettlementInfo->BrokerID));
        AppendLog("\tInvestorID" + QString::fromLocal8Bit( pSettlementInfo->InvestorID));
        AppendLog("\tContent" + QString::fromLocal8Bit( pSettlementInfo->Content));
        AppendLog("\tAccountID" + QString::fromLocal8Bit( pSettlementInfo->AccountID));
        AppendLog("\tCurrencyID" + QString::fromLocal8Bit( pSettlementInfo->CurrencyID));
        AppendLog("\tSettlementID "+ QString::number( pSettlementInfo->SettlementID));
        AppendLog("\tSequenceNo "+ QString::number( pSettlementInfo->SequenceNo));
    }
    if (pRspInfo)
    {
        AppendLog("\tErrorMsg" + QString::fromLocal8Bit( pRspInfo->ErrorMsg));
        AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
    }
    AppendLog("\tnRequestID "+ QString::number( nRequestID));
    AppendLog("\tbIsLast "+ QString::number( bIsLast));
    AppendLog("</OnRspQrySettlementInfo>");
}
void MainWindow::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    AppendLog("<OnRspQryInvestorPosition>");
    if (pInvestorPosition)
    {
        AppendLog("\tInstrumentID" + QString::fromLocal8Bit( pInvestorPosition->InstrumentID));
        AppendLog("\tBrokerID" + QString::fromLocal8Bit( pInvestorPosition->BrokerID));
        AppendLog("\tInvestorID" + QString::fromLocal8Bit( pInvestorPosition->InvestorID));
        AppendLog("\tTradingDay" + QString::fromLocal8Bit( pInvestorPosition->TradingDay));
        AppendLog("\tExchangeID" + QString::fromLocal8Bit( pInvestorPosition->ExchangeID));
        AppendLog("\tInvestUnitID" + QString::fromLocal8Bit( pInvestorPosition->InvestUnitID));
        AppendLog("\tYdPosition "+ QString::number( pInvestorPosition->YdPosition));
        AppendLog("\tPosition "+ QString::number( pInvestorPosition->Position));
        AppendLog("\tLongFrozen "+ QString::number( pInvestorPosition->LongFrozen));
        AppendLog("\tShortFrozen "+ QString::number( pInvestorPosition->ShortFrozen));
        AppendLog("\tOpenVolume "+ QString::number( pInvestorPosition->OpenVolume));
        AppendLog("\tCloseVolume "+ QString::number( pInvestorPosition->CloseVolume));
        AppendLog("\tSettlementID "+ QString::number( pInvestorPosition->SettlementID));
        AppendLog("\tCombPosition "+ QString::number( pInvestorPosition->CombPosition));
        AppendLog("\tCombLongFrozen "+ QString::number( pInvestorPosition->CombLongFrozen));
        AppendLog("\tCombShortFrozen "+ QString::number( pInvestorPosition->CombShortFrozen));
        AppendLog("\tTodayPosition "+ QString::number( pInvestorPosition->TodayPosition));
        AppendLog("\tStrikeFrozen "+ QString::number( pInvestorPosition->StrikeFrozen));
        AppendLog("\tAbandonFrozen "+ QString::number( pInvestorPosition->AbandonFrozen));
        AppendLog("\tYdStrikeFrozen "+ QString::number( pInvestorPosition->YdStrikeFrozen));
        AppendLog("\tPosiDirection " + QString( pInvestorPosition->PosiDirection));
        AppendLog("\tHedgeFlag " + QString( pInvestorPosition->HedgeFlag));
        AppendLog("\tPositionDate " + QString( pInvestorPosition->PositionDate));
        AppendLog("\tLongFrozenAmount "+ QString::number( pInvestorPosition->LongFrozenAmount));
        AppendLog("\tShortFrozenAmount "+ QString::number( pInvestorPosition->ShortFrozenAmount));
        AppendLog("\tOpenAmount "+ QString::number( pInvestorPosition->OpenAmount));
        AppendLog("\tCloseAmount "+ QString::number( pInvestorPosition->CloseAmount));
        AppendLog("\tPositionCost "+ QString::number( pInvestorPosition->PositionCost));
        AppendLog("\tPreMargin "+ QString::number( pInvestorPosition->PreMargin));
        AppendLog("\tUseMargin "+ QString::number( pInvestorPosition->UseMargin));
        AppendLog("\tFrozenMargin "+ QString::number( pInvestorPosition->FrozenMargin));
        AppendLog("\tFrozenCash "+ QString::number( pInvestorPosition->FrozenCash));
        AppendLog("\tFrozenCommission "+ QString::number( pInvestorPosition->FrozenCommission));
        AppendLog("\tCashIn "+ QString::number( pInvestorPosition->CashIn));
        AppendLog("\tCommission "+ QString::number( pInvestorPosition->Commission));
        AppendLog("\tCloseProfit "+ QString::number( pInvestorPosition->CloseProfit));
        AppendLog("\tPositionProfit "+ QString::number( pInvestorPosition->PositionProfit));
        AppendLog("\tPreSettlementPrice "+ QString::number( pInvestorPosition->PreSettlementPrice));
        AppendLog("\tSettlementPrice "+ QString::number( pInvestorPosition->SettlementPrice));
        AppendLog("\tOpenCost "+ QString::number( pInvestorPosition->OpenCost));
        AppendLog("\tExchangeMargin "+ QString::number( pInvestorPosition->ExchangeMargin));
        AppendLog("\tCloseProfitByDate "+ QString::number( pInvestorPosition->CloseProfitByDate));
        AppendLog("\tCloseProfitByTrade "+ QString::number( pInvestorPosition->CloseProfitByTrade));
        AppendLog("\tMarginRateByMoney "+ QString::number( pInvestorPosition->MarginRateByMoney));
        AppendLog("\tMarginRateByVolume "+ QString::number( pInvestorPosition->MarginRateByVolume));
        AppendLog("\tStrikeFrozenAmount "+ QString::number( pInvestorPosition->StrikeFrozenAmount));
    }
    if (pRspInfo)
    {
        AppendLog("\tErrorMsg" + QString::fromLocal8Bit( pRspInfo->ErrorMsg));
        AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
    }
    AppendLog("\tnRequestID "+ QString::number( nRequestID));
    AppendLog("\tbIsLast "+ QString::number( bIsLast));
    AppendLog("</OnRspQryInvestorPosition>");
}
void MainWindow::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo){
    AppendLog("<OnErrRtnOrderAction>");
    if (pOrderAction)
    {
        AppendLog("\tBrokerID" + QString::fromLocal8Bit( pOrderAction->BrokerID));
        AppendLog("\tInvestorID" + QString::fromLocal8Bit( pOrderAction->InvestorID));
        AppendLog("\tOrderRef" + QString::fromLocal8Bit( pOrderAction->OrderRef));
        AppendLog("\tExchangeID" + QString::fromLocal8Bit( pOrderAction->ExchangeID));
        AppendLog("\tOrderSysID" + QString::fromLocal8Bit( pOrderAction->OrderSysID));
        AppendLog("\tActionDate" + QString::fromLocal8Bit( pOrderAction->ActionDate));
        AppendLog("\tActionTime" + QString::fromLocal8Bit( pOrderAction->ActionTime));
        AppendLog("\tTraderID" + QString::fromLocal8Bit( pOrderAction->TraderID));
        AppendLog("\tOrderLocalID" + QString::fromLocal8Bit( pOrderAction->OrderLocalID));
        AppendLog("\tActionLocalID" + QString::fromLocal8Bit( pOrderAction->ActionLocalID));
        AppendLog("\tParticipantID" + QString::fromLocal8Bit( pOrderAction->ParticipantID));
        AppendLog("\tClientID" + QString::fromLocal8Bit( pOrderAction->ClientID));
        AppendLog("\tBusinessUnit" + QString::fromLocal8Bit( pOrderAction->BusinessUnit));
        AppendLog("\tUserID" + QString::fromLocal8Bit( pOrderAction->UserID));
        AppendLog("\tStatusMsg" + QString::fromLocal8Bit( pOrderAction->StatusMsg));
        AppendLog("\tInstrumentID" + QString::fromLocal8Bit( pOrderAction->InstrumentID));
        AppendLog("\tBranchID" + QString::fromLocal8Bit( pOrderAction->BranchID));
        AppendLog("\tInvestUnitID" + QString::fromLocal8Bit( pOrderAction->InvestUnitID));
        AppendLog("\tIPAddress" + QString::fromLocal8Bit( pOrderAction->IPAddress));
        AppendLog("\tMacAddress" + QString::fromLocal8Bit( pOrderAction->MacAddress));
        AppendLog("\tOrderActionRef "+ QString::number( pOrderAction->OrderActionRef));
        AppendLog("\tRequestID "+ QString::number( pOrderAction->RequestID));
        AppendLog("\tFrontID "+ QString::number( pOrderAction->FrontID));
        AppendLog("\tSessionID "+ QString::number( pOrderAction->SessionID));
        AppendLog("\tVolumeChange "+ QString::number( pOrderAction->VolumeChange));
        AppendLog("\tInstallID "+ QString::number( pOrderAction->InstallID));
        AppendLog("\tActionFlag " + QString( pOrderAction->ActionFlag));
        AppendLog("\tOrderActionStatus " + QString( pOrderAction->OrderActionStatus));
        AppendLog("\tLimitPrice "+ QString::number( pOrderAction->LimitPrice));
    }
    if (pRspInfo)
    {
        AppendLog("\tErrorMsg" + QString::fromLocal8Bit( pRspInfo->ErrorMsg));
        AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
    }
    AppendLog("</OnErrRtnOrderAction>");
}
void MainWindow::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    AppendLog("<OnRspOrderAction>");
    if (pInputOrderAction)
    {
        AppendLog("\tBrokerID" + QString::fromLocal8Bit( pInputOrderAction->BrokerID));
        AppendLog("\tInvestorID" + QString::fromLocal8Bit( pInputOrderAction->InvestorID));
        AppendLog("\tOrderRef" + QString::fromLocal8Bit( pInputOrderAction->OrderRef));
        AppendLog("\tExchangeID" + QString::fromLocal8Bit( pInputOrderAction->ExchangeID));
        AppendLog("\tOrderSysID" + QString::fromLocal8Bit( pInputOrderAction->OrderSysID));
        AppendLog("\tUserID" + QString::fromLocal8Bit( pInputOrderAction->UserID));
        AppendLog("\tInstrumentID" + QString::fromLocal8Bit( pInputOrderAction->InstrumentID));
        AppendLog("\tInvestUnitID" + QString::fromLocal8Bit( pInputOrderAction->InvestUnitID));
        AppendLog("\tIPAddress" + QString::fromLocal8Bit( pInputOrderAction->IPAddress));
        AppendLog("\tMacAddress" + QString::fromLocal8Bit( pInputOrderAction->MacAddress));
        AppendLog("\tOrderActionRef "+ QString::number( pInputOrderAction->OrderActionRef));
        AppendLog("\tRequestID "+ QString::number( pInputOrderAction->RequestID));
        AppendLog("\tFrontID "+ QString::number( pInputOrderAction->FrontID));
        AppendLog("\tSessionID "+ QString::number( pInputOrderAction->SessionID));
        AppendLog("\tVolumeChange "+ QString::number( pInputOrderAction->VolumeChange));
        AppendLog("\tActionFlag " + QString( pInputOrderAction->ActionFlag));
        AppendLog("\tLimitPrice "+ QString::number( pInputOrderAction->LimitPrice));
    }
    if (pRspInfo)
    {
        AppendLog("\tErrorMsg" + QString::fromLocal8Bit( pRspInfo->ErrorMsg));
        AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
    }
    AppendLog("\tnRequestID "+ QString::number( nRequestID));
    AppendLog("\tbIsLast "+ QString::number( bIsLast));
    AppendLog("</OnRspOrderAction>");
}
void MainWindow::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo){
    AppendLog("<OnErrRtnOrderInsert>");
    if (pInputOrder)
    {
        AppendLog("\tBrokerID" + QString::fromLocal8Bit( pInputOrder->BrokerID));
        AppendLog("\tInvestorID" + QString::fromLocal8Bit( pInputOrder->InvestorID));
        AppendLog("\tInstrumentID" + QString::fromLocal8Bit( pInputOrder->InstrumentID));
        AppendLog("\tOrderRef" + QString::fromLocal8Bit( pInputOrder->OrderRef));
        AppendLog("\tUserID" + QString::fromLocal8Bit( pInputOrder->UserID));
        AppendLog("\tCombOffsetFlag" + QString::fromLocal8Bit( pInputOrder->CombOffsetFlag));
        AppendLog("\tCombHedgeFlag" + QString::fromLocal8Bit( pInputOrder->CombHedgeFlag));
        AppendLog("\tGTDDate" + QString::fromLocal8Bit( pInputOrder->GTDDate));
        AppendLog("\tBusinessUnit" + QString::fromLocal8Bit( pInputOrder->BusinessUnit));
        AppendLog("\tExchangeID" + QString::fromLocal8Bit( pInputOrder->ExchangeID));
        AppendLog("\tInvestUnitID" + QString::fromLocal8Bit( pInputOrder->InvestUnitID));
        AppendLog("\tAccountID" + QString::fromLocal8Bit( pInputOrder->AccountID));
        AppendLog("\tCurrencyID" + QString::fromLocal8Bit( pInputOrder->CurrencyID));
        AppendLog("\tClientID" + QString::fromLocal8Bit( pInputOrder->ClientID));
        AppendLog("\tIPAddress" + QString::fromLocal8Bit( pInputOrder->IPAddress));
        AppendLog("\tMacAddress" + QString::fromLocal8Bit( pInputOrder->MacAddress));
        AppendLog("\tVolumeTotalOriginal "+ QString::number( pInputOrder->VolumeTotalOriginal));
        AppendLog("\tMinVolume "+ QString::number( pInputOrder->MinVolume));
        AppendLog("\tIsAutoSuspend "+ QString::number( pInputOrder->IsAutoSuspend));
        AppendLog("\tRequestID "+ QString::number( pInputOrder->RequestID));
        AppendLog("\tUserForceClose "+ QString::number( pInputOrder->UserForceClose));
        AppendLog("\tIsSwapOrder "+ QString::number( pInputOrder->IsSwapOrder));
        AppendLog("\tOrderPriceType " + QString( pInputOrder->OrderPriceType));
        AppendLog("\tDirection " + QString( pInputOrder->Direction));
        AppendLog("\tTimeCondition " + QString( pInputOrder->TimeCondition));
        AppendLog("\tVolumeCondition " + QString( pInputOrder->VolumeCondition));
        AppendLog("\tContingentCondition " + QString( pInputOrder->ContingentCondition));
        AppendLog("\tForceCloseReason " + QString( pInputOrder->ForceCloseReason));
        AppendLog("\tLimitPrice "+ QString::number( pInputOrder->LimitPrice));
        AppendLog("\tStopPrice "+ QString::number( pInputOrder->StopPrice));
    }
    if (pRspInfo)
    {
        AppendLog("\tErrorMsg" + QString::fromLocal8Bit( pRspInfo->ErrorMsg));
        AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
    }
    AppendLog("</OnErrRtnOrderInsert>");
}
void MainWindow::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    AppendLog("<OnRspQryOrder>");
    if (pOrder)
    {
        AppendLog("\tBrokerID " + QString::fromLocal8Bit( pOrder->BrokerID));
        AppendLog("\tInvestorID " + QString::fromLocal8Bit( pOrder->InvestorID));
        AppendLog("\tInstrumentID " + QString::fromLocal8Bit( pOrder->InstrumentID));
        AppendLog("\tOrderRef " + QString::fromLocal8Bit( pOrder->OrderRef));
        AppendLog("\tUserID " + QString::fromLocal8Bit( pOrder->UserID));
        AppendLog("\tCombOffsetFlag " + QString::fromLocal8Bit( pOrder->CombOffsetFlag));
        AppendLog("\tCombHedgeFlag " + QString::fromLocal8Bit( pOrder->CombHedgeFlag));
        AppendLog("\tGTDDate " + QString::fromLocal8Bit( pOrder->GTDDate));
        AppendLog("\tBusinessUnit " + QString::fromLocal8Bit( pOrder->BusinessUnit));
        AppendLog("\tOrderLocalID " + QString::fromLocal8Bit( pOrder->OrderLocalID));
        AppendLog("\tExchangeID " + QString::fromLocal8Bit( pOrder->ExchangeID));
        AppendLog("\tParticipantID " + QString::fromLocal8Bit( pOrder->ParticipantID));
        AppendLog("\tClientID " + QString::fromLocal8Bit( pOrder->ClientID));
        AppendLog("\tExchangeInstID " + QString::fromLocal8Bit( pOrder->ExchangeInstID));
        AppendLog("\tTraderID " + QString::fromLocal8Bit( pOrder->TraderID));
        AppendLog("\tTradingDay " + QString::fromLocal8Bit( pOrder->TradingDay));
        AppendLog("\tOrderSysID " + QString::fromLocal8Bit( pOrder->OrderSysID));
        AppendLog("\tInsertDate " + QString::fromLocal8Bit( pOrder->InsertDate));
        AppendLog("\tInsertTime " + QString::fromLocal8Bit( pOrder->InsertTime));
        AppendLog("\tActiveTime " + QString::fromLocal8Bit( pOrder->ActiveTime));
        AppendLog("\tSuspendTime " + QString::fromLocal8Bit( pOrder->SuspendTime));
        AppendLog("\tUpdateTime " + QString::fromLocal8Bit( pOrder->UpdateTime));
        AppendLog("\tCancelTime " + QString::fromLocal8Bit( pOrder->CancelTime));
        AppendLog("\tActiveTraderID " + QString::fromLocal8Bit( pOrder->ActiveTraderID));
        AppendLog("\tClearingPartID " + QString::fromLocal8Bit( pOrder->ClearingPartID));
        AppendLog("\tUserProductInfo " + QString::fromLocal8Bit( pOrder->UserProductInfo));
        AppendLog("\tStatusMsg " + QString::fromLocal8Bit( pOrder->StatusMsg));
        AppendLog("\tActiveUserID " + QString::fromLocal8Bit( pOrder->ActiveUserID));
        AppendLog("\tRelativeOrderSysID " + QString::fromLocal8Bit( pOrder->RelativeOrderSysID));
        AppendLog("\tBranchID " + QString::fromLocal8Bit( pOrder->BranchID));
        AppendLog("\tInvestUnitID " + QString::fromLocal8Bit( pOrder->InvestUnitID));
        AppendLog("\tAccountID " + QString::fromLocal8Bit( pOrder->AccountID));
        AppendLog("\tCurrencyID " + QString::fromLocal8Bit( pOrder->CurrencyID));
        AppendLog("\tIPAddress " + QString::fromLocal8Bit( pOrder->IPAddress));
        AppendLog("\tMacAddress " + QString::fromLocal8Bit( pOrder->MacAddress));
        AppendLog("\tVolumeTotalOriginal "+ QString::number( pOrder->VolumeTotalOriginal));
        AppendLog("\tMinVolume "+ QString::number( pOrder->MinVolume));
        AppendLog("\tIsAutoSuspend "+ QString::number( pOrder->IsAutoSuspend));
        AppendLog("\tRequestID "+ QString::number( pOrder->RequestID));
        AppendLog("\tInstallID "+ QString::number( pOrder->InstallID));
        AppendLog("\tNotifySequence "+ QString::number( pOrder->NotifySequence));
        AppendLog("\tSettlementID "+ QString::number( pOrder->SettlementID));
        AppendLog("\tVolumeTraded "+ QString::number( pOrder->VolumeTraded));
        AppendLog("\tVolumeTotal "+ QString::number( pOrder->VolumeTotal));
        AppendLog("\tSequenceNo "+ QString::number( pOrder->SequenceNo));
        AppendLog("\tFrontID "+ QString::number( pOrder->FrontID));
        AppendLog("\tSessionID "+ QString::number( pOrder->SessionID));
        AppendLog("\tUserForceClose "+ QString::number( pOrder->UserForceClose));
        AppendLog("\tBrokerOrderSeq "+ QString::number( pOrder->BrokerOrderSeq));
        AppendLog("\tZCETotalTradedVolume "+ QString::number( pOrder->ZCETotalTradedVolume));
        AppendLog("\tIsSwapOrder "+ QString::number( pOrder->IsSwapOrder));
        AppendLog("\tOrderPriceType " + QString( pOrder->OrderPriceType));
        AppendLog("\tDirection " + QString( pOrder->Direction));
        AppendLog("\tTimeCondition " + QString( pOrder->TimeCondition));
        AppendLog("\tVolumeCondition " + QString( pOrder->VolumeCondition));
        AppendLog("\tContingentCondition " + QString( pOrder->ContingentCondition));
        AppendLog("\tForceCloseReason " + QString( pOrder->ForceCloseReason));
        AppendLog("\tOrderSubmitStatus " + QString( pOrder->OrderSubmitStatus));
        AppendLog("\tOrderSource " + QString( pOrder->OrderSource));
        AppendLog("\tOrderStatus " + QString( pOrder->OrderStatus));
        AppendLog("\tOrderType " + QString( pOrder->OrderType));
        AppendLog("\tLimitPrice "+ QString::number( pOrder->LimitPrice));
        AppendLog("\tStopPrice "+ QString::number( pOrder->StopPrice));
    }
    if (pRspInfo)
    {
        AppendLog("\tErrorMsg" + QString::fromLocal8Bit( pRspInfo->ErrorMsg));
        AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
    }
    AppendLog("\tnRequestID "+ QString::number( nRequestID));
    AppendLog("\tbIsLast "+ QString::number( bIsLast));
    AppendLog("</OnRspQryOrder>");
}
void MainWindow::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    AppendLog("<OnRspQryTradingAccount>");
    if (pTradingAccount)
    {
        AppendLog("\tBrokerID " + QString::fromLocal8Bit( pTradingAccount->BrokerID));
        AppendLog("\tAccountID " + QString::fromLocal8Bit( pTradingAccount->AccountID));
        AppendLog("\tTradingDay " + QString::fromLocal8Bit( pTradingAccount->TradingDay));
        AppendLog("\tCurrencyID " + QString::fromLocal8Bit( pTradingAccount->CurrencyID));
        AppendLog("\tSettlementID "+ QString::number( pTradingAccount->SettlementID));
        AppendLog("\tBizType " + QString( pTradingAccount->BizType));
        AppendLog("\tPreMortgage "+ QString::number( pTradingAccount->PreMortgage));
        AppendLog("\tPreCredit "+ QString::number( pTradingAccount->PreCredit));
        AppendLog("\tPreDeposit "+ QString::number( pTradingAccount->PreDeposit));
        AppendLog("\tPreBalance "+ QString::number( pTradingAccount->PreBalance));
        AppendLog("\tPreMargin "+ QString::number( pTradingAccount->PreMargin));
        AppendLog("\tInterestBase "+ QString::number( pTradingAccount->InterestBase));
        AppendLog("\tInterest "+ QString::number( pTradingAccount->Interest));
        AppendLog("\tDeposit "+ QString::number( pTradingAccount->Deposit));
        AppendLog("\tWithdraw "+ QString::number( pTradingAccount->Withdraw));
        AppendLog("\tFrozenMargin "+ QString::number( pTradingAccount->FrozenMargin));
        AppendLog("\tFrozenCash "+ QString::number( pTradingAccount->FrozenCash));
        AppendLog("\tFrozenCommission "+ QString::number( pTradingAccount->FrozenCommission));
        AppendLog("\tCurrMargin "+ QString::number( pTradingAccount->CurrMargin));
        AppendLog("\tCashIn "+ QString::number( pTradingAccount->CashIn));
        AppendLog("\tCommission "+ QString::number( pTradingAccount->Commission));
        AppendLog("\tCloseProfit "+ QString::number( pTradingAccount->CloseProfit));
        AppendLog("\tPositionProfit "+ QString::number( pTradingAccount->PositionProfit));
        AppendLog("\tBalance "+ QString::number( pTradingAccount->Balance));
        AppendLog("\tAvailable "+ QString::number( pTradingAccount->Available));
        AppendLog("\tWithdrawQuota "+ QString::number( pTradingAccount->WithdrawQuota));
        AppendLog("\tReserve "+ QString::number( pTradingAccount->Reserve));
        AppendLog("\tCredit "+ QString::number( pTradingAccount->Credit));
        AppendLog("\tMortgage "+ QString::number( pTradingAccount->Mortgage));
        AppendLog("\tExchangeMargin "+ QString::number( pTradingAccount->ExchangeMargin));
        AppendLog("\tDeliveryMargin "+ QString::number( pTradingAccount->DeliveryMargin));
        AppendLog("\tExchangeDeliveryMargin "+ QString::number( pTradingAccount->ExchangeDeliveryMargin));
        AppendLog("\tReserveBalance "+ QString::number( pTradingAccount->ReserveBalance));
        AppendLog("\tPreFundMortgageIn "+ QString::number( pTradingAccount->PreFundMortgageIn));
        AppendLog("\tPreFundMortgageOut "+ QString::number( pTradingAccount->PreFundMortgageOut));
        AppendLog("\tFundMortgageIn "+ QString::number( pTradingAccount->FundMortgageIn));
        AppendLog("\tFundMortgageOut "+ QString::number( pTradingAccount->FundMortgageOut));
        AppendLog("\tFundMortgageAvailable "+ QString::number( pTradingAccount->FundMortgageAvailable));
        AppendLog("\tMortgageableFund "+ QString::number( pTradingAccount->MortgageableFund));
        AppendLog("\tSpecProductMargin "+ QString::number( pTradingAccount->SpecProductMargin));
        AppendLog("\tSpecProductFrozenMargin "+ QString::number( pTradingAccount->SpecProductFrozenMargin));
        AppendLog("\tSpecProductCommission "+ QString::number( pTradingAccount->SpecProductCommission));
        AppendLog("\tSpecProductFrozenCommission "+ QString::number( pTradingAccount->SpecProductFrozenCommission));
        AppendLog("\tSpecProductPositionProfit "+ QString::number( pTradingAccount->SpecProductPositionProfit));
        AppendLog("\tSpecProductCloseProfit "+ QString::number( pTradingAccount->SpecProductCloseProfit));
        AppendLog("\tSpecProductPositionProfitByAlg "+ QString::number( pTradingAccount->SpecProductPositionProfitByAlg));
        AppendLog("\tSpecProductExchangeMargin "+ QString::number( pTradingAccount->SpecProductExchangeMargin));
        AppendLog("\tFrozenSwap "+ QString::number( pTradingAccount->FrozenSwap));
        AppendLog("\tRemainSwap "+ QString::number( pTradingAccount->RemainSwap));
    }
    if (pRspInfo)
    {
        AppendLog("\tErrorMsg " + QString::fromLocal8Bit( pRspInfo->ErrorMsg));
        AppendLog("\tErrorID "+ QString::number( pRspInfo->ErrorID));
    }
    AppendLog("\tnRequestID "+ QString::number( nRequestID));
    AppendLog("\tbIsLast "+ QString::number( bIsLast));
    AppendLog("</OnRspQryTradingAccount>");
}

void MainWindow::on_btn_qry_Order_clicked()
{
    QryOrder();
}

int MainWindow::ReqQryTradingAccount(){
   CThostFtdcQryTradingAccountField a = { 0 };
   strcpy_s(a.BrokerID, m_BrokerID);
   strcpy_s(a.InvestorID, m_InvestorID);
   strcpy_s(a.CurrencyID, "CNY");
   return m_ptraderapi->ReqQryTradingAccount(&a, 5);
}

int MainWindow::qryInstrument(QString sInstrumentID)
{
    //qDebug() << "查询合约 " << endl;
    CThostFtdcQryInstrumentField t = { 0 };
    std::string strt = sInstrumentID.toStdString();
    const char* str1 = strt.c_str();
    strcpy_s(t.InstrumentID, str1);
    while (m_ptraderapi->ReqQryInstrument(&t, 6) != 0) {
        Sleep(1000);

    }
    return 0;
}

int MainWindow::qryInvestorPositon(){
    CThostFtdcQryInvestorPositionField a = { 0 };
    strcpy_s(a.BrokerID, m_BrokerID);
    strcpy_s(a.InvestorID, m_UserID);
    strcpy_s(a.InstrumentID, "");//不填写合约则返回所有持仓
    return m_ptraderapi->ReqQryInvestorPosition(&a, 7);
}

int MainWindow::QryOrder()
{
    CThostFtdcQryOrderField a = { 0 };
    strcpy_s(a.BrokerID, m_BrokerID);
    strcpy_s(a.InvestorID, m_InvestorID);
    return m_ptraderapi->ReqQryOrder(&a, 8);
}

int MainWindow::CancelOrder(CThostFtdcOrderField AOrder)
{
    CThostFtdcInputOrderActionField a ={ 0 };
    strcpy_s(a.BrokerID, m_BrokerID);
    strcpy_s(a.InvestorID, m_InvestorID);
    a.OrderActionRef = 0;
    strcpy_s(a.OrderRef,AOrder.OrderRef);
    a.RequestID = AOrder.RequestID;
    a.FrontID = AOrder.FrontID;
    a.SessionID = AOrder.SessionID;
    strcpy_s(a.ExchangeID, AOrder.ExchangeID);
    strcpy_s(a.OrderSysID, AOrder.OrderSysID);
    a.ActionFlag = THOST_FTDC_AF_Delete;
    a.LimitPrice = AOrder.LimitPrice;
    a.VolumeChange = 0;
    strcpy_s(a.UserID, m_UserID);
    strcpy_s(a.InstrumentID, AOrder.InstrumentID);
    return m_ptraderapi->ReqOrderAction(&a, 9);
}


void MainWindow::ReqSettlementInfoConfirm(){
    CThostFtdcSettlementInfoConfirmField Confirm = { 0 };
    strcpy_s(Confirm.BrokerID, m_BrokerID);
    strcpy_s(Confirm.InvestorID, m_InvestorID);
    m_ptraderapi->ReqSettlementInfoConfirm(&Confirm, 10);
}



void MainWindow::on_pushButton_clicked()
{
   qryInvestorPositon();
}

void MainWindow::on_pushButton_2_clicked()
{
    ReqSettlementInfoConfirm();
}

void MainWindow::on_pushButton_3_clicked()
{
ReqQryTradingAccount();
}

void MainWindow::AppendLog(QString msg){
  emit send_AppendMsg(msg);
}

void MainWindow::on_AppendMsg(QString msg){
QDateTime current_date_time = QDateTime::currentDateTime();
QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz");
ui->edt_log->append(current_date + "-> " + msg);
}
