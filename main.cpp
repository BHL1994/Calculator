#include <QApplication>
#include "calculator.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Calculator calculator;
    calculator.setWindowTitle("Simple Calculator");
    calculator.resize(400, 500); // Setting a larger size for the calculator window
    calculator.show();

    return app.exec();
}
