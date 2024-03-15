#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

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
    //void changeSignClicked();
    void clearALL();
    void clear();

    void setStandardMode();
    void setEngineeringMode();

private:
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
    //QString m_power_sign      = 'x' + QChar(0x000000b2);
    QString m_reciprocal_sign = "1/x";

    QString m_division_sign   = QChar(0x000000F7);
    QString m_times_sign      = QChar(0x000000D7);
    QString m_plus_sign       = "+";
    QString m_minus_sign      = "-";

    //QString m_change_sign     = QChar(0x000000b1);
};

#endif // CALCULATOR_H
