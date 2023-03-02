#pragma once

#include <QWidget>
#include <QSpinBox>
#include <QSlider>
#include "LineWidget.h"

class MainForm : public QWidget {
    Q_OBJECT

public:
    explicit MainForm(QWidget* parent = nullptr);

private:
    LineWidget* m_lineWidget{ nullptr };
    QSpinBox*   m_spinBoxWidth{ nullptr };
    QSlider*    m_sliderWidth{ nullptr };
    QSpinBox*   m_spinBoxAngle{ nullptr };
    QSlider*    m_sliderAngle{ nullptr };
};