#include "logindialog.h"
#include "ui_logindialog.h"
#include "traderspi.h"
#include <QtDebug>
#include "common.h"

using std::string;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    m_TradeSpi->UnReisterSpi(this);
    delete ui;
}

void LoginDialog::setTradeApi(CTraderApi *TradeApi, CTraderSpi *ATradeSpi){
    m_tradeApi = TradeApi;
    m_TradeSpi = ATradeSpi;
    m_TradeSpi->RegisterSpi(this);
}

void LoginDialog::OnFrontConnected(){
    Authenticate();
}
void LoginDialog::OnFrontDisconnected(int nReason){

}
void LoginDialog::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    if(pRspAuthenticateField){
        if (pRspInfo->ErrorID == 0){

            ui->lbl_status->setText("认证:" +QString::fromLocal8Bit(pRspInfo->ErrorMsg));
            UserLogin();
        }else {

            ui->lbl_status->setText("认证:" +QString::fromLocal8Bit(pRspInfo->ErrorMsg));
        }

    }
}

void LoginDialog::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast){
    if (pRspUserLogin && pRspInfo){
        if(pRspInfo->ErrorID == 0){
            //this->accept();
             ui->lbl_status->setText("登陆:" +QString::fromLocal8Bit(pRspInfo->ErrorMsg));
        }else{
             ui->lbl_status->setText("登陆:" +QString::fromLocal8Bit(pRspInfo->ErrorMsg));

        }
    }
}

int LoginDialog::UserLogin(){
   qDebug() << "用户登陆" << endl;

   CThostFtdcReqUserLoginField reqUserLogin;
   memset(&reqUserLogin, 0, sizeof(reqUserLogin));

   QString sUserid = ui->edt_user->text();
   QString sPassWord = ui->edt_password->text();

   strcpy_s(reqUserLogin.BrokerID, CTP_BrokerID);
   strcpy_s(reqUserLogin.UserID, sUserid.toStdString().c_str());
   strcpy_s(reqUserLogin.Password, sPassWord.toStdString().c_str());
   return m_tradeApi->ReqUserLogin(&reqUserLogin, 1);
}

int LoginDialog::Authenticate(){
    CThostFtdcReqAuthenticateField field;
    memset(&field, 0, sizeof(field));
    QString sUserid = ui->edt_user->text();
    QString sPassWord = ui->edt_password->text();
    strcpy_s(field.BrokerID, CTP_BrokerID);
    strcpy_s(field.UserID, sUserid.toStdString().c_str());
    strcpy_s(field.AppID, CTP_APPID);
    strcpy_s(field.AuthCode, CTP_AUTHCODE);
    return m_tradeApi->ReqAuthenticate(&field, 2);
}

void LoginDialog::on_but_login_clicked()
{
    //this->setResult(QDialog::Accepted);
   qDebug() << m_tradeApi;
   qDebug() << m_tradeApi->GetApiVersion();
   if (m_TradeSpi->Status == LSDisconnected){
       m_tradeApi->RegisterFront(const_cast<char *>(CTP_FrontAddr));
       m_tradeApi->Init();
   }else{
        Authenticate();
   }

   Sleep(3000);


       //
       if (m_TradeSpi->Status == LSLogin_successful){
           this->accept();

       }else if ((m_TradeSpi->Status == LSDisconnected) || (m_TradeSpi->Status == LSAuthenticate_failed) || (m_TradeSpi->Status == LSLogin_failed)){



   }







}
