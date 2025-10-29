#ifndef WorldView_hpp
#define WorldView_hpp

#include <QImage>
#include <QWidget>


class WorldView : public QWidget {
	Q_OBJECT

	Q_PROPERTY(uint zoom  READ zoom  WRITE setZoom)

public:
	explicit WorldView(QImage* p_world, QWidget* p_parent = nullptr);

	uint zoom() const;
	void setZoom(uint p_zoom);

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;
	
	bool hasHeightForWidth() const override;
	int heightForWidth(int p_width) const override;

	void setImage(QImage*);

protected:
	void paintEvent(QPaintEvent*) override;

private:
	QImage* m_world;
	uint m_zoom;
};

#endif
