#include <QtMath>
#include <QtGui>
#include <QWidget>
#include "LineDrawerWidget.h"
LineDrawerWidget::LineDrawerWidget(QWidget* parent) : QWidget(parent) 
{
	//Points = {};
	MousePosition = {};
}
void LineDrawerWidget::mousePressEvent(QMouseEvent* event) {
	MousePressed = true;
	QPointF pnt = event->position();
	MousePosition.X = pnt.x();
	MousePosition.Y = pnt.y();
	if (Points.size() == 0) {
		std::unique_ptr<Point> point(new Point);
		point->X = MousePosition.X;
		point->Y = MousePosition.Y;

		Points.push_back(std::move(point));
	}
	update();
	qDebug() << "Pressed=" << MousePosition.X << " " << MousePosition.Y << "\n";
}
void LineDrawerWidget::mouseMoveEvent(QMouseEvent* event) {
	MousePressed = true;
	QPointF pnt = event->position();
	MousePosition.X = pnt.x();
	MousePosition.Y = pnt.y();
	update();
	qDebug() << "Move=" << MousePosition.X << " " << MousePosition.Y << "\n";
}
void LineDrawerWidget::mouseReleaseEvent(QMouseEvent* event) {
	MousePressed = false;
	QPointF pnt{};

	std::unique_ptr<Point> point(new Point);
	point->X = MousePosition.X;
	point->Y = MousePosition.Y;
	qDebug() << "Append=" << point->X << " " << point->Y << "\n";
	Points.push_back(std::move(point));
	
	MousePosition = {};
	update();
}
void LineDrawerWidget::paintEvent(QPaintEvent* event)
{
	const int m_width = 4;
	// Текущие размеры виджета (в пикселах)
	const int W = size().width(), H = size().height();
	QPainter painter(this);
	// Закраска области виджета фоновым светло-серым цветом
	painter.fillRect(0, 0, W, H, QColor(205, 205, 205));

	// QPen – свойства отображения отрезков и контуров с помощью QPainter. 
	QPen pen;
	pen.setColor(Qt::red);         // Цвет: константа перечислимого типа Qt
	pen.setStyle(Qt::PenStyle::SolidLine);      // Стиль отображения линии
	pen.setCapStyle(Qt::RoundCap); // Стиль отображения концов отрезков
	pen.setWidth(m_width);         // Толщина линии (в пикселах)

	for (int i = 1; i < Points.size(); i++) {
		painter.drawLine(Points[i - 1]->X, Points[i - 1]->Y, Points[i]->X, Points[i]->Y);
	}
	if (MousePressed&&Points.size()>0) {
		painter.drawLine(Points[Points.size()-1]->X, Points[Points.size() - 1]->Y, MousePosition.X,MousePosition.Y);
	}
	qDebug() << "Points=" << Points.size() << "\n";

}

void LineDrawerWidget::cleanPoints() {
	Points.clear();
	update();
}