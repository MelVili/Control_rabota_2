#include <QApplication>
#include <iostream>
#include "mainwindow.h"

// Обработчик сообщений: выводит в консоль и дублирует в окно Qt UI
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    Q_UNUSED(context);
    std::cout << msg.toLocal8Bit().constData() << std::endl;
    MainWindow::logOutput(msg);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    qInstallMessageHandler(customMessageHandler);

    MainWindow w;
    w.show();

    return a.exec();
}