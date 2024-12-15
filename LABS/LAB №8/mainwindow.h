#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QGroupBox>
#include <QFrame>
#include <QLabel>
#include <QSplitter>
#include <QComboBox>
#include <QDebug>

#include <iostream>
#include <memory>

#include "sinus.h"
#include "integralsinus.h"
//#include "sinus.cpp"
//#include "function.h"
#include "Complex.h"
#include "graphwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onCalculateButtonClicked();

private:
    std::unique_ptr<QHBoxLayout> mainLayout;
    std::unique_ptr<QSplitter> splitter;
    std::unique_ptr<QGroupBox> leftGroupBox;
    std::unique_ptr<QVBoxLayout> leftLayout;
    std::unique_ptr<QComboBox> functionComboBox;
    std::unique_ptr<QLabel> rootLabel;
    std::unique_ptr<QWidget> complexWidget;

    std::unique_ptr<QHBoxLayout> xLayout;
    std::unique_ptr<QHBoxLayout> yLayout;

    std::unique_ptr<QLineEdit> maxYEdit;
    std::unique_ptr<QLineEdit> minYEdit;

    std::unique_ptr<QLineEdit> maxXEdit;
    std::unique_ptr<QLineEdit> minXEdit;

    std::unique_ptr<QLineEdit> precisionEdit;
    std::unique_ptr<QPushButton> calculateButton;
    std::unique_ptr<QLineEdit> resultEdit;
    std::unique_ptr<QGroupBox> rightGroupBox;
    std::unique_ptr<QVBoxLayout> rightLayout;
    std::unique_ptr<QWidget> centerWidget;
    std::unique_ptr<QVBoxLayout> centerLayout;
    std::unique_ptr<QLabel> graphPlaceholder;
    std::unique_ptr<QFrame> line;

    std::unique_ptr<Sinus<Complex>> complexSinus;
    std::unique_ptr<IntegralSinus<Complex>> integralSinus;
    std::unique_ptr<GraphWidget> graphWidget;

};
#endif // MAINWINDOW_H
