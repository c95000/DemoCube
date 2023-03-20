#include "TestViewController.h"
#include <QPushButton>
#include "FlowLayout.h"

TestViewController::TestViewController(QWidget *parent)
    : QWidget{parent}
{
    QFlowLayout *rootLayout = new QFlowLayout();
    QPushButton *funcButton1 = new QPushButton("功能一");
    rootLayout->addWidget(funcButton1);
    setLayout(rootLayout);

    connect(funcButton1, &QPushButton::clicked, this, &TestViewController::onFuncButton1Clicked);
}
