#ifndef YG_CONFIG_H
#define YG_CONFIG_H
#include <string>
#include<qsettings.h>
#include<qstring.h>

using namespace std;

constexpr auto YGOrder_In = "Order/InOrder";
constexpr auto YGOrder_Out = "Order/OutOrder";

constexpr auto YGOrder_Amount = "Order/Amount";
constexpr auto YGOrder_AccountDir = "Order/AccountDir";
constexpr auto YGOrder_Title = "Order/Title";


constexpr auto YGCTP_FrontAddr = "CTP/FrontAddr";
constexpr auto YGCTP_FrontMdAddr = "CTP/FrontMdAddr";
constexpr auto YGCTP_BrokerID = "CTP/BrokerID";
constexpr auto YGCTP_UserID = "CTP/UserID";
constexpr auto YGCTP_Password = "CTP/Password";
constexpr auto YGCTP_AppID = "CTP/AppID";
constexpr auto YGCTP_AuthCode = "CTP/AuthCode";
constexpr auto YGCTP_RequestID = "CTP/RequestID";

//当月连和正月连
//当月
constexpr auto YGOrder_L8 = "Order/YGL8";
//下月
constexpr auto YGOrder_01 = "Order/YG01";

//高频1 低频2
constexpr auto YGTradeType = "Order/YGTradeType";

constexpr auto YGConfigFileName = "SysConfig.ini";





class YGConfig {

private:
    QSettings* m_configIni;

    void LoadConfig();

public:
    YGConfig(){
        LoadConfig();
    }
    ~YGConfig() { }

    QString getInOrder();
    QString getOutOrder();
    QString getFrontAddr();
    QString getFrontMdAddr();
    QString getBrokerID();
    QString getUserID();
    QString getPassword();
    QString getAppID();
    QString getAuthCode();
	int getRequestID();
	int getTradeType();

	QString getYGL8();
	QString getYG01();

	QString getTitle();

	QString getAccountDir();

	QString getAmount();

    void setInOrder(QString AValue);
    void setOutOrder(QString AValue);
    void setFrontAddr(QString AValue);
    void setFrontMdAddr(QString AValue);
    void setBrokerID(QString AValue);
    void setUserID(QString AValue);
    void setPassword(QString AValue);
    void setAppID(QString AValue);
    void setAuthCode(QString AValue);
    void setAmount(QString AValue);

	void setRequestID(int AValue);

	void setTradeType(int Avalue);

	QString PassDecrypt(QString APass);
	QString PassEncryption(QString APass);

	void setYGL8(QString AValue);
	void setYG01(QString AValue);

};


#endif // YG_CONFIG_H
