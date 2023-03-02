#pragma once
#include <QWidget>
#include "Point.h"
#include <QPushButton>
class LineDrawerWidget : public QWidget {
    Q_OBJECT
private:
    std::vector<std::unique_ptr<Point>> Points;
    bool MousePressed{ false };
    Point MousePosition{};
protected:
     void paintEvent(QPaintEvent* event) override;
     void mousePressEvent(QMouseEvent* event) override;
     void mouseMoveEvent(QMouseEvent* event) override;
     void mouseReleaseEvent(QMouseEvent* event) override;
public:
    explicit LineDrawerWidget(QWidget* parent = nullptr);
    void cleanPoints();
};