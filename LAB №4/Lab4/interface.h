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
private:
    QVBoxLayout *leftLayout;
    QWidget *centralWidget;

    // Виджеты для каждого пункта меню
    QWidget *createPolynomWidget;
    QWidget *changeValueWidget;
    QWidget *calcPolynomWidget;
    QWidget *printPolynomWidget;

    std::vector<QLineEdit> inputFields;
};
#endif // INTERFACE_H
