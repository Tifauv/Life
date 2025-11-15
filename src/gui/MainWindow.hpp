#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QWidget>
#include <QQuickWidget>

#include "World.hpp"
#include "WorldView.hpp"
#include "StatsGraph.hpp"


class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<World> p_world);

public Q_SLOTS:
    void onStepFinished(uint p_stepId, uint p_changes, qint64 p_elapsed);
    void onWorldUpdated(QImage*);

Q_SIGNALS:
    void step();

protected Q_SLOTS:
    void start();
    void pause();
    
    void startStep();
    
    void updateBeat(int p_delay);
    void updateZoom(int p_zoom);

protected:
    void initGraphWidget();
    void emitStep();
    void detectStop(uint p_changes);

private:
    QPushButton*  m_playBtn;
    QPushButton*  m_stepBtn;
    QSlider*      m_speedSld;
    QSlider*      m_zoomSld;
    QLabel*       m_zoomLbl;
    QTimer*       m_beat;
    WorldView*    m_worldView;
    QQuickWidget* m_graphWidget;
    StatsGraph*   m_graph;
};

#endif
