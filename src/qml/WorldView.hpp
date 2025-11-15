#ifndef WorldView_hpp
#define WorldView_hpp

#include <QQuickPaintedItem>
#include <QPainter>

#include "World.hpp"


class WorldView : public QQuickPaintedItem {
	Q_OBJECT

	Q_PROPERTY(uint   zoom   READ zoom   WRITE setZoom)
	Q_PROPERTY(World* world  READ world  WRITE setWorld)
	QML_ELEMENT

public:
	explicit WorldView(QQuickItem* p_parent = nullptr);

	qreal implicitWidth() const;
	qreal implicitHeight() const;

	uint zoom() const;
	void setZoom(uint p_zoom);

	World* world() const;
	Q_INVOKABLE void setWorld(World* p_world);

	void paint(QPainter* p_painter) override;

private:
	World* m_world;
	uint m_zoom;
};

#endif
