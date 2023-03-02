#include <QtMath>
#include <QtGui>
#include "LineWidget.h"
#include "Enums.h"


void LineWidget::setWidth(int widthPix)
{
    if (m_width != widthPix)
    {
        m_width = widthPix;
        update();
        emit widthChanged(widthPix);
    }
}


void LineWidget::setAngle(int angleDeg)
{
    if (m_angle != angleDeg)
    {
        m_angle = angleDeg;  
        update();
        emit angleChanged(angleDeg);
    }
}


void LineWidget::setPenStyle(Qt::PenStyle penStyle)
{
    if (m_penStyle != penStyle)
    {
        m_penStyle = penStyle;
        update();
        emit penStyleChanged(penStyle);
    }
}
void LineWidget::setFigureType(Enums::FigureType figureType)
{
    if (m_figureType != figureType)
    {
        m_figureType = figureType;
        update();
        emit FigureTypeChanged(figureType);
    }
}

void LineWidget::paintEvent(QPaintEvent* event) 
{	
    // Текущие размеры виджета (в пикселах)
    const int W = size().width(), H = size().height();

    QPainter painter(this);
    // Закраска области виджета фоновым светло-серым цветом
    painter.fillRect(0, 0, W, H, QColor(205, 205, 205));

    // QPen – свойства отображения отрезков и контуров с помощью QPainter. 
    QPen pen;
    pen.setColor(Qt::red);         // Цвет: константа перечислимого типа Qt
    pen.setStyle(m_penStyle);      // Стиль отображения линии
    pen.setCapStyle(Qt::RoundCap); // Стиль отображения концов отрезков
    pen.setWidth(m_width);         // Толщина линии (в пикселах)
    // Перенос и поворот системы координат QPainter.
    painter.translate(W / 2, H / 2);
    if (m_figureType == Enums::FigureType::Line) {

        // Поворот: по часовой стрелке, в градусах.
        painter.rotate(-m_angle);
        // Установка пера 
        painter.setPen(pen);
        // Построение отрезка: (x1, y1) – (x2, y2)
        painter.drawLine(-W / 2, 0, W / 2, 0);
    }else if(m_figureType==Enums::FigureType::Triangle)
    {
        // Поворот: по часовой стрелке, в градусах.
        painter.rotate(-m_angle);
        // Установка пера 
        painter.setPen(pen);
        const int Distance = (W + H) / 6;

        int Angles = 3;
        int sqrtDistance = Distance / qSqrt(2);
        for (int i = 0; i < Angles; i++) {
            painter.drawLine(qCos(i* M_PI*2 / Angles)* sqrtDistance, qSin(i * M_PI*2 / Angles)* sqrtDistance, qCos((i+1) * M_PI*2 / Angles)* sqrtDistance, qSin((i+1) * M_PI*2 / Angles)* sqrtDistance);
        }
        /*painter.drawLine(-Distance, -Distance, 0, Distance);
        painter.drawLine(0, Distance, Distance, -Distance);
        painter.drawLine(Distance, -Distance, Distance, -Distance);*/
    }
    else {
        // Поворот: по часовой стрелке, в градусах.
        painter.rotate(-m_angle);
        // Установка пера 
        painter.setPen(pen);
        const int Height = (W + H) /10;
        const int Width = Height*2;
        painter.drawLine(-Width, -Height, Width, -Height);
        painter.drawLine(Width, -Height, Width, Height);
        painter.drawLine(Width, Height, -Width, Height);
        painter.drawLine(-Width, Height, -Width, -Height);
       // painter.drawLine(Distance, -Distance, Distance, -Distance);
    }
}

void LineWidget::mousePressEvent(QMouseEvent* event)
{
    QPointF pnt = event->position();
    PressPos = pnt;
}
void LineWidget::mouseMoveEvent(QMouseEvent* event)
{
    QPointF pnt = event->position ();
    QPointF delta = pnt - PressPos;
    setWidth((int)delta.manhattanLength());
    // Координаты указателя мыши в системе координат виджета
    /*QPointF pnt = event->position();
    QPointF center{ size().width() / 2.0f, size().height() / 2.0f };
    QPointF delta = pnt - center;
    double angleRad = qAtan2(- delta.y(), delta.x());
    double angleDeg = qRadiansToDegrees(angleRad);    
    if (angleDeg < 0)
        angleDeg = 360.0 + angleDeg;
    setAngle(angleDeg);*/

}