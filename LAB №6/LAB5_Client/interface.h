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
    void createRightLayout();

public slots:
    void handleMessage(const QString &message);

private:
    UDPCommunicator* communicator;

    QRadioButton *complexRadio;
    QRadioButton *realRadio;

    QVBoxLayout *printLayout;

    QHBoxLayout *mainLayout;
    QVBoxLayout *rightLayout;

    QVBoxLayout *changeLayout;
    QVBoxLayout *calcLayout;

    QWidget *centralWidget;
    QVBoxLayout *leftLayout;
    QVBoxLayout *createLayout;

    QLineEdit *rootCountInput;

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
    QVector<QHBoxLayout*> rootInputLayouts;

    QWidget *createPolynomWidget;
    QWidget *changeValueWidget;
    QWidget *calcPolynomWidget;
    QWidget *printPolynomWidget;

    QLabel *canonicalFormLabel;
    QLabel *nonCanonicalFormLabel;
};
#endif // INTERFACE_H
