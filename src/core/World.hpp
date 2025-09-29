#ifndef World_hpp
#define World_hpp

#include <QObject>
#include <QImage>

#include "lifecore_export.h"


class LIFECORE_EXPORT World : public QObject {
	Q_OBJECT

public:
	explicit World(const QSize p_size);
	explicit World(int p_width, int p_height);

	const QSize size() const;
	int width() const;
	int height() const;
	const QImage& frontImage() const;

	void init();
	void swap();

	bool wasAliveAt(int p_x, int p_y) const;
	bool wasDeadAt(int p_x, int p_y) const;
	bool changedAt(int p_x, int p_y) const;
	
	void copyCellAt(int p_x, int p_y);
	void setAliveAt(int p_x, int p_y);
	void setDeadAt(int p_x, int p_y);

	uint countAliveAround(int p_x, int p_y) const;

Q_SIGNALS:
	void updated();

private:
	const QSize m_size;
	QImage m_image1;
	QImage m_image2;
	QImage* m_frontImage;
	QImage* m_backImage;

	const int COLOR_ALIVE = 0;
	const int COLOR_DEAD  = 1;
};

#endif
