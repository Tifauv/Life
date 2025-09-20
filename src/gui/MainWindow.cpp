#include "MainWindow.hpp"

MainWindow::MainWindow(std::shared_ptr<World> p_world) :
QWidget() {
    setWindowTitle("Life");

    // Actions row
    m_playBtn = new QPushButton(">");
    m_playBtn->setToolTip("Play");
    
    m_stepBtn = new QPushButton(">|");
    m_stepBtn->setToolTip("One step");

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
    actionsLayout->addWidget(m_playBtn);
    actionsLayout->addWidget(m_stepBtn);
    actionsLayout->addWidget(speedLbl);
    actionsLayout->addWidget(m_speedSld);

    // Content view
    m_worldView = new WorldView(p_world);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(actionsLayout);
    mainLayout->addWidget(m_worldView, 0, Qt::AlignCenter);
    setLayout(mainLayout);

    QObject::connect(m_playBtn, &QPushButton::clicked,
                     this,      &MainWindow::start);

    QObject::connect(m_stepBtn, &QPushButton::clicked,
                     this,      &MainWindow::startStep);

    m_beat = new QTimer(this);
    QObject::connect(m_beat,    &QTimer::timeout,
                     this,      &MainWindow::emitStep);
    QObject::connect(m_speedSld, &QSlider::valueChanged,
                     this,       &MainWindow::updateBeat);
}


void MainWindow::start() {
    QObject::disconnect(m_playBtn, &QPushButton::clicked,
                        this,      &MainWindow::start);

    m_stepBtn->setDisabled(true);
    m_playBtn->setText("||");
    m_playBtn->setToolTip("Pause");

    QObject::connect(m_playBtn, &QPushButton::clicked,
                     this,      &MainWindow::pause);
    
    m_beat->start(m_speedSld->value());
}


void MainWindow::pause() {
    m_beat->stop();
    
    QObject::disconnect(m_playBtn, &QPushButton::clicked,
                        this,      &MainWindow::pause);

    m_playBtn->setText(">");
    m_playBtn->setToolTip("Play");
    m_stepBtn->setDisabled(false);
 
    QObject::connect(m_playBtn, &QPushButton::clicked,
                     this,      &MainWindow::start);
}


void MainWindow::startStep() {
    m_playBtn->setDisabled(true);
    m_stepBtn->setDisabled(true);
    emitStep();
}


void MainWindow::updateBeat(int p_delay) {
    m_beat->setInterval( (p_delay == 0 ? 1 : p_delay) );
}


void MainWindow::emitStep() {
    emit step();
}


void MainWindow::detectStop(uint p_changes) {
    if (p_changes == 0 && m_beat->isActive())
        pause();
}


void MainWindow::stepFinished() {
    if (!m_beat->isActive()) {
        m_stepBtn->setDisabled(false);
        m_playBtn->setDisabled(false);
    }
}
