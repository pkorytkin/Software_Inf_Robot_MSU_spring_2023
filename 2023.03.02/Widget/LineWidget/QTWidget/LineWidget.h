#pragma once

#include <QWidget>
#include "Enums.h"

class LineWidget : public QWidget {
    Q_OBJECT

private:
    QPointF PressPos{};
    int m_width{ 0 };
    int m_angle{ 0 };
    Qt::PenStyle m_penStyle{ Qt::SolidLine };
    Enums::FigureType m_figureType{ Enums::FigureType::Line};//default init with Line same as =Enums::FigureType::Line from c++11
    
public:
    explicit LineWidget(QWidget* parent = nullptr) : QWidget(parent) {}

    int getWidth() const                { return m_width; }
    int getAngle() const                { return m_angle; }
    Qt::PenStyle getPenStyle() const { return m_penStyle; }
    Enums::FigureType getFigureType() const { return m_figureType; }
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;


public slots:
   void setWidth(int);
   void setAngle(int);
   void setPenStyle(Qt::PenStyle);
   void setFigureType(Enums::FigureType);

signals:
   void widthChanged(int);
   void angleChanged(int);
   void penStyleChanged(Qt::PenStyle);
   void FigureTypeChanged(Enums::FigureType);
};