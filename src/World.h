#ifndef WORLD_H
#define WORLD_H

#include <QWidget>
#include <QImage>

class World : public QWidget {
Q_OBJECT

public:
	explicit World(QWidget* p_parent = nullptr, const QSize p_size = QSize(1024, 1024));
	explicit World(QWidget* p_parent = nullptr, int p_width = 1024, int p_height = 1024);

	void init();
	void swap();

	void setAliveAt(int p_x, int p_y);
	void setDeadAt(int p_x, int p_y);

	uint countAliveAround(int p_x, int p_y) const;

protected:
	void paintEvent(QPaintEvent* p_event) override;

	void resetImage(QImage& p_image);

signals:
	void swapped();

private:
	const QSize m_size;
	QImage m_image1;
	QImage m_image2;
	QImage* m_frontImage;
	QImage* m_backImage;

	const QRgb m_deadColor;
	const QRgb m_aliveColor;

	const int COLOR_ALIVE = 0;
	const int COLOR_DEAD = 1;
};

#endif
