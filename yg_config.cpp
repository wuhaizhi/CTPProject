#include "yg_config.h"
#include <QMessageBox>
#include <QFile>
#include<QTextCodec>

#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif

void YGConfig::LoadConfig(){

    QFile aFile(YGConfigFileName);
    if (!aFile.exists()){
        QMessageBox::critical(NULL, "错误", "配置文件不存在！", QMessageBox::Yes, QMessageBox::Yes);
    }
    m_configIni = new QSettings(YGConfigFileName, QSettings::IniFormat);
    m_configIni->setIniCodec(QTextCodec::codecForName("GB2312"));
}

//YGConfig::YGConfig(){
//    this->LoadConfig();
//}

QString YGConfig::getInOrder() {

    QString ss;
    ss = m_configIni->value(YGOrder_In, "").toString();
    return ss;
}

int YGConfig::getRequestID() {
	int ss;
	ss = m_configIni->value(YGCTP_RequestID, 0).toInt();
	return ss;
}

int YGConfig::getTradeType()
{
	int ss;
	ss = m_configIni->value(YGTradeType, 1).toInt();
	return ss;
}

QString YGConfig::getYGL8()
{
	return m_configIni->value(YGOrder_L8, "").toString();
}

QString YGConfig::getYG01()
{
	return m_configIni->value(YGOrder_01, "").toString();
}

QString YGConfig::getTitle()
{
	QString ss;
	ss = m_configIni->value(YGOrder_Title, "").toString();
	return ss;
}

QString YGConfig::getAccountDir()
{
	QString ss;
	ss = m_configIni->value(YGOrder_AccountDir, "data\\").toString();
	return ss;
}

void YGConfig::setRequestID(int AValue) {
	m_configIni->setValue(YGCTP_RequestID, AValue);
}

void YGConfig::setTradeType(int Avalue)
{
	m_configIni->setValue(YGTradeType, Avalue);
}

QString YGConfig::PassDecrypt(QString APass)
{

std:string ss = APass.toStdString();
	std::string newpass = "";
	for each (char s in ss)
	{
		char ts;

		switch (s) {
		case '5':ts = '0'; break;
		case '6':ts = '1'; break;
		case '7':ts = '2'; break;
		case '8':ts = '3'; break;
		case '9':ts = '4'; break;
		case '0':ts = '5'; break;
		case '1':ts = '6'; break;
		case '2':ts = '7'; break;
		case '3':ts = '8'; break;
		case '4':ts = '9'; break;
		case 'n':ts = 'a'; break;
		case 'o':ts = 'b'; break;
		case 'p':ts = 'c'; break;
		case 'q':ts = 'd'; break;
		case 'r':ts = 'e'; break;
		case 's':ts = 'f'; break;
		case 't':ts = 'g'; break;
		case 'u':ts = 'h'; break;
		case 'v':ts = 'i'; break;
		case 'w':ts = 'j'; break;
		case 'x':ts = 'k'; break;
		case 'y':ts = 'l'; break;
		case 'z':ts = 'm'; break;
		case 'a':ts = 'n'; break;
		case 'b':ts = 'o'; break;
		case 'c':ts = 'p'; break;
		case 'd':ts = 'q'; break;
		case 'e':ts = 'r'; break;
		case 'f':ts = 's'; break;
		case 'g':ts = 't'; break;
		case 'h':ts = 'u'; break;
		case 'i':ts = 'v'; break;
		case 'j':ts = 'w'; break;
		case 'k':ts = 'x'; break;
		case 'l':ts = 'y'; break;
		case 'm':ts = 'z'; break;
		default:
			ts = s; break;
		}

		newpass += ts;
	}

	return QString::fromStdString(newpass);
}

QString YGConfig::PassEncryption(QString APass)
{
std:string ss = APass.toStdString();
	std::string newpass = "";
	for each (char s in ss)
	{
		char ts;

		switch (s) {
		case '0':ts = '5'; break;
		case '1':ts = '6'; break;
		case '2':ts = '7'; break;
		case '3':ts = '8'; break;
		case '4':ts = '9'; break;
		case '5':ts = '0'; break;
		case '6':ts = '1'; break;
		case '7':ts = '2'; break;
		case '8':ts = '3'; break;
		case '9':ts = '4'; break;
		case 'a':ts = 'n'; break;
		case 'b':ts = 'o'; break;
		case 'c':ts = 'p'; break;
		case 'd':ts = 'q'; break;
		case 'e':ts = 'r'; break;
		case 'f':ts = 's'; break;
		case 'g':ts = 't'; break;
		case 'h':ts = 'u'; break;
		case 'i':ts = 'v'; break;
		case 'j':ts = 'w'; break;
		case 'k':ts = 'x'; break;
		case 'l':ts = 'y'; break;
		case 'm':ts = 'z'; break;
		case 'n':ts = 'a'; break;
		case 'o':ts = 'b'; break;
		case 'p':ts = 'c'; break;
		case 'q':ts = 'd'; break;
		case 'r':ts = 'e'; break;
		case 's':ts = 'f'; break;
		case 't':ts = 'g'; break;
		case 'u':ts = 'h'; break;
		case 'v':ts = 'i'; break;
		case 'w':ts = 'j'; break;
		case 'x':ts = 'k'; break;
		case 'y':ts = 'l'; break;
		case 'z':ts = 'm'; break;
		default:
			ts = s; break;
		}

		newpass += ts;
	}

	return QString::fromStdString(newpass);
}

void YGConfig::setYGL8(QString AValue)
{
	m_configIni->setValue(YGOrder_L8, AValue);
}

void YGConfig::setYG01(QString AValue)
{
	m_configIni->setValue(YGOrder_01, AValue);
}

void YGConfig::setInOrder(QString AValue)
{
    m_configIni->setValue(YGOrder_In, AValue);
}

QString YGConfig::getAmount()
{
    return m_configIni->value(YGOrder_Amount, "").toString();
}

void YGConfig::setAmount(QString AValue)
{
    m_configIni->setValue(YGOrder_Amount, AValue);
}

QString YGConfig::getOutOrder()
{

    QString ss;
    ss = m_configIni->value(YGOrder_Out, "").toString();
    return ss;
}

void YGConfig::setOutOrder(QString AValue)
{
    m_configIni->setValue(YGOrder_Out, AValue);
}

QString YGConfig::getFrontAddr()
{
    QString ss;
    ss = m_configIni->value(YGCTP_FrontAddr, "").toString();
    return ss;
}

void YGConfig::setFrontAddr(QString AValue)
{
m_configIni->setValue(YGCTP_FrontAddr, AValue);
}


QString YGConfig::getFrontMdAddr()
{
    QString ss;
    ss = m_configIni->value(YGCTP_FrontMdAddr, "").toString();
    return ss;
}

void YGConfig::setFrontMdAddr(QString AValue)
{
  m_configIni->setValue(YGCTP_FrontMdAddr, AValue);
}

QString YGConfig::getBrokerID()
{
    QString ss;
    ss = m_configIni->value(YGCTP_BrokerID, "").toString();
    return ss;
}

void YGConfig::setBrokerID(QString AValue)
{
    m_configIni->setValue(YGCTP_BrokerID, AValue);
}

QString YGConfig::getUserID()
{
    QString ss;
    ss = m_configIni->value(YGCTP_UserID, "").toString();
    return ss;
}

void YGConfig::setUserID(QString AValue)
{
    m_configIni->setValue(YGCTP_UserID, AValue);
}

QString YGConfig::getPassword()
{
    QString ss;
    ss = m_configIni->value(YGCTP_Password, "").toString();

	ss = PassDecrypt(ss);
    return ss;
}

void YGConfig::setPassword(QString AValue)
{

	QString spass = PassEncryption(AValue);
    m_configIni->setValue(YGCTP_Password, spass);
}

QString YGConfig::getAppID()
{
    return  m_configIni->value(YGCTP_AppID, "").toString();
}

void YGConfig::setAppID(QString AValue)
{
    m_configIni->setValue(YGCTP_AppID,AValue);
}

QString YGConfig::getAuthCode()
{
    return m_configIni->value(YGCTP_AuthCode, "").toString();
}

void YGConfig::setAuthCode(QString AValue)
{
    m_configIni->setValue(YGCTP_AuthCode,AValue);
}
