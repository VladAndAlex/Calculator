#include "calculator.h"

#include <QToolButton>
#include <QDebug>
#include <QtMath>
#include <QPushButton>
#include <mybutton.h>


Calculator::Calculator() {

    mainWidget = new QWidget();
    mainLayout = new QGridLayout();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);
    
    m_display_up   = new QLineEdit();
    m_display_down = new QLineEdit();
    m_sign         = new QLabel();

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

    //Создание стандартных кнопок

    for (int i = 0; i < 10; ++i)
        m_digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));

    pointButton = createButton(".", SLOT(pointClicked()));

    clearButton    = createButton("CE", SLOT(clear()));
    clearALLButton = createButton("C",  SLOT(clearALL()));

    divisionButton = createButton(m_division_sign, SLOT(doubleOperatorClicked()));
    timesButton    = createButton(m_timem_sign,    SLOT(doubleOperatorClicked()));
    minusButton    = createButton(m_minum_sign,    SLOT(doubleOperatorClicked()));
    plusButton     = createButton(m_plum_sign,     SLOT(doubleOperatorClicked()));

    sqrtButton       = createButton(m_sqrt_sign,       SLOT(unaryOperatorClicked()));
    reciprocalButton = createButton(m_reciprocal_sign, SLOT(unaryOperatorClicked()));

    equalButton = createButton("=", SLOT(equalClicked()));


    mainLayout->addWidget(m_display_up,   0, 0, 1, 9);
    mainLayout->addWidget(m_sign,         1, 0, 1, 9);
    mainLayout->addWidget(m_display_down, 2, 0, 1, 9);
    mainLayout->addWidget(clearALLButton, 3, 7, 1, 1);
    mainLayout->addWidget(clearButton,    3, 8, 1, 1);

    for (int i = 1; i < 10; ++i) {
        int row = ((9 - i) / 3) + 4;
        int column = ((i - 1) % 3) + 4;
        mainLayout->addWidget(m_digitButtons[i], row, column, 1, 1);
    }

    mainLayout->addWidget(m_digitButtons[0], 7, 5, 1, 2);
    mainLayout->addWidget(pointButton, 7, 4);

    mainLayout->addWidget(divisionButton, 4, 7);
    mainLayout->addWidget(timesButton,    5, 7);
    mainLayout->addWidget(minusButton,    6, 7);
    mainLayout->addWidget(plusButton,     7, 7);

    mainLayout->addWidget(sqrtButton,       4, 8);
    mainLayout->addWidget(reciprocalButton, 5, 8);
    mainLayout->addWidget(equalButton,      6, 8, 2, 1);

    //создание инженерных кнопок
    sinhButton     = createButton("sinh",   SLOT(unaryOperatorClicked()));
    sinButton      = createButton("sin",    SLOT(unaryOperatorClicked()));
    expButton      = createButton("exp",    SLOT(unaryOperatorClicked()));
    power_2_Button = createButton(m_power_2,SLOT(unaryOperatorClicked()));
    coshButton     = createButton("cosh",   SLOT(unaryOperatorClicked()));
    cosButton      =  createButton("cos",   SLOT(unaryOperatorClicked()));
    lnButton       = createButton("ln",     SLOT(unaryOperatorClicked()));
    power_3_Button = createButton(m_power_3,SLOT(unaryOperatorClicked()));
    tanhButton     = createButton("tanh",   SLOT(unaryOperatorClicked()));
    tanButton      = createButton("tan",    SLOT(unaryOperatorClicked()));
    logButton      = createButton(m_log,    SLOT(doubleOperatorClicked()));
    power_y_Button = createButton(m_power_y,     SLOT(doubleOperatorClicked()));
    factButton     = createButton("n!",     SLOT(unaryOperatorClicked()));
    piButton       = createButton("pi",     SLOT(unaryOperatorClicked()));
    cuberootButton = createButton("x^(1/3)", SLOT(unaryOperatorClicked()));
    yrootButton    = createButton(m_power_reverse_y, SLOT(doubleOperatorClicked()));

    mainLayout->addWidget(sinhButton, 4, 0);
    mainLayout->addWidget(sinButton, 4, 1);
    mainLayout->addWidget(expButton, 4, 2);
    mainLayout->addWidget(power_2_Button, 4, 3);
    mainLayout->addWidget(coshButton, 5, 0);
    mainLayout->addWidget(cosButton, 5, 1);
    mainLayout->addWidget(lnButton, 5, 2);
    mainLayout->addWidget(power_3_Button, 5, 3);
    mainLayout->addWidget(tanhButton, 6, 0);
    mainLayout->addWidget(tanButton, 6, 1);
    mainLayout->addWidget(logButton, 6, 2);
    mainLayout->addWidget(power_y_Button, 6, 3);
    mainLayout->addWidget(factButton, 7, 0);
    mainLayout->addWidget(piButton, 7, 1);
    mainLayout->addWidget(cuberootButton, 7, 2);
    mainLayout->addWidget(yrootButton, 7, 3);

    //делаем дополнительные кнопки невидимыми
    sinhButton->setVisible(false);
    sinButton->setVisible(false);
    expButton->setVisible(false);
    power_2_Button->setVisible(false);
    coshButton->setVisible(false);
    cosButton->setVisible(false);
    lnButton->setVisible(false);
    power_3_Button->setVisible(false);
    tanhButton->setVisible(false);
    tanButton->setVisible(false);
    logButton->setVisible(false);
    power_y_Button->setVisible(false);
    factButton->setVisible(false);
    piButton->setVisible(false);
    cuberootButton->setVisible(false);
    yrootButton->setVisible(false);

    //радиокнопки
    standardModeButton = new QRadioButton(tr("Standard"));
    QRadioButton *engineeringModeButton = new QRadioButton(tr("Engineering"));
    modeGroupBox = new QGroupBox();

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(standardModeButton);
    vBoxLayout->addWidget(engineeringModeButton);
    modeGroupBox->setLayout(vBoxLayout);
    modeGroupBox->setFlat(true);
    standardModeButton->setChecked(true);

    connect(standardModeButton, &QRadioButton::toggled, this, &Calculator::setStandardMode);

    mainLayout->addWidget(modeGroupBox, 3, 0, 1, 7);


    //кнопка смены режима
    QPushButton* themeButton = new QPushButton("light", this);
    qApp->setStyleSheet(lightTheme);
    mainLayout->addWidget(themeButton, 3, 6, 1, 1);

    // Подключение сигнала нажатия кнопки к слоту
    connect(themeButton, &QPushButton::clicked, this, [this, themeButton](){
        if(themeButton->text() == "light") {
            themeButton->setText("dark");
            qApp->setStyleSheet(darkTheme); // предполагая, что darkTheme - это переменная, доступная в этом контексте
        }
        else {
            themeButton->setText("light");
            qApp->setStyleSheet(lightTheme);
        }
    });


    setWindowTitle("Standard Calculator");

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
    }
    else if (operation == m_reciprocal_sign) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    else if (operation == "sinh")
        result = std::sinh(operand);

    else if (operation == "sin")
        result = std::sin(operand);

    else if (operation == "exp")
        result = std::exp(operand);

    else if (operation == m_power_2)
        result = operand * operand;

    else if (operation == "cosh")
        result = std::cosh(operand);

    else if (operation == "cos")
        result = std::cos(operand);

    else if (operation == "ln") {
        if (operand <= 0) {
            abortOperation();
            return;
        }
        result = std::log(operand);
    }
    else if (operation == m_power_3)
        result = operand * operand * operand;

    else if (operation == "tanh")
        result = std::tanh(operand);

    else if (operation == "tan")
        result = std::tan(operand);

    else if (operation == "n!") {
        result = 1;
        for (int i = 1; i <= operand; ++i)
            result *= i;
    }
    else if (operation == "pi")
        result = 3.141592653589793238462643383279502884L;

    else if (operation == "x^(1/3)")
        result = std::pow(operand, 1.0/3);

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

void Calculator::setStandardMode(bool checked) {
    sinhButton->setVisible(!checked);
    sinButton->setVisible(!checked);
    expButton->setVisible(!checked);
    power_2_Button->setVisible(!checked);
    coshButton->setVisible(!checked);
    cosButton->setVisible(!checked);
    lnButton->setVisible(!checked);
    power_3_Button->setVisible(!checked);
    tanhButton->setVisible(!checked);
    tanButton->setVisible(!checked);
    logButton->setVisible(!checked);
    power_y_Button->setVisible(!checked);
    factButton->setVisible(!checked);
    piButton->setVisible(!checked);
    cuberootButton->setVisible(!checked);
    yrootButton->setVisible(!checked);

    if (checked)
        setWindowTitle("Standard Calculator");
    else
        setWindowTitle("Engineer Calculator");

}



bool Calculator::calculate(double operand, const QString &operation)
{
    double tmp_total = m_display_up->text().toDouble();

    if (operation == m_plum_sign)
        tmp_total += operand;

    else if (operation == m_minum_sign)
        tmp_total -= operand;

    else if (operation == m_timem_sign)
        tmp_total *= operand;

    else if (operation == m_division_sign) {
        if (operand == 0.0)
            return false;
        tmp_total /= operand;
    }
    else if (operation == m_power_y)
        tmp_total = std::pow(tmp_total, operand);

    else if (operation == m_power_reverse_y)
         tmp_total = std::pow(tmp_total, 1.0/operand);

    else if (operation == m_log) {
        if (operand <= 0 or tmp_total <= 0)
            return false;
        tmp_total = std::log(tmp_total) / std::log(operand);
    }

    m_display_up->setText(QString::number(tmp_total));
    return true;
}
