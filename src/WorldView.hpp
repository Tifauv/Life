#ifndef WorldView_hpp
#define WorldView_hpp

#include <QWidget>

#include "World.hpp"


class WorldView : public QWidget {
	Q_OBJECT

public:
	explicit WorldView(std::shared_ptr<World> p_world, QWidget* p_parent = nullptr);

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;
	
	bool hasHeightForWidth() const override;
	int heightForWidth(int p_width) const override;

protected:
	void paintEvent(QPaintEvent* p_event) override;

private:
    std::shared_ptr<World> m_world;
};

#endif
