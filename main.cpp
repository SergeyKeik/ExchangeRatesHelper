#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.resize(1280, 720);
    window.setWindowTitle("Курсы валют");
    window.show();
    window.setWindowIcon(QIcon("D:/Programming/Sem2/Lab2/Lab2Gui2/icon.png"));
    const int resultCode = app.exec();
    return resultCode;
}
