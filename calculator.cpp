#include "calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), firstValue(""), currentInput(""), pendingOperator("")
{
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(display, 0, 0, 1, 4);

    //Creates the array of buttons for the calculator
    const char *buttonTexts[5][4] = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", ".", "=", "+"},
        {"C", "", "", ""}
    };

    //this will connect each button on the arrray to one of the 'Clicked' functions
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 4; ++col) {
            QPushButton *button;
            if(strcmp(buttonTexts[row][col], "") != 0) {
                //this will create the = button and connects the equals clicked function to it. When the button is pressed
                //the equalsClicked function will be called
                if (strcmp(buttonTexts[row][col], "=") == 0) {
                    button = createButton(buttonTexts[row][col], SLOT(equalsClicked()));
                    button->setStyleSheet("background-color: orange;");
                //Same logic as above, this will create a C button to clear the display and
                //will call the clearClicked function
                } else if (strcmp(buttonTexts[row][col], "C") == 0) {
                    button = createButton(buttonTexts[row][col], SLOT(clearClicked()));
                    button->setStyleSheet("background-color: red; color: white;");
                }
                //If the button is a digit from 0-9 then call the digitClicked function
                else if (strcmp(buttonTexts[row][col], "0") >= 0 && strcmp(buttonTexts[row][col], "9") <= 0) {
                    button = createButton(buttonTexts[row][col], SLOT(digitClicked()));
                } else {
                    button = createButton(buttonTexts[row][col], SLOT(operatorClicked()));
                    if (col == 3) {
                        button->setStyleSheet("background-color: orange;");
                    }
                }
                layout->addWidget(button, row + 1, col);
            }
        }
    }

    setLayout(layout);
}

Calculator::~Calculator() {}

//Function that creates button
QPushButton *Calculator::createButton(const QString &text, const char *member) {
    QPushButton *button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}


void Calculator::digitClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString digit = clickedButton->text();
    //if the current input is 0 and the button that is clicked is not a decimal point
    //replace the number 0 with the digit
    if (currentInput == "0" && digit != ".") {
        currentInput = digit;
    } else {
        //otherwise append it to the current digit
        currentInput += digit;
    }
    //displays the result to the screen
    display->setText(currentInput);
}

//Same logic as above. This is called when one of the operator buttons is clicked
void Calculator::operatorClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString clickedOperator = clickedButton->text();

    //If the current input has a value and the pending operator has a value we can enter this statement
    if (!currentInput.isEmpty() && !pendingOperator.isEmpty()) {
        //Perform the calculation
        equalsClicked();
        //The first value is now the result of that previous calculation
        firstValue = currentInput;
        //The pending operator is now the operator that was last clicked
        pendingOperator = clickedOperator;
        //Set the current input to blank
        currentInput = "";
      //otherwise if we have a current input but we did not click an operator
    } else if (!currentInput.isEmpty()) {
        //Set the fist value to the current input
        firstValue = currentInput;
        //set the pending operator to the one that was clicked
        pendingOperator = clickedOperator;
        //set the current input back to blank
        currentInput = "";
     //If we have no current input or first value set the pending operator to the clicked operator
    } else if (!firstValue.isEmpty()) {
        pendingOperator = clickedOperator;
    }
}


//Same logic as above, this is called when the equal button is clicked
void Calculator::equalsClicked() {
    //Checks if there is a pending operator and a first value which is needed to complete an operation
    if (!pendingOperator.isEmpty() && !firstValue.isEmpty()) {
        double result = 0.0;
        double secondValue = currentInput.toDouble();
        //Checks to see which operator is the pending operator and then it performs the calculation
        if (pendingOperator == "+") {
            result = firstValue.toDouble() + secondValue;
        } else if (pendingOperator == "-") {
            result = firstValue.toDouble() - secondValue;
        } else if (pendingOperator == "*") {
            result = firstValue.toDouble() * secondValue;
        } else if (pendingOperator == "/") {
            if (secondValue != 0.0) {
                result = firstValue.toDouble() / secondValue;
            } else {
                display->setText("Error: Division by zero");
                return;
            }
        }
        //Converts the result into a string and stores it in current input
        currentInput = QString::number(result);
        //Displays current input into set Text
        display->setText(currentInput);
        //Clears the values for the first Value and pendingOperator
        firstValue = "";
        pendingOperator = "";
    }
}

//This function simply resets all the values
void Calculator::clearClicked() {
    firstValue = "";
    currentInput = "";
    pendingOperator = "";
    display->setText("0");
}
