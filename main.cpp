#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    LoginDialog *lg = new LoginDialog();
    Qt::WindowFlags    flags=lg->windowFlags();
    lg->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);

    int ret=lg->exec();

    if (ret==QDialog::Accepted)
    {
       w.show();
       return a.exec();
    }else {
        a.exit();
    }
}
