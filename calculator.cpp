#include "calculator.h"

#include <QGridLayout>
#include <QToolButton>
#include <QDebug>
#include <QtMath>
#include <QRadioButton>
//#include <QButtonGroup>
#include <QGroupBox>

#include <mybutton.h>


Calculator::Calculator() {
    m_display_up   = new QLineEdit();
    m_display_down = new QLineEdit();
    m_sign         = new QLabel();
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    m_display_down->setText("0");
    m_display_up->setReadOnly(true);
    m_display_down->setReadOnly(true);

    m_display_up->setAlignment(Qt::AlignRight);
    m_display_down->setAlignment(Qt::AlignRight);
    m_sign->setAlignment(Qt::AlignRight);

    m_display_up->setMaxLength(15);
    m_display_down->setMaxLength(15);

    QFont font = m_display_up->font();
    font.setPointSize(font.pointSize() + 15);
    m_display_up->setFont(font);
    m_display_down->setFont(font);
    m_sign->setFont(font);

    //Создание кнопок

    for (int i = 0; i < 10; ++i)
        m_digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));

    MyButton *pointButton = createButton(".", SLOT(pointClicked()));
    //MyButton *changeSignButton = createButton(m_change_sign, SLOT(changesSignClicked()));

    MyButton *clearButton     = createButton("CE", SLOT(clear()));
    MyButton *clearALLButton  = createButton("C",  SLOT(clearALL()));

    MyButton *divisionButton = createButton(m_division_sign, SLOT(doubleOperatorClicked()));
    MyButton *timesButton    = createButton(m_times_sign,    SLOT(doubleOperatorClicked()));
    MyButton *minusButton    = createButton(m_minus_sign,    SLOT(doubleOperatorClicked()));
    MyButton *plusButton     = createButton(m_plus_sign,     SLOT(doubleOperatorClicked()));

    MyButton *sqrtButton       = createButton(m_sqrt_sign,       SLOT(unaryOperatorClicked()));
    //MyButton *powerButton    = createButton(m_power_sign,      SLOT(unaryOperatorClicked()));
    MyButton *reciprocalButton = createButton(m_reciprocal_sign, SLOT(unaryOperatorClicked()));

    MyButton *equalButton = createButton("=", SLOT(equalClicked()));


    mainLayout->addWidget(m_display_up,   0, 0, 1, 5);
    mainLayout->addWidget(m_sign,         1, 0, 1, 5);
    mainLayout->addWidget(m_display_down, 2, 0, 1, 5);
    mainLayout->addWidget(clearALLButton, 3, 3, 1, 1);
    mainLayout->addWidget(clearButton,    3, 4, 1, 1);

    for (int i = 1; i < 10; ++i) {
        int row = ((9 - i) / 3) + 4;
        int column = ((i - 1) % 3);
        mainLayout->addWidget(m_digitButtons[i], row, column, 1, 1);
    }

    mainLayout->addWidget(m_digitButtons[0], 7, 0, 1, 2);
    mainLayout->addWidget(pointButton, 7, 2);
    //mainLayout->addWidget(changeSignButton, 7, 3);

    mainLayout->addWidget(divisionButton, 4, 3);
    mainLayout->addWidget(timesButton,    5, 3);
    mainLayout->addWidget(minusButton,    6, 3);
    mainLayout->addWidget(plusButton,     7, 3);

    mainLayout->addWidget(sqrtButton,       4, 4);
    //mainLayout->addWidget(powerButton, 5, 4);
    mainLayout->addWidget(reciprocalButton, 5, 4);
    mainLayout->addWidget(equalButton,      6, 4, 2, 1);

    //радиокнопки
    QRadioButton *standardModeButton = new QRadioButton(tr("Standard"));
    QRadioButton *engineeringModeButton = new QRadioButton(tr("Engineering"));
    QGroupBox *modeGroupBox = new QGroupBox();

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(standardModeButton);
    vBoxLayout->addWidget(engineeringModeButton);
    modeGroupBox->setLayout(vBoxLayout);
    standardModeButton->setChecked(true);

    mainLayout->addWidget(modeGroupBox, 3, 0, 1, 3);

    connect(standardModeButton, &QRadioButton::toggled, this, &Calculator::setStandardMode);
    connect(engineeringModeButton, &QRadioButton::toggled, this, &Calculator::setEngineeringMode);


    setLayout(mainLayout);

    setWindowTitle("Calculator");

}

MyButton *Calculator::createButton(const QString &text, const char *member)
{
    MyButton* btn = new MyButton(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}

void Calculator::digitClicked() {
    MyButton *btn = (MyButton*) sender();
    int digit = btn->text().toUInt();

    if (m_display_down->text() == "0") {
        m_display_down->clear();
        m_display_up->clear();
    }

    m_display_down->setText(m_display_down->text() + QString::number(digit));
}

void Calculator::unaryOperatorClicked() {
    MyButton *btn = (MyButton*) sender();
    QString operation = btn->text();
    double operand = m_display_down->text().toDouble();
    double result = 0.0;

    if (operation == m_sqrt_sign) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    } else if (operation == m_reciprocal_sign) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    m_display_down->setText(QString::number(result));
}

void Calculator::doubleOperatorClicked() {
    MyButton *btn = (MyButton*) sender();
    QString operation = btn->text();
    double operand = m_display_down->text().toDouble();

    if (m_display_down->text() == "0")
        return;

    m_sign->setText(operation);

    if (m_display_down->text() == "")
        return;

    m_display_down->clear();

    if (!m_pending_operation.isEmpty()) {
        if(!calculate(operand, m_pending_operation)) {
            abortOperation();
            return;
        }
        m_pending_operation.clear();
    } else
        m_display_up->setText(QString::number(operand));

    m_pending_operation = operation;
}

void Calculator::equalClicked() {
    double operand = m_display_down->text().toDouble();
    if (!m_pending_operation.isEmpty()) {
        if(!calculate(operand, m_pending_operation)) {
            abortOperation();
            return;
        }
        m_pending_operation.clear();
    }
    m_display_down->setText(m_display_up->text());
    m_display_up->clear();
    m_sign->clear();
}

void Calculator::pointClicked() {
    if (!m_display_down->text().contains(('.')))
        m_display_down->setText(m_display_down->text() + '.');
}

//void Calculator::changeSignClicked() {}

void Calculator::clearALL() {
    m_display_down->setText("0");
    m_display_up->clear();
    m_sign->clear();
    m_pending_operation.clear();
}

void Calculator::clear() {
    m_display_down->setText("0");
}

void Calculator::abortOperation() {
    m_display_up->setText("***");
    m_display_down->setText("***");
}

void Calculator::setStandardMode() {}
void Calculator::setEngineeringMode() {}

bool Calculator::calculate(double operand, const QString &operation)
{
    double tmp_total = m_display_up->text().toDouble();

    if (operation == m_plus_sign)
        tmp_total += operand;
    else if (operation == m_minus_sign)
        tmp_total -= operand;
    else if (operation == m_times_sign)
        tmp_total *= operand;
    else if (operation == m_division_sign) {
        if (operand == 0.0)
            return false;
        tmp_total /= operand;
    }
    m_display_up->setText(QString::number(tmp_total));
    return true;
}
