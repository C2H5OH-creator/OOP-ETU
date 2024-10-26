#ifndef INTERFACE_H
#define INTERFACE_H

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "number.h"
#include "Polynom.h"

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

private slots:
    //void onRadioButtonClicked();
    void OnCreatePolynomClicked();
    void OnChangeValueClicked();
    void OnCalcPolynomClicked();
    void OnPrintPolynomClicked();
    void onRootCountChanged(const QString &text);
    void onConfirmCreate();
    void onClearCreateFields();
    void onConfirmChangeButton();

private:
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

    Polynom polynom;
};
#endif // INTERFACE_H
