#ifndef CIRCLEPALETTE_H
#define CIRCLEPALETTE_H

#include <QLabel>
#include <QPoint>

namespace PrestoPalette
{
enum GlobalGamutShape
{
	GamutShapeNone,
	GamutShapeLine,
	GamutShapeTriangle,
	GamutShapeSquare
};
}

class CirclePalette : public QWidget
{
	Q_OBJECT
public:
	explicit CirclePalette(QWidget *parent = 0);

	QWidget *drawnElements;
	QLabel *colorWheel;
	QLabel *backgroundWheel;
	QVector<QColor> selectedColors;

	void ChangeGamutShape(PrestoPalette::GlobalGamutShape shape);

signals:
	void selectedColorsChanged();

private slots:


private:
	bool eventFilter( QObject* watched, QEvent* event );
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:
	int primaryRadius = 15;
	int secondaryRadius = 5;
	int centroidRadius = 5;

	std::vector<QPoint*> points;
	std::vector<QLabel*> lines;

	QPoint dragStartPosition;
	bool isDragging;
	QPoint *dragPoint;
	QPoint relativeDistance;
	PrestoPalette::GlobalGamutShape gamutShape;
	QPixmap circlePic;

	void create_gamut_line();
        void create_gamut_triangle();
	void create_gamut_square();
	void destroy_gamut();

	void _draw_primary_imp(QPainter &painter, QVector<QColor> *colors, QLabel *colorWheel, const QPoint &p, int circleRadius);
	void _draw_line_imp(QPainter &painter, QVector<QColor> *colors, QLabel *colorWheel, const QPoint &p1, const QPoint &p2, int circleRadius);
	void _draw_centroid(QPainter &painter, QVector<QColor> *colors, QLabel *colorWheel, std::vector<QPoint*> &points, int circleRadius);
	bool _is_collision(const QPoint &circle, const QPoint &hitTest);
};

#endif // CIRCLEPALETTE_H