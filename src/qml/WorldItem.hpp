#ifndef WorldItem_hpp
#define WorldItem_hpp

#include <QQuickPaintedItem>
#include <QPainter>

#include "World.hpp"


class WorldItem : public QQuickPaintedItem {
	Q_OBJECT

	Q_PROPERTY(uint zoom  READ zoom  WRITE setZoom)
	QML_ELEMENT

public:
	explicit WorldItem(QQuickItem* p_parent = nullptr);

	uint zoom() const;
	void setZoom(uint p_zoom);

	Q_INVOKABLE void setWorld(std::shared_ptr<World> p_world);

	void paint(QPainter* p_painter) override;

private:
	std::shared_ptr<World> m_world;
	uint m_zoom;
};

#endif
