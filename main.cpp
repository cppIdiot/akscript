#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setQuitOnLastWindowClosed(true);
    QApplication::quitOnLastWindowClosed();

    MainWindow *w = new MainWindow;

    w->show();

    return a.exec();
}
