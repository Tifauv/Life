#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QWidget>

#include "WorldView.hpp"


class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<World> p_world);

public slots:
    void detectStop(uint p_changes);
    void stepFinished();

signals:
    void step();

protected slots:
    void start();
    void pause();
    
    void startStep();
    
    void updateBeat(int p_delay);

protected:
    void emitStep();
    
private:
    QPushButton* m_playBtn;  
    QPushButton* m_stepBtn;
    QSlider*     m_speedSld;
    QTimer*      m_beat;
    WorldView*   m_worldView;
};

#endif
