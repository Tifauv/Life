#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

#include "WorldView.hpp"


class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<World> p_world);

public slots:
    void stepFinished();

signals:
    void next();

protected slots:
    void sendNext();

private:
    QPushButton* m_nextStepBtn;
    QSlider*     m_speedSld;
    WorldView*   m_worldView;
};

#endif
