#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitClicked();
    void operatorClicked();
    void equalsClicked();
    void clearClicked();

private:
    QLineEdit *display;
    QPushButton *createButton(const QString &text, const char *member);
    void calculateResult();

    QString firstValue;
    QString currentInput;
    QString pendingOperator;
};

#endif // CALCULATOR_H
