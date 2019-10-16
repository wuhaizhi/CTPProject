#include "main.h"
#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

#include <QDebug>
#include <QDir>


int main(int argc, char *argv[])
{

    CTraderApi *C_TradeApi = new CTraderApi();
    CTraderSpi *C_TradeSpi= new CTraderSpi();
    qDebug() << C_TradeApi;
    QDir* aDir = new QDir();
    if (!aDir->exists(".\\flow"))
    {
        aDir->mkdir(".\\flow");
    }
    C_TradeApi->CreateFtdcTraderApi(".\\flow");
    C_TradeApi->RegisterSpi(C_TradeSpi);
    C_TradeApi->SubscribePublicTopic(THOST_TERT_QUICK);
    C_TradeApi->SubscribePrivateTopic(THOST_TERT_QUICK);

    QApplication a(argc, argv);
    MainWindow w;
    w.setTradeApi(C_TradeApi,C_TradeSpi);


   //Init_TraderA();

    LoginDialog* dlgTableSize = new LoginDialog();
    dlgTableSize->setTradeApi(C_TradeApi,C_TradeSpi);
    Qt::WindowFlags    flags = dlgTableSize->windowFlags();
    dlgTableSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint); //设置对话框固定大小

    dlgTableSize->setWindowTitle("设置基本信息");


    int ret=dlgTableSize->exec();

    if (ret==QDialog::Accepted)
    {
       w.show();
       return a.exec();
    }else {
        a.exit();
    }
}
