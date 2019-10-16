#include "traderapi.h"

//#include "stdafx.h"
#include <stdio.h>
#include <QDebug>
//#include "define.h"

CThostFtdcTraderApi* CTraderApi::CreateFtdcTraderApi(const char *pszFlowPath /*= ""*/)
{
    return m_pApi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);
}

const char * CTraderApi::GetApiVersion()
{
    return m_pApi->GetApiVersion();
}

//////////////////////////////////////////////////////////////////////////以下可替换模板

void CTraderApi::Release()
{
    qDebug("<Release>\n");
    qDebug("</Release>\n");

    m_pApi->Release();
};

void CTraderApi::Init()
{
    qDebug("<Init>\n");
    qDebug("</Init>\n");

    m_pApi->Init();
};

int CTraderApi::Join()
{
    qDebug("<Join>\n");
    qDebug("</Join>\n");

    return m_pApi->Join();
};

const char *CTraderApi::GetTradingDay()
{
    qDebug("<GetTradingDay>\n");
    qDebug("</GetTradingDay>\n");

    return m_pApi->GetTradingDay();
};

void CTraderApi::RegisterFront(char *pszFrontAddress)
{
    qDebug("<RegisterFront>\n");
    qDebug("\tpszFrontAddress [%s]\n", pszFrontAddress);
    qDebug("</RegisterFront>\n");

    m_pApi->RegisterFront(pszFrontAddress);
}

void CTraderApi::RegisterNameServer(char *pszNsAddress)
{
    qDebug("<RegisterNameServer>\n");
    qDebug("\tpszNsAddress [%s]\n", pszNsAddress);
    qDebug("</RegisterNameServer>\n");

    m_pApi->RegisterNameServer(pszNsAddress);
}

void CTraderApi::RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo)
{
    qDebug("<RegisterFensUserInfo>\n");
    if (pFensUserInfo)
    {
        qDebug("\tBrokerID [%s]\n", pFensUserInfo->BrokerID);
        qDebug("\tUserID [%s]\n", pFensUserInfo->UserID);
        qDebug("\tLoginMode [%c]\n", pFensUserInfo->LoginMode);
    }
    qDebug("</RegisterFensUserInfo>\n");

    m_pApi->RegisterFensUserInfo(pFensUserInfo);
};

void CTraderApi::RegisterSpi(CThostFtdcTraderSpi *pSpi)
{
    qDebug("<RegisterSpi>\n");
    if (pSpi)
    {
    }
    qDebug("</RegisterSpi>\n");

    m_pApi->RegisterSpi(pSpi);
};

void CTraderApi::SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType)
{
    qDebug("<SubscribePrivateTopic>\n");
    qDebug("\tnResumeType [%d]\n", nResumeType);
    qDebug("</SubscribePrivateTopic>\n");

    m_pApi->SubscribePrivateTopic(nResumeType);
}

void CTraderApi::SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType)
{
    qDebug("<SubscribePublicTopic>\n");
    qDebug("\tnResumeType [%d]\n", nResumeType);
    qDebug("</SubscribePublicTopic>\n");

    m_pApi->SubscribePublicTopic(nResumeType);
}

int CTraderApi::ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID)
{
    qDebug("<ReqAuthenticate>\n");
    if (pReqAuthenticateField)
    {
        qDebug("\tBrokerID [%s]\n", pReqAuthenticateField->BrokerID);
        qDebug("\tUserID [%s]\n", pReqAuthenticateField->UserID);
        qDebug("\tUserProductInfo [%s]\n", pReqAuthenticateField->UserProductInfo);
        qDebug("\tAuthCode [%s]\n", pReqAuthenticateField->AuthCode);
        qDebug("\tAppID [%s]\n", pReqAuthenticateField->AppID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqAuthenticate>\n");

    return m_pApi->ReqAuthenticate(pReqAuthenticateField, nRequestID);
}


int CTraderApi::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID)
{
    qDebug("<ReqUserLogin>\n");
    if (pReqUserLoginField)
    {
        qDebug("\tTradingDay [%s]\n", pReqUserLoginField->TradingDay);
        qDebug("\tBrokerID [%s]\n", pReqUserLoginField->BrokerID);
        qDebug("\tUserID [%s]\n", pReqUserLoginField->UserID);
        qDebug("\tPassword [%s]\n", pReqUserLoginField->Password);
        qDebug("\tUserProductInfo [%s]\n", pReqUserLoginField->UserProductInfo);
        qDebug("\tInterfaceProductInfo [%s]\n", pReqUserLoginField->InterfaceProductInfo);
        qDebug("\tProtocolInfo [%s]\n", pReqUserLoginField->ProtocolInfo);
        qDebug("\tMacAddress [%s]\n", pReqUserLoginField->MacAddress);
        qDebug("\tOneTimePassword [%s]\n", pReqUserLoginField->OneTimePassword);
        qDebug("\tClientIPAddress [%s]\n", pReqUserLoginField->ClientIPAddress);
        qDebug("\tLoginRemark [%s]\n", pReqUserLoginField->LoginRemark);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqUserLogin>\n");
    return m_pApi->ReqUserLogin(pReqUserLoginField, nRequestID);
};


int CTraderApi::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
    qDebug("<ReqUserLogout>\n");
    if (pUserLogout)
    {
        qDebug("\tBrokerID [%s]\n", pUserLogout->BrokerID);
        qDebug("\tUserID [%s]\n", pUserLogout->UserID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqUserLogout>\n");

    return m_pApi->ReqUserLogout(pUserLogout, nRequestID);
};


int CTraderApi::ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID)
{
    qDebug("<ReqUserPasswordUpdate>\n");
    if (pUserPasswordUpdate)
    {
        qDebug("\tBrokerID [%s]\n", pUserPasswordUpdate->BrokerID);
        qDebug("\tUserID [%s]\n", pUserPasswordUpdate->UserID);
        qDebug("\tOldPassword [%s]\n", pUserPasswordUpdate->OldPassword);
        qDebug("\tNewPassword [%s]\n", pUserPasswordUpdate->NewPassword);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqUserPasswordUpdate>\n");

    return m_pApi->ReqUserPasswordUpdate(pUserPasswordUpdate, nRequestID);
};


int CTraderApi::ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID)
{
    qDebug("<ReqTradingAccountPasswordUpdate>\n");
    if (pTradingAccountPasswordUpdate)
    {
        qDebug("\tBrokerID [%s]\n", pTradingAccountPasswordUpdate->BrokerID);
        qDebug("\tAccountID [%s]\n", pTradingAccountPasswordUpdate->AccountID);
        qDebug("\tOldPassword [%s]\n", pTradingAccountPasswordUpdate->OldPassword);
        qDebug("\tNewPassword [%s]\n", pTradingAccountPasswordUpdate->NewPassword);
        qDebug("\tCurrencyID [%s]\n", pTradingAccountPasswordUpdate->CurrencyID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqTradingAccountPasswordUpdate>\n");

    return m_pApi->ReqTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate, nRequestID);
};


//int CTraderApi::ReqUserLogin2(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
//{
//	qDebug("<ReqUserLogin2>\n");
//	if (pReqUserLogin)
//	{
//		qDebug("\tTradingDay [%s]\n", pReqUserLogin->TradingDay);
//		qDebug("\tBrokerID [%s]\n", pReqUserLogin->BrokerID);
//		qDebug("\tUserID [%s]\n", pReqUserLogin->UserID);
//		qDebug("\tPassword [%s]\n", pReqUserLogin->Password);
//		qDebug("\tUserProductInfo [%s]\n", pReqUserLogin->UserProductInfo);
//		qDebug("\tInterfaceProductInfo [%s]\n", pReqUserLogin->InterfaceProductInfo);
//		qDebug("\tProtocolInfo [%s]\n", pReqUserLogin->ProtocolInfo);
//		qDebug("\tMacAddress [%s]\n", pReqUserLogin->MacAddress);
//		qDebug("\tOneTimePassword [%s]\n", pReqUserLogin->OneTimePassword);
//		qDebug("\tClientIPAddress [%s]\n", pReqUserLogin->ClientIPAddress);
//		qDebug("\tLoginRemark [%s]\n", pReqUserLogin->LoginRemark);
//	}
//	qDebug("\tnRequestID [%d]\n", nRequestID);
//	qDebug("</ReqUserLogin2>\n");
//
//	return m_pApi->ReqUserLogin2(pReqUserLogin, nRequestID);
//};


//int CTraderApi::ReqUserPasswordUpdate2(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID)
//{
//	qDebug("<ReqUserPasswordUpdate2>\n");
//	if (pUserPasswordUpdate)
//	{
//		qDebug("\tBrokerID [%s]\n", pUserPasswordUpdate->BrokerID);
//		qDebug("\tUserID [%s]\n", pUserPasswordUpdate->UserID);
//		qDebug("\tOldPassword [%s]\n", pUserPasswordUpdate->OldPassword);
//		qDebug("\tNewPassword [%s]\n", pUserPasswordUpdate->NewPassword);
//	}
//	qDebug("\tnRequestID [%d]\n", nRequestID);
//	qDebug("</ReqUserPasswordUpdate2>\n");
//
//	return m_pApi->ReqUserPasswordUpdate2(pUserPasswordUpdate, nRequestID);
//};


int CTraderApi::ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID)
{
    /*qDebug("<ReqOrderInsert>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqOrderInsert>\n");*/

    return m_pApi->ReqOrderInsert(pInputOrder, nRequestID);
};


int CTraderApi::ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID)
{
    qDebug("<ReqParkedOrderInsert>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqParkedOrderInsert>\n");

    return m_pApi->ReqParkedOrderInsert(pParkedOrder, nRequestID);
};


int CTraderApi::ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID)
{
    qDebug("<ReqParkedOrderAction>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqParkedOrderAction>\n");

    return m_pApi->ReqParkedOrderAction(pParkedOrderAction, nRequestID);
};


int CTraderApi::ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID)
{
    qDebug("<ReqOrderAction>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqOrderAction>\n");

    return m_pApi->ReqOrderAction(pInputOrderAction, nRequestID);
};


int CTraderApi::ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID)
{
    qDebug("<ReqQueryMaxOrderVolume>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQueryMaxOrderVolume>\n");

    return m_pApi->ReqQueryMaxOrderVolume(pQueryMaxOrderVolume, nRequestID);
};


int CTraderApi::ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID)
{
    qDebug("<ReqSettlementInfoConfirm>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqSettlementInfoConfirm>\n");

    return m_pApi->ReqSettlementInfoConfirm(pSettlementInfoConfirm, nRequestID);
};


int CTraderApi::ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID)
{
    qDebug("<ReqRemoveParkedOrder>\n");
    if (pRemoveParkedOrder)
    {
        qDebug("\tBrokerID [%s]\n", pRemoveParkedOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pRemoveParkedOrder->InvestorID);
        qDebug("\tParkedOrderID [%s]\n", pRemoveParkedOrder->ParkedOrderID);
        qDebug("\tInvestUnitID [%s]\n", pRemoveParkedOrder->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqRemoveParkedOrder>\n");

    return m_pApi->ReqRemoveParkedOrder(pRemoveParkedOrder, nRequestID);
};


int CTraderApi::ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID)
{
    qDebug("<ReqRemoveParkedOrderAction>\n");
    if (pRemoveParkedOrderAction)
    {
        qDebug("\tBrokerID [%s]\n", pRemoveParkedOrderAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pRemoveParkedOrderAction->InvestorID);
        qDebug("\tParkedOrderActionID [%s]\n", pRemoveParkedOrderAction->ParkedOrderActionID);
        qDebug("\tInvestUnitID [%s]\n", pRemoveParkedOrderAction->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqRemoveParkedOrderAction>\n");

    return m_pApi->ReqRemoveParkedOrderAction(pRemoveParkedOrderAction, nRequestID);
};


int CTraderApi::ReqExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, int nRequestID)
{
    qDebug("<ReqExecOrderInsert>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqExecOrderInsert>\n");

    return m_pApi->ReqExecOrderInsert(pInputExecOrder, nRequestID);
};


int CTraderApi::ReqExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, int nRequestID)
{
    qDebug("<ReqExecOrderAction>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqExecOrderAction>\n");

    return m_pApi->ReqExecOrderAction(pInputExecOrderAction, nRequestID);
};


int CTraderApi::ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID)
{
    /*qDebug("<ReqForQuoteInsert>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqForQuoteInsert>\n");

    return m_pApi->ReqForQuoteInsert(pInputForQuote, nRequestID);*/
    qDebug("<ReqForQuoteInsert>\n"
        "\tBrokerID [%s]\n"
        "\tInvestorID [%s]\n"
        "\tInstrumentID [%s]\n"
        "\tForQuoteRef [%s]\n"
        "\tUserID [%s]\n"
        "\tExchangeID [%s]\n"
        "\tInvestUnitID [%s]\n"
        "\tIPAddress [%s]\n"
        "\tMacAddress [%s]\n"
        "\tnRequestID [%d]\n"
        "</ReqForQuoteInsert>\n",
        pInputForQuote->BrokerID,
        pInputForQuote->InvestorID,
        pInputForQuote->InstrumentID,
        pInputForQuote->InstrumentID,
        pInputForQuote->UserID,
        pInputForQuote->ExchangeID,
        pInputForQuote->InvestUnitID,
        pInputForQuote->IPAddress,
        pInputForQuote->MacAddress,
        nRequestID);

    return m_pApi->ReqForQuoteInsert(pInputForQuote, nRequestID);
};


int CTraderApi::ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID)
{
    qDebug("<ReqQuoteInsert>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQuoteInsert>\n");

    return m_pApi->ReqQuoteInsert(pInputQuote, nRequestID);
};


int CTraderApi::ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID)
{
    qDebug("<ReqQuoteAction>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQuoteAction>\n");

    return m_pApi->ReqQuoteAction(pInputQuoteAction, nRequestID);
};


int CTraderApi::ReqBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, int nRequestID)
{
    qDebug("<ReqBatchOrderAction>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqBatchOrderAction>\n");

    return m_pApi->ReqBatchOrderAction(pInputBatchOrderAction, nRequestID);
};


int CTraderApi::ReqOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, int nRequestID)
{
    qDebug("<ReqOptionSelfCloseInsert>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqOptionSelfCloseInsert>\n");

    return m_pApi->ReqOptionSelfCloseInsert(pInputOptionSelfClose, nRequestID);
};


int CTraderApi::ReqOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, int nRequestID)
{
    qDebug("<ReqOptionSelfCloseAction>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqOptionSelfCloseAction>\n");

    return m_pApi->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, nRequestID);
};


int CTraderApi::ReqCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, int nRequestID)
{
    qDebug("<ReqCombActionInsert>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqCombActionInsert>\n");

    return m_pApi->ReqCombActionInsert(pInputCombAction, nRequestID);
};


int CTraderApi::ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID)
{
    qDebug("<ReqQryOrder>\n");
    if (pQryOrder)
    {
        qDebug("\tBrokerID [%s]\n", pQryOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryOrder->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryOrder->ExchangeID);
        qDebug("\tOrderSysID [%s]\n", pQryOrder->OrderSysID);
        qDebug("\tInsertTimeStart [%s]\n", pQryOrder->InsertTimeStart);
        qDebug("\tInsertTimeEnd [%s]\n", pQryOrder->InsertTimeEnd);
        qDebug("\tInvestUnitID [%s]\n", pQryOrder->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryOrder>\n");

    return m_pApi->ReqQryOrder(pQryOrder, nRequestID);
};


int CTraderApi::ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID)
{
    qDebug("<ReqQryTrade>\n");
    if (pQryTrade)
    {
        qDebug("\tBrokerID [%s]\n", pQryTrade->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryTrade->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryTrade->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryTrade->ExchangeID);
        qDebug("\tTradeID [%s]\n", pQryTrade->TradeID);
        qDebug("\tTradeTimeStart [%s]\n", pQryTrade->TradeTimeStart);
        qDebug("\tTradeTimeEnd [%s]\n", pQryTrade->TradeTimeEnd);
        qDebug("\tInvestUnitID [%s]\n", pQryTrade->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryTrade>\n");

    return m_pApi->ReqQryTrade(pQryTrade, nRequestID);
};


int CTraderApi::ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID)
{
    qDebug("<ReqQryInvestorPosition>\n");
    if (pQryInvestorPosition)
    {
        qDebug("\tBrokerID [%s]\n", pQryInvestorPosition->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryInvestorPosition->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryInvestorPosition->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryInvestorPosition->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQryInvestorPosition->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryInvestorPosition>\n");

    return m_pApi->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
};


int CTraderApi::ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID)
{
    qDebug("<ReqQryTradingAccount>\n");
    if (pQryTradingAccount)
    {
        qDebug("\tBrokerID [%s]\n", pQryTradingAccount->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryTradingAccount->InvestorID);
        qDebug("\tCurrencyID [%s]\n", pQryTradingAccount->CurrencyID);
        qDebug("\tAccountID [%s]\n", pQryTradingAccount->AccountID);
        qDebug("\tBizType [%c]\n", pQryTradingAccount->BizType);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryTradingAccount>\n");

    return m_pApi->ReqQryTradingAccount(pQryTradingAccount, nRequestID);
};


int CTraderApi::ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID)
{
    qDebug("<ReqQryInvestor>\n");
    if (pQryInvestor)
    {
        qDebug("\tBrokerID [%s]\n", pQryInvestor->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryInvestor->InvestorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryInvestor>\n");

    return m_pApi->ReqQryInvestor(pQryInvestor, nRequestID);
};


int CTraderApi::ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID)
{
    qDebug("<ReqQryTradingCode>\n");
    if (pQryTradingCode)
    {
        qDebug("\tBrokerID [%s]\n", pQryTradingCode->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryTradingCode->InvestorID);
        qDebug("\tExchangeID [%s]\n", pQryTradingCode->ExchangeID);
        qDebug("\tClientID [%s]\n", pQryTradingCode->ClientID);
        qDebug("\tInvestUnitID [%s]\n", pQryTradingCode->InvestUnitID);
        qDebug("\tClientIDType [%c]\n", pQryTradingCode->ClientIDType);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryTradingCode>\n");

    return m_pApi->ReqQryTradingCode(pQryTradingCode, nRequestID);
};


int CTraderApi::ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID)
{
    qDebug("<ReqQryInstrumentMarginRate>\n");
    if (pQryInstrumentMarginRate)
    {
        qDebug("\tBrokerID [%s]\n", pQryInstrumentMarginRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryInstrumentMarginRate->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryInstrumentMarginRate->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryInstrumentMarginRate->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQryInstrumentMarginRate->InvestUnitID);
        qDebug("\tHedgeFlag [%c]\n", pQryInstrumentMarginRate->HedgeFlag);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryInstrumentMarginRate>\n");

    return m_pApi->ReqQryInstrumentMarginRate(pQryInstrumentMarginRate, nRequestID);
};


int CTraderApi::ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID)
{
    qDebug("<ReqQryInstrumentCommissionRate>\n");
    if (pQryInstrumentCommissionRate)
    {
        qDebug("\tBrokerID [%s]\n", pQryInstrumentCommissionRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryInstrumentCommissionRate->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryInstrumentCommissionRate->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryInstrumentCommissionRate->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQryInstrumentCommissionRate->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryInstrumentCommissionRate>\n");

    return m_pApi->ReqQryInstrumentCommissionRate(pQryInstrumentCommissionRate, nRequestID);
};


int CTraderApi::ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID)
{
    qDebug("<ReqQryExchange>\n");
    if (pQryExchange)
    {
        qDebug("\tExchangeID [%s]\n", pQryExchange->ExchangeID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryExchange>\n");

    return m_pApi->ReqQryExchange(pQryExchange, nRequestID);
};


int CTraderApi::ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID)
{
    qDebug("<ReqQryProduct>\n");
    if (pQryProduct)
    {
        qDebug("\tProductID [%s]\n", pQryProduct->ProductID);
        qDebug("\tExchangeID [%s]\n", pQryProduct->ExchangeID);
        qDebug("\tProductClass [%c]\n", pQryProduct->ProductClass);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryProduct>\n");

    return m_pApi->ReqQryProduct(pQryProduct, nRequestID);
};


int CTraderApi::ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID)
{
    qDebug("<ReqQryInstrument>\n");
    if (pQryInstrument)
    {
        qDebug("\tInstrumentID [%s]\n", pQryInstrument->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryInstrument->ExchangeID);
        qDebug("\tExchangeInstID [%s]\n", pQryInstrument->ExchangeInstID);
        qDebug("\tProductID [%s]\n", pQryInstrument->ProductID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryInstrument>\n");

    return m_pApi->ReqQryInstrument(pQryInstrument, nRequestID);
};


int CTraderApi::ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID)
{
    qDebug("<ReqQryDepthMarketData>\n");
    if (pQryDepthMarketData)
    {
        qDebug("\tInstrumentID [%s]\n", pQryDepthMarketData->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryDepthMarketData->ExchangeID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryDepthMarketData>\n");

    return m_pApi->ReqQryDepthMarketData(pQryDepthMarketData, nRequestID);
};


int CTraderApi::ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID)
{
    qDebug("<ReqQrySettlementInfo>\n");
    if (pQrySettlementInfo)
    {
        qDebug("\tBrokerID [%s]\n", pQrySettlementInfo->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQrySettlementInfo->InvestorID);
        qDebug("\tTradingDay [%s]\n", pQrySettlementInfo->TradingDay);
        qDebug("\tAccountID [%s]\n", pQrySettlementInfo->AccountID);
        qDebug("\tCurrencyID [%s]\n", pQrySettlementInfo->CurrencyID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQrySettlementInfo>\n");

    return m_pApi->ReqQrySettlementInfo(pQrySettlementInfo, nRequestID);
};


int CTraderApi::ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID)
{
    qDebug("<ReqQryTransferBank>\n");
    if (pQryTransferBank)
    {
        qDebug("\tBankID [%s]\n", pQryTransferBank->BankID);
        qDebug("\tBankBrchID [%s]\n", pQryTransferBank->BankBrchID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryTransferBank>\n");

    return m_pApi->ReqQryTransferBank(pQryTransferBank, nRequestID);
};


int CTraderApi::ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID)
{
    qDebug("<ReqQryInvestorPositionDetail>\n");
    if (pQryInvestorPositionDetail)
    {
        qDebug("\tBrokerID [%s]\n", pQryInvestorPositionDetail->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryInvestorPositionDetail->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryInvestorPositionDetail->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryInvestorPositionDetail->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQryInvestorPositionDetail->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryInvestorPositionDetail>\n");

    return m_pApi->ReqQryInvestorPositionDetail(pQryInvestorPositionDetail, nRequestID);
};


int CTraderApi::ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID)
{
    qDebug("<ReqQryNotice>\n");
    if (pQryNotice)
    {
        qDebug("\tBrokerID [%s]\n", pQryNotice->BrokerID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryNotice>\n");

    return m_pApi->ReqQryNotice(pQryNotice, nRequestID);
};


int CTraderApi::ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID)
{
    qDebug("<ReqQrySettlementInfoConfirm>\n");
    if (pQrySettlementInfoConfirm)
    {
        qDebug("\tBrokerID [%s]\n", pQrySettlementInfoConfirm->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQrySettlementInfoConfirm->InvestorID);
        qDebug("\tAccountID [%s]\n", pQrySettlementInfoConfirm->AccountID);
        qDebug("\tCurrencyID [%s]\n", pQrySettlementInfoConfirm->CurrencyID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQrySettlementInfoConfirm>\n");

    return m_pApi->ReqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, nRequestID);
};


int CTraderApi::ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID)
{
    qDebug("<ReqQryInvestorPositionCombineDetail>\n");
    if (pQryInvestorPositionCombineDetail)
    {
        qDebug("\tBrokerID [%s]\n", pQryInvestorPositionCombineDetail->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryInvestorPositionCombineDetail->InvestorID);
        qDebug("\tCombInstrumentID [%s]\n", pQryInvestorPositionCombineDetail->CombInstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryInvestorPositionCombineDetail->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQryInvestorPositionCombineDetail->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryInvestorPositionCombineDetail>\n");

    return m_pApi->ReqQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail, nRequestID);
};


int CTraderApi::ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey, int nRequestID)
{
    qDebug("<ReqQryCFMMCTradingAccountKey>\n");
    if (pQryCFMMCTradingAccountKey)
    {
        qDebug("\tBrokerID [%s]\n", pQryCFMMCTradingAccountKey->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryCFMMCTradingAccountKey->InvestorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryCFMMCTradingAccountKey>\n");

    return m_pApi->ReqQryCFMMCTradingAccountKey(pQryCFMMCTradingAccountKey, nRequestID);
};


int CTraderApi::ReqQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset, int nRequestID)
{
    qDebug("<ReqQryEWarrantOffset>\n");
    if (pQryEWarrantOffset)
    {
        qDebug("\tBrokerID [%s]\n", pQryEWarrantOffset->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryEWarrantOffset->InvestorID);
        qDebug("\tExchangeID [%s]\n", pQryEWarrantOffset->ExchangeID);
        qDebug("\tInstrumentID [%s]\n", pQryEWarrantOffset->InstrumentID);
        qDebug("\tInvestUnitID [%s]\n", pQryEWarrantOffset->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryEWarrantOffset>\n");

    return m_pApi->ReqQryEWarrantOffset(pQryEWarrantOffset, nRequestID);
};


int CTraderApi::ReqQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin, int nRequestID)
{
    qDebug("<ReqQryInvestorProductGroupMargin>\n");
    if (pQryInvestorProductGroupMargin)
    {
        qDebug("\tBrokerID [%s]\n", pQryInvestorProductGroupMargin->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryInvestorProductGroupMargin->InvestorID);
        qDebug("\tProductGroupID [%s]\n", pQryInvestorProductGroupMargin->ProductGroupID);
        qDebug("\tExchangeID [%s]\n", pQryInvestorProductGroupMargin->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQryInvestorProductGroupMargin->InvestUnitID);
        qDebug("\tHedgeFlag [%c]\n", pQryInvestorProductGroupMargin->HedgeFlag);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryInvestorProductGroupMargin>\n");

    return m_pApi->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, nRequestID);
};


int CTraderApi::ReqQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField *pQryExchangeMarginRate, int nRequestID)
{
    qDebug("<ReqQryExchangeMarginRate>\n");
    if (pQryExchangeMarginRate)
    {
        qDebug("\tBrokerID [%s]\n", pQryExchangeMarginRate->BrokerID);
        qDebug("\tInstrumentID [%s]\n", pQryExchangeMarginRate->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryExchangeMarginRate->ExchangeID);
        qDebug("\tHedgeFlag [%c]\n", pQryExchangeMarginRate->HedgeFlag);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryExchangeMarginRate>\n");

    return m_pApi->ReqQryExchangeMarginRate(pQryExchangeMarginRate, nRequestID);
};


int CTraderApi::ReqQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField *pQryExchangeMarginRateAdjust, int nRequestID)
{
    qDebug("<ReqQryExchangeMarginRateAdjust>\n");
    if (pQryExchangeMarginRateAdjust)
    {
        qDebug("\tBrokerID [%s]\n", pQryExchangeMarginRateAdjust->BrokerID);
        qDebug("\tInstrumentID [%s]\n", pQryExchangeMarginRateAdjust->InstrumentID);
        qDebug("\tHedgeFlag [%c]\n", pQryExchangeMarginRateAdjust->HedgeFlag);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryExchangeMarginRateAdjust>\n");

    return m_pApi->ReqQryExchangeMarginRateAdjust(pQryExchangeMarginRateAdjust, nRequestID);
};


int CTraderApi::ReqQryExchangeRate(CThostFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID)
{
    qDebug("<ReqQryExchangeRate>\n");
    if (pQryExchangeRate)
    {
        qDebug("\tBrokerID [%s]\n", pQryExchangeRate->BrokerID);
        qDebug("\tFromCurrencyID [%s]\n", pQryExchangeRate->FromCurrencyID);
        qDebug("\tToCurrencyID [%s]\n", pQryExchangeRate->ToCurrencyID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryExchangeRate>\n");

    return m_pApi->ReqQryExchangeRate(pQryExchangeRate, nRequestID);
};


int CTraderApi::ReqQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap, int nRequestID)
{
    qDebug("<ReqQrySecAgentACIDMap>\n");
    if (pQrySecAgentACIDMap)
    {
        qDebug("\tBrokerID [%s]\n", pQrySecAgentACIDMap->BrokerID);
        qDebug("\tUserID [%s]\n", pQrySecAgentACIDMap->UserID);
        qDebug("\tAccountID [%s]\n", pQrySecAgentACIDMap->AccountID);
        qDebug("\tCurrencyID [%s]\n", pQrySecAgentACIDMap->CurrencyID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQrySecAgentACIDMap>\n");

    return m_pApi->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, nRequestID);
};


int CTraderApi::ReqQryProductExchRate(CThostFtdcQryProductExchRateField *pQryProductExchRate, int nRequestID)
{
    qDebug("<ReqQryProductExchRate>\n");
    if (pQryProductExchRate)
    {
        qDebug("\tProductID [%s]\n", pQryProductExchRate->ProductID);
        qDebug("\tExchangeID [%s]\n", pQryProductExchRate->ExchangeID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryProductExchRate>\n");

    return m_pApi->ReqQryProductExchRate(pQryProductExchRate, nRequestID);
};


int CTraderApi::ReqQryProductGroup(CThostFtdcQryProductGroupField *pQryProductGroup, int nRequestID)
{
    qDebug("<ReqQryProductGroup>\n");
    if (pQryProductGroup)
    {
        qDebug("\tProductID [%s]\n", pQryProductGroup->ProductID);
        qDebug("\tExchangeID [%s]\n", pQryProductGroup->ExchangeID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryProductGroup>\n");

    return m_pApi->ReqQryProductGroup(pQryProductGroup, nRequestID);
};


int CTraderApi::ReqQryMMInstrumentCommissionRate(CThostFtdcQryMMInstrumentCommissionRateField *pQryMMInstrumentCommissionRate, int nRequestID)
{
    qDebug("<ReqQryMMInstrumentCommissionRate>\n");
    if (pQryMMInstrumentCommissionRate)
    {
        qDebug("\tBrokerID [%s]\n", pQryMMInstrumentCommissionRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryMMInstrumentCommissionRate->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryMMInstrumentCommissionRate->InstrumentID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryMMInstrumentCommissionRate>\n");

    return m_pApi->ReqQryMMInstrumentCommissionRate(pQryMMInstrumentCommissionRate, nRequestID);
};


int CTraderApi::ReqQryMMOptionInstrCommRate(CThostFtdcQryMMOptionInstrCommRateField *pQryMMOptionInstrCommRate, int nRequestID)
{
    qDebug("<ReqQryMMOptionInstrCommRate>\n");
    if (pQryMMOptionInstrCommRate)
    {
        qDebug("\tBrokerID [%s]\n", pQryMMOptionInstrCommRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryMMOptionInstrCommRate->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryMMOptionInstrCommRate->InstrumentID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryMMOptionInstrCommRate>\n");

    return m_pApi->ReqQryMMOptionInstrCommRate(pQryMMOptionInstrCommRate, nRequestID);
};


int CTraderApi::ReqQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField *pQryInstrumentOrderCommRate, int nRequestID)
{
    qDebug("<ReqQryInstrumentOrderCommRate>\n");
    if (pQryInstrumentOrderCommRate)
    {
        qDebug("\tBrokerID [%s]\n", pQryInstrumentOrderCommRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryInstrumentOrderCommRate->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryInstrumentOrderCommRate->InstrumentID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryInstrumentOrderCommRate>\n");

    return m_pApi->ReqQryInstrumentOrderCommRate(pQryInstrumentOrderCommRate, nRequestID);
};


int CTraderApi::ReqQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost, int nRequestID)
{
    qDebug("<ReqQryOptionInstrTradeCost>\n");
    if (pQryOptionInstrTradeCost)
    {
        qDebug("\tBrokerID [%s]\n", pQryOptionInstrTradeCost->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryOptionInstrTradeCost->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryOptionInstrTradeCost->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryOptionInstrTradeCost->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQryOptionInstrTradeCost->InvestUnitID);
        qDebug("\tHedgeFlag [%c]\n", pQryOptionInstrTradeCost->HedgeFlag);
        qDebug("\tInputPrice [%.8lf]\n", pQryOptionInstrTradeCost->InputPrice);
        qDebug("\tUnderlyingPrice [%.8lf]\n", pQryOptionInstrTradeCost->UnderlyingPrice);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryOptionInstrTradeCost>\n");

    return m_pApi->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, nRequestID);
};


int CTraderApi::ReqQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField *pQryOptionInstrCommRate, int nRequestID)
{
    qDebug("<ReqQryOptionInstrCommRate>\n");
    if (pQryOptionInstrCommRate)
    {
        qDebug("\tBrokerID [%s]\n", pQryOptionInstrCommRate->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryOptionInstrCommRate->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryOptionInstrCommRate->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryOptionInstrCommRate->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQryOptionInstrCommRate->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryOptionInstrCommRate>\n");

    return m_pApi->ReqQryOptionInstrCommRate(pQryOptionInstrCommRate, nRequestID);
};


int CTraderApi::ReqQryExecOrder(CThostFtdcQryExecOrderField *pQryExecOrder, int nRequestID)
{
    qDebug("<ReqQryExecOrder>\n");
    if (pQryExecOrder)
    {
        qDebug("\tBrokerID [%s]\n", pQryExecOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryExecOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryExecOrder->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryExecOrder->ExchangeID);
        qDebug("\tExecOrderSysID [%s]\n", pQryExecOrder->ExecOrderSysID);
        qDebug("\tInsertTimeStart [%s]\n", pQryExecOrder->InsertTimeStart);
        qDebug("\tInsertTimeEnd [%s]\n", pQryExecOrder->InsertTimeEnd);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryExecOrder>\n");

    return m_pApi->ReqQryExecOrder(pQryExecOrder, nRequestID);
};


int CTraderApi::ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID)
{
    qDebug("<ReqQryForQuote>\n");
    if (pQryForQuote)
    {
        qDebug("\tBrokerID [%s]\n", pQryForQuote->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryForQuote->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryForQuote->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryForQuote->ExchangeID);
        qDebug("\tInsertTimeStart [%s]\n", pQryForQuote->InsertTimeStart);
        qDebug("\tInsertTimeEnd [%s]\n", pQryForQuote->InsertTimeEnd);
        qDebug("\tInvestUnitID [%s]\n", pQryForQuote->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryForQuote>\n");

    return m_pApi->ReqQryForQuote(pQryForQuote, nRequestID);
};


int CTraderApi::ReqQryQuote(CThostFtdcQryQuoteField *pQryQuote, int nRequestID)
{
    qDebug("<ReqQryQuote>\n");
    if (pQryQuote)
    {
        qDebug("\tBrokerID [%s]\n", pQryQuote->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryQuote->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryQuote->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryQuote->ExchangeID);
        qDebug("\tQuoteSysID [%s]\n", pQryQuote->QuoteSysID);
        qDebug("\tInsertTimeStart [%s]\n", pQryQuote->InsertTimeStart);
        qDebug("\tInsertTimeEnd [%s]\n", pQryQuote->InsertTimeEnd);
        qDebug("\tInvestUnitID [%s]\n", pQryQuote->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryQuote>\n");

    return m_pApi->ReqQryQuote(pQryQuote, nRequestID);
};


int CTraderApi::ReqQryOptionSelfClose(CThostFtdcQryOptionSelfCloseField *pQryOptionSelfClose, int nRequestID)
{
    qDebug("<ReqQryOptionSelfClose>\n");
    if (pQryOptionSelfClose)
    {
        qDebug("\tBrokerID [%s]\n", pQryOptionSelfClose->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryOptionSelfClose->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryOptionSelfClose->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryOptionSelfClose->ExchangeID);
        qDebug("\tOptionSelfCloseSysID [%s]\n", pQryOptionSelfClose->OptionSelfCloseSysID);
        qDebug("\tInsertTimeStart [%s]\n", pQryOptionSelfClose->InsertTimeStart);
        qDebug("\tInsertTimeEnd [%s]\n", pQryOptionSelfClose->InsertTimeEnd);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryOptionSelfClose>\n");

    return m_pApi->ReqQryOptionSelfClose(pQryOptionSelfClose, nRequestID);
};


int CTraderApi::ReqQryInvestUnit(CThostFtdcQryInvestUnitField *pQryInvestUnit, int nRequestID)
{
    qDebug("<ReqQryInvestUnit>\n");
    if (pQryInvestUnit)
    {
        qDebug("\tBrokerID [%s]\n", pQryInvestUnit->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryInvestUnit->InvestorID);
        qDebug("\tInvestUnitID [%s]\n", pQryInvestUnit->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryInvestUnit>\n");

    return m_pApi->ReqQryInvestUnit(pQryInvestUnit, nRequestID);
};


int CTraderApi::ReqQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard, int nRequestID)
{
    qDebug("<ReqQryCombInstrumentGuard>\n");
    if (pQryCombInstrumentGuard)
    {
        qDebug("\tBrokerID [%s]\n", pQryCombInstrumentGuard->BrokerID);
        qDebug("\tInstrumentID [%s]\n", pQryCombInstrumentGuard->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryCombInstrumentGuard->ExchangeID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryCombInstrumentGuard>\n");

    return m_pApi->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, nRequestID);
};


int CTraderApi::ReqQryCombAction(CThostFtdcQryCombActionField *pQryCombAction, int nRequestID)
{
    qDebug("<ReqQryCombAction>\n");
    if (pQryCombAction)
    {
        qDebug("\tBrokerID [%s]\n", pQryCombAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryCombAction->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryCombAction->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryCombAction->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQryCombAction->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryCombAction>\n");

    return m_pApi->ReqQryCombAction(pQryCombAction, nRequestID);
};


int CTraderApi::ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID)
{
    qDebug("<ReqQryTransferSerial>\n");
    if (pQryTransferSerial)
    {
        qDebug("\tBrokerID [%s]\n", pQryTransferSerial->BrokerID);
        qDebug("\tAccountID [%s]\n", pQryTransferSerial->AccountID);
        qDebug("\tBankID [%s]\n", pQryTransferSerial->BankID);
        qDebug("\tCurrencyID [%s]\n", pQryTransferSerial->CurrencyID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryTransferSerial>\n");

    return m_pApi->ReqQryTransferSerial(pQryTransferSerial, nRequestID);
};


int CTraderApi::ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID)
{
    qDebug("<ReqQryAccountregister>\n");
    if (pQryAccountregister)
    {
        qDebug("\tBrokerID [%s]\n", pQryAccountregister->BrokerID);
        qDebug("\tAccountID [%s]\n", pQryAccountregister->AccountID);
        qDebug("\tBankID [%s]\n", pQryAccountregister->BankID);
        qDebug("\tBankBranchID [%s]\n", pQryAccountregister->BankBranchID);
        qDebug("\tCurrencyID [%s]\n", pQryAccountregister->CurrencyID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryAccountregister>\n");

    return m_pApi->ReqQryAccountregister(pQryAccountregister, nRequestID);
};


int CTraderApi::ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID)
{
    qDebug("<ReqQryContractBank>\n");
    if (pQryContractBank)
    {
        qDebug("\tBrokerID [%s]\n", pQryContractBank->BrokerID);
        qDebug("\tBankID [%s]\n", pQryContractBank->BankID);
        qDebug("\tBankBrchID [%s]\n", pQryContractBank->BankBrchID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryContractBank>\n");

    return m_pApi->ReqQryContractBank(pQryContractBank, nRequestID);
};


int CTraderApi::ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID)
{
    qDebug("<ReqQryParkedOrder>\n");
    if (pQryParkedOrder)
    {
        qDebug("\tBrokerID [%s]\n", pQryParkedOrder->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryParkedOrder->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryParkedOrder->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryParkedOrder->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQryParkedOrder->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryParkedOrder>\n");

    return m_pApi->ReqQryParkedOrder(pQryParkedOrder, nRequestID);
};


int CTraderApi::ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID)
{
    qDebug("<ReqQryParkedOrderAction>\n");
    if (pQryParkedOrderAction)
    {
        qDebug("\tBrokerID [%s]\n", pQryParkedOrderAction->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryParkedOrderAction->InvestorID);
        qDebug("\tInstrumentID [%s]\n", pQryParkedOrderAction->InstrumentID);
        qDebug("\tExchangeID [%s]\n", pQryParkedOrderAction->ExchangeID);
        qDebug("\tInvestUnitID [%s]\n", pQryParkedOrderAction->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryParkedOrderAction>\n");

    return m_pApi->ReqQryParkedOrderAction(pQryParkedOrderAction, nRequestID);
};


int CTraderApi::ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID)
{
    qDebug("<ReqQryTradingNotice>\n");
    if (pQryTradingNotice)
    {
        qDebug("\tBrokerID [%s]\n", pQryTradingNotice->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryTradingNotice->InvestorID);
        qDebug("\tInvestUnitID [%s]\n", pQryTradingNotice->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryTradingNotice>\n");

    return m_pApi->ReqQryTradingNotice(pQryTradingNotice, nRequestID);
};


int CTraderApi::ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID)
{
    qDebug("<ReqQryBrokerTradingParams>\n");
    if (pQryBrokerTradingParams)
    {
        qDebug("\tBrokerID [%s]\n", pQryBrokerTradingParams->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryBrokerTradingParams->InvestorID);
        qDebug("\tCurrencyID [%s]\n", pQryBrokerTradingParams->CurrencyID);
        qDebug("\tAccountID [%s]\n", pQryBrokerTradingParams->AccountID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryBrokerTradingParams>\n");

    return m_pApi->ReqQryBrokerTradingParams(pQryBrokerTradingParams, nRequestID);
};


int CTraderApi::ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField *pQryBrokerTradingAlgos, int nRequestID)
{
    qDebug("<ReqQryBrokerTradingAlgos>\n");
    if (pQryBrokerTradingAlgos)
    {
        qDebug("\tBrokerID [%s]\n", pQryBrokerTradingAlgos->BrokerID);
        qDebug("\tExchangeID [%s]\n", pQryBrokerTradingAlgos->ExchangeID);
        qDebug("\tInstrumentID [%s]\n", pQryBrokerTradingAlgos->InstrumentID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQryBrokerTradingAlgos>\n");

    return m_pApi->ReqQryBrokerTradingAlgos(pQryBrokerTradingAlgos, nRequestID);
};


int CTraderApi::ReqQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, int nRequestID)
{
    qDebug("<ReqQueryCFMMCTradingAccountToken>\n");
    if (pQueryCFMMCTradingAccountToken)
    {
        qDebug("\tBrokerID [%s]\n", pQueryCFMMCTradingAccountToken->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQueryCFMMCTradingAccountToken->InvestorID);
        qDebug("\tInvestUnitID [%s]\n", pQueryCFMMCTradingAccountToken->InvestUnitID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQueryCFMMCTradingAccountToken>\n");

    return m_pApi->ReqQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken, nRequestID);
};


int CTraderApi::ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID)
{
    qDebug("<ReqFromBankToFutureByFuture>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqFromBankToFutureByFuture>\n");

    return m_pApi->ReqFromBankToFutureByFuture(pReqTransfer, nRequestID);
};


int CTraderApi::ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID)
{
    qDebug("<ReqFromFutureToBankByFuture>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqFromFutureToBankByFuture>\n");

    return m_pApi->ReqFromFutureToBankByFuture(pReqTransfer, nRequestID);
};


int CTraderApi::ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, int nRequestID)
{
    qDebug("<ReqQueryBankAccountMoneyByFuture>\n");
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
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQueryBankAccountMoneyByFuture>\n");

    return m_pApi->ReqQueryBankAccountMoneyByFuture(pReqQueryAccount, nRequestID);
}

///请求查询资金账户
int CTraderApi::ReqQrySecAgentTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID)
{
    qDebug("<ReqQrySecAgentTradingAccount>\n");
    if (pQryTradingAccount)
    {
        qDebug("\tBrokerID [%s]\n", pQryTradingAccount->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQryTradingAccount->InvestorID);
        qDebug("\tCurrencyID [%s]\n", pQryTradingAccount->CurrencyID);
        qDebug("\tBizType [%s]\n", pQryTradingAccount->BizType);
        qDebug("\tAccountID [%s]\n", pQryTradingAccount->AccountID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQrySecAgentTradingAccount>\n");

    return m_pApi->ReqQrySecAgentTradingAccount(pQryTradingAccount, nRequestID);
};

///请求查询二级代理商资金校验模式
int CTraderApi::ReqQrySecAgentCheckMode(CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode, int nRequestID)
{
    qDebug("<ReqQrySecAgentCheckMode>\n");
    if (pQrySecAgentCheckMode)
    {
        qDebug("\tBrokerID [%s]\n", pQrySecAgentCheckMode->BrokerID);
        qDebug("\tInvestorID [%s]\n", pQrySecAgentCheckMode->InvestorID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQrySecAgentCheckMode>\n");

    return m_pApi->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, nRequestID);
};

///注册用户终端信息，用于中继服务器多连接模式
///需要在终端认证成功后，用户登录前调用该接口
int CTraderApi::RegisterUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo)
{
    qDebug("<RegisterUserSystemInfo>\n");
    if (pUserSystemInfo)
    {
        qDebug("\tBrokerID [%s]\n", pUserSystemInfo->BrokerID);
        qDebug("\tUserID [%s]\n", pUserSystemInfo->UserID);
        qDebug("\tClientSystemInfoLen [%d]\n", pUserSystemInfo->ClientSystemInfoLen);
        qDebug("\tClientSystemInfo [%s]\n", pUserSystemInfo->ClientSystemInfo);
        qDebug("\tClientPublicIP [%s]\n", pUserSystemInfo->ClientPublicIP);
        qDebug("\tClientIPPort [%d]\n", pUserSystemInfo->ClientIPPort);
        qDebug("\tClientLoginTime [%s]\n", pUserSystemInfo->ClientLoginTime);
        qDebug("\tClientAppID [%s]\n", pUserSystemInfo->ClientAppID);
    }
    qDebug("</RegisterUserSystemInfo>\n");

    return m_pApi->RegisterUserSystemInfo(pUserSystemInfo);
}

///上报用户终端信息，用于中继服务器操作员登录模式
///操作员登录后，可以多次调用该接口上报客户信息
int CTraderApi::SubmitUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo)
{
    qDebug("<SubmitUserSystemInfo>\n");
    if (pUserSystemInfo)
    {
        qDebug("\tBrokerID [%s]\n", pUserSystemInfo->BrokerID);
        qDebug("\tUserID [%s]\n", pUserSystemInfo->UserID);
        qDebug("\tClientSystemInfoLen [%d]\n", pUserSystemInfo->ClientSystemInfoLen);
        qDebug("\tClientSystemInfo [%s]\n", pUserSystemInfo->ClientSystemInfo);
        qDebug("\tClientPublicIP [%s]\n", pUserSystemInfo->ClientPublicIP);
        qDebug("\tClientIPPort [%d]\n", pUserSystemInfo->ClientIPPort);
        qDebug("\tClientLoginTime [%s]\n", pUserSystemInfo->ClientLoginTime);
        qDebug("\tClientAppID [%s]\n", pUserSystemInfo->ClientAppID);
    }
    qDebug("</SubmitUserSystemInfo>\n");

    return m_pApi->RegisterUserSystemInfo(pUserSystemInfo);
}

///查询用户当前支持的认证模式
int CTraderApi::ReqUserAuthMethod(CThostFtdcReqUserAuthMethodField *pReqUserAuthMethod, int nRequestID)
{
    qDebug("<ReqUserAuthMethod>\n");
    if (pReqUserAuthMethod)
    {
        qDebug("\tTradingDay [%s]\n", pReqUserAuthMethod->TradingDay);
        qDebug("\tBrokerID [%s]\n", pReqUserAuthMethod->BrokerID);
        qDebug("\tUserID [%s]\n", pReqUserAuthMethod->UserID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqUserAuthMethod>\n");

    return m_pApi->ReqUserAuthMethod(pReqUserAuthMethod, nRequestID);
}

///用户发出获取图形验证码请求
int CTraderApi::ReqGenUserCaptcha(CThostFtdcReqGenUserCaptchaField *pReqGenUserCaptcha, int nRequestID)
{
    qDebug("<ReqGenUserCaptcha>\n");
    if (pReqGenUserCaptcha)
    {
        qDebug("\tTradingDay [%s]\n", pReqGenUserCaptcha->TradingDay);
        qDebug("\tBrokerID [%s]\n", pReqGenUserCaptcha->BrokerID);
        qDebug("\tUserID [%s]\n", pReqGenUserCaptcha->UserID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqGenUserCaptcha>\n");

    return m_pApi->ReqGenUserCaptcha(pReqGenUserCaptcha, nRequestID);
}

///用户发出获取短信验证码请求
int CTraderApi::ReqGenUserText(CThostFtdcReqGenUserTextField *pReqGenUserText, int nRequestID)
{
    qDebug("<ReqGenUserText>\n");
    if (pReqGenUserText)
    {
        qDebug("\tTradingDay [%s]\n", pReqGenUserText->TradingDay);
        qDebug("\tBrokerID [%s]\n", pReqGenUserText->BrokerID);
        qDebug("\tUserID [%s]\n", pReqGenUserText->UserID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqGenUserText>\n");

    return m_pApi->ReqGenUserText(pReqGenUserText, nRequestID);
}

///用户发出带有图片验证码的登陆请求
int CTraderApi::ReqUserLoginWithCaptcha(CThostFtdcReqUserLoginWithCaptchaField *pReqUserLoginWithCaptcha, int nRequestID)
{
    qDebug("<ReqUserLoginWithCaptcha>\n");
    if (pReqUserLoginWithCaptcha)
    {
        qDebug("\tTradingDay [%s]\n", pReqUserLoginWithCaptcha->TradingDay);
        qDebug("\tBrokerID [%s]\n", pReqUserLoginWithCaptcha->BrokerID);
        qDebug("\tUserID [%s]\n", pReqUserLoginWithCaptcha->UserID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqUserLoginWithCaptcha>\n");

    return m_pApi->ReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha, nRequestID);
}

///用户发出带有短信验证码的登陆请求
int CTraderApi::ReqUserLoginWithText(CThostFtdcReqUserLoginWithTextField *pReqUserLoginWithText, int nRequestID)
{
    qDebug("<ReqUserLoginWithText>\n");
    if (pReqUserLoginWithText)
    {
        qDebug("\tTradingDay [%s]\n", pReqUserLoginWithText->TradingDay);
        qDebug("\tBrokerID [%s]\n", pReqUserLoginWithText->BrokerID);
        qDebug("\tUserID [%s]\n", pReqUserLoginWithText->UserID);
        qDebug("\tPassword [%s]\n", pReqUserLoginWithText->Password);
        qDebug("\tUserProductInfo [%s]\n", pReqUserLoginWithText->UserProductInfo);
        qDebug("\tInterfaceProductInfo [%s]\n", pReqUserLoginWithText->InterfaceProductInfo);
        qDebug("\tProtocolInfo [%s]\n", pReqUserLoginWithText->ProtocolInfo);
        qDebug("\tMacAddress [%s]\n", pReqUserLoginWithText->MacAddress);
        qDebug("\tClientIPAddress [%s]\n", pReqUserLoginWithText->ClientIPAddress);
        qDebug("\tLoginRemark [%s]\n", pReqUserLoginWithText->LoginRemark);
        qDebug("\tText [%s]\n", pReqUserLoginWithText->Text);
        qDebug("\tClientIPPort [%d]\n", pReqUserLoginWithText->ClientIPPort);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqUserLoginWithText>\n");

    return m_pApi->ReqUserLoginWithText(pReqUserLoginWithText, nRequestID);
}

///用户发出带有动态口令的登陆请求
int CTraderApi::ReqUserLoginWithOTP(CThostFtdcReqUserLoginWithOTPField *pReqUserLoginWithOTP, int nRequestID)
{
    qDebug("<ReqUserLoginWithOTP>\n");
    if (pReqUserLoginWithOTP)
    {
        qDebug("\tTradingDay [%s]\n", pReqUserLoginWithOTP->TradingDay);
        qDebug("\tBrokerID [%s]\n", pReqUserLoginWithOTP->BrokerID);
        qDebug("\tUserID [%s]\n", pReqUserLoginWithOTP->UserID);
        qDebug("\tPassword [%s]\n", pReqUserLoginWithOTP->Password);
        qDebug("\tUserProductInfo [%s]\n", pReqUserLoginWithOTP->UserProductInfo);
        qDebug("\tInterfaceProductInfo [%s]\n", pReqUserLoginWithOTP->InterfaceProductInfo);
        qDebug("\tProtocolInfo [%s]\n", pReqUserLoginWithOTP->ProtocolInfo);
        qDebug("\tMacAddress [%s]\n", pReqUserLoginWithOTP->MacAddress);
        qDebug("\tClientIPAddress [%s]\n", pReqUserLoginWithOTP->ClientIPAddress);
        qDebug("\tLoginRemark [%s]\n", pReqUserLoginWithOTP->LoginRemark);
        qDebug("\tOTPPassword [%s]\n", pReqUserLoginWithOTP->OTPPassword);
        qDebug("\tClientIPPort [%d]\n", pReqUserLoginWithOTP->ClientIPPort);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqUserLoginWithOTP>\n");

    return m_pApi->ReqUserLoginWithOTP(pReqUserLoginWithOTP, nRequestID);
}

///请求查询二级代理商信息
int CTraderApi::ReqQrySecAgentTradeInfo(CThostFtdcQrySecAgentTradeInfoField *pQrySecAgentTradeInfo, int nRequestID)
{
    qDebug("<ReqQrySecAgentTradeInfo>\n");
    if (pQrySecAgentTradeInfo)
    {
        qDebug("\tBrokerID [%s]\n", pQrySecAgentTradeInfo->BrokerID);
        qDebug("\tBrokerSecAgentID [%s]\n", pQrySecAgentTradeInfo->BrokerSecAgentID);
    }
    qDebug("\tnRequestID [%d]\n", nRequestID);
    qDebug("</ReqQrySecAgentTradeInfo>\n");

    return m_pApi->ReqQrySecAgentTradeInfo(pQrySecAgentTradeInfo, nRequestID);
}
