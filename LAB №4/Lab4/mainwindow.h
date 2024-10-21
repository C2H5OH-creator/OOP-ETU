#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
};
#endif // MAINWINDOW_H
