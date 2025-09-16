#include "MainWindow.hpp"

MainWindow::MainWindow(std::shared_ptr<World> p_world) :
QWidget() {
    setWindowTitle("Life");

    // Actions row
    m_nextStepBtn = new QPushButton("&Next step >");

    QLabel* speedLbl = new QLabel("Speed:");

    m_speedSld = new QSlider(Qt::Horizontal);
    m_speedSld->setMinimum(0);
    m_speedSld->setMaximum(1000);
    m_speedSld->setSingleStep(50);
    m_speedSld->setPageStep(250);
    m_speedSld->setValue(500);
    m_speedSld->setTickPosition(QSlider::TicksAbove);
    m_speedSld->setTickInterval(50);

    QHBoxLayout* actionsLayout = new QHBoxLayout;
    actionsLayout->addWidget(m_nextStepBtn);
    actionsLayout->addWidget(speedLbl);
    actionsLayout->addWidget(m_speedSld);

    // Content view
    m_worldView = new WorldView(p_world);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(actionsLayout);
    mainLayout->addWidget(m_worldView);
    setLayout(mainLayout);

    QObject::connect(m_nextStepBtn, &QPushButton::clicked,
                     this,          &MainWindow::sendNext);
}


void MainWindow::sendNext() {
    m_nextStepBtn->setDisabled(true);
    emit next();
}


void MainWindow::stepFinished() {
    m_nextStepBtn->setDisabled(false);
}
