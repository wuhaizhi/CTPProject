#include "traderspi.h"
#include <stdio.h>
#include <QDebug>
void CTraderSpi::OnFrontConnected()
{
    qDebug("<OnFrontConnected>\n");
    Status = LSConnected;
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnFrontConnected();
    }
    qDebug("</OnFrontConnected>\n");
};

void CTraderSpi::RegisterSpi(CThostFtdcTraderSpi *pSpi){
  m_SpiList.append(pSpi);
}

void CTraderSpi::UnReisterSpi(CThostFtdcTraderSpi *pSpi){
    for (int i = 0; i < m_SpiList.size();i++) {
        CThostFtdcTraderSpi* traderSpi = m_SpiList.at(i);
        if (traderSpi == pSpi){
            m_SpiList.removeAt(i);
            break;
        }
    }
}

void CTraderSpi::OnFrontDisconnected(int nReason)
{
    qDebug("<OnFrontDisconnected>\n");
    qDebug("\tnReason [%d]\n", nReason);
    Status = LSDisconnected;
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnFrontDisconnected(nReason);
    }
    qDebug("</OnFrontDisconnected>\n");
}

void CTraderSpi::OnHeartBeatWarning(int nTimeLapse)
{
    qDebug("<OnHeartBeatWarning>\n");
    qDebug("\tnTimeLapse [%d]\n", nTimeLapse);
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnHeartBeatWarning(nTimeLapse);
    }
    qDebug("</OnHeartBeatWarning>\n");
}

void CTraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspAuthenticate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspAuthenticate(pRspAuthenticateField, pRspInfo,nRequestID,bIsLast);
    }
    if (pRspAuthenticateField)
    {
        qDebug("\tBrokerID [%s]\n", pRspAuthenticateField->BrokerID);
        qDebug("\tUserID [%s]\n", pRspAuthenticateField->UserID);
        qDebug("\tUserProductInfo [%s]\n", pRspAuthenticateField->UserProductInfo);
        qDebug("\tAppID [%s]\n", pRspAuthenticateField->AppID);
        qDebug("\tAppType [%c]\n", pRspAuthenticateField->AppType);
    }
    if (pRspInfo)
    {
        if (pRspInfo->ErrorID == 0){
            Status = LSAuthenticate_successful;
        }else
        {
             Status = LSAuthenticate_failed;
        }
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspAuthenticate>\n");
};

void CTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspUserLogin>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspUserLogin(pRspUserLogin, pRspInfo,nRequestID,bIsLast);
    }
    if (pRspUserLogin)
    {
        qDebug("\tTradingDay [%s]\n", pRspUserLogin->TradingDay);
        qDebug("\tLoginTime [%s]\n", pRspUserLogin->LoginTime);
        qDebug("\tBrokerID [%s]\n", pRspUserLogin->BrokerID);
        qDebug("\tUserID [%s]\n", pRspUserLogin->UserID);
        qDebug("\tSystemName [%s]\n", pRspUserLogin->SystemName);
        qDebug("\tMaxOrderRef [%s]\n", pRspUserLogin->MaxOrderRef);
        qDebug("\tSHFETime [%s]\n", pRspUserLogin->SHFETime);
        qDebug("\tDCETime [%s]\n", pRspUserLogin->DCETime);
        qDebug("\tCZCETime [%s]\n", pRspUserLogin->CZCETime);
        qDebug("\tFFEXTime [%s]\n", pRspUserLogin->FFEXTime);
        qDebug("\tINETime [%s]\n", pRspUserLogin->INETime);
        qDebug("\tFrontID [%d]\n", pRspUserLogin->FrontID);
        qDebug("\tSessionID [%d]\n", pRspUserLogin->SessionID);
    }
    if (pRspInfo)
    {
        if (pRspInfo->ErrorID == 0){
            Status = LSLogin_successful;
        }else
        {
             Status = LSLogin_failed;
        }
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspUserLogin>\n");
};

void CTraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspUserLogout>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspUserLogout(pUserLogout, pRspInfo,nRequestID,bIsLast);
    }
    if (pUserLogout)
    {
        qDebug("\tBrokerID [%s]\n", pUserLogout->BrokerID);
        qDebug("\tUserID [%s]\n", pUserLogout->UserID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspUserLogout>\n");
};

void CTraderSpi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspUserPasswordUpdate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspUserPasswordUpdate(pUserPasswordUpdate, pRspInfo,nRequestID,bIsLast);
    }
    if (pUserPasswordUpdate)
    {
        qDebug("\tBrokerID [%s]\n", pUserPasswordUpdate->BrokerID);
        qDebug("\tUserID [%s]\n", pUserPasswordUpdate->UserID);
        qDebug("\tOldPassword [%s]\n", pUserPasswordUpdate->OldPassword);
        qDebug("\tNewPassword [%s]\n", pUserPasswordUpdate->NewPassword);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspUserPasswordUpdate>\n");
};

void CTraderSpi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspTradingAccountPasswordUpdate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate, pRspInfo,nRequestID,bIsLast);
    }
    if (pTradingAccountPasswordUpdate)
    {
        qDebug("\tBrokerID [%s]\n", pTradingAccountPasswordUpdate->BrokerID);
        qDebug("\tAccountID [%s]\n", pTradingAccountPasswordUpdate->AccountID);
        qDebug("\tOldPassword [%s]\n", pTradingAccountPasswordUpdate->OldPassword);
        qDebug("\tNewPassword [%s]\n", pTradingAccountPasswordUpdate->NewPassword);
        qDebug("\tCurrencyID [%s]\n", pTradingAccountPasswordUpdate->CurrencyID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspTradingAccountPasswordUpdate>\n");
};

void CTraderSpi::OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspUserAuthMethod>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspUserAuthMethod(pRspUserAuthMethod, pRspInfo,nRequestID,bIsLast);
    }
    if (pRspUserAuthMethod)
    {
        qDebug("\tUsableAuthMethod [%d]\n", pRspUserAuthMethod->UsableAuthMethod);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspUserAuthMethod>\n");
};

void CTraderSpi::OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspGenUserCaptcha>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspGenUserCaptcha(pRspGenUserCaptcha, pRspInfo,nRequestID,bIsLast);
    }
    if (pRspGenUserCaptcha)
    {
        qDebug("\tBrokerID [%s]\n", pRspGenUserCaptcha->BrokerID);
        qDebug("\tUserID [%s]\n", pRspGenUserCaptcha->UserID);
        qDebug("\tCaptchaInfo [%s]\n", pRspGenUserCaptcha->CaptchaInfo);
        qDebug("\tCaptchaInfoLen [%d]\n", pRspGenUserCaptcha->CaptchaInfoLen);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspGenUserCaptcha>\n");
};

void CTraderSpi::OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspGenUserText>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspGenUserText(pRspGenUserText, pRspInfo,nRequestID,bIsLast);
    }
    if (pRspGenUserText)
    {
        qDebug("\tUserTextSeq [%d]\n", pRspGenUserText->UserTextSeq);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspGenUserText>\n");
};

void CTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspOrderInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspOrderInsert(pInputOrder, pRspInfo,nRequestID,bIsLast);
    }
    if (pInputOrder)
    {
        qDebug("\tBrokerID [%s]\n", pInputOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputOrder->InstrumentID);
        qDebug("\tOrderRef [%s]\n", pInputOrder->OrderRef);
        qDebug("\tUserID [%s]\n", pInputOrder->UserID);
        qDebug("\tCombOffsetFlag [%s]\n", pInputOrder->CombOffsetFlag);
        qDebug("\tCombHedgeFlag [%s]\n", pInputOrder->CombHedgeFlag);
        qDebug("\tGTDDate [%s]\n", pInputOrder->GTDDate);
        qDebug("\tBusinessUnit [%s]\n", pInputOrder->BusinessUnit);
        qDebug("\tExchangeID [%s]\n", pInputOrder->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInputOrder->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pInputOrder->AccountID);
        qDebug("\tCurrencyID [%s]\n", pInputOrder->CurrencyID);
        qDebug("\tClientID [%s]\n", pInputOrder->ClientID);
        qDebug("\tIPAddress [%s]\n", pInputOrder->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputOrder->MacAddress);
        qDebug("\tVolumeTotalOriginal [%d]\n", pInputOrder->VolumeTotalOriginal);
        qDebug("\tMinVolume [%d]\n", pInputOrder->MinVolume);
        qDebug("\tIsAutoSuspend [%d]\n", pInputOrder->IsAutoSuspend);
        qDebug("\tRequestID [%d]\n", pInputOrder->RequestID);
        qDebug("\tUserForceClose [%d]\n", pInputOrder->UserForceClose);
        qDebug("\tIsSwapOrder [%d]\n", pInputOrder->IsSwapOrder);
        qDebug("\tOrderPriceType [%c]\n", pInputOrder->OrderPriceType);
        qDebug("\tDirection [%c]\n", pInputOrder->Direction);
        qDebug("\tTimeCondition [%c]\n", pInputOrder->TimeCondition);
        qDebug("\tVolumeCondition [%c]\n", pInputOrder->VolumeCondition);
        qDebug("\tContingentCondition [%c]\n", pInputOrder->ContingentCondition);
        qDebug("\tForceCloseReason [%c]\n", pInputOrder->ForceCloseReason);
        qDebug("\tLimitPrice [%.8lf]\n", pInputOrder->LimitPrice);
        qDebug("\tStopPrice [%.8lf]\n", pInputOrder->StopPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspOrderInsert>\n");
};

void CTraderSpi::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspParkedOrderInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspParkedOrderInsert(pParkedOrder, pRspInfo,nRequestID,bIsLast);
    }
    if (pParkedOrder)
    {
        qDebug("\tBrokerID [%s]\n", pParkedOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pParkedOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pParkedOrder->InstrumentID);
        qDebug("\tOrderRef [%s]\n", pParkedOrder->OrderRef);
        qDebug("\tUserID [%s]\n", pParkedOrder->UserID);
        qDebug("\tCombOffsetFlag [%s]\n", pParkedOrder->CombOffsetFlag);
        qDebug("\tCombHedgeFlag [%s]\n", pParkedOrder->CombHedgeFlag);
        qDebug("\tGTDDate [%s]\n", pParkedOrder->GTDDate);
        qDebug("\tBusinessUnit [%s]\n", pParkedOrder->BusinessUnit);
        qDebug("\tExchangeID [%s]\n", pParkedOrder->ExchangeID);
        qDebug("\tParkedOrderID [%s]\n", pParkedOrder->ParkedOrderID);
        qDebug("\tErrorMsg [%s]\n", pParkedOrder->ErrorMsg);
        qDebug("\tAccountID [%s]\n", pParkedOrder->AccountID);
        qDebug("\tCurrencyID [%s]\n", pParkedOrder->CurrencyID);
        qDebug("\tClientID [%s]\n", pParkedOrder->ClientID);
        qDebug("\tInvestUnitID [%s]\n", pParkedOrder->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pParkedOrder->IPAddress);
        qDebug("\tMacAddress [%s]\n", pParkedOrder->MacAddress);
        qDebug("\tVolumeTotalOriginal [%d]\n", pParkedOrder->VolumeTotalOriginal);
        qDebug("\tMinVolume [%d]\n", pParkedOrder->MinVolume);
        qDebug("\tIsAutoSuspend [%d]\n", pParkedOrder->IsAutoSuspend);
        qDebug("\tRequestID [%d]\n", pParkedOrder->RequestID);
        qDebug("\tUserForceClose [%d]\n", pParkedOrder->UserForceClose);
        qDebug("\tErrorID [%d]\n", pParkedOrder->ErrorID);
        qDebug("\tIsSwapOrder [%d]\n", pParkedOrder->IsSwapOrder);
        qDebug("\tOrderPriceType [%c]\n", pParkedOrder->OrderPriceType);
        qDebug("\tDirection [%c]\n", pParkedOrder->Direction);
        qDebug("\tTimeCondition [%c]\n", pParkedOrder->TimeCondition);
        qDebug("\tVolumeCondition [%c]\n", pParkedOrder->VolumeCondition);
        qDebug("\tContingentCondition [%c]\n", pParkedOrder->ContingentCondition);
        qDebug("\tForceCloseReason [%c]\n", pParkedOrder->ForceCloseReason);
        qDebug("\tUserType [%c]\n", pParkedOrder->UserType);
        qDebug("\tStatus [%c]\n", pParkedOrder->Status);
        qDebug("\tLimitPrice [%.8lf]\n", pParkedOrder->LimitPrice);
        qDebug("\tStopPrice [%.8lf]\n", pParkedOrder->StopPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspParkedOrderInsert>\n");
};

void CTraderSpi::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspParkedOrderAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspParkedOrderAction(pParkedOrderAction, pRspInfo,nRequestID,bIsLast);
    }
    if (pParkedOrderAction)
    {
        qDebug("\tBrokerID [%s]\n", pParkedOrderAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pParkedOrderAction->InvestorID);
        qDebug("\tOrderRef [%s]\n", pParkedOrderAction->OrderRef);
        qDebug("\tExchangeID [%s]\n", pParkedOrderAction->ExchangeID);
        qDebug("\tOrderSysID [%s]\n", pParkedOrderAction->OrderSysID);
        qDebug("\tUserID [%s]\n", pParkedOrderAction->UserID);
        qDebug("\tInstrumentID [%s]\n", pParkedOrderAction->InstrumentID);
        qDebug("\tParkedOrderActionID [%s]\n", pParkedOrderAction->ParkedOrderActionID);
        qDebug("\tErrorMsg [%s]\n", pParkedOrderAction->ErrorMsg);
        qDebug("\tInvestUnitID [%s]\n", pParkedOrderAction->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pParkedOrderAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pParkedOrderAction->MacAddress);
        qDebug("\tOrderActionRef [%d]\n", pParkedOrderAction->OrderActionRef);
        qDebug("\tRequestID [%d]\n", pParkedOrderAction->RequestID);
        qDebug("\tFrontID [%d]\n", pParkedOrderAction->FrontID);
        qDebug("\tSessionID [%d]\n", pParkedOrderAction->SessionID);
        qDebug("\tVolumeChange [%d]\n", pParkedOrderAction->VolumeChange);
        qDebug("\tErrorID [%d]\n", pParkedOrderAction->ErrorID);
        qDebug("\tActionFlag [%c]\n", pParkedOrderAction->ActionFlag);
        qDebug("\tUserType [%c]\n", pParkedOrderAction->UserType);
        qDebug("\tStatus [%c]\n", pParkedOrderAction->Status);
        qDebug("\tLimitPrice [%.8lf]\n", pParkedOrderAction->LimitPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspParkedOrderAction>\n");
};

void CTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspOrderAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspOrderAction(pInputOrderAction, pRspInfo,nRequestID,bIsLast);
    }
    if (pInputOrderAction)
    {
        qDebug("\tBrokerID [%s]\n", pInputOrderAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputOrderAction->InvestorID);
        qDebug("\tOrderRef [%s]\n", pInputOrderAction->OrderRef);
        qDebug("\tExchangeID [%s]\n", pInputOrderAction->ExchangeID);
        qDebug("\tOrderSysID [%s]\n", pInputOrderAction->OrderSysID);
        qDebug("\tUserID [%s]\n", pInputOrderAction->UserID);
        qDebug("\tInstrumentID [%s]\n", pInputOrderAction->InstrumentID);
        qDebug("\tInvestUnitID [%s]\n", pInputOrderAction->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pInputOrderAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputOrderAction->MacAddress);
        qDebug("\tOrderActionRef [%d]\n", pInputOrderAction->OrderActionRef);
        qDebug("\tRequestID [%d]\n", pInputOrderAction->RequestID);
        qDebug("\tFrontID [%d]\n", pInputOrderAction->FrontID);
        qDebug("\tSessionID [%d]\n", pInputOrderAction->SessionID);
        qDebug("\tVolumeChange [%d]\n", pInputOrderAction->VolumeChange);
        qDebug("\tActionFlag [%c]\n", pInputOrderAction->ActionFlag);
        qDebug("\tLimitPrice [%.8lf]\n", pInputOrderAction->LimitPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspOrderAction>\n");
};

void CTraderSpi::OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQueryMaxOrderVolume>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQueryMaxOrderVolume(pQueryMaxOrderVolume, pRspInfo,nRequestID,bIsLast);
    }
    if (pQueryMaxOrderVolume)
    {
        qDebug("\tBrokerID [%s]\n", pQueryMaxOrderVolume->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQueryMaxOrderVolume->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQueryMaxOrderVolume->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQueryMaxOrderVolume->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQueryMaxOrderVolume->InvestUnitID);
        qDebug("\tMaxVolume [%d]\n", pQueryMaxOrderVolume->MaxVolume);
        qDebug("\tDirection [%c]\n", pQueryMaxOrderVolume->Direction);
        qDebug("\tOffsetFlag [%c]\n", pQueryMaxOrderVolume->OffsetFlag);
        qDebug("\tHedgeFlag [%c]\n", pQueryMaxOrderVolume->HedgeFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQueryMaxOrderVolume>\n");
};

void CTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspSettlementInfoConfirm>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspSettlementInfoConfirm(pSettlementInfoConfirm, pRspInfo,nRequestID,bIsLast);
    }
    if (pSettlementInfoConfirm)
    {
        qDebug("\tBrokerID [%s]\n", pSettlementInfoConfirm->BrokerID);
        qDebug("\tInvestorID [%s]\n", pSettlementInfoConfirm->InvestorID);
        qDebug("\tConfirmDate [%s]\n", pSettlementInfoConfirm->ConfirmDate);
        qDebug("\tConfirmTime [%s]\n", pSettlementInfoConfirm->ConfirmTime);
        qDebug("\tAccountID [%s]\n", pSettlementInfoConfirm->AccountID);
        qDebug("\tCurrencyID [%s]\n", pSettlementInfoConfirm->CurrencyID);
        qDebug("\tSettlementID [%d]\n", pSettlementInfoConfirm->SettlementID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspSettlementInfoConfirm>\n");
};

void CTraderSpi::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspRemoveParkedOrder>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspRemoveParkedOrder(pRemoveParkedOrder, pRspInfo,nRequestID,bIsLast);
    }
    if (pRemoveParkedOrder)
    {
        qDebug("\tBrokerID [%s]\n", pRemoveParkedOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pRemoveParkedOrder->InvestorID);
        qDebug("\tParkedOrderID [%s]\n", pRemoveParkedOrder->ParkedOrderID);
        qDebug("\tInvestUnitID [%s]\n", pRemoveParkedOrder->InvestUnitID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspRemoveParkedOrder>\n");
};

void CTraderSpi::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspRemoveParkedOrderAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspRemoveParkedOrderAction(pRemoveParkedOrderAction, pRspInfo,nRequestID,bIsLast);
    }
    if (pRemoveParkedOrderAction)
    {
        qDebug("\tBrokerID [%s]\n", pRemoveParkedOrderAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pRemoveParkedOrderAction->InvestorID);
        qDebug("\tParkedOrderActionID [%s]\n", pRemoveParkedOrderAction->ParkedOrderActionID);
        qDebug("\tInvestUnitID [%s]\n", pRemoveParkedOrderAction->InvestUnitID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspRemoveParkedOrderAction>\n");
};

void CTraderSpi::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspExecOrderInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspExecOrderInsert(pInputExecOrder, pRspInfo,nRequestID,bIsLast);
    }
    if (pInputExecOrder)
    {
        qDebug("\tBrokerID [%s]\n", pInputExecOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputExecOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputExecOrder->InstrumentID);
        qDebug("\tExecOrderRef [%s]\n", pInputExecOrder->ExecOrderRef);
        qDebug("\tUserID [%s]\n", pInputExecOrder->UserID);
        qDebug("\tBusinessUnit [%s]\n", pInputExecOrder->BusinessUnit);
        qDebug("\tExchangeID [%s]\n", pInputExecOrder->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInputExecOrder->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pInputExecOrder->AccountID);
        qDebug("\tCurrencyID [%s]\n", pInputExecOrder->CurrencyID);
        qDebug("\tClientID [%s]\n", pInputExecOrder->ClientID);
        qDebug("\tIPAddress [%s]\n", pInputExecOrder->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputExecOrder->MacAddress);
        qDebug("\tVolume [%d]\n", pInputExecOrder->Volume);
        qDebug("\tRequestID [%d]\n", pInputExecOrder->RequestID);
        qDebug("\tOffsetFlag [%c]\n", pInputExecOrder->OffsetFlag);
        qDebug("\tHedgeFlag [%c]\n", pInputExecOrder->HedgeFlag);
        qDebug("\tActionType [%c]\n", pInputExecOrder->ActionType);
        qDebug("\tPosiDirection [%c]\n", pInputExecOrder->PosiDirection);
        qDebug("\tReservePositionFlag [%c]\n", pInputExecOrder->ReservePositionFlag);
        qDebug("\tCloseFlag [%c]\n", pInputExecOrder->CloseFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspExecOrderInsert>\n");
};

void CTraderSpi::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspExecOrderAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspExecOrderAction(pInputExecOrderAction, pRspInfo,nRequestID,bIsLast);
    }
    if (pInputExecOrderAction)
    {
        qDebug("\tBrokerID [%s]\n", pInputExecOrderAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputExecOrderAction->InvestorID);
        qDebug("\tExecOrderRef [%s]\n", pInputExecOrderAction->ExecOrderRef);
        qDebug("\tExchangeID [%s]\n", pInputExecOrderAction->ExchangeID);
        qDebug("\tExecOrderSysID [%s]\n", pInputExecOrderAction->ExecOrderSysID);
        qDebug("\tUserID [%s]\n", pInputExecOrderAction->UserID);
        qDebug("\tInstrumentID [%s]\n", pInputExecOrderAction->InstrumentID);
        qDebug("\tInvestUnitID [%s]\n", pInputExecOrderAction->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pInputExecOrderAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputExecOrderAction->MacAddress);
        qDebug("\tExecOrderActionRef [%d]\n", pInputExecOrderAction->ExecOrderActionRef);
        qDebug("\tRequestID [%d]\n", pInputExecOrderAction->RequestID);
        qDebug("\tFrontID [%d]\n", pInputExecOrderAction->FrontID);
        qDebug("\tSessionID [%d]\n", pInputExecOrderAction->SessionID);
        qDebug("\tActionFlag [%c]\n", pInputExecOrderAction->ActionFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspExecOrderAction>\n");
};

void CTraderSpi::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspForQuoteInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspForQuoteInsert(pInputForQuote, pRspInfo,nRequestID,bIsLast);
    }
    if (pInputForQuote)
    {
        qDebug("\tBrokerID [%s]\n", pInputForQuote->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputForQuote->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputForQuote->InstrumentID);
        qDebug("\tForQuoteRef [%s]\n", pInputForQuote->ForQuoteRef);
        qDebug("\tUserID [%s]\n", pInputForQuote->UserID);
        qDebug("\tExchangeID [%s]\n", pInputForQuote->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInputForQuote->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pInputForQuote->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputForQuote->MacAddress);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspForQuoteInsert>\n");
};

void CTraderSpi::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQuoteInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQuoteInsert(pInputQuote, pRspInfo,nRequestID,bIsLast);
    }
    if (pInputQuote)
    {
        qDebug("\tBrokerID [%s]\n", pInputQuote->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputQuote->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputQuote->InstrumentID);
        qDebug("\tQuoteRef [%s]\n", pInputQuote->QuoteRef);
        qDebug("\tUserID [%s]\n", pInputQuote->UserID);
        qDebug("\tBusinessUnit [%s]\n", pInputQuote->BusinessUnit);
        qDebug("\tAskOrderRef [%s]\n", pInputQuote->AskOrderRef);
        qDebug("\tBidOrderRef [%s]\n", pInputQuote->BidOrderRef);
        qDebug("\tForQuoteSysID [%s]\n", pInputQuote->ForQuoteSysID);
        qDebug("\tExchangeID [%s]\n", pInputQuote->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInputQuote->InvestUnitID);
        qDebug("\tClientID [%s]\n", pInputQuote->ClientID);
        qDebug("\tIPAddress [%s]\n", pInputQuote->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputQuote->MacAddress);
        qDebug("\tAskVolume [%d]\n", pInputQuote->AskVolume);
        qDebug("\tBidVolume [%d]\n", pInputQuote->BidVolume);
        qDebug("\tRequestID [%d]\n", pInputQuote->RequestID);
        qDebug("\tAskOffsetFlag [%c]\n", pInputQuote->AskOffsetFlag);
        qDebug("\tBidOffsetFlag [%c]\n", pInputQuote->BidOffsetFlag);
        qDebug("\tAskHedgeFlag [%c]\n", pInputQuote->AskHedgeFlag);
        qDebug("\tBidHedgeFlag [%c]\n", pInputQuote->BidHedgeFlag);
        qDebug("\tAskPrice [%.8lf]\n", pInputQuote->AskPrice);
        qDebug("\tBidPrice [%.8lf]\n", pInputQuote->BidPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQuoteInsert>\n");
};

void CTraderSpi::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQuoteAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQuoteAction(pInputQuoteAction, pRspInfo,nRequestID,bIsLast);
    }
    if (pInputQuoteAction)
    {
        qDebug("\tBrokerID [%s]\n", pInputQuoteAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputQuoteAction->InvestorID);
        qDebug("\tQuoteRef [%s]\n", pInputQuoteAction->QuoteRef);
        qDebug("\tExchangeID [%s]\n", pInputQuoteAction->ExchangeID);
        qDebug("\tQuoteSysID [%s]\n", pInputQuoteAction->QuoteSysID);
        qDebug("\tUserID [%s]\n", pInputQuoteAction->UserID);
        qDebug("\tInstrumentID [%s]\n", pInputQuoteAction->InstrumentID);
        qDebug("\tInvestUnitID [%s]\n", pInputQuoteAction->InvestUnitID);
        qDebug("\tClientID [%s]\n", pInputQuoteAction->ClientID);
        qDebug("\tIPAddress [%s]\n", pInputQuoteAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputQuoteAction->MacAddress);
        qDebug("\tQuoteActionRef [%d]\n", pInputQuoteAction->QuoteActionRef);
        qDebug("\tRequestID [%d]\n", pInputQuoteAction->RequestID);
        qDebug("\tFrontID [%d]\n", pInputQuoteAction->FrontID);
        qDebug("\tSessionID [%d]\n", pInputQuoteAction->SessionID);
        qDebug("\tActionFlag [%c]\n", pInputQuoteAction->ActionFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQuoteAction>\n");
};

void CTraderSpi::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspBatchOrderAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspBatchOrderAction(pInputBatchOrderAction, pRspInfo,nRequestID,bIsLast);
    }
    if (pInputBatchOrderAction)
    {
        qDebug("\tBrokerID [%s]\n", pInputBatchOrderAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputBatchOrderAction->InvestorID);
        qDebug("\tExchangeID [%s]\n", pInputBatchOrderAction->ExchangeID);
        qDebug("\tUserID [%s]\n", pInputBatchOrderAction->UserID);
        qDebug("\tInvestUnitID [%s]\n", pInputBatchOrderAction->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pInputBatchOrderAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputBatchOrderAction->MacAddress);
        qDebug("\tOrderActionRef [%d]\n", pInputBatchOrderAction->OrderActionRef);
        qDebug("\tRequestID [%d]\n", pInputBatchOrderAction->RequestID);
        qDebug("\tFrontID [%d]\n", pInputBatchOrderAction->FrontID);
        qDebug("\tSessionID [%d]\n", pInputBatchOrderAction->SessionID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspBatchOrderAction>\n");
};

void CTraderSpi::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspOptionSelfCloseInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspOptionSelfCloseInsert(pInputOptionSelfClose, pRspInfo,nRequestID,bIsLast);
    }
    if (pInputOptionSelfClose)
    {
        qDebug("\tBrokerID [%s]\n", pInputOptionSelfClose->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputOptionSelfClose->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputOptionSelfClose->InstrumentID);
        qDebug("\tOptionSelfCloseRef [%s]\n", pInputOptionSelfClose->OptionSelfCloseRef);
        qDebug("\tUserID [%s]\n", pInputOptionSelfClose->UserID);
        qDebug("\tBusinessUnit [%s]\n", pInputOptionSelfClose->BusinessUnit);
        qDebug("\tExchangeID [%s]\n", pInputOptionSelfClose->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInputOptionSelfClose->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pInputOptionSelfClose->AccountID);
        qDebug("\tCurrencyID [%s]\n", pInputOptionSelfClose->CurrencyID);
        qDebug("\tClientID [%s]\n", pInputOptionSelfClose->ClientID);
        qDebug("\tIPAddress [%s]\n", pInputOptionSelfClose->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputOptionSelfClose->MacAddress);
        qDebug("\tVolume [%d]\n", pInputOptionSelfClose->Volume);
        qDebug("\tRequestID [%d]\n", pInputOptionSelfClose->RequestID);
        qDebug("\tHedgeFlag [%c]\n", pInputOptionSelfClose->HedgeFlag);
        qDebug("\tOptSelfCloseFlag [%c]\n", pInputOptionSelfClose->OptSelfCloseFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspOptionSelfCloseInsert>\n");
};

void CTraderSpi::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspOptionSelfCloseAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspOptionSelfCloseAction(pInputOptionSelfCloseAction, pRspInfo,nRequestID,bIsLast);
    }
    if (pInputOptionSelfCloseAction)
    {
        qDebug("\tBrokerID [%s]\n", pInputOptionSelfCloseAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputOptionSelfCloseAction->InvestorID);
        qDebug("\tOptionSelfCloseRef [%s]\n", pInputOptionSelfCloseAction->OptionSelfCloseRef);
        qDebug("\tExchangeID [%s]\n", pInputOptionSelfCloseAction->ExchangeID);
        qDebug("\tOptionSelfCloseSysID [%s]\n", pInputOptionSelfCloseAction->OptionSelfCloseSysID);
        qDebug("\tUserID [%s]\n", pInputOptionSelfCloseAction->UserID);
        qDebug("\tInstrumentID [%s]\n", pInputOptionSelfCloseAction->InstrumentID);
        qDebug("\tInvestUnitID [%s]\n", pInputOptionSelfCloseAction->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pInputOptionSelfCloseAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputOptionSelfCloseAction->MacAddress);
        qDebug("\tOptionSelfCloseActionRef [%d]\n", pInputOptionSelfCloseAction->OptionSelfCloseActionRef);
        qDebug("\tRequestID [%d]\n", pInputOptionSelfCloseAction->RequestID);
        qDebug("\tFrontID [%d]\n", pInputOptionSelfCloseAction->FrontID);
        qDebug("\tSessionID [%d]\n", pInputOptionSelfCloseAction->SessionID);
        qDebug("\tActionFlag [%c]\n", pInputOptionSelfCloseAction->ActionFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspOptionSelfCloseAction>\n");
};

void CTraderSpi::OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspCombActionInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspCombActionInsert(pInputCombAction, pRspInfo,nRequestID,bIsLast);
    }
    if (pInputCombAction)
    {
        qDebug("\tBrokerID [%s]\n", pInputCombAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputCombAction->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputCombAction->InstrumentID);
        qDebug("\tCombActionRef [%s]\n", pInputCombAction->CombActionRef);
        qDebug("\tUserID [%s]\n", pInputCombAction->UserID);
        qDebug("\tExchangeID [%s]\n", pInputCombAction->ExchangeID);
        qDebug("\tIPAddress [%s]\n", pInputCombAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputCombAction->MacAddress);
        qDebug("\tInvestUnitID [%s]\n", pInputCombAction->InvestUnitID);
        qDebug("\tVolume [%d]\n", pInputCombAction->Volume);
        qDebug("\tDirection [%c]\n", pInputCombAction->Direction);
        qDebug("\tCombDirection [%c]\n", pInputCombAction->CombDirection);
        qDebug("\tHedgeFlag [%c]\n", pInputCombAction->HedgeFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspCombActionInsert>\n");
};

void CTraderSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryOrder>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryOrder(pOrder, pRspInfo,nRequestID,bIsLast);
    }
    if (pOrder)
    {
        qDebug("\tBrokerID [%s]\n", pOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pOrder->InstrumentID);
        qDebug("\tOrderRef [%s]\n", pOrder->OrderRef);
        qDebug("\tUserID [%s]\n", pOrder->UserID);
        qDebug("\tCombOffsetFlag [%s]\n", pOrder->CombOffsetFlag);
        qDebug("\tCombHedgeFlag [%s]\n", pOrder->CombHedgeFlag);
        qDebug("\tGTDDate [%s]\n", pOrder->GTDDate);
        qDebug("\tBusinessUnit [%s]\n", pOrder->BusinessUnit);
        qDebug("\tOrderLocalID [%s]\n", pOrder->OrderLocalID);
        qDebug("\tExchangeID [%s]\n", pOrder->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pOrder->ParticipantID);
        qDebug("\tClientID [%s]\n", pOrder->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pOrder->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pOrder->TraderID);
        qDebug("\tTradingDay [%s]\n", pOrder->TradingDay);
        qDebug("\tOrderSysID [%s]\n", pOrder->OrderSysID);
        qDebug("\tInsertDate [%s]\n", pOrder->InsertDate);
        qDebug("\tInsertTime [%s]\n", pOrder->InsertTime);
        qDebug("\tActiveTime [%s]\n", pOrder->ActiveTime);
        qDebug("\tSuspendTime [%s]\n", pOrder->SuspendTime);
        qDebug("\tUpdateTime [%s]\n", pOrder->UpdateTime);
        qDebug("\tCancelTime [%s]\n", pOrder->CancelTime);
        qDebug("\tActiveTraderID [%s]\n", pOrder->ActiveTraderID);
        qDebug("\tClearingPartID [%s]\n", pOrder->ClearingPartID);
        qDebug("\tUserProductInfo [%s]\n", pOrder->UserProductInfo);
        qDebug("\tStatusMsg [%s]\n", pOrder->StatusMsg);
        qDebug("\tActiveUserID [%s]\n", pOrder->ActiveUserID);
        qDebug("\tRelativeOrderSysID [%s]\n", pOrder->RelativeOrderSysID);
        qDebug("\tBranchID [%s]\n", pOrder->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pOrder->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pOrder->AccountID);
        qDebug("\tCurrencyID [%s]\n", pOrder->CurrencyID);
        qDebug("\tIPAddress [%s]\n", pOrder->IPAddress);
        qDebug("\tMacAddress [%s]\n", pOrder->MacAddress);
        qDebug("\tVolumeTotalOriginal [%d]\n", pOrder->VolumeTotalOriginal);
        qDebug("\tMinVolume [%d]\n", pOrder->MinVolume);
        qDebug("\tIsAutoSuspend [%d]\n", pOrder->IsAutoSuspend);
        qDebug("\tRequestID [%d]\n", pOrder->RequestID);
        qDebug("\tInstallID [%d]\n", pOrder->InstallID);
        qDebug("\tNotifySequence [%d]\n", pOrder->NotifySequence);
        qDebug("\tSettlementID [%d]\n", pOrder->SettlementID);
        qDebug("\tVolumeTraded [%d]\n", pOrder->VolumeTraded);
        qDebug("\tVolumeTotal [%d]\n", pOrder->VolumeTotal);
        qDebug("\tSequenceNo [%d]\n", pOrder->SequenceNo);
        qDebug("\tFrontID [%d]\n", pOrder->FrontID);
        qDebug("\tSessionID [%d]\n", pOrder->SessionID);
        qDebug("\tUserForceClose [%d]\n", pOrder->UserForceClose);
        qDebug("\tBrokerOrderSeq [%d]\n", pOrder->BrokerOrderSeq);
        qDebug("\tZCETotalTradedVolume [%d]\n", pOrder->ZCETotalTradedVolume);
        qDebug("\tIsSwapOrder [%d]\n", pOrder->IsSwapOrder);
        qDebug("\tOrderPriceType [%c]\n", pOrder->OrderPriceType);
        qDebug("\tDirection [%c]\n", pOrder->Direction);
        qDebug("\tTimeCondition [%c]\n", pOrder->TimeCondition);
        qDebug("\tVolumeCondition [%c]\n", pOrder->VolumeCondition);
        qDebug("\tContingentCondition [%c]\n", pOrder->ContingentCondition);
        qDebug("\tForceCloseReason [%c]\n", pOrder->ForceCloseReason);
        qDebug("\tOrderSubmitStatus [%c]\n", pOrder->OrderSubmitStatus);
        qDebug("\tOrderSource [%c]\n", pOrder->OrderSource);
        qDebug("\tOrderStatus [%c]\n", pOrder->OrderStatus);
        qDebug("\tOrderType [%c]\n", pOrder->OrderType);
        qDebug("\tLimitPrice [%.8lf]\n", pOrder->LimitPrice);
        qDebug("\tStopPrice [%.8lf]\n", pOrder->StopPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryOrder>\n");
};

void CTraderSpi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryTrade>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryTrade(pTrade, pRspInfo,nRequestID,bIsLast);
    }
    if (pTrade)
    {
        qDebug("\tBrokerID [%s]\n", pTrade->BrokerID);
        qDebug("\tInvestorID [%s]\n", pTrade->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pTrade->InstrumentID);
        qDebug("\tOrderRef [%s]\n", pTrade->OrderRef);
        qDebug("\tUserID [%s]\n", pTrade->UserID);
        qDebug("\tExchangeID [%s]\n", pTrade->ExchangeID);
        qDebug("\tTradeID [%s]\n", pTrade->TradeID);
        qDebug("\tOrderSysID [%s]\n", pTrade->OrderSysID);
        qDebug("\tParticipantID [%s]\n", pTrade->ParticipantID);
        qDebug("\tClientID [%s]\n", pTrade->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pTrade->ExchangeInstID);
        qDebug("\tTradeDate [%s]\n", pTrade->TradeDate);
        qDebug("\tTradeTime [%s]\n", pTrade->TradeTime);
        qDebug("\tTraderID [%s]\n", pTrade->TraderID);
        qDebug("\tOrderLocalID [%s]\n", pTrade->OrderLocalID);
        qDebug("\tClearingPartID [%s]\n", pTrade->ClearingPartID);
        qDebug("\tBusinessUnit [%s]\n", pTrade->BusinessUnit);
        qDebug("\tTradingDay [%s]\n", pTrade->TradingDay);
        qDebug("\tInvestUnitID [%s]\n", pTrade->InvestUnitID);
        qDebug("\tVolume [%d]\n", pTrade->Volume);
        qDebug("\tSequenceNo [%d]\n", pTrade->SequenceNo);
        qDebug("\tSettlementID [%d]\n", pTrade->SettlementID);
        qDebug("\tBrokerOrderSeq [%d]\n", pTrade->BrokerOrderSeq);
        qDebug("\tDirection [%c]\n", pTrade->Direction);
        qDebug("\tTradingRole [%c]\n", pTrade->TradingRole);
        qDebug("\tOffsetFlag [%c]\n", pTrade->OffsetFlag);
        qDebug("\tHedgeFlag [%c]\n", pTrade->HedgeFlag);
        qDebug("\tTradeType [%c]\n", pTrade->TradeType);
        qDebug("\tPriceSource [%c]\n", pTrade->PriceSource);
        qDebug("\tTradeSource [%c]\n", pTrade->TradeSource);
        qDebug("\tPrice [%.8lf]\n", pTrade->Price);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryTrade>\n");
};

void CTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryInvestorPosition>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryInvestorPosition(pInvestorPosition, pRspInfo,nRequestID,bIsLast);
    }
    if (pInvestorPosition)
    {
        qDebug("\tInstrumentID [%s]\n", pInvestorPosition->InstrumentID);
        qDebug("\tBrokerID [%s]\n", pInvestorPosition->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInvestorPosition->InvestorID);
        qDebug("\tTradingDay [%s]\n", pInvestorPosition->TradingDay);
        qDebug("\tExchangeID [%s]\n", pInvestorPosition->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInvestorPosition->InvestUnitID);
        qDebug("\tYdPosition [%d]\n", pInvestorPosition->YdPosition);
        qDebug("\tPosition [%d]\n", pInvestorPosition->Position);
        qDebug("\tLongFrozen [%d]\n", pInvestorPosition->LongFrozen);
        qDebug("\tShortFrozen [%d]\n", pInvestorPosition->ShortFrozen);
        qDebug("\tOpenVolume [%d]\n", pInvestorPosition->OpenVolume);
        qDebug("\tCloseVolume [%d]\n", pInvestorPosition->CloseVolume);
        qDebug("\tSettlementID [%d]\n", pInvestorPosition->SettlementID);
        qDebug("\tCombPosition [%d]\n", pInvestorPosition->CombPosition);
        qDebug("\tCombLongFrozen [%d]\n", pInvestorPosition->CombLongFrozen);
        qDebug("\tCombShortFrozen [%d]\n", pInvestorPosition->CombShortFrozen);
        qDebug("\tTodayPosition [%d]\n", pInvestorPosition->TodayPosition);
        qDebug("\tStrikeFrozen [%d]\n", pInvestorPosition->StrikeFrozen);
        qDebug("\tAbandonFrozen [%d]\n", pInvestorPosition->AbandonFrozen);
        qDebug("\tYdStrikeFrozen [%d]\n", pInvestorPosition->YdStrikeFrozen);
        qDebug("\tPosiDirection [%c]\n", pInvestorPosition->PosiDirection);
        qDebug("\tHedgeFlag [%c]\n", pInvestorPosition->HedgeFlag);
        qDebug("\tPositionDate [%c]\n", pInvestorPosition->PositionDate);
        qDebug("\tLongFrozenAmount [%.8lf]\n", pInvestorPosition->LongFrozenAmount);
        qDebug("\tShortFrozenAmount [%.8lf]\n", pInvestorPosition->ShortFrozenAmount);
        qDebug("\tOpenAmount [%.8lf]\n", pInvestorPosition->OpenAmount);
        qDebug("\tCloseAmount [%.8lf]\n", pInvestorPosition->CloseAmount);
        qDebug("\tPositionCost [%.8lf]\n", pInvestorPosition->PositionCost);
        qDebug("\tPreMargin [%.8lf]\n", pInvestorPosition->PreMargin);
        qDebug("\tUseMargin [%.8lf]\n", pInvestorPosition->UseMargin);
        qDebug("\tFrozenMargin [%.8lf]\n", pInvestorPosition->FrozenMargin);
        qDebug("\tFrozenCash [%.8lf]\n", pInvestorPosition->FrozenCash);
        qDebug("\tFrozenCommission [%.8lf]\n", pInvestorPosition->FrozenCommission);
        qDebug("\tCashIn [%.8lf]\n", pInvestorPosition->CashIn);
        qDebug("\tCommission [%.8lf]\n", pInvestorPosition->Commission);
        qDebug("\tCloseProfit [%.8lf]\n", pInvestorPosition->CloseProfit);
        qDebug("\tPositionProfit [%.8lf]\n", pInvestorPosition->PositionProfit);
        qDebug("\tPreSettlementPrice [%.8lf]\n", pInvestorPosition->PreSettlementPrice);
        qDebug("\tSettlementPrice [%.8lf]\n", pInvestorPosition->SettlementPrice);
        qDebug("\tOpenCost [%.8lf]\n", pInvestorPosition->OpenCost);
        qDebug("\tExchangeMargin [%.8lf]\n", pInvestorPosition->ExchangeMargin);
        qDebug("\tCloseProfitByDate [%.8lf]\n", pInvestorPosition->CloseProfitByDate);
        qDebug("\tCloseProfitByTrade [%.8lf]\n", pInvestorPosition->CloseProfitByTrade);
        qDebug("\tMarginRateByMoney [%.8lf]\n", pInvestorPosition->MarginRateByMoney);
        qDebug("\tMarginRateByVolume [%.8lf]\n", pInvestorPosition->MarginRateByVolume);
        qDebug("\tStrikeFrozenAmount [%.8lf]\n", pInvestorPosition->StrikeFrozenAmount);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryInvestorPosition>\n");
};

void CTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryTradingAccount>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryTradingAccount(pTradingAccount, pRspInfo,nRequestID,bIsLast);
    }
    if (pTradingAccount)
    {
        qDebug("\tBrokerID [%s]\n", pTradingAccount->BrokerID);
        qDebug("\tAccountID [%s]\n", pTradingAccount->AccountID);
        qDebug("\tTradingDay [%s]\n", pTradingAccount->TradingDay);
        qDebug("\tCurrencyID [%s]\n", pTradingAccount->CurrencyID);
        qDebug("\tSettlementID [%d]\n", pTradingAccount->SettlementID);
        qDebug("\tBizType [%c]\n", pTradingAccount->BizType);
        qDebug("\tPreMortgage [%.8lf]\n", pTradingAccount->PreMortgage);
        qDebug("\tPreCredit [%.8lf]\n", pTradingAccount->PreCredit);
        qDebug("\tPreDeposit [%.8lf]\n", pTradingAccount->PreDeposit);
        qDebug("\tPreBalance [%.8lf]\n", pTradingAccount->PreBalance);
        qDebug("\tPreMargin [%.8lf]\n", pTradingAccount->PreMargin);
        qDebug("\tInterestBase [%.8lf]\n", pTradingAccount->InterestBase);
        qDebug("\tInterest [%.8lf]\n", pTradingAccount->Interest);
        qDebug("\tDeposit [%.8lf]\n", pTradingAccount->Deposit);
        qDebug("\tWithdraw [%.8lf]\n", pTradingAccount->Withdraw);
        qDebug("\tFrozenMargin [%.8lf]\n", pTradingAccount->FrozenMargin);
        qDebug("\tFrozenCash [%.8lf]\n", pTradingAccount->FrozenCash);
        qDebug("\tFrozenCommission [%.8lf]\n", pTradingAccount->FrozenCommission);
        qDebug("\tCurrMargin [%.8lf]\n", pTradingAccount->CurrMargin);
        qDebug("\tCashIn [%.8lf]\n", pTradingAccount->CashIn);
        qDebug("\tCommission [%.8lf]\n", pTradingAccount->Commission);
        qDebug("\tCloseProfit [%.8lf]\n", pTradingAccount->CloseProfit);
        qDebug("\tPositionProfit [%.8lf]\n", pTradingAccount->PositionProfit);
        qDebug("\tBalance [%.8lf]\n", pTradingAccount->Balance);
        qDebug("\tAvailable [%.8lf]\n", pTradingAccount->Available);
        qDebug("\tWithdrawQuota [%.8lf]\n", pTradingAccount->WithdrawQuota);
        qDebug("\tReserve [%.8lf]\n", pTradingAccount->Reserve);
        qDebug("\tCredit [%.8lf]\n", pTradingAccount->Credit);
        qDebug("\tMortgage [%.8lf]\n", pTradingAccount->Mortgage);
        qDebug("\tExchangeMargin [%.8lf]\n", pTradingAccount->ExchangeMargin);
        qDebug("\tDeliveryMargin [%.8lf]\n", pTradingAccount->DeliveryMargin);
        qDebug("\tExchangeDeliveryMargin [%.8lf]\n", pTradingAccount->ExchangeDeliveryMargin);
        qDebug("\tReserveBalance [%.8lf]\n", pTradingAccount->ReserveBalance);
        qDebug("\tPreFundMortgageIn [%.8lf]\n", pTradingAccount->PreFundMortgageIn);
        qDebug("\tPreFundMortgageOut [%.8lf]\n", pTradingAccount->PreFundMortgageOut);
        qDebug("\tFundMortgageIn [%.8lf]\n", pTradingAccount->FundMortgageIn);
        qDebug("\tFundMortgageOut [%.8lf]\n", pTradingAccount->FundMortgageOut);
        qDebug("\tFundMortgageAvailable [%.8lf]\n", pTradingAccount->FundMortgageAvailable);
        qDebug("\tMortgageableFund [%.8lf]\n", pTradingAccount->MortgageableFund);
        qDebug("\tSpecProductMargin [%.8lf]\n", pTradingAccount->SpecProductMargin);
        qDebug("\tSpecProductFrozenMargin [%.8lf]\n", pTradingAccount->SpecProductFrozenMargin);
        qDebug("\tSpecProductCommission [%.8lf]\n", pTradingAccount->SpecProductCommission);
        qDebug("\tSpecProductFrozenCommission [%.8lf]\n", pTradingAccount->SpecProductFrozenCommission);
        qDebug("\tSpecProductPositionProfit [%.8lf]\n", pTradingAccount->SpecProductPositionProfit);
        qDebug("\tSpecProductCloseProfit [%.8lf]\n", pTradingAccount->SpecProductCloseProfit);
        qDebug("\tSpecProductPositionProfitByAlg [%.8lf]\n", pTradingAccount->SpecProductPositionProfitByAlg);
        qDebug("\tSpecProductExchangeMargin [%.8lf]\n", pTradingAccount->SpecProductExchangeMargin);
        qDebug("\tFrozenSwap [%.8lf]\n", pTradingAccount->FrozenSwap);
        qDebug("\tRemainSwap [%.8lf]\n", pTradingAccount->RemainSwap);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryTradingAccount>\n");
};

void CTraderSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryInvestor>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryInvestor(pInvestor, pRspInfo,nRequestID,bIsLast);
    }
    if (pInvestor)
    {
        qDebug("\tInvestorID [%s]\n", pInvestor->InvestorID);
        qDebug("\tBrokerID [%s]\n", pInvestor->BrokerID);
        qDebug("\tInvestorGroupID [%s]\n", pInvestor->InvestorGroupID);
        qDebug("\tInvestorName [%s]\n", pInvestor->InvestorName);
        qDebug("\tIdentifiedCardNo [%s]\n", pInvestor->IdentifiedCardNo);
        qDebug("\tTelephone [%s]\n", pInvestor->Telephone);
        qDebug("\tAddress [%s]\n", pInvestor->Address);
        qDebug("\tOpenDate [%s]\n", pInvestor->OpenDate);
        qDebug("\tMobile [%s]\n", pInvestor->Mobile);
        qDebug("\tCommModelID [%s]\n", pInvestor->CommModelID);
        qDebug("\tMarginModelID [%s]\n", pInvestor->MarginModelID);
        qDebug("\tIsActive [%d]\n", pInvestor->IsActive);
        qDebug("\tIdentifiedCardType [%c]\n", pInvestor->IdentifiedCardType);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryInvestor>\n");
};

void CTraderSpi::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryTradingCode>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryTradingCode(pTradingCode, pRspInfo,nRequestID,bIsLast);
    }
    if (pTradingCode)
    {
        qDebug("\tInvestorID [%s]\n", pTradingCode->InvestorID);
        qDebug("\tBrokerID [%s]\n", pTradingCode->BrokerID);
        qDebug("\tExchangeID [%s]\n", pTradingCode->ExchangeID);
        qDebug("\tClientID [%s]\n", pTradingCode->ClientID);
        qDebug("\tBranchID [%s]\n", pTradingCode->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pTradingCode->InvestUnitID);
        qDebug("\tIsActive [%d]\n", pTradingCode->IsActive);
        qDebug("\tClientIDType [%c]\n", pTradingCode->ClientIDType);
        qDebug("\tBizType [%c]\n", pTradingCode->BizType);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryTradingCode>\n");
};

void CTraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryInstrumentMarginRate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryInstrumentMarginRate(pInstrumentMarginRate, pRspInfo,nRequestID,bIsLast);
    }
    if (pInstrumentMarginRate)
    {
        qDebug("\tInstrumentID [%s]\n", pInstrumentMarginRate->InstrumentID);
        qDebug("\tBrokerID [%s]\n", pInstrumentMarginRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInstrumentMarginRate->InvestorID);
        qDebug("\tExchangeID [%s]\n", pInstrumentMarginRate->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInstrumentMarginRate->InvestUnitID);
        qDebug("\tIsRelative [%d]\n", pInstrumentMarginRate->IsRelative);
        qDebug("\tInvestorRange [%c]\n", pInstrumentMarginRate->InvestorRange);
        qDebug("\tHedgeFlag [%c]\n", pInstrumentMarginRate->HedgeFlag);
        qDebug("\tLongMarginRatioByMoney [%.8lf]\n", pInstrumentMarginRate->LongMarginRatioByMoney);
        qDebug("\tLongMarginRatioByVolume [%.8lf]\n", pInstrumentMarginRate->LongMarginRatioByVolume);
        qDebug("\tShortMarginRatioByMoney [%.8lf]\n", pInstrumentMarginRate->ShortMarginRatioByMoney);
        qDebug("\tShortMarginRatioByVolume [%.8lf]\n", pInstrumentMarginRate->ShortMarginRatioByVolume);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryInstrumentMarginRate>\n");
};

void CTraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryInstrumentCommissionRate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryInstrumentCommissionRate(pInstrumentCommissionRate, pRspInfo,nRequestID,bIsLast);
    }
    if (pInstrumentCommissionRate)
    {
        qDebug("\tInstrumentID [%s]\n", pInstrumentCommissionRate->InstrumentID);
        qDebug("\tBrokerID [%s]\n", pInstrumentCommissionRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInstrumentCommissionRate->InvestorID);
        qDebug("\tExchangeID [%s]\n", pInstrumentCommissionRate->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInstrumentCommissionRate->InvestUnitID);
        qDebug("\tInvestorRange [%c]\n", pInstrumentCommissionRate->InvestorRange);
        qDebug("\tBizType [%c]\n", pInstrumentCommissionRate->BizType);
        qDebug("\tOpenRatioByMoney [%.8lf]\n", pInstrumentCommissionRate->OpenRatioByMoney);
        qDebug("\tOpenRatioByVolume [%.8lf]\n", pInstrumentCommissionRate->OpenRatioByVolume);
        qDebug("\tCloseRatioByMoney [%.8lf]\n", pInstrumentCommissionRate->CloseRatioByMoney);
        qDebug("\tCloseRatioByVolume [%.8lf]\n", pInstrumentCommissionRate->CloseRatioByVolume);
        qDebug("\tCloseTodayRatioByMoney [%.8lf]\n", pInstrumentCommissionRate->CloseTodayRatioByMoney);
        qDebug("\tCloseTodayRatioByVolume [%.8lf]\n", pInstrumentCommissionRate->CloseTodayRatioByVolume);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryInstrumentCommissionRate>\n");
};

void CTraderSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryExchange>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryExchange(pExchange, pRspInfo,nRequestID,bIsLast);
    }
    if (pExchange)
    {
        qDebug("\tExchangeID [%s]\n", pExchange->ExchangeID);
        qDebug("\tExchangeName [%s]\n", pExchange->ExchangeName);
        qDebug("\tExchangeProperty [%c]\n", pExchange->ExchangeProperty);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryExchange>\n");
};

void CTraderSpi::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryProduct>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryProduct(pProduct, pRspInfo,nRequestID,bIsLast);
    }
    if (pProduct)
    {
        qDebug("\tProductID [%s]\n", pProduct->ProductID);
        qDebug("\tProductName [%s]\n", pProduct->ProductName);
        qDebug("\tExchangeID [%s]\n", pProduct->ExchangeID);
        qDebug("\tTradeCurrencyID [%s]\n", pProduct->TradeCurrencyID);
        qDebug("\tExchangeProductID [%s]\n", pProduct->ExchangeProductID);
        qDebug("\tVolumeMultiple [%d]\n", pProduct->VolumeMultiple);
        qDebug("\tMaxMarketOrderVolume [%d]\n", pProduct->MaxMarketOrderVolume);
        qDebug("\tMinMarketOrderVolume [%d]\n", pProduct->MinMarketOrderVolume);
        qDebug("\tMaxLimitOrderVolume [%d]\n", pProduct->MaxLimitOrderVolume);
        qDebug("\tMinLimitOrderVolume [%d]\n", pProduct->MinLimitOrderVolume);
        qDebug("\tProductClass [%c]\n", pProduct->ProductClass);
        qDebug("\tPositionType [%c]\n", pProduct->PositionType);
        qDebug("\tPositionDateType [%c]\n", pProduct->PositionDateType);
        qDebug("\tCloseDealType [%c]\n", pProduct->CloseDealType);
        qDebug("\tMortgageFundUseRange [%c]\n", pProduct->MortgageFundUseRange);
        qDebug("\tPriceTick [%.8lf]\n", pProduct->PriceTick);
        qDebug("\tUnderlyingMultiple [%.8lf]\n", pProduct->UnderlyingMultiple);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryProduct>\n");
};

void CTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryInstrument>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryInstrument(pInstrument, pRspInfo,nRequestID,bIsLast);
    }
    if (pInstrument)
    {
        qDebug("\tInstrumentID [%s]\n", pInstrument->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pInstrument->ExchangeID);
        qDebug("\tInstrumentName [%s]\n", pInstrument->InstrumentName);
        qDebug("\tExchangeInstID [%s]\n", pInstrument->ExchangeInstID);
        qDebug("\tProductID [%s]\n", pInstrument->ProductID);
        qDebug("\tCreateDate [%s]\n", pInstrument->CreateDate);
        qDebug("\tOpenDate [%s]\n", pInstrument->OpenDate);
        qDebug("\tExpireDate [%s]\n", pInstrument->ExpireDate);
        qDebug("\tStartDelivDate [%s]\n", pInstrument->StartDelivDate);
        qDebug("\tEndDelivDate [%s]\n", pInstrument->EndDelivDate);
        qDebug("\tUnderlyingInstrID [%s]\n", pInstrument->UnderlyingInstrID);
        qDebug("\tDeliveryYear [%d]\n", pInstrument->DeliveryYear);
        qDebug("\tDeliveryMonth [%d]\n", pInstrument->DeliveryMonth);
        qDebug("\tMaxMarketOrderVolume [%d]\n", pInstrument->MaxMarketOrderVolume);
        qDebug("\tMinMarketOrderVolume [%d]\n", pInstrument->MinMarketOrderVolume);
        qDebug("\tMaxLimitOrderVolume [%d]\n", pInstrument->MaxLimitOrderVolume);
        qDebug("\tMinLimitOrderVolume [%d]\n", pInstrument->MinLimitOrderVolume);
        qDebug("\tVolumeMultiple [%d]\n", pInstrument->VolumeMultiple);
        qDebug("\tIsTrading [%d]\n", pInstrument->IsTrading);
        qDebug("\tProductClass [%c]\n", pInstrument->ProductClass);
        qDebug("\tInstLifePhase [%c]\n", pInstrument->InstLifePhase);
        qDebug("\tPositionType [%c]\n", pInstrument->PositionType);
        qDebug("\tPositionDateType [%c]\n", pInstrument->PositionDateType);
        qDebug("\tMaxMarginSideAlgorithm [%c]\n", pInstrument->MaxMarginSideAlgorithm);
        qDebug("\tOptionsType [%c]\n", pInstrument->OptionsType);
        qDebug("\tCombinationType [%c]\n", pInstrument->CombinationType);
        qDebug("\tPriceTick [%.8lf]\n", pInstrument->PriceTick);
        qDebug("\tLongMarginRatio [%.8lf]\n", pInstrument->LongMarginRatio);
        qDebug("\tShortMarginRatio [%.8lf]\n", pInstrument->ShortMarginRatio);
        qDebug("\tStrikePrice [%.8lf]\n", pInstrument->StrikePrice);
        qDebug("\tUnderlyingMultiple [%.8lf]\n", pInstrument->UnderlyingMultiple);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryInstrument>\n");
};

void CTraderSpi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryDepthMarketData>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryDepthMarketData(pDepthMarketData, pRspInfo,nRequestID,bIsLast);
    }
    if (pDepthMarketData)
    {
        qDebug("\tTradingDay [%s]\n", pDepthMarketData->TradingDay);
        qDebug("\tInstrumentID [%s]\n", pDepthMarketData->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pDepthMarketData->ExchangeID);
        qDebug("\tExchangeInstID [%s]\n", pDepthMarketData->ExchangeInstID);
        qDebug("\tUpdateTime [%s]\n", pDepthMarketData->UpdateTime);
        qDebug("\tActionDay [%s]\n", pDepthMarketData->ActionDay);
        qDebug("\tVolume [%d]\n", pDepthMarketData->Volume);
        qDebug("\tUpdateMillisec [%d]\n", pDepthMarketData->UpdateMillisec);
        qDebug("\tBidVolume1 [%d]\n", pDepthMarketData->BidVolume1);
        qDebug("\tAskVolume1 [%d]\n", pDepthMarketData->AskVolume1);
        qDebug("\tBidVolume2 [%d]\n", pDepthMarketData->BidVolume2);
        qDebug("\tAskVolume2 [%d]\n", pDepthMarketData->AskVolume2);
        qDebug("\tBidVolume3 [%d]\n", pDepthMarketData->BidVolume3);
        qDebug("\tAskVolume3 [%d]\n", pDepthMarketData->AskVolume3);
        qDebug("\tBidVolume4 [%d]\n", pDepthMarketData->BidVolume4);
        qDebug("\tAskVolume4 [%d]\n", pDepthMarketData->AskVolume4);
        qDebug("\tBidVolume5 [%d]\n", pDepthMarketData->BidVolume5);
        qDebug("\tAskVolume5 [%d]\n", pDepthMarketData->AskVolume5);
        qDebug("\tLastPrice [%.8lf]\n", pDepthMarketData->LastPrice);
        qDebug("\tPreSettlementPrice [%.8lf]\n", pDepthMarketData->PreSettlementPrice);
        qDebug("\tPreClosePrice [%.8lf]\n", pDepthMarketData->PreClosePrice);
        qDebug("\tPreOpenInterest [%.8lf]\n", pDepthMarketData->PreOpenInterest);
        qDebug("\tOpenPrice [%.8lf]\n", pDepthMarketData->OpenPrice);
        qDebug("\tHighestPrice [%.8lf]\n", pDepthMarketData->HighestPrice);
        qDebug("\tLowestPrice [%.8lf]\n", pDepthMarketData->LowestPrice);
        qDebug("\tTurnover [%.8lf]\n", pDepthMarketData->Turnover);
        qDebug("\tOpenInterest [%.8lf]\n", pDepthMarketData->OpenInterest);
        qDebug("\tClosePrice [%.8lf]\n", pDepthMarketData->ClosePrice);
        qDebug("\tSettlementPrice [%.8lf]\n", pDepthMarketData->SettlementPrice);
        qDebug("\tUpperLimitPrice [%.8lf]\n", pDepthMarketData->UpperLimitPrice);
        qDebug("\tLowerLimitPrice [%.8lf]\n", pDepthMarketData->LowerLimitPrice);
        qDebug("\tPreDelta [%.8lf]\n", pDepthMarketData->PreDelta);
        qDebug("\tCurrDelta [%.8lf]\n", pDepthMarketData->CurrDelta);
        qDebug("\tBidPrice1 [%.8lf]\n", pDepthMarketData->BidPrice1);
        qDebug("\tAskPrice1 [%.8lf]\n", pDepthMarketData->AskPrice1);
        qDebug("\tBidPrice2 [%.8lf]\n", pDepthMarketData->BidPrice2);
        qDebug("\tAskPrice2 [%.8lf]\n", pDepthMarketData->AskPrice2);
        qDebug("\tBidPrice3 [%.8lf]\n", pDepthMarketData->BidPrice3);
        qDebug("\tAskPrice3 [%.8lf]\n", pDepthMarketData->AskPrice3);
        qDebug("\tBidPrice4 [%.8lf]\n", pDepthMarketData->BidPrice4);
        qDebug("\tAskPrice4 [%.8lf]\n", pDepthMarketData->AskPrice4);
        qDebug("\tBidPrice5 [%.8lf]\n", pDepthMarketData->BidPrice5);
        qDebug("\tAskPrice5 [%.8lf]\n", pDepthMarketData->AskPrice5);
        qDebug("\tAveragePrice [%.8lf]\n", pDepthMarketData->AveragePrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryDepthMarketData>\n");
};

void CTraderSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQrySettlementInfo>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQrySettlementInfo(pSettlementInfo, pRspInfo,nRequestID,bIsLast);
    }
    if (pSettlementInfo)
    {
        qDebug("\tTradingDay [%s]\n", pSettlementInfo->TradingDay);
        qDebug("\tBrokerID [%s]\n", pSettlementInfo->BrokerID);
        qDebug("\tInvestorID [%s]\n", pSettlementInfo->InvestorID);
        qDebug("\tContent [%s]\n", pSettlementInfo->Content);
        qDebug("\tAccountID [%s]\n", pSettlementInfo->AccountID);
        qDebug("\tCurrencyID [%s]\n", pSettlementInfo->CurrencyID);
        qDebug("\tSettlementID [%d]\n", pSettlementInfo->SettlementID);
        qDebug("\tSequenceNo [%d]\n", pSettlementInfo->SequenceNo);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQrySettlementInfo>\n");
};

void CTraderSpi::OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryTransferBank>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryTransferBank(pTransferBank, pRspInfo,nRequestID,bIsLast);
    }
    if (pTransferBank)
    {
        qDebug("\tBankID [%s]\n", pTransferBank->BankID);
        qDebug("\tBankBrchID [%s]\n", pTransferBank->BankBrchID);
        qDebug("\tBankName [%s]\n", pTransferBank->BankName);
        qDebug("\tIsActive [%d]\n", pTransferBank->IsActive);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryTransferBank>\n");
};

void CTraderSpi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryInvestorPositionDetail>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryInvestorPositionDetail(pInvestorPositionDetail, pRspInfo,nRequestID,bIsLast);
    }
    if (pInvestorPositionDetail)
    {
        qDebug("\tInstrumentID [%s]\n", pInvestorPositionDetail->InstrumentID);
        qDebug("\tBrokerID [%s]\n", pInvestorPositionDetail->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInvestorPositionDetail->InvestorID);
        qDebug("\tOpenDate [%s]\n", pInvestorPositionDetail->OpenDate);
        qDebug("\tTradeID [%s]\n", pInvestorPositionDetail->TradeID);
        qDebug("\tTradingDay [%s]\n", pInvestorPositionDetail->TradingDay);
        qDebug("\tCombInstrumentID [%s]\n", pInvestorPositionDetail->CombInstrumentID);
        qDebug("\tExchangeID [%s]\n", pInvestorPositionDetail->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInvestorPositionDetail->InvestUnitID);
        qDebug("\tVolume [%d]\n", pInvestorPositionDetail->Volume);
        qDebug("\tSettlementID [%d]\n", pInvestorPositionDetail->SettlementID);
        qDebug("\tCloseVolume [%d]\n", pInvestorPositionDetail->CloseVolume);
        qDebug("\tHedgeFlag [%c]\n", pInvestorPositionDetail->HedgeFlag);
        qDebug("\tDirection [%c]\n", pInvestorPositionDetail->Direction);
        qDebug("\tTradeType [%c]\n", pInvestorPositionDetail->TradeType);
        qDebug("\tOpenPrice [%.8lf]\n", pInvestorPositionDetail->OpenPrice);
        qDebug("\tCloseProfitByDate [%.8lf]\n", pInvestorPositionDetail->CloseProfitByDate);
        qDebug("\tCloseProfitByTrade [%.8lf]\n", pInvestorPositionDetail->CloseProfitByTrade);
        qDebug("\tPositionProfitByDate [%.8lf]\n", pInvestorPositionDetail->PositionProfitByDate);
        qDebug("\tPositionProfitByTrade [%.8lf]\n", pInvestorPositionDetail->PositionProfitByTrade);
        qDebug("\tMargin [%.8lf]\n", pInvestorPositionDetail->Margin);
        qDebug("\tExchMargin [%.8lf]\n", pInvestorPositionDetail->ExchMargin);
        qDebug("\tMarginRateByMoney [%.8lf]\n", pInvestorPositionDetail->MarginRateByMoney);
        qDebug("\tMarginRateByVolume [%.8lf]\n", pInvestorPositionDetail->MarginRateByVolume);
        qDebug("\tLastSettlementPrice [%.8lf]\n", pInvestorPositionDetail->LastSettlementPrice);
        qDebug("\tSettlementPrice [%.8lf]\n", pInvestorPositionDetail->SettlementPrice);
        qDebug("\tCloseAmount [%.8lf]\n", pInvestorPositionDetail->CloseAmount);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryInvestorPositionDetail>\n");
};

void CTraderSpi::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryNotice>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryNotice(pNotice, pRspInfo,nRequestID,bIsLast);
    }
    if (pNotice)
    {
        qDebug("\tBrokerID [%s]\n", pNotice->BrokerID);
        qDebug("\tContent [%s]\n", pNotice->Content);
        qDebug("\tSequenceLabel [%s]\n", pNotice->SequenceLabel);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryNotice>\n");
};

void CTraderSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQrySettlementInfoConfirm>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQrySettlementInfoConfirm(pSettlementInfoConfirm, pRspInfo,nRequestID,bIsLast);
    }
    if (pSettlementInfoConfirm)
    {
        qDebug("\tBrokerID [%s]\n", pSettlementInfoConfirm->BrokerID);
        qDebug("\tInvestorID [%s]\n", pSettlementInfoConfirm->InvestorID);
        qDebug("\tConfirmDate [%s]\n", pSettlementInfoConfirm->ConfirmDate);
        qDebug("\tConfirmTime [%s]\n", pSettlementInfoConfirm->ConfirmTime);
        qDebug("\tAccountID [%s]\n", pSettlementInfoConfirm->AccountID);
        qDebug("\tCurrencyID [%s]\n", pSettlementInfoConfirm->CurrencyID);
        qDebug("\tSettlementID [%d]\n", pSettlementInfoConfirm->SettlementID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQrySettlementInfoConfirm>\n");
};

void CTraderSpi::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryInvestorPositionCombineDetail>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryInvestorPositionCombineDetail(pInvestorPositionCombineDetail, pRspInfo,nRequestID,bIsLast);
    }
    if (pInvestorPositionCombineDetail)
    {
        qDebug("\tTradingDay [%s]\n", pInvestorPositionCombineDetail->TradingDay);
        qDebug("\tOpenDate [%s]\n", pInvestorPositionCombineDetail->OpenDate);
        qDebug("\tExchangeID [%s]\n", pInvestorPositionCombineDetail->ExchangeID);
        qDebug("\tBrokerID [%s]\n", pInvestorPositionCombineDetail->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInvestorPositionCombineDetail->InvestorID);
        qDebug("\tComTradeID [%s]\n", pInvestorPositionCombineDetail->ComTradeID);
        qDebug("\tTradeID [%s]\n", pInvestorPositionCombineDetail->TradeID);
        qDebug("\tInstrumentID [%s]\n", pInvestorPositionCombineDetail->InstrumentID);
        qDebug("\tCombInstrumentID [%s]\n", pInvestorPositionCombineDetail->CombInstrumentID);
        qDebug("\tInvestUnitID [%s]\n", pInvestorPositionCombineDetail->InvestUnitID);
        qDebug("\tSettlementID [%d]\n", pInvestorPositionCombineDetail->SettlementID);
        qDebug("\tTotalAmt [%d]\n", pInvestorPositionCombineDetail->TotalAmt);
        qDebug("\tLegID [%d]\n", pInvestorPositionCombineDetail->LegID);
        qDebug("\tLegMultiple [%d]\n", pInvestorPositionCombineDetail->LegMultiple);
        qDebug("\tTradeGroupID [%d]\n", pInvestorPositionCombineDetail->TradeGroupID);
        qDebug("\tHedgeFlag [%c]\n", pInvestorPositionCombineDetail->HedgeFlag);
        qDebug("\tDirection [%c]\n", pInvestorPositionCombineDetail->Direction);
        qDebug("\tMargin [%.8lf]\n", pInvestorPositionCombineDetail->Margin);
        qDebug("\tExchMargin [%.8lf]\n", pInvestorPositionCombineDetail->ExchMargin);
        qDebug("\tMarginRateByMoney [%.8lf]\n", pInvestorPositionCombineDetail->MarginRateByMoney);
        qDebug("\tMarginRateByVolume [%.8lf]\n", pInvestorPositionCombineDetail->MarginRateByVolume);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryInvestorPositionCombineDetail>\n");
};

void CTraderSpi::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryCFMMCTradingAccountKey>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryCFMMCTradingAccountKey(pCFMMCTradingAccountKey, pRspInfo,nRequestID,bIsLast);
    }
    if (pCFMMCTradingAccountKey)
    {
        qDebug("\tBrokerID [%s]\n", pCFMMCTradingAccountKey->BrokerID);
        qDebug("\tParticipantID [%s]\n", pCFMMCTradingAccountKey->ParticipantID);
        qDebug("\tAccountID [%s]\n", pCFMMCTradingAccountKey->AccountID);
        qDebug("\tCurrentKey [%s]\n", pCFMMCTradingAccountKey->CurrentKey);
        qDebug("\tKeyID [%d]\n", pCFMMCTradingAccountKey->KeyID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryCFMMCTradingAccountKey>\n");
};

void CTraderSpi::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryEWarrantOffset>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryEWarrantOffset(pEWarrantOffset, pRspInfo,nRequestID,bIsLast);
    }
    if (pEWarrantOffset)
    {
        qDebug("\tTradingDay [%s]\n", pEWarrantOffset->TradingDay);
        qDebug("\tBrokerID [%s]\n", pEWarrantOffset->BrokerID);
        qDebug("\tInvestorID [%s]\n", pEWarrantOffset->InvestorID);
        qDebug("\tExchangeID [%s]\n", pEWarrantOffset->ExchangeID);
        qDebug("\tInstrumentID [%s]\n", pEWarrantOffset->InstrumentID);
        qDebug("\tInvestUnitID [%s]\n", pEWarrantOffset->InvestUnitID);
        qDebug("\tVolume [%d]\n", pEWarrantOffset->Volume);
        qDebug("\tDirection [%c]\n", pEWarrantOffset->Direction);
        qDebug("\tHedgeFlag [%c]\n", pEWarrantOffset->HedgeFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryEWarrantOffset>\n");
};

void CTraderSpi::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryInvestorProductGroupMargin>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryInvestorProductGroupMargin(pInvestorProductGroupMargin, pRspInfo,nRequestID,bIsLast);
    }
    if (pInvestorProductGroupMargin)
    {
        qDebug("\tProductGroupID [%s]\n", pInvestorProductGroupMargin->ProductGroupID);
        qDebug("\tBrokerID [%s]\n", pInvestorProductGroupMargin->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInvestorProductGroupMargin->InvestorID);
        qDebug("\tTradingDay [%s]\n", pInvestorProductGroupMargin->TradingDay);
        qDebug("\tExchangeID [%s]\n", pInvestorProductGroupMargin->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInvestorProductGroupMargin->InvestUnitID);
        qDebug("\tSettlementID [%d]\n", pInvestorProductGroupMargin->SettlementID);
        qDebug("\tHedgeFlag [%c]\n", pInvestorProductGroupMargin->HedgeFlag);
        qDebug("\tFrozenMargin [%.8lf]\n", pInvestorProductGroupMargin->FrozenMargin);
        qDebug("\tLongFrozenMargin [%.8lf]\n", pInvestorProductGroupMargin->LongFrozenMargin);
        qDebug("\tShortFrozenMargin [%.8lf]\n", pInvestorProductGroupMargin->ShortFrozenMargin);
        qDebug("\tUseMargin [%.8lf]\n", pInvestorProductGroupMargin->UseMargin);
        qDebug("\tLongUseMargin [%.8lf]\n", pInvestorProductGroupMargin->LongUseMargin);
        qDebug("\tShortUseMargin [%.8lf]\n", pInvestorProductGroupMargin->ShortUseMargin);
        qDebug("\tExchMargin [%.8lf]\n", pInvestorProductGroupMargin->ExchMargin);
        qDebug("\tLongExchMargin [%.8lf]\n", pInvestorProductGroupMargin->LongExchMargin);
        qDebug("\tShortExchMargin [%.8lf]\n", pInvestorProductGroupMargin->ShortExchMargin);
        qDebug("\tCloseProfit [%.8lf]\n", pInvestorProductGroupMargin->CloseProfit);
        qDebug("\tFrozenCommission [%.8lf]\n", pInvestorProductGroupMargin->FrozenCommission);
        qDebug("\tCommission [%.8lf]\n", pInvestorProductGroupMargin->Commission);
        qDebug("\tFrozenCash [%.8lf]\n", pInvestorProductGroupMargin->FrozenCash);
        qDebug("\tCashIn [%.8lf]\n", pInvestorProductGroupMargin->CashIn);
        qDebug("\tPositionProfit [%.8lf]\n", pInvestorProductGroupMargin->PositionProfit);
        qDebug("\tOffsetAmount [%.8lf]\n", pInvestorProductGroupMargin->OffsetAmount);
        qDebug("\tLongOffsetAmount [%.8lf]\n", pInvestorProductGroupMargin->LongOffsetAmount);
        qDebug("\tShortOffsetAmount [%.8lf]\n", pInvestorProductGroupMargin->ShortOffsetAmount);
        qDebug("\tExchOffsetAmount [%.8lf]\n", pInvestorProductGroupMargin->ExchOffsetAmount);
        qDebug("\tLongExchOffsetAmount [%.8lf]\n", pInvestorProductGroupMargin->LongExchOffsetAmount);
        qDebug("\tShortExchOffsetAmount [%.8lf]\n", pInvestorProductGroupMargin->ShortExchOffsetAmount);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryInvestorProductGroupMargin>\n");
};

void CTraderSpi::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryExchangeMarginRate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryExchangeMarginRate(pExchangeMarginRate, pRspInfo,nRequestID,bIsLast);
    }
    if (pExchangeMarginRate)
    {
        qDebug("\tBrokerID [%s]\n", pExchangeMarginRate->BrokerID);
        qDebug("\tInstrumentID [%s]\n", pExchangeMarginRate->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pExchangeMarginRate->ExchangeID);
        qDebug("\tHedgeFlag [%c]\n", pExchangeMarginRate->HedgeFlag);
        qDebug("\tLongMarginRatioByMoney [%.8lf]\n", pExchangeMarginRate->LongMarginRatioByMoney);
        qDebug("\tLongMarginRatioByVolume [%.8lf]\n", pExchangeMarginRate->LongMarginRatioByVolume);
        qDebug("\tShortMarginRatioByMoney [%.8lf]\n", pExchangeMarginRate->ShortMarginRatioByMoney);
        qDebug("\tShortMarginRatioByVolume [%.8lf]\n", pExchangeMarginRate->ShortMarginRatioByVolume);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryExchangeMarginRate>\n");
};

void CTraderSpi::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryExchangeMarginRateAdjust>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryExchangeMarginRateAdjust(pExchangeMarginRateAdjust, pRspInfo,nRequestID,bIsLast);
    }
    if (pExchangeMarginRateAdjust)
    {
        qDebug("\tBrokerID [%s]\n", pExchangeMarginRateAdjust->BrokerID);
        qDebug("\tInstrumentID [%s]\n", pExchangeMarginRateAdjust->InstrumentID);
        qDebug("\tHedgeFlag [%c]\n", pExchangeMarginRateAdjust->HedgeFlag);
        qDebug("\tLongMarginRatioByMoney [%.8lf]\n", pExchangeMarginRateAdjust->LongMarginRatioByMoney);
        qDebug("\tLongMarginRatioByVolume [%.8lf]\n", pExchangeMarginRateAdjust->LongMarginRatioByVolume);
        qDebug("\tShortMarginRatioByMoney [%.8lf]\n", pExchangeMarginRateAdjust->ShortMarginRatioByMoney);
        qDebug("\tShortMarginRatioByVolume [%.8lf]\n", pExchangeMarginRateAdjust->ShortMarginRatioByVolume);
        qDebug("\tExchLongMarginRatioByMoney [%.8lf]\n", pExchangeMarginRateAdjust->ExchLongMarginRatioByMoney);
        qDebug("\tExchLongMarginRatioByVolume [%.8lf]\n", pExchangeMarginRateAdjust->ExchLongMarginRatioByVolume);
        qDebug("\tExchShortMarginRatioByMoney [%.8lf]\n", pExchangeMarginRateAdjust->ExchShortMarginRatioByMoney);
        qDebug("\tExchShortMarginRatioByVolume [%.8lf]\n", pExchangeMarginRateAdjust->ExchShortMarginRatioByVolume);
        qDebug("\tNoLongMarginRatioByMoney [%.8lf]\n", pExchangeMarginRateAdjust->NoLongMarginRatioByMoney);
        qDebug("\tNoLongMarginRatioByVolume [%.8lf]\n", pExchangeMarginRateAdjust->NoLongMarginRatioByVolume);
        qDebug("\tNoShortMarginRatioByMoney [%.8lf]\n", pExchangeMarginRateAdjust->NoShortMarginRatioByMoney);
        qDebug("\tNoShortMarginRatioByVolume [%.8lf]\n", pExchangeMarginRateAdjust->NoShortMarginRatioByVolume);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryExchangeMarginRateAdjust>\n");
};

void CTraderSpi::OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryExchangeRate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryExchangeRate(pExchangeRate, pRspInfo,nRequestID,bIsLast);
    }
    if (pExchangeRate)
    {
        qDebug("\tBrokerID [%s]\n", pExchangeRate->BrokerID);
        qDebug("\tFromCurrencyID [%s]\n", pExchangeRate->FromCurrencyID);
        qDebug("\tToCurrencyID [%s]\n", pExchangeRate->ToCurrencyID);
        qDebug("\tFromCurrencyUnit [%.8lf]\n", pExchangeRate->FromCurrencyUnit);
        qDebug("\tExchangeRate [%.8lf]\n", pExchangeRate->ExchangeRate);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryExchangeRate>\n");
};

void CTraderSpi::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQrySecAgentACIDMap>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQrySecAgentACIDMap(pSecAgentACIDMap, pRspInfo,nRequestID,bIsLast);
    }
    if (pSecAgentACIDMap)
    {
        qDebug("\tBrokerID [%s]\n", pSecAgentACIDMap->BrokerID);
        qDebug("\tUserID [%s]\n", pSecAgentACIDMap->UserID);
        qDebug("\tAccountID [%s]\n", pSecAgentACIDMap->AccountID);
        qDebug("\tCurrencyID [%s]\n", pSecAgentACIDMap->CurrencyID);
        qDebug("\tBrokerSecAgentID [%s]\n", pSecAgentACIDMap->BrokerSecAgentID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQrySecAgentACIDMap>\n");
};

void CTraderSpi::OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryProductExchRate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryProductExchRate(pProductExchRate, pRspInfo,nRequestID,bIsLast);
    }
    if (pProductExchRate)
    {
        qDebug("\tProductID [%s]\n", pProductExchRate->ProductID);
        qDebug("\tQuoteCurrencyID [%s]\n", pProductExchRate->QuoteCurrencyID);
        qDebug("\tExchangeID [%s]\n", pProductExchRate->ExchangeID);
        qDebug("\tExchangeRate [%.8lf]\n", pProductExchRate->ExchangeRate);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryProductExchRate>\n");
};

void CTraderSpi::OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryProductGroup>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryProductGroup(pProductGroup, pRspInfo,nRequestID,bIsLast);
    }
    if (pProductGroup)
    {
        qDebug("\tProductID [%s]\n", pProductGroup->ProductID);
        qDebug("\tExchangeID [%s]\n", pProductGroup->ExchangeID);
        qDebug("\tProductGroupID [%s]\n", pProductGroup->ProductGroupID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryProductGroup>\n");
};

void CTraderSpi::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryMMInstrumentCommissionRate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryMMInstrumentCommissionRate(pMMInstrumentCommissionRate, pRspInfo,nRequestID,bIsLast);
    }
    if (pMMInstrumentCommissionRate)
    {
        qDebug("\tInstrumentID [%s]\n", pMMInstrumentCommissionRate->InstrumentID);
        qDebug("\tBrokerID [%s]\n", pMMInstrumentCommissionRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pMMInstrumentCommissionRate->InvestorID);
        qDebug("\tInvestorRange [%c]\n", pMMInstrumentCommissionRate->InvestorRange);
        qDebug("\tOpenRatioByMoney [%.8lf]\n", pMMInstrumentCommissionRate->OpenRatioByMoney);
        qDebug("\tOpenRatioByVolume [%.8lf]\n", pMMInstrumentCommissionRate->OpenRatioByVolume);
        qDebug("\tCloseRatioByMoney [%.8lf]\n", pMMInstrumentCommissionRate->CloseRatioByMoney);
        qDebug("\tCloseRatioByVolume [%.8lf]\n", pMMInstrumentCommissionRate->CloseRatioByVolume);
        qDebug("\tCloseTodayRatioByMoney [%.8lf]\n", pMMInstrumentCommissionRate->CloseTodayRatioByMoney);
        qDebug("\tCloseTodayRatioByVolume [%.8lf]\n", pMMInstrumentCommissionRate->CloseTodayRatioByVolume);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryMMInstrumentCommissionRate>\n");
};

void CTraderSpi::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryMMOptionInstrCommRate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryMMOptionInstrCommRate(pMMOptionInstrCommRate, pRspInfo,nRequestID,bIsLast);
    }
    if (pMMOptionInstrCommRate)
    {
        qDebug("\tInstrumentID [%s]\n", pMMOptionInstrCommRate->InstrumentID);
        qDebug("\tBrokerID [%s]\n", pMMOptionInstrCommRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pMMOptionInstrCommRate->InvestorID);
        qDebug("\tInvestorRange [%c]\n", pMMOptionInstrCommRate->InvestorRange);
        qDebug("\tOpenRatioByMoney [%.8lf]\n", pMMOptionInstrCommRate->OpenRatioByMoney);
        qDebug("\tOpenRatioByVolume [%.8lf]\n", pMMOptionInstrCommRate->OpenRatioByVolume);
        qDebug("\tCloseRatioByMoney [%.8lf]\n", pMMOptionInstrCommRate->CloseRatioByMoney);
        qDebug("\tCloseRatioByVolume [%.8lf]\n", pMMOptionInstrCommRate->CloseRatioByVolume);
        qDebug("\tCloseTodayRatioByMoney [%.8lf]\n", pMMOptionInstrCommRate->CloseTodayRatioByMoney);
        qDebug("\tCloseTodayRatioByVolume [%.8lf]\n", pMMOptionInstrCommRate->CloseTodayRatioByVolume);
        qDebug("\tStrikeRatioByMoney [%.8lf]\n", pMMOptionInstrCommRate->StrikeRatioByMoney);
        qDebug("\tStrikeRatioByVolume [%.8lf]\n", pMMOptionInstrCommRate->StrikeRatioByVolume);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryMMOptionInstrCommRate>\n");
};

void CTraderSpi::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryInstrumentOrderCommRate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryInstrumentOrderCommRate(pInstrumentOrderCommRate, pRspInfo,nRequestID,bIsLast);
    }
    if (pInstrumentOrderCommRate)
    {
        qDebug("\tInstrumentID [%s]\n", pInstrumentOrderCommRate->InstrumentID);
        qDebug("\tBrokerID [%s]\n", pInstrumentOrderCommRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInstrumentOrderCommRate->InvestorID);
        qDebug("\tExchangeID [%s]\n", pInstrumentOrderCommRate->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInstrumentOrderCommRate->InvestUnitID);
        qDebug("\tInvestorRange [%c]\n", pInstrumentOrderCommRate->InvestorRange);
        qDebug("\tHedgeFlag [%c]\n", pInstrumentOrderCommRate->HedgeFlag);
        qDebug("\tOrderCommByVolume [%.8lf]\n", pInstrumentOrderCommRate->OrderCommByVolume);
        qDebug("\tOrderActionCommByVolume [%.8lf]\n", pInstrumentOrderCommRate->OrderActionCommByVolume);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryInstrumentOrderCommRate>\n");
};

void CTraderSpi::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQrySecAgentTradingAccount>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQrySecAgentTradingAccount(pTradingAccount, pRspInfo,nRequestID,bIsLast);
    }
    if (pTradingAccount)
    {
        qDebug("\tBrokerID [%s]\n", pTradingAccount->BrokerID);
        qDebug("\tAccountID [%s]\n", pTradingAccount->AccountID);
        qDebug("\tTradingDay [%s]\n", pTradingAccount->TradingDay);
        qDebug("\tCurrencyID [%s]\n", pTradingAccount->CurrencyID);
        qDebug("\tSettlementID [%d]\n", pTradingAccount->SettlementID);
        qDebug("\tBizType [%c]\n", pTradingAccount->BizType);
        qDebug("\tPreMortgage [%.8lf]\n", pTradingAccount->PreMortgage);
        qDebug("\tPreCredit [%.8lf]\n", pTradingAccount->PreCredit);
        qDebug("\tPreDeposit [%.8lf]\n", pTradingAccount->PreDeposit);
        qDebug("\tPreBalance [%.8lf]\n", pTradingAccount->PreBalance);
        qDebug("\tPreMargin [%.8lf]\n", pTradingAccount->PreMargin);
        qDebug("\tInterestBase [%.8lf]\n", pTradingAccount->InterestBase);
        qDebug("\tInterest [%.8lf]\n", pTradingAccount->Interest);
        qDebug("\tDeposit [%.8lf]\n", pTradingAccount->Deposit);
        qDebug("\tWithdraw [%.8lf]\n", pTradingAccount->Withdraw);
        qDebug("\tFrozenMargin [%.8lf]\n", pTradingAccount->FrozenMargin);
        qDebug("\tFrozenCash [%.8lf]\n", pTradingAccount->FrozenCash);
        qDebug("\tFrozenCommission [%.8lf]\n", pTradingAccount->FrozenCommission);
        qDebug("\tCurrMargin [%.8lf]\n", pTradingAccount->CurrMargin);
        qDebug("\tCashIn [%.8lf]\n", pTradingAccount->CashIn);
        qDebug("\tCommission [%.8lf]\n", pTradingAccount->Commission);
        qDebug("\tCloseProfit [%.8lf]\n", pTradingAccount->CloseProfit);
        qDebug("\tPositionProfit [%.8lf]\n", pTradingAccount->PositionProfit);
        qDebug("\tBalance [%.8lf]\n", pTradingAccount->Balance);
        qDebug("\tAvailable [%.8lf]\n", pTradingAccount->Available);
        qDebug("\tWithdrawQuota [%.8lf]\n", pTradingAccount->WithdrawQuota);
        qDebug("\tReserve [%.8lf]\n", pTradingAccount->Reserve);
        qDebug("\tCredit [%.8lf]\n", pTradingAccount->Credit);
        qDebug("\tMortgage [%.8lf]\n", pTradingAccount->Mortgage);
        qDebug("\tExchangeMargin [%.8lf]\n", pTradingAccount->ExchangeMargin);
        qDebug("\tDeliveryMargin [%.8lf]\n", pTradingAccount->DeliveryMargin);
        qDebug("\tExchangeDeliveryMargin [%.8lf]\n", pTradingAccount->ExchangeDeliveryMargin);
        qDebug("\tReserveBalance [%.8lf]\n", pTradingAccount->ReserveBalance);
        qDebug("\tPreFundMortgageIn [%.8lf]\n", pTradingAccount->PreFundMortgageIn);
        qDebug("\tPreFundMortgageOut [%.8lf]\n", pTradingAccount->PreFundMortgageOut);
        qDebug("\tFundMortgageIn [%.8lf]\n", pTradingAccount->FundMortgageIn);
        qDebug("\tFundMortgageOut [%.8lf]\n", pTradingAccount->FundMortgageOut);
        qDebug("\tFundMortgageAvailable [%.8lf]\n", pTradingAccount->FundMortgageAvailable);
        qDebug("\tMortgageableFund [%.8lf]\n", pTradingAccount->MortgageableFund);
        qDebug("\tSpecProductMargin [%.8lf]\n", pTradingAccount->SpecProductMargin);
        qDebug("\tSpecProductFrozenMargin [%.8lf]\n", pTradingAccount->SpecProductFrozenMargin);
        qDebug("\tSpecProductCommission [%.8lf]\n", pTradingAccount->SpecProductCommission);
        qDebug("\tSpecProductFrozenCommission [%.8lf]\n", pTradingAccount->SpecProductFrozenCommission);
        qDebug("\tSpecProductPositionProfit [%.8lf]\n", pTradingAccount->SpecProductPositionProfit);
        qDebug("\tSpecProductCloseProfit [%.8lf]\n", pTradingAccount->SpecProductCloseProfit);
        qDebug("\tSpecProductPositionProfitByAlg [%.8lf]\n", pTradingAccount->SpecProductPositionProfitByAlg);
        qDebug("\tSpecProductExchangeMargin [%.8lf]\n", pTradingAccount->SpecProductExchangeMargin);
        qDebug("\tFrozenSwap [%.8lf]\n", pTradingAccount->FrozenSwap);
        qDebug("\tRemainSwap [%.8lf]\n", pTradingAccount->RemainSwap);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQrySecAgentTradingAccount>\n");
};

void CTraderSpi::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQrySecAgentCheckMode>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQrySecAgentCheckMode(pSecAgentCheckMode, pRspInfo,nRequestID,bIsLast);
    }
    if (pSecAgentCheckMode)
    {
        qDebug("\tInvestorID [%s]\n", pSecAgentCheckMode->InvestorID);
        qDebug("\tBrokerID [%s]\n", pSecAgentCheckMode->BrokerID);
        qDebug("\tCurrencyID [%s]\n", pSecAgentCheckMode->CurrencyID);
        qDebug("\tBrokerSecAgentID [%s]\n", pSecAgentCheckMode->BrokerSecAgentID);
        qDebug("\tCheckSelfAccount [%d]\n", pSecAgentCheckMode->CheckSelfAccount);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQrySecAgentCheckMode>\n");
};

void CTraderSpi::OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQrySecAgentTradeInfo>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQrySecAgentTradeInfo(pSecAgentTradeInfo, pRspInfo,nRequestID,bIsLast);
    }
    if (pSecAgentTradeInfo)
    {
        qDebug("\tBrokerID [%s]\n", pSecAgentTradeInfo->BrokerID);
        qDebug("\tBrokerSecAgentID [%s]\n", pSecAgentTradeInfo->BrokerSecAgentID);
        qDebug("\tInvestorID [%s]\n", pSecAgentTradeInfo->InvestorID);
        qDebug("\tLongCustomerName [%s]\n", pSecAgentTradeInfo->LongCustomerName);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQrySecAgentTradeInfo>\n");
};

void CTraderSpi::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryOptionInstrTradeCost>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryOptionInstrTradeCost(pOptionInstrTradeCost, pRspInfo,nRequestID,bIsLast);
    }
    if (pOptionInstrTradeCost)
    {
        qDebug("\tBrokerID [%s]\n", pOptionInstrTradeCost->BrokerID);
        qDebug("\tInvestorID [%s]\n", pOptionInstrTradeCost->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pOptionInstrTradeCost->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pOptionInstrTradeCost->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pOptionInstrTradeCost->InvestUnitID);
        qDebug("\tHedgeFlag [%c]\n", pOptionInstrTradeCost->HedgeFlag);
        qDebug("\tFixedMargin [%.8lf]\n", pOptionInstrTradeCost->FixedMargin);
        qDebug("\tMiniMargin [%.8lf]\n", pOptionInstrTradeCost->MiniMargin);
        qDebug("\tRoyalty [%.8lf]\n", pOptionInstrTradeCost->Royalty);
        qDebug("\tExchFixedMargin [%.8lf]\n", pOptionInstrTradeCost->ExchFixedMargin);
        qDebug("\tExchMiniMargin [%.8lf]\n", pOptionInstrTradeCost->ExchMiniMargin);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryOptionInstrTradeCost>\n");
};

void CTraderSpi::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryOptionInstrCommRate>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryOptionInstrCommRate(pOptionInstrCommRate, pRspInfo,nRequestID,bIsLast);
    }
    if (pOptionInstrCommRate)
    {
        qDebug("\tInstrumentID [%s]\n", pOptionInstrCommRate->InstrumentID);
        qDebug("\tBrokerID [%s]\n", pOptionInstrCommRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pOptionInstrCommRate->InvestorID);
        qDebug("\tExchangeID [%s]\n", pOptionInstrCommRate->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pOptionInstrCommRate->InvestUnitID);
        qDebug("\tInvestorRange [%c]\n", pOptionInstrCommRate->InvestorRange);
        qDebug("\tOpenRatioByMoney [%.8lf]\n", pOptionInstrCommRate->OpenRatioByMoney);
        qDebug("\tOpenRatioByVolume [%.8lf]\n", pOptionInstrCommRate->OpenRatioByVolume);
        qDebug("\tCloseRatioByMoney [%.8lf]\n", pOptionInstrCommRate->CloseRatioByMoney);
        qDebug("\tCloseRatioByVolume [%.8lf]\n", pOptionInstrCommRate->CloseRatioByVolume);
        qDebug("\tCloseTodayRatioByMoney [%.8lf]\n", pOptionInstrCommRate->CloseTodayRatioByMoney);
        qDebug("\tCloseTodayRatioByVolume [%.8lf]\n", pOptionInstrCommRate->CloseTodayRatioByVolume);
        qDebug("\tStrikeRatioByMoney [%.8lf]\n", pOptionInstrCommRate->StrikeRatioByMoney);
        qDebug("\tStrikeRatioByVolume [%.8lf]\n", pOptionInstrCommRate->StrikeRatioByVolume);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryOptionInstrCommRate>\n");
};

void CTraderSpi::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryExecOrder>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryExecOrder(pExecOrder, pRspInfo,nRequestID,bIsLast);
    }
    if (pExecOrder)
    {
        qDebug("\tBrokerID [%s]\n", pExecOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pExecOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pExecOrder->InstrumentID);
        qDebug("\tExecOrderRef [%s]\n", pExecOrder->ExecOrderRef);
        qDebug("\tUserID [%s]\n", pExecOrder->UserID);
        qDebug("\tBusinessUnit [%s]\n", pExecOrder->BusinessUnit);
        qDebug("\tExecOrderLocalID [%s]\n", pExecOrder->ExecOrderLocalID);
        qDebug("\tExchangeID [%s]\n", pExecOrder->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pExecOrder->ParticipantID);
        qDebug("\tClientID [%s]\n", pExecOrder->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pExecOrder->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pExecOrder->TraderID);
        qDebug("\tTradingDay [%s]\n", pExecOrder->TradingDay);
        qDebug("\tExecOrderSysID [%s]\n", pExecOrder->ExecOrderSysID);
        qDebug("\tInsertDate [%s]\n", pExecOrder->InsertDate);
        qDebug("\tInsertTime [%s]\n", pExecOrder->InsertTime);
        qDebug("\tCancelTime [%s]\n", pExecOrder->CancelTime);
        qDebug("\tClearingPartID [%s]\n", pExecOrder->ClearingPartID);
        qDebug("\tUserProductInfo [%s]\n", pExecOrder->UserProductInfo);
        qDebug("\tStatusMsg [%s]\n", pExecOrder->StatusMsg);
        qDebug("\tActiveUserID [%s]\n", pExecOrder->ActiveUserID);
        qDebug("\tBranchID [%s]\n", pExecOrder->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pExecOrder->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pExecOrder->AccountID);
        qDebug("\tCurrencyID [%s]\n", pExecOrder->CurrencyID);
        qDebug("\tIPAddress [%s]\n", pExecOrder->IPAddress);
        qDebug("\tMacAddress [%s]\n", pExecOrder->MacAddress);
        qDebug("\tVolume [%d]\n", pExecOrder->Volume);
        qDebug("\tRequestID [%d]\n", pExecOrder->RequestID);
        qDebug("\tInstallID [%d]\n", pExecOrder->InstallID);
        qDebug("\tNotifySequence [%d]\n", pExecOrder->NotifySequence);
        qDebug("\tSettlementID [%d]\n", pExecOrder->SettlementID);
        qDebug("\tSequenceNo [%d]\n", pExecOrder->SequenceNo);
        qDebug("\tFrontID [%d]\n", pExecOrder->FrontID);
        qDebug("\tSessionID [%d]\n", pExecOrder->SessionID);
        qDebug("\tBrokerExecOrderSeq [%d]\n", pExecOrder->BrokerExecOrderSeq);
        qDebug("\tOffsetFlag [%c]\n", pExecOrder->OffsetFlag);
        qDebug("\tHedgeFlag [%c]\n", pExecOrder->HedgeFlag);
        qDebug("\tActionType [%c]\n", pExecOrder->ActionType);
        qDebug("\tPosiDirection [%c]\n", pExecOrder->PosiDirection);
        qDebug("\tReservePositionFlag [%c]\n", pExecOrder->ReservePositionFlag);
        qDebug("\tCloseFlag [%c]\n", pExecOrder->CloseFlag);
        qDebug("\tOrderSubmitStatus [%c]\n", pExecOrder->OrderSubmitStatus);
        qDebug("\tExecResult [%c]\n", pExecOrder->ExecResult);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryExecOrder>\n");
};

void CTraderSpi::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryForQuote>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryForQuote(pForQuote, pRspInfo,nRequestID,bIsLast);
    }
    if (pForQuote)
    {
        qDebug("\tBrokerID [%s]\n", pForQuote->BrokerID);
        qDebug("\tInvestorID [%s]\n", pForQuote->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pForQuote->InstrumentID);
        qDebug("\tForQuoteRef [%s]\n", pForQuote->ForQuoteRef);
        qDebug("\tUserID [%s]\n", pForQuote->UserID);
        qDebug("\tForQuoteLocalID [%s]\n", pForQuote->ForQuoteLocalID);
        qDebug("\tExchangeID [%s]\n", pForQuote->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pForQuote->ParticipantID);
        qDebug("\tClientID [%s]\n", pForQuote->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pForQuote->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pForQuote->TraderID);
        qDebug("\tInsertDate [%s]\n", pForQuote->InsertDate);
        qDebug("\tInsertTime [%s]\n", pForQuote->InsertTime);
        qDebug("\tStatusMsg [%s]\n", pForQuote->StatusMsg);
        qDebug("\tActiveUserID [%s]\n", pForQuote->ActiveUserID);
        qDebug("\tInvestUnitID [%s]\n", pForQuote->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pForQuote->IPAddress);
        qDebug("\tMacAddress [%s]\n", pForQuote->MacAddress);
        qDebug("\tInstallID [%d]\n", pForQuote->InstallID);
        qDebug("\tFrontID [%d]\n", pForQuote->FrontID);
        qDebug("\tSessionID [%d]\n", pForQuote->SessionID);
        qDebug("\tBrokerForQutoSeq [%d]\n", pForQuote->BrokerForQutoSeq);
        qDebug("\tForQuoteStatus [%c]\n", pForQuote->ForQuoteStatus);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryForQuote>\n");
};

void CTraderSpi::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryQuote>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryQuote(pQuote, pRspInfo,nRequestID,bIsLast);
    }
    if (pQuote)
    {
        qDebug("\tBrokerID [%s]\n", pQuote->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQuote->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQuote->InstrumentID);
        qDebug("\tQuoteRef [%s]\n", pQuote->QuoteRef);
        qDebug("\tUserID [%s]\n", pQuote->UserID);
        qDebug("\tBusinessUnit [%s]\n", pQuote->BusinessUnit);
        qDebug("\tQuoteLocalID [%s]\n", pQuote->QuoteLocalID);
        qDebug("\tExchangeID [%s]\n", pQuote->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pQuote->ParticipantID);
        qDebug("\tClientID [%s]\n", pQuote->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pQuote->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pQuote->TraderID);
        qDebug("\tTradingDay [%s]\n", pQuote->TradingDay);
        qDebug("\tQuoteSysID [%s]\n", pQuote->QuoteSysID);
        qDebug("\tInsertDate [%s]\n", pQuote->InsertDate);
        qDebug("\tInsertTime [%s]\n", pQuote->InsertTime);
        qDebug("\tCancelTime [%s]\n", pQuote->CancelTime);
        qDebug("\tClearingPartID [%s]\n", pQuote->ClearingPartID);
        qDebug("\tAskOrderSysID [%s]\n", pQuote->AskOrderSysID);
        qDebug("\tBidOrderSysID [%s]\n", pQuote->BidOrderSysID);
        qDebug("\tUserProductInfo [%s]\n", pQuote->UserProductInfo);
        qDebug("\tStatusMsg [%s]\n", pQuote->StatusMsg);
        qDebug("\tActiveUserID [%s]\n", pQuote->ActiveUserID);
        qDebug("\tAskOrderRef [%s]\n", pQuote->AskOrderRef);
        qDebug("\tBidOrderRef [%s]\n", pQuote->BidOrderRef);
        qDebug("\tForQuoteSysID [%s]\n", pQuote->ForQuoteSysID);
        qDebug("\tBranchID [%s]\n", pQuote->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pQuote->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pQuote->AccountID);
        qDebug("\tCurrencyID [%s]\n", pQuote->CurrencyID);
        qDebug("\tIPAddress [%s]\n", pQuote->IPAddress);
        qDebug("\tMacAddress [%s]\n", pQuote->MacAddress);
        qDebug("\tAskVolume [%d]\n", pQuote->AskVolume);
        qDebug("\tBidVolume [%d]\n", pQuote->BidVolume);
        qDebug("\tRequestID [%d]\n", pQuote->RequestID);
        qDebug("\tInstallID [%d]\n", pQuote->InstallID);
        qDebug("\tNotifySequence [%d]\n", pQuote->NotifySequence);
        qDebug("\tSettlementID [%d]\n", pQuote->SettlementID);
        qDebug("\tSequenceNo [%d]\n", pQuote->SequenceNo);
        qDebug("\tFrontID [%d]\n", pQuote->FrontID);
        qDebug("\tSessionID [%d]\n", pQuote->SessionID);
        qDebug("\tBrokerQuoteSeq [%d]\n", pQuote->BrokerQuoteSeq);
        qDebug("\tAskOffsetFlag [%c]\n", pQuote->AskOffsetFlag);
        qDebug("\tBidOffsetFlag [%c]\n", pQuote->BidOffsetFlag);
        qDebug("\tAskHedgeFlag [%c]\n", pQuote->AskHedgeFlag);
        qDebug("\tBidHedgeFlag [%c]\n", pQuote->BidHedgeFlag);
        qDebug("\tOrderSubmitStatus [%c]\n", pQuote->OrderSubmitStatus);
        qDebug("\tQuoteStatus [%c]\n", pQuote->QuoteStatus);
        qDebug("\tAskPrice [%.8lf]\n", pQuote->AskPrice);
        qDebug("\tBidPrice [%.8lf]\n", pQuote->BidPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryQuote>\n");
};

void CTraderSpi::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryOptionSelfClose>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryOptionSelfClose(pOptionSelfClose, pRspInfo,nRequestID,bIsLast);
    }
    if (pOptionSelfClose)
    {
        qDebug("\tBrokerID [%s]\n", pOptionSelfClose->BrokerID);
        qDebug("\tInvestorID [%s]\n", pOptionSelfClose->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pOptionSelfClose->InstrumentID);
        qDebug("\tOptionSelfCloseRef [%s]\n", pOptionSelfClose->OptionSelfCloseRef);
        qDebug("\tUserID [%s]\n", pOptionSelfClose->UserID);
        qDebug("\tBusinessUnit [%s]\n", pOptionSelfClose->BusinessUnit);
        qDebug("\tOptionSelfCloseLocalID [%s]\n", pOptionSelfClose->OptionSelfCloseLocalID);
        qDebug("\tExchangeID [%s]\n", pOptionSelfClose->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pOptionSelfClose->ParticipantID);
        qDebug("\tClientID [%s]\n", pOptionSelfClose->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pOptionSelfClose->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pOptionSelfClose->TraderID);
        qDebug("\tTradingDay [%s]\n", pOptionSelfClose->TradingDay);
        qDebug("\tOptionSelfCloseSysID [%s]\n", pOptionSelfClose->OptionSelfCloseSysID);
        qDebug("\tInsertDate [%s]\n", pOptionSelfClose->InsertDate);
        qDebug("\tInsertTime [%s]\n", pOptionSelfClose->InsertTime);
        qDebug("\tCancelTime [%s]\n", pOptionSelfClose->CancelTime);
        qDebug("\tClearingPartID [%s]\n", pOptionSelfClose->ClearingPartID);
        qDebug("\tUserProductInfo [%s]\n", pOptionSelfClose->UserProductInfo);
        qDebug("\tStatusMsg [%s]\n", pOptionSelfClose->StatusMsg);
        qDebug("\tActiveUserID [%s]\n", pOptionSelfClose->ActiveUserID);
        qDebug("\tBranchID [%s]\n", pOptionSelfClose->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pOptionSelfClose->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pOptionSelfClose->AccountID);
        qDebug("\tCurrencyID [%s]\n", pOptionSelfClose->CurrencyID);
        qDebug("\tIPAddress [%s]\n", pOptionSelfClose->IPAddress);
        qDebug("\tMacAddress [%s]\n", pOptionSelfClose->MacAddress);
        qDebug("\tVolume [%d]\n", pOptionSelfClose->Volume);
        qDebug("\tRequestID [%d]\n", pOptionSelfClose->RequestID);
        qDebug("\tInstallID [%d]\n", pOptionSelfClose->InstallID);
        qDebug("\tNotifySequence [%d]\n", pOptionSelfClose->NotifySequence);
        qDebug("\tSettlementID [%d]\n", pOptionSelfClose->SettlementID);
        qDebug("\tSequenceNo [%d]\n", pOptionSelfClose->SequenceNo);
        qDebug("\tFrontID [%d]\n", pOptionSelfClose->FrontID);
        qDebug("\tSessionID [%d]\n", pOptionSelfClose->SessionID);
        qDebug("\tBrokerOptionSelfCloseSeq [%d]\n", pOptionSelfClose->BrokerOptionSelfCloseSeq);
        qDebug("\tHedgeFlag [%c]\n", pOptionSelfClose->HedgeFlag);
        qDebug("\tOptSelfCloseFlag [%c]\n", pOptionSelfClose->OptSelfCloseFlag);
        qDebug("\tOrderSubmitStatus [%c]\n", pOptionSelfClose->OrderSubmitStatus);
        qDebug("\tExecResult [%c]\n", pOptionSelfClose->ExecResult);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryOptionSelfClose>\n");
};

void CTraderSpi::OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryInvestUnit>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryInvestUnit(pInvestUnit, pRspInfo,nRequestID,bIsLast);
    }
    if (pInvestUnit)
    {
        qDebug("\tBrokerID [%s]\n", pInvestUnit->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInvestUnit->InvestorID);
        qDebug("\tInvestUnitID [%s]\n", pInvestUnit->InvestUnitID);
        qDebug("\tInvestorUnitName [%s]\n", pInvestUnit->InvestorUnitName);
        qDebug("\tInvestorGroupID [%s]\n", pInvestUnit->InvestorGroupID);
        qDebug("\tCommModelID [%s]\n", pInvestUnit->CommModelID);
        qDebug("\tMarginModelID [%s]\n", pInvestUnit->MarginModelID);
        qDebug("\tAccountID [%s]\n", pInvestUnit->AccountID);
        qDebug("\tCurrencyID [%s]\n", pInvestUnit->CurrencyID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryInvestUnit>\n");
};

void CTraderSpi::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryCombInstrumentGuard>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryCombInstrumentGuard(pCombInstrumentGuard, pRspInfo,nRequestID,bIsLast);
    }
    if (pCombInstrumentGuard)
    {
        qDebug("\tBrokerID [%s]\n", pCombInstrumentGuard->BrokerID);
        qDebug("\tInstrumentID [%s]\n", pCombInstrumentGuard->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pCombInstrumentGuard->ExchangeID);
        qDebug("\tGuarantRatio [%.8lf]\n", pCombInstrumentGuard->GuarantRatio);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryCombInstrumentGuard>\n");
};

void CTraderSpi::OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryCombAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryCombAction(pCombAction, pRspInfo,nRequestID,bIsLast);
    }
    if (pCombAction)
    {
        qDebug("\tBrokerID [%s]\n", pCombAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pCombAction->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pCombAction->InstrumentID);
        qDebug("\tCombActionRef [%s]\n", pCombAction->CombActionRef);
        qDebug("\tUserID [%s]\n", pCombAction->UserID);
        qDebug("\tActionLocalID [%s]\n", pCombAction->ActionLocalID);
        qDebug("\tExchangeID [%s]\n", pCombAction->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pCombAction->ParticipantID);
        qDebug("\tClientID [%s]\n", pCombAction->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pCombAction->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pCombAction->TraderID);
        qDebug("\tTradingDay [%s]\n", pCombAction->TradingDay);
        qDebug("\tUserProductInfo [%s]\n", pCombAction->UserProductInfo);
        qDebug("\tStatusMsg [%s]\n", pCombAction->StatusMsg);
        qDebug("\tIPAddress [%s]\n", pCombAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pCombAction->MacAddress);
        qDebug("\tComTradeID [%s]\n", pCombAction->ComTradeID);
        qDebug("\tBranchID [%s]\n", pCombAction->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pCombAction->InvestUnitID);
        qDebug("\tVolume [%d]\n", pCombAction->Volume);
        qDebug("\tInstallID [%d]\n", pCombAction->InstallID);
        qDebug("\tNotifySequence [%d]\n", pCombAction->NotifySequence);
        qDebug("\tSettlementID [%d]\n", pCombAction->SettlementID);
        qDebug("\tSequenceNo [%d]\n", pCombAction->SequenceNo);
        qDebug("\tFrontID [%d]\n", pCombAction->FrontID);
        qDebug("\tSessionID [%d]\n", pCombAction->SessionID);
        qDebug("\tDirection [%c]\n", pCombAction->Direction);
        qDebug("\tCombDirection [%c]\n", pCombAction->CombDirection);
        qDebug("\tHedgeFlag [%c]\n", pCombAction->HedgeFlag);
        qDebug("\tActionStatus [%c]\n", pCombAction->ActionStatus);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryCombAction>\n");
};

void CTraderSpi::OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryTransferSerial>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryTransferSerial(pTransferSerial, pRspInfo,nRequestID,bIsLast);
    }
    if (pTransferSerial)
    {
        qDebug("\tTradeDate [%s]\n", pTransferSerial->TradeDate);
        qDebug("\tTradingDay [%s]\n", pTransferSerial->TradingDay);
        qDebug("\tTradeTime [%s]\n", pTransferSerial->TradeTime);
        qDebug("\tTradeCode [%s]\n", pTransferSerial->TradeCode);
        qDebug("\tBankID [%s]\n", pTransferSerial->BankID);
        qDebug("\tBankBranchID [%s]\n", pTransferSerial->BankBranchID);
        qDebug("\tBankAccount [%s]\n", pTransferSerial->BankAccount);
        qDebug("\tBankSerial [%s]\n", pTransferSerial->BankSerial);
        qDebug("\tBrokerID [%s]\n", pTransferSerial->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pTransferSerial->BrokerBranchID);
        qDebug("\tAccountID [%s]\n", pTransferSerial->AccountID);
        qDebug("\tInvestorID [%s]\n", pTransferSerial->InvestorID);
        qDebug("\tIdentifiedCardNo [%s]\n", pTransferSerial->IdentifiedCardNo);
        qDebug("\tCurrencyID [%s]\n", pTransferSerial->CurrencyID);
        qDebug("\tOperatorCode [%s]\n", pTransferSerial->OperatorCode);
        qDebug("\tBankNewAccount [%s]\n", pTransferSerial->BankNewAccount);
        qDebug("\tErrorMsg [%s]\n", pTransferSerial->ErrorMsg);
        qDebug("\tPlateSerial [%d]\n", pTransferSerial->PlateSerial);
        qDebug("\tSessionID [%d]\n", pTransferSerial->SessionID);
        qDebug("\tFutureSerial [%d]\n", pTransferSerial->FutureSerial);
        qDebug("\tErrorID [%d]\n", pTransferSerial->ErrorID);
        qDebug("\tBankAccType [%c]\n", pTransferSerial->BankAccType);
        qDebug("\tFutureAccType [%c]\n", pTransferSerial->FutureAccType);
        qDebug("\tIdCardType [%c]\n", pTransferSerial->IdCardType);
        qDebug("\tAvailabilityFlag [%c]\n", pTransferSerial->AvailabilityFlag);
        qDebug("\tTradeAmount [%.8lf]\n", pTransferSerial->TradeAmount);
        qDebug("\tCustFee [%.8lf]\n", pTransferSerial->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pTransferSerial->BrokerFee);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryTransferSerial>\n");
};

void CTraderSpi::OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryAccountregister>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryAccountregister(pAccountregister, pRspInfo,nRequestID,bIsLast);
    }
    if (pAccountregister)
    {
        qDebug("\tTradeDay [%s]\n", pAccountregister->TradeDay);
        qDebug("\tBankID [%s]\n", pAccountregister->BankID);
        qDebug("\tBankBranchID [%s]\n", pAccountregister->BankBranchID);
        qDebug("\tBankAccount [%s]\n", pAccountregister->BankAccount);
        qDebug("\tBrokerID [%s]\n", pAccountregister->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pAccountregister->BrokerBranchID);
        qDebug("\tAccountID [%s]\n", pAccountregister->AccountID);
        qDebug("\tIdentifiedCardNo [%s]\n", pAccountregister->IdentifiedCardNo);
        qDebug("\tCustomerName [%s]\n", pAccountregister->CustomerName);
        qDebug("\tCurrencyID [%s]\n", pAccountregister->CurrencyID);
        qDebug("\tRegDate [%s]\n", pAccountregister->RegDate);
        qDebug("\tOutDate [%s]\n", pAccountregister->OutDate);
        qDebug("\tLongCustomerName [%s]\n", pAccountregister->LongCustomerName);
        qDebug("\tTID [%d]\n", pAccountregister->TID);
        qDebug("\tIdCardType [%c]\n", pAccountregister->IdCardType);
        qDebug("\tOpenOrDestroy [%c]\n", pAccountregister->OpenOrDestroy);
        qDebug("\tCustType [%c]\n", pAccountregister->CustType);
        qDebug("\tBankAccType [%c]\n", pAccountregister->BankAccType);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryAccountregister>\n");
};

void CTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspError>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspError(pRspInfo,nRequestID,bIsLast);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspError>\n");
};
void CTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
    qDebug("<OnRtnOrder>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnOrder(pOrder);
    }
    if (pOrder)
    {
        qDebug("\tBrokerID [%s]\n", pOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pOrder->InstrumentID);
        qDebug("\tOrderRef [%s]\n", pOrder->OrderRef);
        qDebug("\tUserID [%s]\n", pOrder->UserID);
        qDebug("\tCombOffsetFlag [%s]\n", pOrder->CombOffsetFlag);
        qDebug("\tCombHedgeFlag [%s]\n", pOrder->CombHedgeFlag);
        qDebug("\tGTDDate [%s]\n", pOrder->GTDDate);
        qDebug("\tBusinessUnit [%s]\n", pOrder->BusinessUnit);
        qDebug("\tOrderLocalID [%s]\n", pOrder->OrderLocalID);
        qDebug("\tExchangeID [%s]\n", pOrder->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pOrder->ParticipantID);
        qDebug("\tClientID [%s]\n", pOrder->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pOrder->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pOrder->TraderID);
        qDebug("\tTradingDay [%s]\n", pOrder->TradingDay);
        qDebug("\tOrderSysID [%s]\n", pOrder->OrderSysID);
        qDebug("\tInsertDate [%s]\n", pOrder->InsertDate);
        qDebug("\tInsertTime [%s]\n", pOrder->InsertTime);
        qDebug("\tActiveTime [%s]\n", pOrder->ActiveTime);
        qDebug("\tSuspendTime [%s]\n", pOrder->SuspendTime);
        qDebug("\tUpdateTime [%s]\n", pOrder->UpdateTime);
        qDebug("\tCancelTime [%s]\n", pOrder->CancelTime);
        qDebug("\tActiveTraderID [%s]\n", pOrder->ActiveTraderID);
        qDebug("\tClearingPartID [%s]\n", pOrder->ClearingPartID);
        qDebug("\tUserProductInfo [%s]\n", pOrder->UserProductInfo);
        qDebug("\tStatusMsg [%s]\n", pOrder->StatusMsg);
        qDebug("\tActiveUserID [%s]\n", pOrder->ActiveUserID);
        qDebug("\tRelativeOrderSysID [%s]\n", pOrder->RelativeOrderSysID);
        qDebug("\tBranchID [%s]\n", pOrder->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pOrder->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pOrder->AccountID);
        qDebug("\tCurrencyID [%s]\n", pOrder->CurrencyID);
        qDebug("\tIPAddress [%s]\n", pOrder->IPAddress);
        qDebug("\tMacAddress [%s]\n", pOrder->MacAddress);
        qDebug("\tVolumeTotalOriginal [%d]\n", pOrder->VolumeTotalOriginal);
        qDebug("\tMinVolume [%d]\n", pOrder->MinVolume);
        qDebug("\tIsAutoSuspend [%d]\n", pOrder->IsAutoSuspend);
        qDebug("\tRequestID [%d]\n", pOrder->RequestID);
        qDebug("\tInstallID [%d]\n", pOrder->InstallID);
        qDebug("\tNotifySequence [%d]\n", pOrder->NotifySequence);
        qDebug("\tSettlementID [%d]\n", pOrder->SettlementID);
        qDebug("\tVolumeTraded [%d]\n", pOrder->VolumeTraded);
        qDebug("\tVolumeTotal [%d]\n", pOrder->VolumeTotal);
        qDebug("\tSequenceNo [%d]\n", pOrder->SequenceNo);
        qDebug("\tFrontID [%d]\n", pOrder->FrontID);
        qDebug("\tSessionID [%d]\n", pOrder->SessionID);
        qDebug("\tUserForceClose [%d]\n", pOrder->UserForceClose);
        qDebug("\tBrokerOrderSeq [%d]\n", pOrder->BrokerOrderSeq);
        qDebug("\tZCETotalTradedVolume [%d]\n", pOrder->ZCETotalTradedVolume);
        qDebug("\tIsSwapOrder [%d]\n", pOrder->IsSwapOrder);
        qDebug("\tOrderPriceType [%c]\n", pOrder->OrderPriceType);
        qDebug("\tDirection [%c]\n", pOrder->Direction);
        qDebug("\tTimeCondition [%c]\n", pOrder->TimeCondition);
        qDebug("\tVolumeCondition [%c]\n", pOrder->VolumeCondition);
        qDebug("\tContingentCondition [%c]\n", pOrder->ContingentCondition);
        qDebug("\tForceCloseReason [%c]\n", pOrder->ForceCloseReason);
        qDebug("\tOrderSubmitStatus [%c]\n", pOrder->OrderSubmitStatus);
        qDebug("\tOrderSource [%c]\n", pOrder->OrderSource);
        qDebug("\tOrderStatus [%c]\n", pOrder->OrderStatus);
        qDebug("\tOrderType [%c]\n", pOrder->OrderType);
        qDebug("\tLimitPrice [%.8lf]\n", pOrder->LimitPrice);
        qDebug("\tStopPrice [%.8lf]\n", pOrder->StopPrice);
    }
    qDebug("</OnRtnOrder>\n");
};
void CTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    qDebug("<OnRtnTrade>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnTrade(pTrade);
    }
    if (pTrade)
    {
        qDebug("\tBrokerID [%s]\n", pTrade->BrokerID);
        qDebug("\tInvestorID [%s]\n", pTrade->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pTrade->InstrumentID);
        qDebug("\tOrderRef [%s]\n", pTrade->OrderRef);
        qDebug("\tUserID [%s]\n", pTrade->UserID);
        qDebug("\tExchangeID [%s]\n", pTrade->ExchangeID);
        qDebug("\tTradeID [%s]\n", pTrade->TradeID);
        qDebug("\tOrderSysID [%s]\n", pTrade->OrderSysID);
        qDebug("\tParticipantID [%s]\n", pTrade->ParticipantID);
        qDebug("\tClientID [%s]\n", pTrade->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pTrade->ExchangeInstID);
        qDebug("\tTradeDate [%s]\n", pTrade->TradeDate);
        qDebug("\tTradeTime [%s]\n", pTrade->TradeTime);
        qDebug("\tTraderID [%s]\n", pTrade->TraderID);
        qDebug("\tOrderLocalID [%s]\n", pTrade->OrderLocalID);
        qDebug("\tClearingPartID [%s]\n", pTrade->ClearingPartID);
        qDebug("\tBusinessUnit [%s]\n", pTrade->BusinessUnit);
        qDebug("\tTradingDay [%s]\n", pTrade->TradingDay);
        qDebug("\tInvestUnitID [%s]\n", pTrade->InvestUnitID);
        qDebug("\tVolume [%d]\n", pTrade->Volume);
        qDebug("\tSequenceNo [%d]\n", pTrade->SequenceNo);
        qDebug("\tSettlementID [%d]\n", pTrade->SettlementID);
        qDebug("\tBrokerOrderSeq [%d]\n", pTrade->BrokerOrderSeq);
        qDebug("\tDirection [%c]\n", pTrade->Direction);
        qDebug("\tTradingRole [%c]\n", pTrade->TradingRole);
        qDebug("\tOffsetFlag [%c]\n", pTrade->OffsetFlag);
        qDebug("\tHedgeFlag [%c]\n", pTrade->HedgeFlag);
        qDebug("\tTradeType [%c]\n", pTrade->TradeType);
        qDebug("\tPriceSource [%c]\n", pTrade->PriceSource);
        qDebug("\tTradeSource [%c]\n", pTrade->TradeSource);
        qDebug("\tPrice [%.8lf]\n", pTrade->Price);
    }
    qDebug("</OnRtnTrade>\n");
};
void CTraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnOrderInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnOrderInsert(pInputOrder, pRspInfo );
    }
    if (pInputOrder)
    {
        qDebug("\tBrokerID [%s]\n", pInputOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputOrder->InstrumentID);
        qDebug("\tOrderRef [%s]\n", pInputOrder->OrderRef);
        qDebug("\tUserID [%s]\n", pInputOrder->UserID);
        qDebug("\tCombOffsetFlag [%s]\n", pInputOrder->CombOffsetFlag);
        qDebug("\tCombHedgeFlag [%s]\n", pInputOrder->CombHedgeFlag);
        qDebug("\tGTDDate [%s]\n", pInputOrder->GTDDate);
        qDebug("\tBusinessUnit [%s]\n", pInputOrder->BusinessUnit);
        qDebug("\tExchangeID [%s]\n", pInputOrder->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInputOrder->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pInputOrder->AccountID);
        qDebug("\tCurrencyID [%s]\n", pInputOrder->CurrencyID);
        qDebug("\tClientID [%s]\n", pInputOrder->ClientID);
        qDebug("\tIPAddress [%s]\n", pInputOrder->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputOrder->MacAddress);
        qDebug("\tVolumeTotalOriginal [%d]\n", pInputOrder->VolumeTotalOriginal);
        qDebug("\tMinVolume [%d]\n", pInputOrder->MinVolume);
        qDebug("\tIsAutoSuspend [%d]\n", pInputOrder->IsAutoSuspend);
        qDebug("\tRequestID [%d]\n", pInputOrder->RequestID);
        qDebug("\tUserForceClose [%d]\n", pInputOrder->UserForceClose);
        qDebug("\tIsSwapOrder [%d]\n", pInputOrder->IsSwapOrder);
        qDebug("\tOrderPriceType [%c]\n", pInputOrder->OrderPriceType);
        qDebug("\tDirection [%c]\n", pInputOrder->Direction);
        qDebug("\tTimeCondition [%c]\n", pInputOrder->TimeCondition);
        qDebug("\tVolumeCondition [%c]\n", pInputOrder->VolumeCondition);
        qDebug("\tContingentCondition [%c]\n", pInputOrder->ContingentCondition);
        qDebug("\tForceCloseReason [%c]\n", pInputOrder->ForceCloseReason);
        qDebug("\tLimitPrice [%.8lf]\n", pInputOrder->LimitPrice);
        qDebug("\tStopPrice [%.8lf]\n", pInputOrder->StopPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnOrderInsert>\n");
};
void CTraderSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnOrderAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnOrderAction(pOrderAction, pRspInfo);
    }
    if (pOrderAction)
    {
        qDebug("\tBrokerID [%s]\n", pOrderAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pOrderAction->InvestorID);
        qDebug("\tOrderRef [%s]\n", pOrderAction->OrderRef);
        qDebug("\tExchangeID [%s]\n", pOrderAction->ExchangeID);
        qDebug("\tOrderSysID [%s]\n", pOrderAction->OrderSysID);
        qDebug("\tActionDate [%s]\n", pOrderAction->ActionDate);
        qDebug("\tActionTime [%s]\n", pOrderAction->ActionTime);
        qDebug("\tTraderID [%s]\n", pOrderAction->TraderID);
        qDebug("\tOrderLocalID [%s]\n", pOrderAction->OrderLocalID);
        qDebug("\tActionLocalID [%s]\n", pOrderAction->ActionLocalID);
        qDebug("\tParticipantID [%s]\n", pOrderAction->ParticipantID);
        qDebug("\tClientID [%s]\n", pOrderAction->ClientID);
        qDebug("\tBusinessUnit [%s]\n", pOrderAction->BusinessUnit);
        qDebug("\tUserID [%s]\n", pOrderAction->UserID);
        qDebug("\tStatusMsg [%s]\n", pOrderAction->StatusMsg);
        qDebug("\tInstrumentID [%s]\n", pOrderAction->InstrumentID);
        qDebug("\tBranchID [%s]\n", pOrderAction->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pOrderAction->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pOrderAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pOrderAction->MacAddress);
        qDebug("\tOrderActionRef [%d]\n", pOrderAction->OrderActionRef);
        qDebug("\tRequestID [%d]\n", pOrderAction->RequestID);
        qDebug("\tFrontID [%d]\n", pOrderAction->FrontID);
        qDebug("\tSessionID [%d]\n", pOrderAction->SessionID);
        qDebug("\tVolumeChange [%d]\n", pOrderAction->VolumeChange);
        qDebug("\tInstallID [%d]\n", pOrderAction->InstallID);
        qDebug("\tActionFlag [%c]\n", pOrderAction->ActionFlag);
        qDebug("\tOrderActionStatus [%c]\n", pOrderAction->OrderActionStatus);
        qDebug("\tLimitPrice [%.8lf]\n", pOrderAction->LimitPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnOrderAction>\n");
};
void CTraderSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
    qDebug("<OnRtnInstrumentStatus>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnInstrumentStatus(pInstrumentStatus);
    }
    if (pInstrumentStatus)
    {
        qDebug("\tExchangeID [%s]\n", pInstrumentStatus->ExchangeID);
        qDebug("\tExchangeInstID [%s]\n", pInstrumentStatus->ExchangeInstID);
        qDebug("\tSettlementGroupID [%s]\n", pInstrumentStatus->SettlementGroupID);
        qDebug("\tInstrumentID [%s]\n", pInstrumentStatus->InstrumentID);
        qDebug("\tEnterTime [%s]\n", pInstrumentStatus->EnterTime);
        qDebug("\tTradingSegmentSN [%d]\n", pInstrumentStatus->TradingSegmentSN);
        qDebug("\tInstrumentStatus [%c]\n", pInstrumentStatus->InstrumentStatus);
        qDebug("\tEnterReason [%c]\n", pInstrumentStatus->EnterReason);
    }
    qDebug("</OnRtnInstrumentStatus>\n");
};
void CTraderSpi::OnRtnBulletin(CThostFtdcBulletinField *pBulletin)
{
    qDebug("<OnRtnBulletin>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnBulletin(pBulletin);
    }
    if (pBulletin)
    {
        qDebug("\tExchangeID [%s]\n", pBulletin->ExchangeID);
        qDebug("\tTradingDay [%s]\n", pBulletin->TradingDay);
        qDebug("\tNewsType [%s]\n", pBulletin->NewsType);
        qDebug("\tSendTime [%s]\n", pBulletin->SendTime);
        qDebug("\tAbstract [%s]\n", pBulletin->Abstract);
        qDebug("\tComeFrom [%s]\n", pBulletin->ComeFrom);
        qDebug("\tContent [%s]\n", pBulletin->Content);
        qDebug("\tURLLink [%s]\n", pBulletin->URLLink);
        qDebug("\tMarketID [%s]\n", pBulletin->MarketID);
        qDebug("\tBulletinID [%d]\n", pBulletin->BulletinID);
        qDebug("\tSequenceNo [%d]\n", pBulletin->SequenceNo);
        qDebug("\tNewsUrgency [%c]\n", pBulletin->NewsUrgency);
    }
    qDebug("</OnRtnBulletin>\n");
};
void CTraderSpi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{
    qDebug("<OnRtnTradingNotice>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnTradingNotice(pTradingNoticeInfo);
    }
    if (pTradingNoticeInfo)
    {
        qDebug("\tBrokerID [%s]\n", pTradingNoticeInfo->BrokerID);
        qDebug("\tInvestorID [%s]\n", pTradingNoticeInfo->InvestorID);
        qDebug("\tSendTime [%s]\n", pTradingNoticeInfo->SendTime);
        qDebug("\tFieldContent [%s]\n", pTradingNoticeInfo->FieldContent);
        qDebug("\tInvestUnitID [%s]\n", pTradingNoticeInfo->InvestUnitID);
        qDebug("\tSequenceNo [%d]\n", pTradingNoticeInfo->SequenceNo);
        qDebug("\tSequenceSeries [%d]\n", pTradingNoticeInfo->SequenceSeries);
    }
    qDebug("</OnRtnTradingNotice>\n");
};
void CTraderSpi::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder)
{
    qDebug("<OnRtnErrorConditionalOrder>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnErrorConditionalOrder(pErrorConditionalOrder);
    }
    if (pErrorConditionalOrder)
    {
        qDebug("\tBrokerID [%s]\n", pErrorConditionalOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pErrorConditionalOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pErrorConditionalOrder->InstrumentID);
        qDebug("\tOrderRef [%s]\n", pErrorConditionalOrder->OrderRef);
        qDebug("\tUserID [%s]\n", pErrorConditionalOrder->UserID);
        qDebug("\tCombOffsetFlag [%s]\n", pErrorConditionalOrder->CombOffsetFlag);
        qDebug("\tCombHedgeFlag [%s]\n", pErrorConditionalOrder->CombHedgeFlag);
        qDebug("\tGTDDate [%s]\n", pErrorConditionalOrder->GTDDate);
        qDebug("\tBusinessUnit [%s]\n", pErrorConditionalOrder->BusinessUnit);
        qDebug("\tOrderLocalID [%s]\n", pErrorConditionalOrder->OrderLocalID);
        qDebug("\tExchangeID [%s]\n", pErrorConditionalOrder->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pErrorConditionalOrder->ParticipantID);
        qDebug("\tClientID [%s]\n", pErrorConditionalOrder->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pErrorConditionalOrder->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pErrorConditionalOrder->TraderID);
        qDebug("\tTradingDay [%s]\n", pErrorConditionalOrder->TradingDay);
        qDebug("\tOrderSysID [%s]\n", pErrorConditionalOrder->OrderSysID);
        qDebug("\tInsertDate [%s]\n", pErrorConditionalOrder->InsertDate);
        qDebug("\tInsertTime [%s]\n", pErrorConditionalOrder->InsertTime);
        qDebug("\tActiveTime [%s]\n", pErrorConditionalOrder->ActiveTime);
        qDebug("\tSuspendTime [%s]\n", pErrorConditionalOrder->SuspendTime);
        qDebug("\tUpdateTime [%s]\n", pErrorConditionalOrder->UpdateTime);
        qDebug("\tCancelTime [%s]\n", pErrorConditionalOrder->CancelTime);
        qDebug("\tActiveTraderID [%s]\n", pErrorConditionalOrder->ActiveTraderID);
        qDebug("\tClearingPartID [%s]\n", pErrorConditionalOrder->ClearingPartID);
        qDebug("\tUserProductInfo [%s]\n", pErrorConditionalOrder->UserProductInfo);
        qDebug("\tStatusMsg [%s]\n", pErrorConditionalOrder->StatusMsg);
        qDebug("\tActiveUserID [%s]\n", pErrorConditionalOrder->ActiveUserID);
        qDebug("\tRelativeOrderSysID [%s]\n", pErrorConditionalOrder->RelativeOrderSysID);
        qDebug("\tErrorMsg [%s]\n", pErrorConditionalOrder->ErrorMsg);
        qDebug("\tBranchID [%s]\n", pErrorConditionalOrder->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pErrorConditionalOrder->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pErrorConditionalOrder->AccountID);
        qDebug("\tCurrencyID [%s]\n", pErrorConditionalOrder->CurrencyID);
        qDebug("\tIPAddress [%s]\n", pErrorConditionalOrder->IPAddress);
        qDebug("\tMacAddress [%s]\n", pErrorConditionalOrder->MacAddress);
        qDebug("\tVolumeTotalOriginal [%d]\n", pErrorConditionalOrder->VolumeTotalOriginal);
        qDebug("\tMinVolume [%d]\n", pErrorConditionalOrder->MinVolume);
        qDebug("\tIsAutoSuspend [%d]\n", pErrorConditionalOrder->IsAutoSuspend);
        qDebug("\tRequestID [%d]\n", pErrorConditionalOrder->RequestID);
        qDebug("\tInstallID [%d]\n", pErrorConditionalOrder->InstallID);
        qDebug("\tNotifySequence [%d]\n", pErrorConditionalOrder->NotifySequence);
        qDebug("\tSettlementID [%d]\n", pErrorConditionalOrder->SettlementID);
        qDebug("\tVolumeTraded [%d]\n", pErrorConditionalOrder->VolumeTraded);
        qDebug("\tVolumeTotal [%d]\n", pErrorConditionalOrder->VolumeTotal);
        qDebug("\tSequenceNo [%d]\n", pErrorConditionalOrder->SequenceNo);
        qDebug("\tFrontID [%d]\n", pErrorConditionalOrder->FrontID);
        qDebug("\tSessionID [%d]\n", pErrorConditionalOrder->SessionID);
        qDebug("\tUserForceClose [%d]\n", pErrorConditionalOrder->UserForceClose);
        qDebug("\tBrokerOrderSeq [%d]\n", pErrorConditionalOrder->BrokerOrderSeq);
        qDebug("\tZCETotalTradedVolume [%d]\n", pErrorConditionalOrder->ZCETotalTradedVolume);
        qDebug("\tErrorID [%d]\n", pErrorConditionalOrder->ErrorID);
        qDebug("\tIsSwapOrder [%d]\n", pErrorConditionalOrder->IsSwapOrder);
        qDebug("\tOrderPriceType [%c]\n", pErrorConditionalOrder->OrderPriceType);
        qDebug("\tDirection [%c]\n", pErrorConditionalOrder->Direction);
        qDebug("\tTimeCondition [%c]\n", pErrorConditionalOrder->TimeCondition);
        qDebug("\tVolumeCondition [%c]\n", pErrorConditionalOrder->VolumeCondition);
        qDebug("\tContingentCondition [%c]\n", pErrorConditionalOrder->ContingentCondition);
        qDebug("\tForceCloseReason [%c]\n", pErrorConditionalOrder->ForceCloseReason);
        qDebug("\tOrderSubmitStatus [%c]\n", pErrorConditionalOrder->OrderSubmitStatus);
        qDebug("\tOrderSource [%c]\n", pErrorConditionalOrder->OrderSource);
        qDebug("\tOrderStatus [%c]\n", pErrorConditionalOrder->OrderStatus);
        qDebug("\tOrderType [%c]\n", pErrorConditionalOrder->OrderType);
        qDebug("\tLimitPrice [%.8lf]\n", pErrorConditionalOrder->LimitPrice);
        qDebug("\tStopPrice [%.8lf]\n", pErrorConditionalOrder->StopPrice);
    }
    qDebug("</OnRtnErrorConditionalOrder>\n");
};
void CTraderSpi::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder)
{
    qDebug("<OnRtnExecOrder>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnExecOrder(pExecOrder);
    }
    if (pExecOrder)
    {
        qDebug("\tBrokerID [%s]\n", pExecOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pExecOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pExecOrder->InstrumentID);
        qDebug("\tExecOrderRef [%s]\n", pExecOrder->ExecOrderRef);
        qDebug("\tUserID [%s]\n", pExecOrder->UserID);
        qDebug("\tBusinessUnit [%s]\n", pExecOrder->BusinessUnit);
        qDebug("\tExecOrderLocalID [%s]\n", pExecOrder->ExecOrderLocalID);
        qDebug("\tExchangeID [%s]\n", pExecOrder->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pExecOrder->ParticipantID);
        qDebug("\tClientID [%s]\n", pExecOrder->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pExecOrder->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pExecOrder->TraderID);
        qDebug("\tTradingDay [%s]\n", pExecOrder->TradingDay);
        qDebug("\tExecOrderSysID [%s]\n", pExecOrder->ExecOrderSysID);
        qDebug("\tInsertDate [%s]\n", pExecOrder->InsertDate);
        qDebug("\tInsertTime [%s]\n", pExecOrder->InsertTime);
        qDebug("\tCancelTime [%s]\n", pExecOrder->CancelTime);
        qDebug("\tClearingPartID [%s]\n", pExecOrder->ClearingPartID);
        qDebug("\tUserProductInfo [%s]\n", pExecOrder->UserProductInfo);
        qDebug("\tStatusMsg [%s]\n", pExecOrder->StatusMsg);
        qDebug("\tActiveUserID [%s]\n", pExecOrder->ActiveUserID);
        qDebug("\tBranchID [%s]\n", pExecOrder->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pExecOrder->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pExecOrder->AccountID);
        qDebug("\tCurrencyID [%s]\n", pExecOrder->CurrencyID);
        qDebug("\tIPAddress [%s]\n", pExecOrder->IPAddress);
        qDebug("\tMacAddress [%s]\n", pExecOrder->MacAddress);
        qDebug("\tVolume [%d]\n", pExecOrder->Volume);
        qDebug("\tRequestID [%d]\n", pExecOrder->RequestID);
        qDebug("\tInstallID [%d]\n", pExecOrder->InstallID);
        qDebug("\tNotifySequence [%d]\n", pExecOrder->NotifySequence);
        qDebug("\tSettlementID [%d]\n", pExecOrder->SettlementID);
        qDebug("\tSequenceNo [%d]\n", pExecOrder->SequenceNo);
        qDebug("\tFrontID [%d]\n", pExecOrder->FrontID);
        qDebug("\tSessionID [%d]\n", pExecOrder->SessionID);
        qDebug("\tBrokerExecOrderSeq [%d]\n", pExecOrder->BrokerExecOrderSeq);
        qDebug("\tOffsetFlag [%c]\n", pExecOrder->OffsetFlag);
        qDebug("\tHedgeFlag [%c]\n", pExecOrder->HedgeFlag);
        qDebug("\tActionType [%c]\n", pExecOrder->ActionType);
        qDebug("\tPosiDirection [%c]\n", pExecOrder->PosiDirection);
        qDebug("\tReservePositionFlag [%c]\n", pExecOrder->ReservePositionFlag);
        qDebug("\tCloseFlag [%c]\n", pExecOrder->CloseFlag);
        qDebug("\tOrderSubmitStatus [%c]\n", pExecOrder->OrderSubmitStatus);
        qDebug("\tExecResult [%c]\n", pExecOrder->ExecResult);
    }
    qDebug("</OnRtnExecOrder>\n");
};
void CTraderSpi::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnExecOrderInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnExecOrderInsert(pInputExecOrder, pRspInfo);
    }
    if (pInputExecOrder)
    {
        qDebug("\tBrokerID [%s]\n", pInputExecOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputExecOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputExecOrder->InstrumentID);
        qDebug("\tExecOrderRef [%s]\n", pInputExecOrder->ExecOrderRef);
        qDebug("\tUserID [%s]\n", pInputExecOrder->UserID);
        qDebug("\tBusinessUnit [%s]\n", pInputExecOrder->BusinessUnit);
        qDebug("\tExchangeID [%s]\n", pInputExecOrder->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInputExecOrder->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pInputExecOrder->AccountID);
        qDebug("\tCurrencyID [%s]\n", pInputExecOrder->CurrencyID);
        qDebug("\tClientID [%s]\n", pInputExecOrder->ClientID);
        qDebug("\tIPAddress [%s]\n", pInputExecOrder->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputExecOrder->MacAddress);
        qDebug("\tVolume [%d]\n", pInputExecOrder->Volume);
        qDebug("\tRequestID [%d]\n", pInputExecOrder->RequestID);
        qDebug("\tOffsetFlag [%c]\n", pInputExecOrder->OffsetFlag);
        qDebug("\tHedgeFlag [%c]\n", pInputExecOrder->HedgeFlag);
        qDebug("\tActionType [%c]\n", pInputExecOrder->ActionType);
        qDebug("\tPosiDirection [%c]\n", pInputExecOrder->PosiDirection);
        qDebug("\tReservePositionFlag [%c]\n", pInputExecOrder->ReservePositionFlag);
        qDebug("\tCloseFlag [%c]\n", pInputExecOrder->CloseFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnExecOrderInsert>\n");
};
void CTraderSpi::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnExecOrderAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnExecOrderAction(pExecOrderAction, pRspInfo);
    }
    if (pExecOrderAction)
    {
        qDebug("\tBrokerID [%s]\n", pExecOrderAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pExecOrderAction->InvestorID);
        qDebug("\tExecOrderRef [%s]\n", pExecOrderAction->ExecOrderRef);
        qDebug("\tExchangeID [%s]\n", pExecOrderAction->ExchangeID);
        qDebug("\tExecOrderSysID [%s]\n", pExecOrderAction->ExecOrderSysID);
        qDebug("\tActionDate [%s]\n", pExecOrderAction->ActionDate);
        qDebug("\tActionTime [%s]\n", pExecOrderAction->ActionTime);
        qDebug("\tTraderID [%s]\n", pExecOrderAction->TraderID);
        qDebug("\tExecOrderLocalID [%s]\n", pExecOrderAction->ExecOrderLocalID);
        qDebug("\tActionLocalID [%s]\n", pExecOrderAction->ActionLocalID);
        qDebug("\tParticipantID [%s]\n", pExecOrderAction->ParticipantID);
        qDebug("\tClientID [%s]\n", pExecOrderAction->ClientID);
        qDebug("\tBusinessUnit [%s]\n", pExecOrderAction->BusinessUnit);
        qDebug("\tUserID [%s]\n", pExecOrderAction->UserID);
        qDebug("\tStatusMsg [%s]\n", pExecOrderAction->StatusMsg);
        qDebug("\tInstrumentID [%s]\n", pExecOrderAction->InstrumentID);
        qDebug("\tBranchID [%s]\n", pExecOrderAction->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pExecOrderAction->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pExecOrderAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pExecOrderAction->MacAddress);
        qDebug("\tExecOrderActionRef [%d]\n", pExecOrderAction->ExecOrderActionRef);
        qDebug("\tRequestID [%d]\n", pExecOrderAction->RequestID);
        qDebug("\tFrontID [%d]\n", pExecOrderAction->FrontID);
        qDebug("\tSessionID [%d]\n", pExecOrderAction->SessionID);
        qDebug("\tInstallID [%d]\n", pExecOrderAction->InstallID);
        qDebug("\tActionFlag [%c]\n", pExecOrderAction->ActionFlag);
        qDebug("\tOrderActionStatus [%c]\n", pExecOrderAction->OrderActionStatus);
        qDebug("\tActionType [%c]\n", pExecOrderAction->ActionType);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnExecOrderAction>\n");
};
void CTraderSpi::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnForQuoteInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnForQuoteInsert(pInputForQuote, pRspInfo );
    }
    if (pInputForQuote)
    {
        qDebug("\tBrokerID [%s]\n", pInputForQuote->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputForQuote->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputForQuote->InstrumentID);
        qDebug("\tForQuoteRef [%s]\n", pInputForQuote->ForQuoteRef);
        qDebug("\tUserID [%s]\n", pInputForQuote->UserID);
        qDebug("\tExchangeID [%s]\n", pInputForQuote->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInputForQuote->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pInputForQuote->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputForQuote->MacAddress);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnForQuoteInsert>\n");
};
void CTraderSpi::OnRtnQuote(CThostFtdcQuoteField *pQuote)
{
    qDebug("<OnRtnQuote>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnQuote(pQuote);
    }
    if (pQuote)
    {
        qDebug("\tBrokerID [%s]\n", pQuote->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQuote->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQuote->InstrumentID);
        qDebug("\tQuoteRef [%s]\n", pQuote->QuoteRef);
        qDebug("\tUserID [%s]\n", pQuote->UserID);
        qDebug("\tBusinessUnit [%s]\n", pQuote->BusinessUnit);
        qDebug("\tQuoteLocalID [%s]\n", pQuote->QuoteLocalID);
        qDebug("\tExchangeID [%s]\n", pQuote->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pQuote->ParticipantID);
        qDebug("\tClientID [%s]\n", pQuote->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pQuote->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pQuote->TraderID);
        qDebug("\tTradingDay [%s]\n", pQuote->TradingDay);
        qDebug("\tQuoteSysID [%s]\n", pQuote->QuoteSysID);
        qDebug("\tInsertDate [%s]\n", pQuote->InsertDate);
        qDebug("\tInsertTime [%s]\n", pQuote->InsertTime);
        qDebug("\tCancelTime [%s]\n", pQuote->CancelTime);
        qDebug("\tClearingPartID [%s]\n", pQuote->ClearingPartID);
        qDebug("\tAskOrderSysID [%s]\n", pQuote->AskOrderSysID);
        qDebug("\tBidOrderSysID [%s]\n", pQuote->BidOrderSysID);
        qDebug("\tUserProductInfo [%s]\n", pQuote->UserProductInfo);
        qDebug("\tStatusMsg [%s]\n", pQuote->StatusMsg);
        qDebug("\tActiveUserID [%s]\n", pQuote->ActiveUserID);
        qDebug("\tAskOrderRef [%s]\n", pQuote->AskOrderRef);
        qDebug("\tBidOrderRef [%s]\n", pQuote->BidOrderRef);
        qDebug("\tForQuoteSysID [%s]\n", pQuote->ForQuoteSysID);
        qDebug("\tBranchID [%s]\n", pQuote->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pQuote->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pQuote->AccountID);
        qDebug("\tCurrencyID [%s]\n", pQuote->CurrencyID);
        qDebug("\tIPAddress [%s]\n", pQuote->IPAddress);
        qDebug("\tMacAddress [%s]\n", pQuote->MacAddress);
        qDebug("\tAskVolume [%d]\n", pQuote->AskVolume);
        qDebug("\tBidVolume [%d]\n", pQuote->BidVolume);
        qDebug("\tRequestID [%d]\n", pQuote->RequestID);
        qDebug("\tInstallID [%d]\n", pQuote->InstallID);
        qDebug("\tNotifySequence [%d]\n", pQuote->NotifySequence);
        qDebug("\tSettlementID [%d]\n", pQuote->SettlementID);
        qDebug("\tSequenceNo [%d]\n", pQuote->SequenceNo);
        qDebug("\tFrontID [%d]\n", pQuote->FrontID);
        qDebug("\tSessionID [%d]\n", pQuote->SessionID);
        qDebug("\tBrokerQuoteSeq [%d]\n", pQuote->BrokerQuoteSeq);
        qDebug("\tAskOffsetFlag [%c]\n", pQuote->AskOffsetFlag);
        qDebug("\tBidOffsetFlag [%c]\n", pQuote->BidOffsetFlag);
        qDebug("\tAskHedgeFlag [%c]\n", pQuote->AskHedgeFlag);
        qDebug("\tBidHedgeFlag [%c]\n", pQuote->BidHedgeFlag);
        qDebug("\tOrderSubmitStatus [%c]\n", pQuote->OrderSubmitStatus);
        qDebug("\tQuoteStatus [%c]\n", pQuote->QuoteStatus);
        qDebug("\tAskPrice [%.8lf]\n", pQuote->AskPrice);
        qDebug("\tBidPrice [%.8lf]\n", pQuote->BidPrice);
    }
    qDebug("</OnRtnQuote>\n");
};
void CTraderSpi::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnQuoteInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnQuoteInsert(pInputQuote, pRspInfo );
    }
    if (pInputQuote)
    {
        qDebug("\tBrokerID [%s]\n", pInputQuote->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputQuote->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputQuote->InstrumentID);
        qDebug("\tQuoteRef [%s]\n", pInputQuote->QuoteRef);
        qDebug("\tUserID [%s]\n", pInputQuote->UserID);
        qDebug("\tBusinessUnit [%s]\n", pInputQuote->BusinessUnit);
        qDebug("\tAskOrderRef [%s]\n", pInputQuote->AskOrderRef);
        qDebug("\tBidOrderRef [%s]\n", pInputQuote->BidOrderRef);
        qDebug("\tForQuoteSysID [%s]\n", pInputQuote->ForQuoteSysID);
        qDebug("\tExchangeID [%s]\n", pInputQuote->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInputQuote->InvestUnitID);
        qDebug("\tClientID [%s]\n", pInputQuote->ClientID);
        qDebug("\tIPAddress [%s]\n", pInputQuote->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputQuote->MacAddress);
        qDebug("\tAskVolume [%d]\n", pInputQuote->AskVolume);
        qDebug("\tBidVolume [%d]\n", pInputQuote->BidVolume);
        qDebug("\tRequestID [%d]\n", pInputQuote->RequestID);
        qDebug("\tAskOffsetFlag [%c]\n", pInputQuote->AskOffsetFlag);
        qDebug("\tBidOffsetFlag [%c]\n", pInputQuote->BidOffsetFlag);
        qDebug("\tAskHedgeFlag [%c]\n", pInputQuote->AskHedgeFlag);
        qDebug("\tBidHedgeFlag [%c]\n", pInputQuote->BidHedgeFlag);
        qDebug("\tAskPrice [%.8lf]\n", pInputQuote->AskPrice);
        qDebug("\tBidPrice [%.8lf]\n", pInputQuote->BidPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnQuoteInsert>\n");
};
void CTraderSpi::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnQuoteAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnQuoteAction(pQuoteAction, pRspInfo );
    }
    if (pQuoteAction)
    {
        qDebug("\tBrokerID [%s]\n", pQuoteAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQuoteAction->InvestorID);
        qDebug("\tQuoteRef [%s]\n", pQuoteAction->QuoteRef);
        qDebug("\tExchangeID [%s]\n", pQuoteAction->ExchangeID);
        qDebug("\tQuoteSysID [%s]\n", pQuoteAction->QuoteSysID);
        qDebug("\tActionDate [%s]\n", pQuoteAction->ActionDate);
        qDebug("\tActionTime [%s]\n", pQuoteAction->ActionTime);
        qDebug("\tTraderID [%s]\n", pQuoteAction->TraderID);
        qDebug("\tQuoteLocalID [%s]\n", pQuoteAction->QuoteLocalID);
        qDebug("\tActionLocalID [%s]\n", pQuoteAction->ActionLocalID);
        qDebug("\tParticipantID [%s]\n", pQuoteAction->ParticipantID);
        qDebug("\tClientID [%s]\n", pQuoteAction->ClientID);
        qDebug("\tBusinessUnit [%s]\n", pQuoteAction->BusinessUnit);
        qDebug("\tUserID [%s]\n", pQuoteAction->UserID);
        qDebug("\tStatusMsg [%s]\n", pQuoteAction->StatusMsg);
        qDebug("\tInstrumentID [%s]\n", pQuoteAction->InstrumentID);
        qDebug("\tBranchID [%s]\n", pQuoteAction->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pQuoteAction->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pQuoteAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pQuoteAction->MacAddress);
        qDebug("\tQuoteActionRef [%d]\n", pQuoteAction->QuoteActionRef);
        qDebug("\tRequestID [%d]\n", pQuoteAction->RequestID);
        qDebug("\tFrontID [%d]\n", pQuoteAction->FrontID);
        qDebug("\tSessionID [%d]\n", pQuoteAction->SessionID);
        qDebug("\tInstallID [%d]\n", pQuoteAction->InstallID);
        qDebug("\tActionFlag [%c]\n", pQuoteAction->ActionFlag);
        qDebug("\tOrderActionStatus [%c]\n", pQuoteAction->OrderActionStatus);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnQuoteAction>\n");
};
void CTraderSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
    qDebug("<OnRtnForQuoteRsp>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnForQuoteRsp(pForQuoteRsp);
    }
    if (pForQuoteRsp)
    {
        qDebug("\tTradingDay [%s]\n", pForQuoteRsp->TradingDay);
        qDebug("\tInstrumentID [%s]\n", pForQuoteRsp->InstrumentID);
        qDebug("\tForQuoteSysID [%s]\n", pForQuoteRsp->ForQuoteSysID);
        qDebug("\tForQuoteTime [%s]\n", pForQuoteRsp->ForQuoteTime);
        qDebug("\tActionDay [%s]\n", pForQuoteRsp->ActionDay);
        qDebug("\tExchangeID [%s]\n", pForQuoteRsp->ExchangeID);
    }
    qDebug("</OnRtnForQuoteRsp>\n");
};
void CTraderSpi::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken)
{
    qDebug("<OnRtnCFMMCTradingAccountToken>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnCFMMCTradingAccountToken(pCFMMCTradingAccountToken);
    }
    if (pCFMMCTradingAccountToken)
    {
        qDebug("\tBrokerID [%s]\n", pCFMMCTradingAccountToken->BrokerID);
        qDebug("\tParticipantID [%s]\n", pCFMMCTradingAccountToken->ParticipantID);
        qDebug("\tAccountID [%s]\n", pCFMMCTradingAccountToken->AccountID);
        qDebug("\tToken [%s]\n", pCFMMCTradingAccountToken->Token);
        qDebug("\tKeyID [%d]\n", pCFMMCTradingAccountToken->KeyID);
    }
    qDebug("</OnRtnCFMMCTradingAccountToken>\n");
};
void CTraderSpi::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnBatchOrderAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnBatchOrderAction(pBatchOrderAction, pRspInfo );
    }
    if (pBatchOrderAction)
    {
        qDebug("\tBrokerID [%s]\n", pBatchOrderAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pBatchOrderAction->InvestorID);
        qDebug("\tExchangeID [%s]\n", pBatchOrderAction->ExchangeID);
        qDebug("\tActionDate [%s]\n", pBatchOrderAction->ActionDate);
        qDebug("\tActionTime [%s]\n", pBatchOrderAction->ActionTime);
        qDebug("\tTraderID [%s]\n", pBatchOrderAction->TraderID);
        qDebug("\tActionLocalID [%s]\n", pBatchOrderAction->ActionLocalID);
        qDebug("\tParticipantID [%s]\n", pBatchOrderAction->ParticipantID);
        qDebug("\tClientID [%s]\n", pBatchOrderAction->ClientID);
        qDebug("\tBusinessUnit [%s]\n", pBatchOrderAction->BusinessUnit);
        qDebug("\tUserID [%s]\n", pBatchOrderAction->UserID);
        qDebug("\tStatusMsg [%s]\n", pBatchOrderAction->StatusMsg);
        qDebug("\tInvestUnitID [%s]\n", pBatchOrderAction->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pBatchOrderAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pBatchOrderAction->MacAddress);
        qDebug("\tOrderActionRef [%d]\n", pBatchOrderAction->OrderActionRef);
        qDebug("\tRequestID [%d]\n", pBatchOrderAction->RequestID);
        qDebug("\tFrontID [%d]\n", pBatchOrderAction->FrontID);
        qDebug("\tSessionID [%d]\n", pBatchOrderAction->SessionID);
        qDebug("\tInstallID [%d]\n", pBatchOrderAction->InstallID);
        qDebug("\tOrderActionStatus [%c]\n", pBatchOrderAction->OrderActionStatus);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnBatchOrderAction>\n");
};
void CTraderSpi::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose)
{
    qDebug("<OnRtnOptionSelfClose>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnOptionSelfClose(pOptionSelfClose);
    }
    if (pOptionSelfClose)
    {
        qDebug("\tBrokerID [%s]\n", pOptionSelfClose->BrokerID);
        qDebug("\tInvestorID [%s]\n", pOptionSelfClose->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pOptionSelfClose->InstrumentID);
        qDebug("\tOptionSelfCloseRef [%s]\n", pOptionSelfClose->OptionSelfCloseRef);
        qDebug("\tUserID [%s]\n", pOptionSelfClose->UserID);
        qDebug("\tBusinessUnit [%s]\n", pOptionSelfClose->BusinessUnit);
        qDebug("\tOptionSelfCloseLocalID [%s]\n", pOptionSelfClose->OptionSelfCloseLocalID);
        qDebug("\tExchangeID [%s]\n", pOptionSelfClose->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pOptionSelfClose->ParticipantID);
        qDebug("\tClientID [%s]\n", pOptionSelfClose->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pOptionSelfClose->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pOptionSelfClose->TraderID);
        qDebug("\tTradingDay [%s]\n", pOptionSelfClose->TradingDay);
        qDebug("\tOptionSelfCloseSysID [%s]\n", pOptionSelfClose->OptionSelfCloseSysID);
        qDebug("\tInsertDate [%s]\n", pOptionSelfClose->InsertDate);
        qDebug("\tInsertTime [%s]\n", pOptionSelfClose->InsertTime);
        qDebug("\tCancelTime [%s]\n", pOptionSelfClose->CancelTime);
        qDebug("\tClearingPartID [%s]\n", pOptionSelfClose->ClearingPartID);
        qDebug("\tUserProductInfo [%s]\n", pOptionSelfClose->UserProductInfo);
        qDebug("\tStatusMsg [%s]\n", pOptionSelfClose->StatusMsg);
        qDebug("\tActiveUserID [%s]\n", pOptionSelfClose->ActiveUserID);
        qDebug("\tBranchID [%s]\n", pOptionSelfClose->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pOptionSelfClose->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pOptionSelfClose->AccountID);
        qDebug("\tCurrencyID [%s]\n", pOptionSelfClose->CurrencyID);
        qDebug("\tIPAddress [%s]\n", pOptionSelfClose->IPAddress);
        qDebug("\tMacAddress [%s]\n", pOptionSelfClose->MacAddress);
        qDebug("\tVolume [%d]\n", pOptionSelfClose->Volume);
        qDebug("\tRequestID [%d]\n", pOptionSelfClose->RequestID);
        qDebug("\tInstallID [%d]\n", pOptionSelfClose->InstallID);
        qDebug("\tNotifySequence [%d]\n", pOptionSelfClose->NotifySequence);
        qDebug("\tSettlementID [%d]\n", pOptionSelfClose->SettlementID);
        qDebug("\tSequenceNo [%d]\n", pOptionSelfClose->SequenceNo);
        qDebug("\tFrontID [%d]\n", pOptionSelfClose->FrontID);
        qDebug("\tSessionID [%d]\n", pOptionSelfClose->SessionID);
        qDebug("\tBrokerOptionSelfCloseSeq [%d]\n", pOptionSelfClose->BrokerOptionSelfCloseSeq);
        qDebug("\tHedgeFlag [%c]\n", pOptionSelfClose->HedgeFlag);
        qDebug("\tOptSelfCloseFlag [%c]\n", pOptionSelfClose->OptSelfCloseFlag);
        qDebug("\tOrderSubmitStatus [%c]\n", pOptionSelfClose->OrderSubmitStatus);
        qDebug("\tExecResult [%c]\n", pOptionSelfClose->ExecResult);
    }
    qDebug("</OnRtnOptionSelfClose>\n");
};
void CTraderSpi::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnOptionSelfCloseInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnOptionSelfCloseInsert(pInputOptionSelfClose, pRspInfo);
    }
    if (pInputOptionSelfClose)
    {
        qDebug("\tBrokerID [%s]\n", pInputOptionSelfClose->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputOptionSelfClose->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputOptionSelfClose->InstrumentID);
        qDebug("\tOptionSelfCloseRef [%s]\n", pInputOptionSelfClose->OptionSelfCloseRef);
        qDebug("\tUserID [%s]\n", pInputOptionSelfClose->UserID);
        qDebug("\tBusinessUnit [%s]\n", pInputOptionSelfClose->BusinessUnit);
        qDebug("\tExchangeID [%s]\n", pInputOptionSelfClose->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pInputOptionSelfClose->InvestUnitID);
        qDebug("\tAccountID [%s]\n", pInputOptionSelfClose->AccountID);
        qDebug("\tCurrencyID [%s]\n", pInputOptionSelfClose->CurrencyID);
        qDebug("\tClientID [%s]\n", pInputOptionSelfClose->ClientID);
        qDebug("\tIPAddress [%s]\n", pInputOptionSelfClose->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputOptionSelfClose->MacAddress);
        qDebug("\tVolume [%d]\n", pInputOptionSelfClose->Volume);
        qDebug("\tRequestID [%d]\n", pInputOptionSelfClose->RequestID);
        qDebug("\tHedgeFlag [%c]\n", pInputOptionSelfClose->HedgeFlag);
        qDebug("\tOptSelfCloseFlag [%c]\n", pInputOptionSelfClose->OptSelfCloseFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnOptionSelfCloseInsert>\n");
};
void CTraderSpi::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnOptionSelfCloseAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnOptionSelfCloseAction(pOptionSelfCloseAction, pRspInfo);
    }
    if (pOptionSelfCloseAction)
    {
        qDebug("\tBrokerID [%s]\n", pOptionSelfCloseAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pOptionSelfCloseAction->InvestorID);
        qDebug("\tOptionSelfCloseRef [%s]\n", pOptionSelfCloseAction->OptionSelfCloseRef);
        qDebug("\tExchangeID [%s]\n", pOptionSelfCloseAction->ExchangeID);
        qDebug("\tOptionSelfCloseSysID [%s]\n", pOptionSelfCloseAction->OptionSelfCloseSysID);
        qDebug("\tActionDate [%s]\n", pOptionSelfCloseAction->ActionDate);
        qDebug("\tActionTime [%s]\n", pOptionSelfCloseAction->ActionTime);
        qDebug("\tTraderID [%s]\n", pOptionSelfCloseAction->TraderID);
        qDebug("\tOptionSelfCloseLocalID [%s]\n", pOptionSelfCloseAction->OptionSelfCloseLocalID);
        qDebug("\tActionLocalID [%s]\n", pOptionSelfCloseAction->ActionLocalID);
        qDebug("\tParticipantID [%s]\n", pOptionSelfCloseAction->ParticipantID);
        qDebug("\tClientID [%s]\n", pOptionSelfCloseAction->ClientID);
        qDebug("\tBusinessUnit [%s]\n", pOptionSelfCloseAction->BusinessUnit);
        qDebug("\tUserID [%s]\n", pOptionSelfCloseAction->UserID);
        qDebug("\tStatusMsg [%s]\n", pOptionSelfCloseAction->StatusMsg);
        qDebug("\tInstrumentID [%s]\n", pOptionSelfCloseAction->InstrumentID);
        qDebug("\tBranchID [%s]\n", pOptionSelfCloseAction->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pOptionSelfCloseAction->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pOptionSelfCloseAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pOptionSelfCloseAction->MacAddress);
        qDebug("\tOptionSelfCloseActionRef [%d]\n", pOptionSelfCloseAction->OptionSelfCloseActionRef);
        qDebug("\tRequestID [%d]\n", pOptionSelfCloseAction->RequestID);
        qDebug("\tFrontID [%d]\n", pOptionSelfCloseAction->FrontID);
        qDebug("\tSessionID [%d]\n", pOptionSelfCloseAction->SessionID);
        qDebug("\tInstallID [%d]\n", pOptionSelfCloseAction->InstallID);
        qDebug("\tActionFlag [%c]\n", pOptionSelfCloseAction->ActionFlag);
        qDebug("\tOrderActionStatus [%c]\n", pOptionSelfCloseAction->OrderActionStatus);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnOptionSelfCloseAction>\n");
};
void CTraderSpi::OnRtnCombAction(CThostFtdcCombActionField *pCombAction)
{
    qDebug("<OnRtnCombAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnCombAction(pCombAction);
    }
    if (pCombAction)
    {
        qDebug("\tBrokerID [%s]\n", pCombAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pCombAction->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pCombAction->InstrumentID);
        qDebug("\tCombActionRef [%s]\n", pCombAction->CombActionRef);
        qDebug("\tUserID [%s]\n", pCombAction->UserID);
        qDebug("\tActionLocalID [%s]\n", pCombAction->ActionLocalID);
        qDebug("\tExchangeID [%s]\n", pCombAction->ExchangeID);
        qDebug("\tParticipantID [%s]\n", pCombAction->ParticipantID);
        qDebug("\tClientID [%s]\n", pCombAction->ClientID);
        qDebug("\tExchangeInstID [%s]\n", pCombAction->ExchangeInstID);
        qDebug("\tTraderID [%s]\n", pCombAction->TraderID);
        qDebug("\tTradingDay [%s]\n", pCombAction->TradingDay);
        qDebug("\tUserProductInfo [%s]\n", pCombAction->UserProductInfo);
        qDebug("\tStatusMsg [%s]\n", pCombAction->StatusMsg);
        qDebug("\tIPAddress [%s]\n", pCombAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pCombAction->MacAddress);
        qDebug("\tComTradeID [%s]\n", pCombAction->ComTradeID);
        qDebug("\tBranchID [%s]\n", pCombAction->BranchID);
        qDebug("\tInvestUnitID [%s]\n", pCombAction->InvestUnitID);
        qDebug("\tVolume [%d]\n", pCombAction->Volume);
        qDebug("\tInstallID [%d]\n", pCombAction->InstallID);
        qDebug("\tNotifySequence [%d]\n", pCombAction->NotifySequence);
        qDebug("\tSettlementID [%d]\n", pCombAction->SettlementID);
        qDebug("\tSequenceNo [%d]\n", pCombAction->SequenceNo);
        qDebug("\tFrontID [%d]\n", pCombAction->FrontID);
        qDebug("\tSessionID [%d]\n", pCombAction->SessionID);
        qDebug("\tDirection [%c]\n", pCombAction->Direction);
        qDebug("\tCombDirection [%c]\n", pCombAction->CombDirection);
        qDebug("\tHedgeFlag [%c]\n", pCombAction->HedgeFlag);
        qDebug("\tActionStatus [%c]\n", pCombAction->ActionStatus);
    }
    qDebug("</OnRtnCombAction>\n");
};
void CTraderSpi::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnCombActionInsert>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnCombActionInsert(pInputCombAction, pRspInfo);
    }
    if (pInputCombAction)
    {
        qDebug("\tBrokerID [%s]\n", pInputCombAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pInputCombAction->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pInputCombAction->InstrumentID);
        qDebug("\tCombActionRef [%s]\n", pInputCombAction->CombActionRef);
        qDebug("\tUserID [%s]\n", pInputCombAction->UserID);
        qDebug("\tExchangeID [%s]\n", pInputCombAction->ExchangeID);
        qDebug("\tIPAddress [%s]\n", pInputCombAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pInputCombAction->MacAddress);
        qDebug("\tInvestUnitID [%s]\n", pInputCombAction->InvestUnitID);
        qDebug("\tVolume [%d]\n", pInputCombAction->Volume);
        qDebug("\tDirection [%c]\n", pInputCombAction->Direction);
        qDebug("\tCombDirection [%c]\n", pInputCombAction->CombDirection);
        qDebug("\tHedgeFlag [%c]\n", pInputCombAction->HedgeFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnCombActionInsert>\n");
};
void CTraderSpi::OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryContractBank>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryContractBank(pContractBank, pRspInfo,nRequestID,bIsLast);
    }
    if (pContractBank)
    {
        qDebug("\tBrokerID [%s]\n", pContractBank->BrokerID);
        qDebug("\tBankID [%s]\n", pContractBank->BankID);
        qDebug("\tBankBrchID [%s]\n", pContractBank->BankBrchID);
        qDebug("\tBankName [%s]\n", pContractBank->BankName);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryContractBank>\n");
};

void CTraderSpi::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryParkedOrder>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryParkedOrder(pParkedOrder, pRspInfo,nRequestID,bIsLast);
    }
    if (pParkedOrder)
    {
        qDebug("\tBrokerID [%s]\n", pParkedOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pParkedOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pParkedOrder->InstrumentID);
        qDebug("\tOrderRef [%s]\n", pParkedOrder->OrderRef);
        qDebug("\tUserID [%s]\n", pParkedOrder->UserID);
        qDebug("\tCombOffsetFlag [%s]\n", pParkedOrder->CombOffsetFlag);
        qDebug("\tCombHedgeFlag [%s]\n", pParkedOrder->CombHedgeFlag);
        qDebug("\tGTDDate [%s]\n", pParkedOrder->GTDDate);
        qDebug("\tBusinessUnit [%s]\n", pParkedOrder->BusinessUnit);
        qDebug("\tExchangeID [%s]\n", pParkedOrder->ExchangeID);
        qDebug("\tParkedOrderID [%s]\n", pParkedOrder->ParkedOrderID);
        qDebug("\tErrorMsg [%s]\n", pParkedOrder->ErrorMsg);
        qDebug("\tAccountID [%s]\n", pParkedOrder->AccountID);
        qDebug("\tCurrencyID [%s]\n", pParkedOrder->CurrencyID);
        qDebug("\tClientID [%s]\n", pParkedOrder->ClientID);
        qDebug("\tInvestUnitID [%s]\n", pParkedOrder->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pParkedOrder->IPAddress);
        qDebug("\tMacAddress [%s]\n", pParkedOrder->MacAddress);
        qDebug("\tVolumeTotalOriginal [%d]\n", pParkedOrder->VolumeTotalOriginal);
        qDebug("\tMinVolume [%d]\n", pParkedOrder->MinVolume);
        qDebug("\tIsAutoSuspend [%d]\n", pParkedOrder->IsAutoSuspend);
        qDebug("\tRequestID [%d]\n", pParkedOrder->RequestID);
        qDebug("\tUserForceClose [%d]\n", pParkedOrder->UserForceClose);
        qDebug("\tErrorID [%d]\n", pParkedOrder->ErrorID);
        qDebug("\tIsSwapOrder [%d]\n", pParkedOrder->IsSwapOrder);
        qDebug("\tOrderPriceType [%c]\n", pParkedOrder->OrderPriceType);
        qDebug("\tDirection [%c]\n", pParkedOrder->Direction);
        qDebug("\tTimeCondition [%c]\n", pParkedOrder->TimeCondition);
        qDebug("\tVolumeCondition [%c]\n", pParkedOrder->VolumeCondition);
        qDebug("\tContingentCondition [%c]\n", pParkedOrder->ContingentCondition);
        qDebug("\tForceCloseReason [%c]\n", pParkedOrder->ForceCloseReason);
        qDebug("\tUserType [%c]\n", pParkedOrder->UserType);
        qDebug("\tStatus [%c]\n", pParkedOrder->Status);
        qDebug("\tLimitPrice [%.8lf]\n", pParkedOrder->LimitPrice);
        qDebug("\tStopPrice [%.8lf]\n", pParkedOrder->StopPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryParkedOrder>\n");
};

void CTraderSpi::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryParkedOrderAction>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryParkedOrderAction(pParkedOrderAction, pRspInfo,nRequestID,bIsLast);
    }
    if (pParkedOrderAction)
    {
        qDebug("\tBrokerID [%s]\n", pParkedOrderAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pParkedOrderAction->InvestorID);
        qDebug("\tOrderRef [%s]\n", pParkedOrderAction->OrderRef);
        qDebug("\tExchangeID [%s]\n", pParkedOrderAction->ExchangeID);
        qDebug("\tOrderSysID [%s]\n", pParkedOrderAction->OrderSysID);
        qDebug("\tUserID [%s]\n", pParkedOrderAction->UserID);
        qDebug("\tInstrumentID [%s]\n", pParkedOrderAction->InstrumentID);
        qDebug("\tParkedOrderActionID [%s]\n", pParkedOrderAction->ParkedOrderActionID);
        qDebug("\tErrorMsg [%s]\n", pParkedOrderAction->ErrorMsg);
        qDebug("\tInvestUnitID [%s]\n", pParkedOrderAction->InvestUnitID);
        qDebug("\tIPAddress [%s]\n", pParkedOrderAction->IPAddress);
        qDebug("\tMacAddress [%s]\n", pParkedOrderAction->MacAddress);
        qDebug("\tOrderActionRef [%d]\n", pParkedOrderAction->OrderActionRef);
        qDebug("\tRequestID [%d]\n", pParkedOrderAction->RequestID);
        qDebug("\tFrontID [%d]\n", pParkedOrderAction->FrontID);
        qDebug("\tSessionID [%d]\n", pParkedOrderAction->SessionID);
        qDebug("\tVolumeChange [%d]\n", pParkedOrderAction->VolumeChange);
        qDebug("\tErrorID [%d]\n", pParkedOrderAction->ErrorID);
        qDebug("\tActionFlag [%c]\n", pParkedOrderAction->ActionFlag);
        qDebug("\tUserType [%c]\n", pParkedOrderAction->UserType);
        qDebug("\tStatus [%c]\n", pParkedOrderAction->Status);
        qDebug("\tLimitPrice [%.8lf]\n", pParkedOrderAction->LimitPrice);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryParkedOrderAction>\n");
};

void CTraderSpi::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryTradingNotice>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryTradingNotice(pTradingNotice, pRspInfo,nRequestID,bIsLast);
    }
    if (pTradingNotice)
    {
        qDebug("\tBrokerID [%s]\n", pTradingNotice->BrokerID);
        qDebug("\tInvestorID [%s]\n", pTradingNotice->InvestorID);
        qDebug("\tUserID [%s]\n", pTradingNotice->UserID);
        qDebug("\tSendTime [%s]\n", pTradingNotice->SendTime);
        qDebug("\tFieldContent [%s]\n", pTradingNotice->FieldContent);
        qDebug("\tInvestUnitID [%s]\n", pTradingNotice->InvestUnitID);
        qDebug("\tSequenceNo [%d]\n", pTradingNotice->SequenceNo);
        qDebug("\tInvestorRange [%c]\n", pTradingNotice->InvestorRange);
        qDebug("\tSequenceSeries [%d]\n", pTradingNotice->SequenceSeries);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryTradingNotice>\n");
};

void CTraderSpi::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryBrokerTradingParams>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryBrokerTradingParams(pBrokerTradingParams, pRspInfo,nRequestID,bIsLast);
    }
    if (pBrokerTradingParams)
    {
        qDebug("\tBrokerID [%s]\n", pBrokerTradingParams->BrokerID);
        qDebug("\tInvestorID [%s]\n", pBrokerTradingParams->InvestorID);
        qDebug("\tCurrencyID [%s]\n", pBrokerTradingParams->CurrencyID);
        qDebug("\tAccountID [%s]\n", pBrokerTradingParams->AccountID);
        qDebug("\tMarginPriceType [%c]\n", pBrokerTradingParams->MarginPriceType);
        qDebug("\tAlgorithm [%c]\n", pBrokerTradingParams->Algorithm);
        qDebug("\tAvailIncludeCloseProfit [%c]\n", pBrokerTradingParams->AvailIncludeCloseProfit);
        qDebug("\tOptionRoyaltyPriceType [%c]\n", pBrokerTradingParams->OptionRoyaltyPriceType);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryBrokerTradingParams>\n");
};

void CTraderSpi::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQryBrokerTradingAlgos>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQryBrokerTradingAlgos(pBrokerTradingAlgos, pRspInfo,nRequestID,bIsLast);
    }
    if (pBrokerTradingAlgos)
    {
        qDebug("\tBrokerID [%s]\n", pBrokerTradingAlgos->BrokerID);
        qDebug("\tExchangeID [%s]\n", pBrokerTradingAlgos->ExchangeID);
        qDebug("\tInstrumentID [%s]\n", pBrokerTradingAlgos->InstrumentID);
        qDebug("\tHandlePositionAlgoID [%c]\n", pBrokerTradingAlgos->HandlePositionAlgoID);
        qDebug("\tFindMarginRateAlgoID [%c]\n", pBrokerTradingAlgos->FindMarginRateAlgoID);
        qDebug("\tHandleTradingAccountAlgoID [%c]\n", pBrokerTradingAlgos->HandleTradingAccountAlgoID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQryBrokerTradingAlgos>\n");
};

void CTraderSpi::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQueryCFMMCTradingAccountToken>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken, pRspInfo,nRequestID,bIsLast);
    }
    if (pQueryCFMMCTradingAccountToken)
    {
        qDebug("\tBrokerID [%s]\n", pQueryCFMMCTradingAccountToken->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQueryCFMMCTradingAccountToken->InvestorID);
        qDebug("\tInvestUnitID [%s]\n", pQueryCFMMCTradingAccountToken->InvestUnitID);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQueryCFMMCTradingAccountToken>\n");
};

void CTraderSpi::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer)
{
    qDebug("<OnRtnFromBankToFutureByBank>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnFromBankToFutureByBank(pRspTransfer);
    }
    if (pRspTransfer)
    {
        qDebug("\tTradeCode [%s]\n", pRspTransfer->TradeCode);
        qDebug("\tBankID [%s]\n", pRspTransfer->BankID);
        qDebug("\tBankBranchID [%s]\n", pRspTransfer->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pRspTransfer->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pRspTransfer->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pRspTransfer->TradeDate);
        qDebug("\tTradeTime [%s]\n", pRspTransfer->TradeTime);
        qDebug("\tBankSerial [%s]\n", pRspTransfer->BankSerial);
        qDebug("\tTradingDay [%s]\n", pRspTransfer->TradingDay);
        qDebug("\tCustomerName [%s]\n", pRspTransfer->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pRspTransfer->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pRspTransfer->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pRspTransfer->BankPassWord);
        qDebug("\tAccountID [%s]\n", pRspTransfer->AccountID);
        qDebug("\tPassword [%s]\n", pRspTransfer->Password);
        qDebug("\tUserID [%s]\n", pRspTransfer->UserID);
        qDebug("\tCurrencyID [%s]\n", pRspTransfer->CurrencyID);
        qDebug("\tMessage [%s]\n", pRspTransfer->Message);
        qDebug("\tDigest [%s]\n", pRspTransfer->Digest);
        qDebug("\tDeviceID [%s]\n", pRspTransfer->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pRspTransfer->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pRspTransfer->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pRspTransfer->OperNo);
        qDebug("\tErrorMsg [%s]\n", pRspTransfer->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pRspTransfer->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pRspTransfer->PlateSerial);
        qDebug("\tSessionID [%d]\n", pRspTransfer->SessionID);
        qDebug("\tInstallID [%d]\n", pRspTransfer->InstallID);
        qDebug("\tFutureSerial [%d]\n", pRspTransfer->FutureSerial);
        qDebug("\tRequestID [%d]\n", pRspTransfer->RequestID);
        qDebug("\tTID [%d]\n", pRspTransfer->TID);
        qDebug("\tErrorID [%d]\n", pRspTransfer->ErrorID);
        qDebug("\tLastFragment [%c]\n", pRspTransfer->LastFragment);
        qDebug("\tIdCardType [%c]\n", pRspTransfer->IdCardType);
        qDebug("\tCustType [%c]\n", pRspTransfer->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pRspTransfer->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pRspTransfer->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pRspTransfer->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pRspTransfer->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pRspTransfer->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pRspTransfer->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pRspTransfer->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pRspTransfer->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pRspTransfer->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pRspTransfer->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pRspTransfer->BrokerFee);
    }
    qDebug("</OnRtnFromBankToFutureByBank>\n");
};
void CTraderSpi::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer)
{
    qDebug("<OnRtnFromFutureToBankByBank>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnFromFutureToBankByBank(pRspTransfer);
    }
    if (pRspTransfer)
    {
        qDebug("\tTradeCode [%s]\n", pRspTransfer->TradeCode);
        qDebug("\tBankID [%s]\n", pRspTransfer->BankID);
        qDebug("\tBankBranchID [%s]\n", pRspTransfer->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pRspTransfer->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pRspTransfer->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pRspTransfer->TradeDate);
        qDebug("\tTradeTime [%s]\n", pRspTransfer->TradeTime);
        qDebug("\tBankSerial [%s]\n", pRspTransfer->BankSerial);
        qDebug("\tTradingDay [%s]\n", pRspTransfer->TradingDay);
        qDebug("\tCustomerName [%s]\n", pRspTransfer->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pRspTransfer->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pRspTransfer->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pRspTransfer->BankPassWord);
        qDebug("\tAccountID [%s]\n", pRspTransfer->AccountID);
        qDebug("\tPassword [%s]\n", pRspTransfer->Password);
        qDebug("\tUserID [%s]\n", pRspTransfer->UserID);
        qDebug("\tCurrencyID [%s]\n", pRspTransfer->CurrencyID);
        qDebug("\tMessage [%s]\n", pRspTransfer->Message);
        qDebug("\tDigest [%s]\n", pRspTransfer->Digest);
        qDebug("\tDeviceID [%s]\n", pRspTransfer->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pRspTransfer->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pRspTransfer->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pRspTransfer->OperNo);
        qDebug("\tErrorMsg [%s]\n", pRspTransfer->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pRspTransfer->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pRspTransfer->PlateSerial);
        qDebug("\tSessionID [%d]\n", pRspTransfer->SessionID);
        qDebug("\tInstallID [%d]\n", pRspTransfer->InstallID);
        qDebug("\tFutureSerial [%d]\n", pRspTransfer->FutureSerial);
        qDebug("\tRequestID [%d]\n", pRspTransfer->RequestID);
        qDebug("\tTID [%d]\n", pRspTransfer->TID);
        qDebug("\tErrorID [%d]\n", pRspTransfer->ErrorID);
        qDebug("\tLastFragment [%c]\n", pRspTransfer->LastFragment);
        qDebug("\tIdCardType [%c]\n", pRspTransfer->IdCardType);
        qDebug("\tCustType [%c]\n", pRspTransfer->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pRspTransfer->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pRspTransfer->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pRspTransfer->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pRspTransfer->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pRspTransfer->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pRspTransfer->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pRspTransfer->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pRspTransfer->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pRspTransfer->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pRspTransfer->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pRspTransfer->BrokerFee);
    }
    qDebug("</OnRtnFromFutureToBankByBank>\n");
};
void CTraderSpi::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal)
{
    qDebug("<OnRtnRepealFromBankToFutureByBank>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnRepealFromBankToFutureByBank(pRspRepeal);
    }
    if (pRspRepeal)
    {
        qDebug("\tBankRepealSerial [%s]\n", pRspRepeal->BankRepealSerial);
        qDebug("\tTradeCode [%s]\n", pRspRepeal->TradeCode);
        qDebug("\tBankID [%s]\n", pRspRepeal->BankID);
        qDebug("\tBankBranchID [%s]\n", pRspRepeal->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pRspRepeal->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pRspRepeal->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pRspRepeal->TradeDate);
        qDebug("\tTradeTime [%s]\n", pRspRepeal->TradeTime);
        qDebug("\tBankSerial [%s]\n", pRspRepeal->BankSerial);
        qDebug("\tTradingDay [%s]\n", pRspRepeal->TradingDay);
        qDebug("\tCustomerName [%s]\n", pRspRepeal->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pRspRepeal->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pRspRepeal->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pRspRepeal->BankPassWord);
        qDebug("\tAccountID [%s]\n", pRspRepeal->AccountID);
        qDebug("\tPassword [%s]\n", pRspRepeal->Password);
        qDebug("\tUserID [%s]\n", pRspRepeal->UserID);
        qDebug("\tCurrencyID [%s]\n", pRspRepeal->CurrencyID);
        qDebug("\tMessage [%s]\n", pRspRepeal->Message);
        qDebug("\tDigest [%s]\n", pRspRepeal->Digest);
        qDebug("\tDeviceID [%s]\n", pRspRepeal->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pRspRepeal->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pRspRepeal->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pRspRepeal->OperNo);
        qDebug("\tErrorMsg [%s]\n", pRspRepeal->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pRspRepeal->LongCustomerName);
        qDebug("\tRepealTimeInterval [%d]\n", pRspRepeal->RepealTimeInterval);
        qDebug("\tRepealedTimes [%d]\n", pRspRepeal->RepealedTimes);
        qDebug("\tPlateRepealSerial [%d]\n", pRspRepeal->PlateRepealSerial);
        qDebug("\tFutureRepealSerial [%d]\n", pRspRepeal->FutureRepealSerial);
        qDebug("\tPlateSerial [%d]\n", pRspRepeal->PlateSerial);
        qDebug("\tSessionID [%d]\n", pRspRepeal->SessionID);
        qDebug("\tInstallID [%d]\n", pRspRepeal->InstallID);
        qDebug("\tFutureSerial [%d]\n", pRspRepeal->FutureSerial);
        qDebug("\tRequestID [%d]\n", pRspRepeal->RequestID);
        qDebug("\tTID [%d]\n", pRspRepeal->TID);
        qDebug("\tErrorID [%d]\n", pRspRepeal->ErrorID);
        qDebug("\tBankRepealFlag [%c]\n", pRspRepeal->BankRepealFlag);
        qDebug("\tBrokerRepealFlag [%c]\n", pRspRepeal->BrokerRepealFlag);
        qDebug("\tLastFragment [%c]\n", pRspRepeal->LastFragment);
        qDebug("\tIdCardType [%c]\n", pRspRepeal->IdCardType);
        qDebug("\tCustType [%c]\n", pRspRepeal->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pRspRepeal->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pRspRepeal->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pRspRepeal->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pRspRepeal->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pRspRepeal->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pRspRepeal->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pRspRepeal->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pRspRepeal->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pRspRepeal->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pRspRepeal->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pRspRepeal->BrokerFee);
    }
    qDebug("</OnRtnRepealFromBankToFutureByBank>\n");
};
void CTraderSpi::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal)
{
    qDebug("<OnRtnRepealFromFutureToBankByBank>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnRepealFromFutureToBankByBank(pRspRepeal);
    }
    if (pRspRepeal)
    {
        qDebug("\tBankRepealSerial [%s]\n", pRspRepeal->BankRepealSerial);
        qDebug("\tTradeCode [%s]\n", pRspRepeal->TradeCode);
        qDebug("\tBankID [%s]\n", pRspRepeal->BankID);
        qDebug("\tBankBranchID [%s]\n", pRspRepeal->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pRspRepeal->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pRspRepeal->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pRspRepeal->TradeDate);
        qDebug("\tTradeTime [%s]\n", pRspRepeal->TradeTime);
        qDebug("\tBankSerial [%s]\n", pRspRepeal->BankSerial);
        qDebug("\tTradingDay [%s]\n", pRspRepeal->TradingDay);
        qDebug("\tCustomerName [%s]\n", pRspRepeal->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pRspRepeal->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pRspRepeal->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pRspRepeal->BankPassWord);
        qDebug("\tAccountID [%s]\n", pRspRepeal->AccountID);
        qDebug("\tPassword [%s]\n", pRspRepeal->Password);
        qDebug("\tUserID [%s]\n", pRspRepeal->UserID);
        qDebug("\tCurrencyID [%s]\n", pRspRepeal->CurrencyID);
        qDebug("\tMessage [%s]\n", pRspRepeal->Message);
        qDebug("\tDigest [%s]\n", pRspRepeal->Digest);
        qDebug("\tDeviceID [%s]\n", pRspRepeal->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pRspRepeal->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pRspRepeal->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pRspRepeal->OperNo);
        qDebug("\tErrorMsg [%s]\n", pRspRepeal->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pRspRepeal->LongCustomerName);
        qDebug("\tRepealTimeInterval [%d]\n", pRspRepeal->RepealTimeInterval);
        qDebug("\tRepealedTimes [%d]\n", pRspRepeal->RepealedTimes);
        qDebug("\tPlateRepealSerial [%d]\n", pRspRepeal->PlateRepealSerial);
        qDebug("\tFutureRepealSerial [%d]\n", pRspRepeal->FutureRepealSerial);
        qDebug("\tPlateSerial [%d]\n", pRspRepeal->PlateSerial);
        qDebug("\tSessionID [%d]\n", pRspRepeal->SessionID);
        qDebug("\tInstallID [%d]\n", pRspRepeal->InstallID);
        qDebug("\tFutureSerial [%d]\n", pRspRepeal->FutureSerial);
        qDebug("\tRequestID [%d]\n", pRspRepeal->RequestID);
        qDebug("\tTID [%d]\n", pRspRepeal->TID);
        qDebug("\tErrorID [%d]\n", pRspRepeal->ErrorID);
        qDebug("\tBankRepealFlag [%c]\n", pRspRepeal->BankRepealFlag);
        qDebug("\tBrokerRepealFlag [%c]\n", pRspRepeal->BrokerRepealFlag);
        qDebug("\tLastFragment [%c]\n", pRspRepeal->LastFragment);
        qDebug("\tIdCardType [%c]\n", pRspRepeal->IdCardType);
        qDebug("\tCustType [%c]\n", pRspRepeal->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pRspRepeal->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pRspRepeal->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pRspRepeal->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pRspRepeal->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pRspRepeal->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pRspRepeal->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pRspRepeal->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pRspRepeal->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pRspRepeal->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pRspRepeal->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pRspRepeal->BrokerFee);
    }
    qDebug("</OnRtnRepealFromFutureToBankByBank>\n");
};
void CTraderSpi::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
    qDebug("<OnRtnFromBankToFutureByFuture>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnFromBankToFutureByFuture(pRspTransfer);
    }
    if (pRspTransfer)
    {
        qDebug("\tTradeCode [%s]\n", pRspTransfer->TradeCode);
        qDebug("\tBankID [%s]\n", pRspTransfer->BankID);
        qDebug("\tBankBranchID [%s]\n", pRspTransfer->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pRspTransfer->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pRspTransfer->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pRspTransfer->TradeDate);
        qDebug("\tTradeTime [%s]\n", pRspTransfer->TradeTime);
        qDebug("\tBankSerial [%s]\n", pRspTransfer->BankSerial);
        qDebug("\tTradingDay [%s]\n", pRspTransfer->TradingDay);
        qDebug("\tCustomerName [%s]\n", pRspTransfer->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pRspTransfer->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pRspTransfer->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pRspTransfer->BankPassWord);
        qDebug("\tAccountID [%s]\n", pRspTransfer->AccountID);
        qDebug("\tPassword [%s]\n", pRspTransfer->Password);
        qDebug("\tUserID [%s]\n", pRspTransfer->UserID);
        qDebug("\tCurrencyID [%s]\n", pRspTransfer->CurrencyID);
        qDebug("\tMessage [%s]\n", pRspTransfer->Message);
        qDebug("\tDigest [%s]\n", pRspTransfer->Digest);
        qDebug("\tDeviceID [%s]\n", pRspTransfer->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pRspTransfer->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pRspTransfer->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pRspTransfer->OperNo);
        qDebug("\tErrorMsg [%s]\n", pRspTransfer->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pRspTransfer->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pRspTransfer->PlateSerial);
        qDebug("\tSessionID [%d]\n", pRspTransfer->SessionID);
        qDebug("\tInstallID [%d]\n", pRspTransfer->InstallID);
        qDebug("\tFutureSerial [%d]\n", pRspTransfer->FutureSerial);
        qDebug("\tRequestID [%d]\n", pRspTransfer->RequestID);
        qDebug("\tTID [%d]\n", pRspTransfer->TID);
        qDebug("\tErrorID [%d]\n", pRspTransfer->ErrorID);
        qDebug("\tLastFragment [%c]\n", pRspTransfer->LastFragment);
        qDebug("\tIdCardType [%c]\n", pRspTransfer->IdCardType);
        qDebug("\tCustType [%c]\n", pRspTransfer->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pRspTransfer->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pRspTransfer->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pRspTransfer->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pRspTransfer->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pRspTransfer->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pRspTransfer->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pRspTransfer->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pRspTransfer->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pRspTransfer->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pRspTransfer->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pRspTransfer->BrokerFee);
    }
    qDebug("</OnRtnFromBankToFutureByFuture>\n");
};
void CTraderSpi::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
    qDebug("<OnRtnFromFutureToBankByFuture>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnFromFutureToBankByFuture(pRspTransfer);
    }
    if (pRspTransfer)
    {
        qDebug("\tTradeCode [%s]\n", pRspTransfer->TradeCode);
        qDebug("\tBankID [%s]\n", pRspTransfer->BankID);
        qDebug("\tBankBranchID [%s]\n", pRspTransfer->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pRspTransfer->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pRspTransfer->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pRspTransfer->TradeDate);
        qDebug("\tTradeTime [%s]\n", pRspTransfer->TradeTime);
        qDebug("\tBankSerial [%s]\n", pRspTransfer->BankSerial);
        qDebug("\tTradingDay [%s]\n", pRspTransfer->TradingDay);
        qDebug("\tCustomerName [%s]\n", pRspTransfer->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pRspTransfer->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pRspTransfer->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pRspTransfer->BankPassWord);
        qDebug("\tAccountID [%s]\n", pRspTransfer->AccountID);
        qDebug("\tPassword [%s]\n", pRspTransfer->Password);
        qDebug("\tUserID [%s]\n", pRspTransfer->UserID);
        qDebug("\tCurrencyID [%s]\n", pRspTransfer->CurrencyID);
        qDebug("\tMessage [%s]\n", pRspTransfer->Message);
        qDebug("\tDigest [%s]\n", pRspTransfer->Digest);
        qDebug("\tDeviceID [%s]\n", pRspTransfer->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pRspTransfer->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pRspTransfer->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pRspTransfer->OperNo);
        qDebug("\tErrorMsg [%s]\n", pRspTransfer->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pRspTransfer->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pRspTransfer->PlateSerial);
        qDebug("\tSessionID [%d]\n", pRspTransfer->SessionID);
        qDebug("\tInstallID [%d]\n", pRspTransfer->InstallID);
        qDebug("\tFutureSerial [%d]\n", pRspTransfer->FutureSerial);
        qDebug("\tRequestID [%d]\n", pRspTransfer->RequestID);
        qDebug("\tTID [%d]\n", pRspTransfer->TID);
        qDebug("\tErrorID [%d]\n", pRspTransfer->ErrorID);
        qDebug("\tLastFragment [%c]\n", pRspTransfer->LastFragment);
        qDebug("\tIdCardType [%c]\n", pRspTransfer->IdCardType);
        qDebug("\tCustType [%c]\n", pRspTransfer->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pRspTransfer->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pRspTransfer->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pRspTransfer->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pRspTransfer->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pRspTransfer->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pRspTransfer->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pRspTransfer->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pRspTransfer->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pRspTransfer->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pRspTransfer->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pRspTransfer->BrokerFee);
    }
    qDebug("</OnRtnFromFutureToBankByFuture>\n");
};
void CTraderSpi::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal)
{
    qDebug("<OnRtnRepealFromBankToFutureByFutureManual>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnRepealFromBankToFutureByFutureManual(pRspRepeal);
    }
    if (pRspRepeal)
    {
        qDebug("\tBankRepealSerial [%s]\n", pRspRepeal->BankRepealSerial);
        qDebug("\tTradeCode [%s]\n", pRspRepeal->TradeCode);
        qDebug("\tBankID [%s]\n", pRspRepeal->BankID);
        qDebug("\tBankBranchID [%s]\n", pRspRepeal->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pRspRepeal->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pRspRepeal->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pRspRepeal->TradeDate);
        qDebug("\tTradeTime [%s]\n", pRspRepeal->TradeTime);
        qDebug("\tBankSerial [%s]\n", pRspRepeal->BankSerial);
        qDebug("\tTradingDay [%s]\n", pRspRepeal->TradingDay);
        qDebug("\tCustomerName [%s]\n", pRspRepeal->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pRspRepeal->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pRspRepeal->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pRspRepeal->BankPassWord);
        qDebug("\tAccountID [%s]\n", pRspRepeal->AccountID);
        qDebug("\tPassword [%s]\n", pRspRepeal->Password);
        qDebug("\tUserID [%s]\n", pRspRepeal->UserID);
        qDebug("\tCurrencyID [%s]\n", pRspRepeal->CurrencyID);
        qDebug("\tMessage [%s]\n", pRspRepeal->Message);
        qDebug("\tDigest [%s]\n", pRspRepeal->Digest);
        qDebug("\tDeviceID [%s]\n", pRspRepeal->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pRspRepeal->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pRspRepeal->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pRspRepeal->OperNo);
        qDebug("\tErrorMsg [%s]\n", pRspRepeal->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pRspRepeal->LongCustomerName);
        qDebug("\tRepealTimeInterval [%d]\n", pRspRepeal->RepealTimeInterval);
        qDebug("\tRepealedTimes [%d]\n", pRspRepeal->RepealedTimes);
        qDebug("\tPlateRepealSerial [%d]\n", pRspRepeal->PlateRepealSerial);
        qDebug("\tFutureRepealSerial [%d]\n", pRspRepeal->FutureRepealSerial);
        qDebug("\tPlateSerial [%d]\n", pRspRepeal->PlateSerial);
        qDebug("\tSessionID [%d]\n", pRspRepeal->SessionID);
        qDebug("\tInstallID [%d]\n", pRspRepeal->InstallID);
        qDebug("\tFutureSerial [%d]\n", pRspRepeal->FutureSerial);
        qDebug("\tRequestID [%d]\n", pRspRepeal->RequestID);
        qDebug("\tTID [%d]\n", pRspRepeal->TID);
        qDebug("\tErrorID [%d]\n", pRspRepeal->ErrorID);
        qDebug("\tBankRepealFlag [%c]\n", pRspRepeal->BankRepealFlag);
        qDebug("\tBrokerRepealFlag [%c]\n", pRspRepeal->BrokerRepealFlag);
        qDebug("\tLastFragment [%c]\n", pRspRepeal->LastFragment);
        qDebug("\tIdCardType [%c]\n", pRspRepeal->IdCardType);
        qDebug("\tCustType [%c]\n", pRspRepeal->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pRspRepeal->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pRspRepeal->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pRspRepeal->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pRspRepeal->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pRspRepeal->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pRspRepeal->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pRspRepeal->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pRspRepeal->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pRspRepeal->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pRspRepeal->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pRspRepeal->BrokerFee);
    }
    qDebug("</OnRtnRepealFromBankToFutureByFutureManual>\n");
};
void CTraderSpi::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal)
{
    qDebug("<OnRtnRepealFromFutureToBankByFutureManual>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnRepealFromFutureToBankByFutureManual(pRspRepeal);
    }
    if (pRspRepeal)
    {
        qDebug("\tBankRepealSerial [%s]\n", pRspRepeal->BankRepealSerial);
        qDebug("\tTradeCode [%s]\n", pRspRepeal->TradeCode);
        qDebug("\tBankID [%s]\n", pRspRepeal->BankID);
        qDebug("\tBankBranchID [%s]\n", pRspRepeal->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pRspRepeal->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pRspRepeal->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pRspRepeal->TradeDate);
        qDebug("\tTradeTime [%s]\n", pRspRepeal->TradeTime);
        qDebug("\tBankSerial [%s]\n", pRspRepeal->BankSerial);
        qDebug("\tTradingDay [%s]\n", pRspRepeal->TradingDay);
        qDebug("\tCustomerName [%s]\n", pRspRepeal->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pRspRepeal->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pRspRepeal->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pRspRepeal->BankPassWord);
        qDebug("\tAccountID [%s]\n", pRspRepeal->AccountID);
        qDebug("\tPassword [%s]\n", pRspRepeal->Password);
        qDebug("\tUserID [%s]\n", pRspRepeal->UserID);
        qDebug("\tCurrencyID [%s]\n", pRspRepeal->CurrencyID);
        qDebug("\tMessage [%s]\n", pRspRepeal->Message);
        qDebug("\tDigest [%s]\n", pRspRepeal->Digest);
        qDebug("\tDeviceID [%s]\n", pRspRepeal->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pRspRepeal->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pRspRepeal->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pRspRepeal->OperNo);
        qDebug("\tErrorMsg [%s]\n", pRspRepeal->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pRspRepeal->LongCustomerName);
        qDebug("\tRepealTimeInterval [%d]\n", pRspRepeal->RepealTimeInterval);
        qDebug("\tRepealedTimes [%d]\n", pRspRepeal->RepealedTimes);
        qDebug("\tPlateRepealSerial [%d]\n", pRspRepeal->PlateRepealSerial);
        qDebug("\tFutureRepealSerial [%d]\n", pRspRepeal->FutureRepealSerial);
        qDebug("\tPlateSerial [%d]\n", pRspRepeal->PlateSerial);
        qDebug("\tSessionID [%d]\n", pRspRepeal->SessionID);
        qDebug("\tInstallID [%d]\n", pRspRepeal->InstallID);
        qDebug("\tFutureSerial [%d]\n", pRspRepeal->FutureSerial);
        qDebug("\tRequestID [%d]\n", pRspRepeal->RequestID);
        qDebug("\tTID [%d]\n", pRspRepeal->TID);
        qDebug("\tErrorID [%d]\n", pRspRepeal->ErrorID);
        qDebug("\tBankRepealFlag [%c]\n", pRspRepeal->BankRepealFlag);
        qDebug("\tBrokerRepealFlag [%c]\n", pRspRepeal->BrokerRepealFlag);
        qDebug("\tLastFragment [%c]\n", pRspRepeal->LastFragment);
        qDebug("\tIdCardType [%c]\n", pRspRepeal->IdCardType);
        qDebug("\tCustType [%c]\n", pRspRepeal->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pRspRepeal->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pRspRepeal->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pRspRepeal->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pRspRepeal->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pRspRepeal->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pRspRepeal->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pRspRepeal->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pRspRepeal->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pRspRepeal->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pRspRepeal->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pRspRepeal->BrokerFee);
    }
    qDebug("</OnRtnRepealFromFutureToBankByFutureManual>\n");
};
void CTraderSpi::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount)
{
    qDebug("<OnRtnQueryBankBalanceByFuture>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnQueryBankBalanceByFuture(pNotifyQueryAccount);
    }
    if (pNotifyQueryAccount)
    {
        qDebug("\tTradeCode [%s]\n", pNotifyQueryAccount->TradeCode);
        qDebug("\tBankID [%s]\n", pNotifyQueryAccount->BankID);
        qDebug("\tBankBranchID [%s]\n", pNotifyQueryAccount->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pNotifyQueryAccount->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pNotifyQueryAccount->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pNotifyQueryAccount->TradeDate);
        qDebug("\tTradeTime [%s]\n", pNotifyQueryAccount->TradeTime);
        qDebug("\tBankSerial [%s]\n", pNotifyQueryAccount->BankSerial);
        qDebug("\tTradingDay [%s]\n", pNotifyQueryAccount->TradingDay);
        qDebug("\tCustomerName [%s]\n", pNotifyQueryAccount->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pNotifyQueryAccount->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pNotifyQueryAccount->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pNotifyQueryAccount->BankPassWord);
        qDebug("\tAccountID [%s]\n", pNotifyQueryAccount->AccountID);
        qDebug("\tPassword [%s]\n", pNotifyQueryAccount->Password);
        qDebug("\tUserID [%s]\n", pNotifyQueryAccount->UserID);
        qDebug("\tCurrencyID [%s]\n", pNotifyQueryAccount->CurrencyID);
        qDebug("\tDigest [%s]\n", pNotifyQueryAccount->Digest);
        qDebug("\tDeviceID [%s]\n", pNotifyQueryAccount->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pNotifyQueryAccount->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pNotifyQueryAccount->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pNotifyQueryAccount->OperNo);
        qDebug("\tErrorMsg [%s]\n", pNotifyQueryAccount->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pNotifyQueryAccount->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pNotifyQueryAccount->PlateSerial);
        qDebug("\tSessionID [%d]\n", pNotifyQueryAccount->SessionID);
        qDebug("\tFutureSerial [%d]\n", pNotifyQueryAccount->FutureSerial);
        qDebug("\tInstallID [%d]\n", pNotifyQueryAccount->InstallID);
        qDebug("\tRequestID [%d]\n", pNotifyQueryAccount->RequestID);
        qDebug("\tTID [%d]\n", pNotifyQueryAccount->TID);
        qDebug("\tErrorID [%d]\n", pNotifyQueryAccount->ErrorID);
        qDebug("\tLastFragment [%c]\n", pNotifyQueryAccount->LastFragment);
        qDebug("\tIdCardType [%c]\n", pNotifyQueryAccount->IdCardType);
        qDebug("\tCustType [%c]\n", pNotifyQueryAccount->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pNotifyQueryAccount->VerifyCertNoFlag);
        qDebug("\tBankAccType [%c]\n", pNotifyQueryAccount->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pNotifyQueryAccount->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pNotifyQueryAccount->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pNotifyQueryAccount->SecuPwdFlag);
        qDebug("\tBankUseAmount [%.8lf]\n", pNotifyQueryAccount->BankUseAmount);
        qDebug("\tBankFetchAmount [%.8lf]\n", pNotifyQueryAccount->BankFetchAmount);
    }
    qDebug("</OnRtnQueryBankBalanceByFuture>\n");
};
void CTraderSpi::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnBankToFutureByFuture>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnBankToFutureByFuture(pReqTransfer, pRspInfo );
    }
    if (pReqTransfer)
    {
        qDebug("\tTradeCode [%s]\n", pReqTransfer->TradeCode);
        qDebug("\tBankID [%s]\n", pReqTransfer->BankID);
        qDebug("\tBankBranchID [%s]\n", pReqTransfer->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pReqTransfer->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pReqTransfer->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pReqTransfer->TradeDate);
        qDebug("\tTradeTime [%s]\n", pReqTransfer->TradeTime);
        qDebug("\tBankSerial [%s]\n", pReqTransfer->BankSerial);
        qDebug("\tTradingDay [%s]\n", pReqTransfer->TradingDay);
        qDebug("\tCustomerName [%s]\n", pReqTransfer->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pReqTransfer->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pReqTransfer->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pReqTransfer->BankPassWord);
        qDebug("\tAccountID [%s]\n", pReqTransfer->AccountID);
        qDebug("\tPassword [%s]\n", pReqTransfer->Password);
        qDebug("\tUserID [%s]\n", pReqTransfer->UserID);
        qDebug("\tCurrencyID [%s]\n", pReqTransfer->CurrencyID);
        qDebug("\tMessage [%s]\n", pReqTransfer->Message);
        qDebug("\tDigest [%s]\n", pReqTransfer->Digest);
        qDebug("\tDeviceID [%s]\n", pReqTransfer->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pReqTransfer->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pReqTransfer->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pReqTransfer->OperNo);
        qDebug("\tLongCustomerName [%s]\n", pReqTransfer->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pReqTransfer->PlateSerial);
        qDebug("\tSessionID [%d]\n", pReqTransfer->SessionID);
        qDebug("\tInstallID [%d]\n", pReqTransfer->InstallID);
        qDebug("\tFutureSerial [%d]\n", pReqTransfer->FutureSerial);
        qDebug("\tRequestID [%d]\n", pReqTransfer->RequestID);
        qDebug("\tTID [%d]\n", pReqTransfer->TID);
        qDebug("\tLastFragment [%c]\n", pReqTransfer->LastFragment);
        qDebug("\tIdCardType [%c]\n", pReqTransfer->IdCardType);
        qDebug("\tCustType [%c]\n", pReqTransfer->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pReqTransfer->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pReqTransfer->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pReqTransfer->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pReqTransfer->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pReqTransfer->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pReqTransfer->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pReqTransfer->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pReqTransfer->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pReqTransfer->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pReqTransfer->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pReqTransfer->BrokerFee);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnBankToFutureByFuture>\n");
};
void CTraderSpi::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnFutureToBankByFuture>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnFutureToBankByFuture(pReqTransfer, pRspInfo );
    }
    if (pReqTransfer)
    {
        qDebug("\tTradeCode [%s]\n", pReqTransfer->TradeCode);
        qDebug("\tBankID [%s]\n", pReqTransfer->BankID);
        qDebug("\tBankBranchID [%s]\n", pReqTransfer->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pReqTransfer->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pReqTransfer->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pReqTransfer->TradeDate);
        qDebug("\tTradeTime [%s]\n", pReqTransfer->TradeTime);
        qDebug("\tBankSerial [%s]\n", pReqTransfer->BankSerial);
        qDebug("\tTradingDay [%s]\n", pReqTransfer->TradingDay);
        qDebug("\tCustomerName [%s]\n", pReqTransfer->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pReqTransfer->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pReqTransfer->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pReqTransfer->BankPassWord);
        qDebug("\tAccountID [%s]\n", pReqTransfer->AccountID);
        qDebug("\tPassword [%s]\n", pReqTransfer->Password);
        qDebug("\tUserID [%s]\n", pReqTransfer->UserID);
        qDebug("\tCurrencyID [%s]\n", pReqTransfer->CurrencyID);
        qDebug("\tMessage [%s]\n", pReqTransfer->Message);
        qDebug("\tDigest [%s]\n", pReqTransfer->Digest);
        qDebug("\tDeviceID [%s]\n", pReqTransfer->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pReqTransfer->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pReqTransfer->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pReqTransfer->OperNo);
        qDebug("\tLongCustomerName [%s]\n", pReqTransfer->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pReqTransfer->PlateSerial);
        qDebug("\tSessionID [%d]\n", pReqTransfer->SessionID);
        qDebug("\tInstallID [%d]\n", pReqTransfer->InstallID);
        qDebug("\tFutureSerial [%d]\n", pReqTransfer->FutureSerial);
        qDebug("\tRequestID [%d]\n", pReqTransfer->RequestID);
        qDebug("\tTID [%d]\n", pReqTransfer->TID);
        qDebug("\tLastFragment [%c]\n", pReqTransfer->LastFragment);
        qDebug("\tIdCardType [%c]\n", pReqTransfer->IdCardType);
        qDebug("\tCustType [%c]\n", pReqTransfer->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pReqTransfer->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pReqTransfer->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pReqTransfer->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pReqTransfer->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pReqTransfer->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pReqTransfer->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pReqTransfer->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pReqTransfer->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pReqTransfer->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pReqTransfer->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pReqTransfer->BrokerFee);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnFutureToBankByFuture>\n");
};
void CTraderSpi::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnRepealBankToFutureByFutureManual>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnRepealBankToFutureByFutureManual(pReqRepeal, pRspInfo);
    }
    if (pReqRepeal)
    {
        qDebug("\tBankRepealSerial [%s]\n", pReqRepeal->BankRepealSerial);
        qDebug("\tTradeCode [%s]\n", pReqRepeal->TradeCode);
        qDebug("\tBankID [%s]\n", pReqRepeal->BankID);
        qDebug("\tBankBranchID [%s]\n", pReqRepeal->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pReqRepeal->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pReqRepeal->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pReqRepeal->TradeDate);
        qDebug("\tTradeTime [%s]\n", pReqRepeal->TradeTime);
        qDebug("\tBankSerial [%s]\n", pReqRepeal->BankSerial);
        qDebug("\tTradingDay [%s]\n", pReqRepeal->TradingDay);
        qDebug("\tCustomerName [%s]\n", pReqRepeal->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pReqRepeal->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pReqRepeal->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pReqRepeal->BankPassWord);
        qDebug("\tAccountID [%s]\n", pReqRepeal->AccountID);
        qDebug("\tPassword [%s]\n", pReqRepeal->Password);
        qDebug("\tUserID [%s]\n", pReqRepeal->UserID);
        qDebug("\tCurrencyID [%s]\n", pReqRepeal->CurrencyID);
        qDebug("\tMessage [%s]\n", pReqRepeal->Message);
        qDebug("\tDigest [%s]\n", pReqRepeal->Digest);
        qDebug("\tDeviceID [%s]\n", pReqRepeal->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pReqRepeal->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pReqRepeal->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pReqRepeal->OperNo);
        qDebug("\tLongCustomerName [%s]\n", pReqRepeal->LongCustomerName);
        qDebug("\tRepealTimeInterval [%d]\n", pReqRepeal->RepealTimeInterval);
        qDebug("\tRepealedTimes [%d]\n", pReqRepeal->RepealedTimes);
        qDebug("\tPlateRepealSerial [%d]\n", pReqRepeal->PlateRepealSerial);
        qDebug("\tFutureRepealSerial [%d]\n", pReqRepeal->FutureRepealSerial);
        qDebug("\tPlateSerial [%d]\n", pReqRepeal->PlateSerial);
        qDebug("\tSessionID [%d]\n", pReqRepeal->SessionID);
        qDebug("\tInstallID [%d]\n", pReqRepeal->InstallID);
        qDebug("\tFutureSerial [%d]\n", pReqRepeal->FutureSerial);
        qDebug("\tRequestID [%d]\n", pReqRepeal->RequestID);
        qDebug("\tTID [%d]\n", pReqRepeal->TID);
        qDebug("\tBankRepealFlag [%c]\n", pReqRepeal->BankRepealFlag);
        qDebug("\tBrokerRepealFlag [%c]\n", pReqRepeal->BrokerRepealFlag);
        qDebug("\tLastFragment [%c]\n", pReqRepeal->LastFragment);
        qDebug("\tIdCardType [%c]\n", pReqRepeal->IdCardType);
        qDebug("\tCustType [%c]\n", pReqRepeal->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pReqRepeal->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pReqRepeal->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pReqRepeal->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pReqRepeal->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pReqRepeal->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pReqRepeal->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pReqRepeal->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pReqRepeal->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pReqRepeal->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pReqRepeal->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pReqRepeal->BrokerFee);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnRepealBankToFutureByFutureManual>\n");
};
void CTraderSpi::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnRepealFutureToBankByFutureManual>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnRepealFutureToBankByFutureManual(pReqRepeal, pRspInfo);
    }
    if (pReqRepeal)
    {
        qDebug("\tBankRepealSerial [%s]\n", pReqRepeal->BankRepealSerial);
        qDebug("\tTradeCode [%s]\n", pReqRepeal->TradeCode);
        qDebug("\tBankID [%s]\n", pReqRepeal->BankID);
        qDebug("\tBankBranchID [%s]\n", pReqRepeal->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pReqRepeal->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pReqRepeal->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pReqRepeal->TradeDate);
        qDebug("\tTradeTime [%s]\n", pReqRepeal->TradeTime);
        qDebug("\tBankSerial [%s]\n", pReqRepeal->BankSerial);
        qDebug("\tTradingDay [%s]\n", pReqRepeal->TradingDay);
        qDebug("\tCustomerName [%s]\n", pReqRepeal->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pReqRepeal->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pReqRepeal->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pReqRepeal->BankPassWord);
        qDebug("\tAccountID [%s]\n", pReqRepeal->AccountID);
        qDebug("\tPassword [%s]\n", pReqRepeal->Password);
        qDebug("\tUserID [%s]\n", pReqRepeal->UserID);
        qDebug("\tCurrencyID [%s]\n", pReqRepeal->CurrencyID);
        qDebug("\tMessage [%s]\n", pReqRepeal->Message);
        qDebug("\tDigest [%s]\n", pReqRepeal->Digest);
        qDebug("\tDeviceID [%s]\n", pReqRepeal->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pReqRepeal->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pReqRepeal->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pReqRepeal->OperNo);
        qDebug("\tLongCustomerName [%s]\n", pReqRepeal->LongCustomerName);
        qDebug("\tRepealTimeInterval [%d]\n", pReqRepeal->RepealTimeInterval);
        qDebug("\tRepealedTimes [%d]\n", pReqRepeal->RepealedTimes);
        qDebug("\tPlateRepealSerial [%d]\n", pReqRepeal->PlateRepealSerial);
        qDebug("\tFutureRepealSerial [%d]\n", pReqRepeal->FutureRepealSerial);
        qDebug("\tPlateSerial [%d]\n", pReqRepeal->PlateSerial);
        qDebug("\tSessionID [%d]\n", pReqRepeal->SessionID);
        qDebug("\tInstallID [%d]\n", pReqRepeal->InstallID);
        qDebug("\tFutureSerial [%d]\n", pReqRepeal->FutureSerial);
        qDebug("\tRequestID [%d]\n", pReqRepeal->RequestID);
        qDebug("\tTID [%d]\n", pReqRepeal->TID);
        qDebug("\tBankRepealFlag [%c]\n", pReqRepeal->BankRepealFlag);
        qDebug("\tBrokerRepealFlag [%c]\n", pReqRepeal->BrokerRepealFlag);
        qDebug("\tLastFragment [%c]\n", pReqRepeal->LastFragment);
        qDebug("\tIdCardType [%c]\n", pReqRepeal->IdCardType);
        qDebug("\tCustType [%c]\n", pReqRepeal->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pReqRepeal->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pReqRepeal->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pReqRepeal->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pReqRepeal->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pReqRepeal->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pReqRepeal->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pReqRepeal->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pReqRepeal->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pReqRepeal->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pReqRepeal->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pReqRepeal->BrokerFee);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnRepealFutureToBankByFutureManual>\n");
};
void CTraderSpi::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo)
{
    qDebug("<OnErrRtnQueryBankBalanceByFuture>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnErrRtnQueryBankBalanceByFuture(pReqQueryAccount, pRspInfo);
    }
    if (pReqQueryAccount)
    {
        qDebug("\tTradeCode [%s]\n", pReqQueryAccount->TradeCode);
        qDebug("\tBankID [%s]\n", pReqQueryAccount->BankID);
        qDebug("\tBankBranchID [%s]\n", pReqQueryAccount->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pReqQueryAccount->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pReqQueryAccount->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pReqQueryAccount->TradeDate);
        qDebug("\tTradeTime [%s]\n", pReqQueryAccount->TradeTime);
        qDebug("\tBankSerial [%s]\n", pReqQueryAccount->BankSerial);
        qDebug("\tTradingDay [%s]\n", pReqQueryAccount->TradingDay);
        qDebug("\tCustomerName [%s]\n", pReqQueryAccount->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pReqQueryAccount->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pReqQueryAccount->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pReqQueryAccount->BankPassWord);
        qDebug("\tAccountID [%s]\n", pReqQueryAccount->AccountID);
        qDebug("\tPassword [%s]\n", pReqQueryAccount->Password);
        qDebug("\tUserID [%s]\n", pReqQueryAccount->UserID);
        qDebug("\tCurrencyID [%s]\n", pReqQueryAccount->CurrencyID);
        qDebug("\tDigest [%s]\n", pReqQueryAccount->Digest);
        qDebug("\tDeviceID [%s]\n", pReqQueryAccount->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pReqQueryAccount->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pReqQueryAccount->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pReqQueryAccount->OperNo);
        qDebug("\tLongCustomerName [%s]\n", pReqQueryAccount->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pReqQueryAccount->PlateSerial);
        qDebug("\tSessionID [%d]\n", pReqQueryAccount->SessionID);
        qDebug("\tFutureSerial [%d]\n", pReqQueryAccount->FutureSerial);
        qDebug("\tInstallID [%d]\n", pReqQueryAccount->InstallID);
        qDebug("\tRequestID [%d]\n", pReqQueryAccount->RequestID);
        qDebug("\tTID [%d]\n", pReqQueryAccount->TID);
        qDebug("\tLastFragment [%c]\n", pReqQueryAccount->LastFragment);
        qDebug("\tIdCardType [%c]\n", pReqQueryAccount->IdCardType);
        qDebug("\tCustType [%c]\n", pReqQueryAccount->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pReqQueryAccount->VerifyCertNoFlag);
        qDebug("\tBankAccType [%c]\n", pReqQueryAccount->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pReqQueryAccount->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pReqQueryAccount->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pReqQueryAccount->SecuPwdFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("</OnErrRtnQueryBankBalanceByFuture>\n");
};
void CTraderSpi::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal)
{
    qDebug("<OnRtnRepealFromBankToFutureByFuture>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnRepealFromBankToFutureByFuture(pRspRepeal);
    }
    if (pRspRepeal)
    {
        qDebug("\tBankRepealSerial [%s]\n", pRspRepeal->BankRepealSerial);
        qDebug("\tTradeCode [%s]\n", pRspRepeal->TradeCode);
        qDebug("\tBankID [%s]\n", pRspRepeal->BankID);
        qDebug("\tBankBranchID [%s]\n", pRspRepeal->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pRspRepeal->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pRspRepeal->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pRspRepeal->TradeDate);
        qDebug("\tTradeTime [%s]\n", pRspRepeal->TradeTime);
        qDebug("\tBankSerial [%s]\n", pRspRepeal->BankSerial);
        qDebug("\tTradingDay [%s]\n", pRspRepeal->TradingDay);
        qDebug("\tCustomerName [%s]\n", pRspRepeal->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pRspRepeal->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pRspRepeal->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pRspRepeal->BankPassWord);
        qDebug("\tAccountID [%s]\n", pRspRepeal->AccountID);
        qDebug("\tPassword [%s]\n", pRspRepeal->Password);
        qDebug("\tUserID [%s]\n", pRspRepeal->UserID);
        qDebug("\tCurrencyID [%s]\n", pRspRepeal->CurrencyID);
        qDebug("\tMessage [%s]\n", pRspRepeal->Message);
        qDebug("\tDigest [%s]\n", pRspRepeal->Digest);
        qDebug("\tDeviceID [%s]\n", pRspRepeal->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pRspRepeal->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pRspRepeal->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pRspRepeal->OperNo);
        qDebug("\tErrorMsg [%s]\n", pRspRepeal->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pRspRepeal->LongCustomerName);
        qDebug("\tRepealTimeInterval [%d]\n", pRspRepeal->RepealTimeInterval);
        qDebug("\tRepealedTimes [%d]\n", pRspRepeal->RepealedTimes);
        qDebug("\tPlateRepealSerial [%d]\n", pRspRepeal->PlateRepealSerial);
        qDebug("\tFutureRepealSerial [%d]\n", pRspRepeal->FutureRepealSerial);
        qDebug("\tPlateSerial [%d]\n", pRspRepeal->PlateSerial);
        qDebug("\tSessionID [%d]\n", pRspRepeal->SessionID);
        qDebug("\tInstallID [%d]\n", pRspRepeal->InstallID);
        qDebug("\tFutureSerial [%d]\n", pRspRepeal->FutureSerial);
        qDebug("\tRequestID [%d]\n", pRspRepeal->RequestID);
        qDebug("\tTID [%d]\n", pRspRepeal->TID);
        qDebug("\tErrorID [%d]\n", pRspRepeal->ErrorID);
        qDebug("\tBankRepealFlag [%c]\n", pRspRepeal->BankRepealFlag);
        qDebug("\tBrokerRepealFlag [%c]\n", pRspRepeal->BrokerRepealFlag);
        qDebug("\tLastFragment [%c]\n", pRspRepeal->LastFragment);
        qDebug("\tIdCardType [%c]\n", pRspRepeal->IdCardType);
        qDebug("\tCustType [%c]\n", pRspRepeal->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pRspRepeal->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pRspRepeal->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pRspRepeal->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pRspRepeal->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pRspRepeal->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pRspRepeal->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pRspRepeal->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pRspRepeal->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pRspRepeal->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pRspRepeal->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pRspRepeal->BrokerFee);
    }
    qDebug("</OnRtnRepealFromBankToFutureByFuture>\n");
};
void CTraderSpi::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal)
{
    qDebug("<OnRtnRepealFromFutureToBankByFuture>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnRepealFromFutureToBankByFuture(pRspRepeal);
    }
    if (pRspRepeal)
    {
        qDebug("\tBankRepealSerial [%s]\n", pRspRepeal->BankRepealSerial);
        qDebug("\tTradeCode [%s]\n", pRspRepeal->TradeCode);
        qDebug("\tBankID [%s]\n", pRspRepeal->BankID);
        qDebug("\tBankBranchID [%s]\n", pRspRepeal->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pRspRepeal->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pRspRepeal->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pRspRepeal->TradeDate);
        qDebug("\tTradeTime [%s]\n", pRspRepeal->TradeTime);
        qDebug("\tBankSerial [%s]\n", pRspRepeal->BankSerial);
        qDebug("\tTradingDay [%s]\n", pRspRepeal->TradingDay);
        qDebug("\tCustomerName [%s]\n", pRspRepeal->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pRspRepeal->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pRspRepeal->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pRspRepeal->BankPassWord);
        qDebug("\tAccountID [%s]\n", pRspRepeal->AccountID);
        qDebug("\tPassword [%s]\n", pRspRepeal->Password);
        qDebug("\tUserID [%s]\n", pRspRepeal->UserID);
        qDebug("\tCurrencyID [%s]\n", pRspRepeal->CurrencyID);
        qDebug("\tMessage [%s]\n", pRspRepeal->Message);
        qDebug("\tDigest [%s]\n", pRspRepeal->Digest);
        qDebug("\tDeviceID [%s]\n", pRspRepeal->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pRspRepeal->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pRspRepeal->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pRspRepeal->OperNo);
        qDebug("\tErrorMsg [%s]\n", pRspRepeal->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pRspRepeal->LongCustomerName);
        qDebug("\tRepealTimeInterval [%d]\n", pRspRepeal->RepealTimeInterval);
        qDebug("\tRepealedTimes [%d]\n", pRspRepeal->RepealedTimes);
        qDebug("\tPlateRepealSerial [%d]\n", pRspRepeal->PlateRepealSerial);
        qDebug("\tFutureRepealSerial [%d]\n", pRspRepeal->FutureRepealSerial);
        qDebug("\tPlateSerial [%d]\n", pRspRepeal->PlateSerial);
        qDebug("\tSessionID [%d]\n", pRspRepeal->SessionID);
        qDebug("\tInstallID [%d]\n", pRspRepeal->InstallID);
        qDebug("\tFutureSerial [%d]\n", pRspRepeal->FutureSerial);
        qDebug("\tRequestID [%d]\n", pRspRepeal->RequestID);
        qDebug("\tTID [%d]\n", pRspRepeal->TID);
        qDebug("\tErrorID [%d]\n", pRspRepeal->ErrorID);
        qDebug("\tBankRepealFlag [%c]\n", pRspRepeal->BankRepealFlag);
        qDebug("\tBrokerRepealFlag [%c]\n", pRspRepeal->BrokerRepealFlag);
        qDebug("\tLastFragment [%c]\n", pRspRepeal->LastFragment);
        qDebug("\tIdCardType [%c]\n", pRspRepeal->IdCardType);
        qDebug("\tCustType [%c]\n", pRspRepeal->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pRspRepeal->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pRspRepeal->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pRspRepeal->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pRspRepeal->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pRspRepeal->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pRspRepeal->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pRspRepeal->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pRspRepeal->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pRspRepeal->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pRspRepeal->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pRspRepeal->BrokerFee);
    }
    qDebug("</OnRtnRepealFromFutureToBankByFuture>\n");
};
void CTraderSpi::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspFromBankToFutureByFuture>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspFromBankToFutureByFuture(pReqTransfer, pRspInfo,nRequestID,bIsLast);
    }
    if (pReqTransfer)
    {
        qDebug("\tTradeCode [%s]\n", pReqTransfer->TradeCode);
        qDebug("\tBankID [%s]\n", pReqTransfer->BankID);
        qDebug("\tBankBranchID [%s]\n", pReqTransfer->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pReqTransfer->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pReqTransfer->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pReqTransfer->TradeDate);
        qDebug("\tTradeTime [%s]\n", pReqTransfer->TradeTime);
        qDebug("\tBankSerial [%s]\n", pReqTransfer->BankSerial);
        qDebug("\tTradingDay [%s]\n", pReqTransfer->TradingDay);
        qDebug("\tCustomerName [%s]\n", pReqTransfer->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pReqTransfer->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pReqTransfer->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pReqTransfer->BankPassWord);
        qDebug("\tAccountID [%s]\n", pReqTransfer->AccountID);
        qDebug("\tPassword [%s]\n", pReqTransfer->Password);
        qDebug("\tUserID [%s]\n", pReqTransfer->UserID);
        qDebug("\tCurrencyID [%s]\n", pReqTransfer->CurrencyID);
        qDebug("\tMessage [%s]\n", pReqTransfer->Message);
        qDebug("\tDigest [%s]\n", pReqTransfer->Digest);
        qDebug("\tDeviceID [%s]\n", pReqTransfer->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pReqTransfer->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pReqTransfer->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pReqTransfer->OperNo);
        qDebug("\tLongCustomerName [%s]\n", pReqTransfer->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pReqTransfer->PlateSerial);
        qDebug("\tSessionID [%d]\n", pReqTransfer->SessionID);
        qDebug("\tInstallID [%d]\n", pReqTransfer->InstallID);
        qDebug("\tFutureSerial [%d]\n", pReqTransfer->FutureSerial);
        qDebug("\tRequestID [%d]\n", pReqTransfer->RequestID);
        qDebug("\tTID [%d]\n", pReqTransfer->TID);
        qDebug("\tLastFragment [%c]\n", pReqTransfer->LastFragment);
        qDebug("\tIdCardType [%c]\n", pReqTransfer->IdCardType);
        qDebug("\tCustType [%c]\n", pReqTransfer->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pReqTransfer->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pReqTransfer->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pReqTransfer->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pReqTransfer->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pReqTransfer->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pReqTransfer->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pReqTransfer->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pReqTransfer->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pReqTransfer->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pReqTransfer->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pReqTransfer->BrokerFee);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspFromBankToFutureByFuture>\n");
};

void CTraderSpi::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspFromFutureToBankByFuture>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspFromFutureToBankByFuture(pReqTransfer, pRspInfo,nRequestID,bIsLast);
    }
    if (pReqTransfer)
    {
        qDebug("\tTradeCode [%s]\n", pReqTransfer->TradeCode);
        qDebug("\tBankID [%s]\n", pReqTransfer->BankID);
        qDebug("\tBankBranchID [%s]\n", pReqTransfer->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pReqTransfer->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pReqTransfer->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pReqTransfer->TradeDate);
        qDebug("\tTradeTime [%s]\n", pReqTransfer->TradeTime);
        qDebug("\tBankSerial [%s]\n", pReqTransfer->BankSerial);
        qDebug("\tTradingDay [%s]\n", pReqTransfer->TradingDay);
        qDebug("\tCustomerName [%s]\n", pReqTransfer->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pReqTransfer->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pReqTransfer->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pReqTransfer->BankPassWord);
        qDebug("\tAccountID [%s]\n", pReqTransfer->AccountID);
        qDebug("\tPassword [%s]\n", pReqTransfer->Password);
        qDebug("\tUserID [%s]\n", pReqTransfer->UserID);
        qDebug("\tCurrencyID [%s]\n", pReqTransfer->CurrencyID);
        qDebug("\tMessage [%s]\n", pReqTransfer->Message);
        qDebug("\tDigest [%s]\n", pReqTransfer->Digest);
        qDebug("\tDeviceID [%s]\n", pReqTransfer->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pReqTransfer->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pReqTransfer->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pReqTransfer->OperNo);
        qDebug("\tLongCustomerName [%s]\n", pReqTransfer->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pReqTransfer->PlateSerial);
        qDebug("\tSessionID [%d]\n", pReqTransfer->SessionID);
        qDebug("\tInstallID [%d]\n", pReqTransfer->InstallID);
        qDebug("\tFutureSerial [%d]\n", pReqTransfer->FutureSerial);
        qDebug("\tRequestID [%d]\n", pReqTransfer->RequestID);
        qDebug("\tTID [%d]\n", pReqTransfer->TID);
        qDebug("\tLastFragment [%c]\n", pReqTransfer->LastFragment);
        qDebug("\tIdCardType [%c]\n", pReqTransfer->IdCardType);
        qDebug("\tCustType [%c]\n", pReqTransfer->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pReqTransfer->VerifyCertNoFlag);
        qDebug("\tFeePayFlag [%c]\n", pReqTransfer->FeePayFlag);
        qDebug("\tBankAccType [%c]\n", pReqTransfer->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pReqTransfer->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pReqTransfer->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pReqTransfer->SecuPwdFlag);
        qDebug("\tTransferStatus [%c]\n", pReqTransfer->TransferStatus);
        qDebug("\tTradeAmount [%.8lf]\n", pReqTransfer->TradeAmount);
        qDebug("\tFutureFetchAmount [%.8lf]\n", pReqTransfer->FutureFetchAmount);
        qDebug("\tCustFee [%.8lf]\n", pReqTransfer->CustFee);
        qDebug("\tBrokerFee [%.8lf]\n", pReqTransfer->BrokerFee);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspFromFutureToBankByFuture>\n");
};

void CTraderSpi::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug("<OnRspQueryBankAccountMoneyByFuture>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRspQueryBankAccountMoneyByFuture(pReqQueryAccount, pRspInfo,nRequestID,bIsLast);
    }
    if (pReqQueryAccount)
    {
        qDebug("\tTradeCode [%s]\n", pReqQueryAccount->TradeCode);
        qDebug("\tBankID [%s]\n", pReqQueryAccount->BankID);
        qDebug("\tBankBranchID [%s]\n", pReqQueryAccount->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pReqQueryAccount->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pReqQueryAccount->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pReqQueryAccount->TradeDate);
        qDebug("\tTradeTime [%s]\n", pReqQueryAccount->TradeTime);
        qDebug("\tBankSerial [%s]\n", pReqQueryAccount->BankSerial);
        qDebug("\tTradingDay [%s]\n", pReqQueryAccount->TradingDay);
        qDebug("\tCustomerName [%s]\n", pReqQueryAccount->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pReqQueryAccount->IdentifiedCardNo);
        qDebug("\tBankAccount [%s]\n", pReqQueryAccount->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pReqQueryAccount->BankPassWord);
        qDebug("\tAccountID [%s]\n", pReqQueryAccount->AccountID);
        qDebug("\tPassword [%s]\n", pReqQueryAccount->Password);
        qDebug("\tUserID [%s]\n", pReqQueryAccount->UserID);
        qDebug("\tCurrencyID [%s]\n", pReqQueryAccount->CurrencyID);
        qDebug("\tDigest [%s]\n", pReqQueryAccount->Digest);
        qDebug("\tDeviceID [%s]\n", pReqQueryAccount->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pReqQueryAccount->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pReqQueryAccount->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pReqQueryAccount->OperNo);
        qDebug("\tLongCustomerName [%s]\n", pReqQueryAccount->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pReqQueryAccount->PlateSerial);
        qDebug("\tSessionID [%d]\n", pReqQueryAccount->SessionID);
        qDebug("\tFutureSerial [%d]\n", pReqQueryAccount->FutureSerial);
        qDebug("\tInstallID [%d]\n", pReqQueryAccount->InstallID);
        qDebug("\tRequestID [%d]\n", pReqQueryAccount->RequestID);
        qDebug("\tTID [%d]\n", pReqQueryAccount->TID);
        qDebug("\tLastFragment [%c]\n", pReqQueryAccount->LastFragment);
        qDebug("\tIdCardType [%c]\n", pReqQueryAccount->IdCardType);
        qDebug("\tCustType [%c]\n", pReqQueryAccount->CustType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pReqQueryAccount->VerifyCertNoFlag);
        qDebug("\tBankAccType [%c]\n", pReqQueryAccount->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pReqQueryAccount->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pReqQueryAccount->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pReqQueryAccount->SecuPwdFlag);
    }
    if (pRspInfo)
    {
        qDebug("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        qDebug("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("\tbIsLast [%d]\n", bIsLast);
    qDebug("</OnRspQueryBankAccountMoneyByFuture>\n");
};

void CTraderSpi::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount)
{
    qDebug("<OnRtnOpenAccountByBank>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnOpenAccountByBank(pOpenAccount);
    }
    if (pOpenAccount)
    {
        qDebug("\tTradeCode [%s]\n", pOpenAccount->TradeCode);
        qDebug("\tBankID [%s]\n", pOpenAccount->BankID);
        qDebug("\tBankBranchID [%s]\n", pOpenAccount->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pOpenAccount->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pOpenAccount->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pOpenAccount->TradeDate);
        qDebug("\tTradeTime [%s]\n", pOpenAccount->TradeTime);
        qDebug("\tBankSerial [%s]\n", pOpenAccount->BankSerial);
        qDebug("\tTradingDay [%s]\n", pOpenAccount->TradingDay);
        qDebug("\tCustomerName [%s]\n", pOpenAccount->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pOpenAccount->IdentifiedCardNo);
        qDebug("\tCountryCode [%s]\n", pOpenAccount->CountryCode);
        qDebug("\tAddress [%s]\n", pOpenAccount->Address);
        qDebug("\tZipCode [%s]\n", pOpenAccount->ZipCode);
        qDebug("\tTelephone [%s]\n", pOpenAccount->Telephone);
        qDebug("\tMobilePhone [%s]\n", pOpenAccount->MobilePhone);
        qDebug("\tFax [%s]\n", pOpenAccount->Fax);
        qDebug("\tEMail [%s]\n", pOpenAccount->EMail);
        qDebug("\tBankAccount [%s]\n", pOpenAccount->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pOpenAccount->BankPassWord);
        qDebug("\tAccountID [%s]\n", pOpenAccount->AccountID);
        qDebug("\tPassword [%s]\n", pOpenAccount->Password);
        qDebug("\tCurrencyID [%s]\n", pOpenAccount->CurrencyID);
        qDebug("\tDigest [%s]\n", pOpenAccount->Digest);
        qDebug("\tDeviceID [%s]\n", pOpenAccount->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pOpenAccount->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pOpenAccount->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pOpenAccount->OperNo);
        qDebug("\tUserID [%s]\n", pOpenAccount->UserID);
        qDebug("\tErrorMsg [%s]\n", pOpenAccount->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pOpenAccount->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pOpenAccount->PlateSerial);
        qDebug("\tSessionID [%d]\n", pOpenAccount->SessionID);
        qDebug("\tInstallID [%d]\n", pOpenAccount->InstallID);
        qDebug("\tTID [%d]\n", pOpenAccount->TID);
        qDebug("\tErrorID [%d]\n", pOpenAccount->ErrorID);
        qDebug("\tLastFragment [%c]\n", pOpenAccount->LastFragment);
        qDebug("\tIdCardType [%c]\n", pOpenAccount->IdCardType);
        qDebug("\tGender [%c]\n", pOpenAccount->Gender);
        qDebug("\tCustType [%c]\n", pOpenAccount->CustType);
        qDebug("\tMoneyAccountStatus [%c]\n", pOpenAccount->MoneyAccountStatus);
        qDebug("\tVerifyCertNoFlag [%c]\n", pOpenAccount->VerifyCertNoFlag);
        qDebug("\tCashExchangeCode [%c]\n", pOpenAccount->CashExchangeCode);
        qDebug("\tBankAccType [%c]\n", pOpenAccount->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pOpenAccount->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pOpenAccount->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pOpenAccount->SecuPwdFlag);
    }
    qDebug("</OnRtnOpenAccountByBank>\n");
};
void CTraderSpi::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount)
{
    qDebug("<OnRtnCancelAccountByBank>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnCancelAccountByBank(pCancelAccount);
    }
    if (pCancelAccount)
    {
        qDebug("\tTradeCode [%s]\n", pCancelAccount->TradeCode);
        qDebug("\tBankID [%s]\n", pCancelAccount->BankID);
        qDebug("\tBankBranchID [%s]\n", pCancelAccount->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pCancelAccount->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pCancelAccount->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pCancelAccount->TradeDate);
        qDebug("\tTradeTime [%s]\n", pCancelAccount->TradeTime);
        qDebug("\tBankSerial [%s]\n", pCancelAccount->BankSerial);
        qDebug("\tTradingDay [%s]\n", pCancelAccount->TradingDay);
        qDebug("\tCustomerName [%s]\n", pCancelAccount->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pCancelAccount->IdentifiedCardNo);
        qDebug("\tCountryCode [%s]\n", pCancelAccount->CountryCode);
        qDebug("\tAddress [%s]\n", pCancelAccount->Address);
        qDebug("\tZipCode [%s]\n", pCancelAccount->ZipCode);
        qDebug("\tTelephone [%s]\n", pCancelAccount->Telephone);
        qDebug("\tMobilePhone [%s]\n", pCancelAccount->MobilePhone);
        qDebug("\tFax [%s]\n", pCancelAccount->Fax);
        qDebug("\tEMail [%s]\n", pCancelAccount->EMail);
        qDebug("\tBankAccount [%s]\n", pCancelAccount->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pCancelAccount->BankPassWord);
        qDebug("\tAccountID [%s]\n", pCancelAccount->AccountID);
        qDebug("\tPassword [%s]\n", pCancelAccount->Password);
        qDebug("\tCurrencyID [%s]\n", pCancelAccount->CurrencyID);
        qDebug("\tDigest [%s]\n", pCancelAccount->Digest);
        qDebug("\tDeviceID [%s]\n", pCancelAccount->DeviceID);
        qDebug("\tBrokerIDByBank [%s]\n", pCancelAccount->BrokerIDByBank);
        qDebug("\tBankSecuAcc [%s]\n", pCancelAccount->BankSecuAcc);
        qDebug("\tOperNo [%s]\n", pCancelAccount->OperNo);
        qDebug("\tUserID [%s]\n", pCancelAccount->UserID);
        qDebug("\tErrorMsg [%s]\n", pCancelAccount->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pCancelAccount->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pCancelAccount->PlateSerial);
        qDebug("\tSessionID [%d]\n", pCancelAccount->SessionID);
        qDebug("\tInstallID [%d]\n", pCancelAccount->InstallID);
        qDebug("\tTID [%d]\n", pCancelAccount->TID);
        qDebug("\tErrorID [%d]\n", pCancelAccount->ErrorID);
        qDebug("\tLastFragment [%c]\n", pCancelAccount->LastFragment);
        qDebug("\tIdCardType [%c]\n", pCancelAccount->IdCardType);
        qDebug("\tGender [%c]\n", pCancelAccount->Gender);
        qDebug("\tCustType [%c]\n", pCancelAccount->CustType);
        qDebug("\tMoneyAccountStatus [%c]\n", pCancelAccount->MoneyAccountStatus);
        qDebug("\tVerifyCertNoFlag [%c]\n", pCancelAccount->VerifyCertNoFlag);
        qDebug("\tCashExchangeCode [%c]\n", pCancelAccount->CashExchangeCode);
        qDebug("\tBankAccType [%c]\n", pCancelAccount->BankAccType);
        qDebug("\tBankSecuAccType [%c]\n", pCancelAccount->BankSecuAccType);
        qDebug("\tBankPwdFlag [%c]\n", pCancelAccount->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pCancelAccount->SecuPwdFlag);
    }
    qDebug("</OnRtnCancelAccountByBank>\n");
};
void CTraderSpi::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount)
{
    qDebug("<OnRtnChangeAccountByBank>\n");
    foreach(CThostFtdcTraderSpi* traderSpi, m_SpiList)
    {
        traderSpi->OnRtnChangeAccountByBank(pChangeAccount);
    }
    if (pChangeAccount)
    {
        qDebug("\tTradeCode [%s]\n", pChangeAccount->TradeCode);
        qDebug("\tBankID [%s]\n", pChangeAccount->BankID);
        qDebug("\tBankBranchID [%s]\n", pChangeAccount->BankBranchID);
        qDebug("\tBrokerID [%s]\n", pChangeAccount->BrokerID);
        qDebug("\tBrokerBranchID [%s]\n", pChangeAccount->BrokerBranchID);
        qDebug("\tTradeDate [%s]\n", pChangeAccount->TradeDate);
        qDebug("\tTradeTime [%s]\n", pChangeAccount->TradeTime);
        qDebug("\tBankSerial [%s]\n", pChangeAccount->BankSerial);
        qDebug("\tTradingDay [%s]\n", pChangeAccount->TradingDay);
        qDebug("\tCustomerName [%s]\n", pChangeAccount->CustomerName);
        qDebug("\tIdentifiedCardNo [%s]\n", pChangeAccount->IdentifiedCardNo);
        qDebug("\tCountryCode [%s]\n", pChangeAccount->CountryCode);
        qDebug("\tAddress [%s]\n", pChangeAccount->Address);
        qDebug("\tZipCode [%s]\n", pChangeAccount->ZipCode);
        qDebug("\tTelephone [%s]\n", pChangeAccount->Telephone);
        qDebug("\tMobilePhone [%s]\n", pChangeAccount->MobilePhone);
        qDebug("\tFax [%s]\n", pChangeAccount->Fax);
        qDebug("\tEMail [%s]\n", pChangeAccount->EMail);
        qDebug("\tBankAccount [%s]\n", pChangeAccount->BankAccount);
        qDebug("\tBankPassWord [%s]\n", pChangeAccount->BankPassWord);
        qDebug("\tNewBankAccount [%s]\n", pChangeAccount->NewBankAccount);
        qDebug("\tNewBankPassWord [%s]\n", pChangeAccount->NewBankPassWord);
        qDebug("\tAccountID [%s]\n", pChangeAccount->AccountID);
        qDebug("\tPassword [%s]\n", pChangeAccount->Password);
        qDebug("\tCurrencyID [%s]\n", pChangeAccount->CurrencyID);
        qDebug("\tBrokerIDByBank [%s]\n", pChangeAccount->BrokerIDByBank);
        qDebug("\tDigest [%s]\n", pChangeAccount->Digest);
        qDebug("\tErrorMsg [%s]\n", pChangeAccount->ErrorMsg);
        qDebug("\tLongCustomerName [%s]\n", pChangeAccount->LongCustomerName);
        qDebug("\tPlateSerial [%d]\n", pChangeAccount->PlateSerial);
        qDebug("\tSessionID [%d]\n", pChangeAccount->SessionID);
        qDebug("\tInstallID [%d]\n", pChangeAccount->InstallID);
        qDebug("\tTID [%d]\n", pChangeAccount->TID);
        qDebug("\tErrorID [%d]\n", pChangeAccount->ErrorID);
        qDebug("\tLastFragment [%c]\n", pChangeAccount->LastFragment);
        qDebug("\tIdCardType [%c]\n", pChangeAccount->IdCardType);
        qDebug("\tGender [%c]\n", pChangeAccount->Gender);
        qDebug("\tCustType [%c]\n", pChangeAccount->CustType);
        qDebug("\tMoneyAccountStatus [%c]\n", pChangeAccount->MoneyAccountStatus);
        qDebug("\tBankAccType [%c]\n", pChangeAccount->BankAccType);
        qDebug("\tVerifyCertNoFlag [%c]\n", pChangeAccount->VerifyCertNoFlag);
        qDebug("\tBankPwdFlag [%c]\n", pChangeAccount->BankPwdFlag);
        qDebug("\tSecuPwdFlag [%c]\n", pChangeAccount->SecuPwdFlag);
    }
    qDebug("</OnRtnChangeAccountByBank>\n");
};

