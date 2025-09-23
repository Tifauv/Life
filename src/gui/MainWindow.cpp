#include "MainWindow.hpp"

MainWindow::MainWindow(std::shared_ptr<World> p_world) :
QWidget() {
    setWindowTitle("Life");

    // Actions row
    m_playBtn = new QPushButton(">");
    m_playBtn->setToolTip("Play");
    
    m_stepBtn = new QPushButton(">|");
    m_stepBtn->setToolTip("One step");

    QLabel* speedLbl = new QLabel("Speed: ");

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

    // Control row
    m_zoomSld = new QSlider(Qt::Horizontal);
    m_zoomSld->setMinimum(1);
    m_zoomSld->setMaximum(5);
    m_zoomSld->setSingleStep(1);
    m_zoomSld->setPageStep(1);
    m_zoomSld->setValue(1);
    m_zoomSld->setTickPosition(QSlider::TicksBelow);
    m_zoomSld->setTickInterval(1);

    m_zoomLbl = new QLabel("x1");

    QHBoxLayout* controlLayout = new QHBoxLayout;
    controlLayout->addWidget(new QLabel("Zoom: "));
    controlLayout->addWidget(m_zoomSld);
    controlLayout->addWidget(m_zoomLbl);

    // Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(actionsLayout);
    mainLayout->addWidget(m_worldView, 0, Qt::AlignCenter);
    mainLayout->addLayout(controlLayout);
    setLayout(mainLayout);

    QObject::connect(m_playBtn, &QPushButton::clicked,
                     this,      &MainWindow::start);
    QObject::connect(m_stepBtn, &QPushButton::clicked,
                     this,      &MainWindow::startStep);
    QObject::connect(m_speedSld, &QSlider::valueChanged,
                     this,       &MainWindow::updateBeat);

    QObject::connect(m_zoomSld, &QSlider::valueChanged,
                     this,      &MainWindow::updateZoom);

    m_beat = new QTimer(this);
    QObject::connect(m_beat,    &QTimer::timeout,
                     this,      &MainWindow::emitStep);
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


void MainWindow::updateZoom(int p_zoom) {
    int zoom = 1 << (p_zoom - 1);

    m_worldView->setZoom(zoom);
    m_zoomLbl->setText("x" + QString::number(zoom));
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
