#ifndef INTERFACE_H
#define INTERFACE_H

#include "../LAB5_Server/udpcommunicator.h"
#include "../LAB5_Server/enums.h"

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

private slots:
    void OnCreatePolynomClicked();
    void OnChangeValueClicked();
    void OnCalcPolynomClicked();
    void OnPrintPolynomClicked();
    void onRootCountChanged(const QString &text);
    void onConfirmCreate();
    void onClearCreateFields();
    void onConfirmChangeButton();
    void createLeftLayout();
    void createRightComplexLayout();
    void createRightDoubleLayout();
    void onNumberSetChanged();

public slots:
    void handleMessage(const QString &message);


private:
    UDPCommunicator* communicator;

    QRadioButton *complexRadio;
    QRadioButton *realRadio;

    bool isComplex = true;

    QVBoxLayout *printLayout;

    QHBoxLayout *mainLayout;
    QVBoxLayout *rightLayout;

    QVBoxLayout *changeLayout;
    QVBoxLayout *calcLayout;

    QWidget *centralWidget;
    QVBoxLayout *leftLayout;
    QVBoxLayout *createLayout;
    QVBoxLayout *createDoubleLayout;

    QLineEdit *rootCountInput;
    QLineEdit *doubleRootCountInput;

    QLineEdit *aNInput;
    QLineEdit *aNInputReal;
    QLineEdit *aNInputImaginary;

    QLineEdit* calcValueReal;
    QLineEdit* calcValueImaginary;

    QLineEdit *changeInput;
    QLineEdit *calcInput;

    QLineEdit *changeInputAnReal;
    QLineEdit *changeInputAnImaginary;
    QLineEdit *changeInputIndex;
    QLineEdit *changeInputRootReal;
    QLineEdit *changeInputRootImaginary;


    QRadioButton* changeAnButton;
    QRadioButton* changeRootButton;

    QLabel* rootInputLabel;

    QVector<QPair<QLineEdit*, QLineEdit*>> rootInputs;
    QVector<QLineEdit*> doubleRootInputs;
    QVector<QHBoxLayout*> rootInputLayouts;

    //Для вещественных чисел
    QWidget *createDoublePolynomWidget;
    QWidget *changeDoubleValueWidget;
    QWidget *calcDoublePolynomWidget;

    QLineEdit *changeInputAn;
    QLineEdit *changeRealInputIndex;
    QLineEdit *changeInputRoot;

    QLineEdit* calcDoubleValueReal;

    //Для комплексных чисел
    QWidget *createPolynomWidget;
    QWidget *changeValueWidget;
    QWidget *calcPolynomWidget;

    //Общее
    QWidget *printPolynomWidget;

    QLabel *canonicalFormLabel;
    QLabel *nonCanonicalFormLabel;
};
#endif // INTERFACE_H
