#include "MainWindow.hpp"

MainWindow::MainWindow(std::shared_ptr<World> p_world) :
QWidget() {
    setWindowTitle(QStringLiteral("Life"));

    // Actions row
    QHBoxLayout* actionsLayout = new QHBoxLayout;

    m_stepBtn = new QPushButton(QStringLiteral("\u23EF"));
    m_stepBtn->setToolTip(QStringLiteral("One step"));
    actionsLayout->addWidget(m_stepBtn);

    m_playBtn = new QPushButton(QStringLiteral("\u23F5"));
    m_playBtn->setToolTip(QStringLiteral("Play"));
    actionsLayout->addWidget(m_playBtn);

    QLabel* speedLbl = new QLabel(QStringLiteral("Speed: "));
    actionsLayout->addWidget(speedLbl);

    m_speedSld = new QSlider(Qt::Horizontal);
    m_speedSld->setMinimum(0);
    m_speedSld->setMaximum(1000);
    m_speedSld->setSingleStep(50);
    m_speedSld->setPageStep(200);
    m_speedSld->setValue(250);
    m_speedSld->setTickPosition(QSlider::TicksAbove);
    m_speedSld->setTickInterval(50);
    actionsLayout->addWidget(m_speedSld);

    // Content view
    m_worldView = new WorldView(p_world->frontImage());

    // Control row
    QHBoxLayout* controlLayout = new QHBoxLayout;

    controlLayout->addWidget(new QLabel(QStringLiteral("Zoom: ")));

    m_zoomSld = new QSlider(Qt::Horizontal);
    m_zoomSld->setMinimum(1);
    m_zoomSld->setMaximum(5);
    m_zoomSld->setSingleStep(1);
    m_zoomSld->setPageStep(1);
    m_zoomSld->setValue(1);
    m_zoomSld->setTickPosition(QSlider::TicksBelow);
    m_zoomSld->setTickInterval(1);
    controlLayout->addWidget(m_zoomSld);

    m_zoomLbl = new QLabel(QStringLiteral("\u27151"));
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


// PUBLIC SLOTS
void MainWindow::onStepFinished(uint p_stepId, uint p_changes, qint64 p_elapsed) {
    detectStop(p_changes);
    m_graph->appendSlice(p_stepId, p_changes, p_elapsed);
}


void MainWindow::onWorldUpdated(QImage* p_world) {
    m_worldView->setImage(p_world);
    if (!m_beat->isActive()) {
        m_stepBtn->setDisabled(false);
        m_playBtn->setDisabled(false);
    }
}


// INTERNAL SLOTS
void MainWindow::start() {
    QObject::disconnect(m_playBtn, &QPushButton::clicked,
                        this,      &MainWindow::start);

    m_stepBtn->setDisabled(true);
    m_playBtn->setText(QStringLiteral("\u23F8"));
    m_playBtn->setToolTip(QStringLiteral("Pause"));

    QObject::connect(m_playBtn, &QPushButton::clicked,
                     this,      &MainWindow::pause);
    
    m_beat->start(m_speedSld->value());
}


void MainWindow::pause() {
    m_beat->stop();
    
    QObject::disconnect(m_playBtn, &QPushButton::clicked,
                        this,      &MainWindow::pause);

    m_playBtn->setText(QStringLiteral("\u23F5"));
    m_playBtn->setToolTip(QStringLiteral("Play"));
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
    m_zoomLbl->setText(QStringLiteral("\u2715") + QString::number(zoom));
}


void MainWindow::emitStep() {
    Q_EMIT step();
}


void MainWindow::detectStop(uint p_changes) {
    if (p_changes == 0 && m_beat->isActive())
        pause();
}
