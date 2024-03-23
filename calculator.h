#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QRadioButton>
#include <QGroupBox>

#include <mybutton.h>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator();


private slots:
    void digitClicked();
    void unaryOperatorClicked();
    void doubleOperatorClicked();
    void equalClicked();
    void pointClicked();
    void clearALL();
    void clear();

    void setStandardMode(bool checked);

private:

    QWidget* mainWidget;
    QGridLayout* mainLayout;

    //стандартные кнопки
    MyButton* pointButton = nullptr;
    MyButton* clearButton    = nullptr;
    MyButton* clearALLButton = nullptr;

    MyButton* divisionButton = nullptr;
    MyButton* timesButton    = nullptr;
    MyButton* minusButton    = nullptr;
    MyButton* plusButton     = nullptr;
    MyButton* sqrtButton       = nullptr;

    MyButton* reciprocalButton = nullptr;
    MyButton* equalButton = nullptr;

    //дополнительные инженерные

    MyButton* sinhButton = nullptr;
    MyButton* sinButton = nullptr;
    MyButton* expButton = nullptr;
    MyButton* power_2_Button = nullptr;
    MyButton* coshButton = nullptr;
    MyButton* cosButton = nullptr;
    MyButton* lnButton = nullptr;
    MyButton* power_3_Button = nullptr;
    MyButton* tanhButton = nullptr;
    MyButton* tanButton = nullptr;
    MyButton* logButton = nullptr;
    MyButton* power_y_Button = nullptr;
    MyButton* factButton = nullptr;
    MyButton* piButton = nullptr;
    MyButton* cuberootButton = nullptr;
    MyButton* yrootButton = nullptr;


    QGroupBox *modeGroupBox;
    QRadioButton *standardModeButton;
    MyButton* createButton(const QString& text, const char* member);
    void abortOperation();
    bool calculate(double operand, const QString& operation);


    QString m_pending_operation;

    QLineEdit* m_display_up;
    QLineEdit* m_display_down;
    QLabel*    m_sign;

    MyButton *m_digitButtons[10];

    //Кнопочки для красоты
    QString m_sqrt_sign       = QChar(0x221A);
    QString m_reciprocal_sign = "1/x";
    QString m_division_sign   = QChar(0x000000F7);
    QString m_timem_sign      = QChar(0x000000D7);
    QString m_plum_sign       = "+";
    QString m_minum_sign      = "-";

    QString m_power_2  = 'x' + QChar(0x000000b2);
    QString m_power_3  = 'x' + QChar(0x000000b3);

    QString m_power_y = "x^y";
    QString m_power_reverse_y = "x^(1/y)";
    QString m_log = "log";


    //темная и светлая темы в виде SCC
    QString darkTheme = R"(
        QWidget {
            background-color: #2D2D30;
            color: #CCCCCC;
        }
        QLineEdit {
            background-color: #333;
            color: #DDD;
            border: 1px solid #555;
        }
        QPushButton {
            background-color: #555;
            border: 1px solid #666;
            color: white;
        }
        QPushButton:hover {
            background-color: #666;
        }
        QPushButton:pressed {
            background-color: #777;
        }

        MyButton {
            background-color: #555;
            border: 1px solid #666;
            color: white;
        }
        MyButton:hover {
            background-color: #666;
        }
        MyButton:pressed {
            background-color: #777;
        }
        QRadioButton {
            color: #DDD;
        }
        QGroupBox {
            border: none;
            margin-top: 1ex;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 3px 0 3px;
            color: #EEE;
        }
    )";

    QString lightTheme = R"(
        QWidget {
            background-color: #FFFFFF;
            color: #000000;
        }
        QLineEdit {
            background-color: #F0F0F0;
            color: #000000;
            border: 1px solid #B0B0B0;
        }
        QPushButton {
            background-color: #E0E0E0;
            border: 1px solid #C0C0C0;
            color: #000000;
        }
        QPushButton:hover {
            background-color: #D0D0D0;
        }
        QPushButton:pressed {
            background-color: #C0C0C0;
        }
        MyButton {
            background-color: #E0E0E0;
            border: 1px solid #C0C0C0;
            color: #000000;
        }
        MyButton:hover {
            background-color: #D0D0D0;
        }
        MyButton:pressed {
            background-color: #C0C0C0;
        }
        QRadioButton {
            color: #000000;
        }
        QGroupBox {
            border: none;
            margin-top: 1ex;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 3px 0 3px;
            color: #000000;
        }
    )";


};

#endif // CALCULATOR_H
