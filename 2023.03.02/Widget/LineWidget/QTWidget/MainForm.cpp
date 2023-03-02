#include <QVBoxLayout>
#include <QPen>
#include <QGroupBox>
#include <QRadioButton>
#include "MainForm.h"

MainForm::MainForm(QWidget* parent) :
          QWidget(parent)
{
    // Виджет для отображения отрезка
    // (Координаты и размеры задаются явно)
    const int LEFT_OFS = 10, TOP_OFS = 10;
    const int IMG_W = 200, IMG_H = 200;    
    m_lineWidget = new LineWidget(this);
    m_lineWidget->setGeometry(LEFT_OFS, TOP_OFS, IMG_W, IMG_H);
    
    const int vectical_offset = 60;

    // Виджеты для задания толщины отрезка
    const int LINE_W_MIN = 1, LINE_W_MAX = 25;
    m_spinBoxWidth = new QSpinBox(this);
    m_spinBoxWidth->setGeometry(10, IMG_H + 20+ vectical_offset, 50, 30);
    m_spinBoxWidth->setRange(LINE_W_MIN, LINE_W_MAX);
    m_sliderWidth = new QSlider(Qt::Horizontal, this);
    m_sliderWidth->setGeometry(70, IMG_H + 20+ vectical_offset, 250, 30);
    m_sliderWidth->setRange(LINE_W_MIN, LINE_W_MAX);

    // Виджеты для задания направления отрезка
    const int LINE_ANGLE_MIN = 0, LINE_ANGLE_MAX = 360;
    m_spinBoxAngle = new QSpinBox(this);
    m_spinBoxAngle->setGeometry(10, IMG_H + 50+ vectical_offset, 50, 30);
    m_spinBoxAngle->setRange(LINE_ANGLE_MIN, LINE_ANGLE_MAX);
    m_sliderAngle = new QSlider(Qt::Horizontal, this);
    m_sliderAngle->setGeometry(70, IMG_H + 50 + vectical_offset, 250, 30);
    m_sliderAngle->setRange(LINE_ANGLE_MIN, LINE_ANGLE_MAX);

    // Связывание виджетов-счетчиков и ползунков для синхронного изменения
    connect(m_spinBoxWidth, SIGNAL(valueChanged(int)), m_sliderWidth, SLOT(setValue(int)));
    connect(m_sliderWidth, SIGNAL(valueChanged(int)), m_spinBoxWidth, SLOT(setValue(int)));
    connect(m_sliderWidth, SIGNAL(valueChanged(int)), m_lineWidget, SLOT(setWidth(int)));
    connect(m_sliderWidth, &QSlider::valueChanged, m_lineWidget, &LineWidget::setWidth);
    connect(m_lineWidget, SIGNAL(widthChanged(int)), m_sliderWidth, SLOT(setValue(int)));    

    connect(m_spinBoxAngle, SIGNAL(valueChanged(int)), m_sliderAngle, SLOT(setValue(int)));
    connect(m_sliderAngle, SIGNAL(valueChanged(int)), m_spinBoxAngle, SLOT(setValue(int)));
    connect(m_sliderAngle, SIGNAL(valueChanged(int)), m_lineWidget, SLOT(setAngle(int)));
    connect(m_lineWidget, SIGNAL(angleChanged(int)), m_sliderAngle, SLOT(setValue(int)));

    // Группа виджетов для задания стиля линии
    QGroupBox* gbPenStyle = new QGroupBox("&Стиль линии", this);
    gbPenStyle->setGeometry(LEFT_OFS + IMG_W + 20, TOP_OFS, 150, 120);
    QRadioButton* radio1 = new QRadioButton("SolidLine");
    QRadioButton* radio2 = new QRadioButton("DashLine");
    QRadioButton* radio3 = new QRadioButton("DotLine");
    QRadioButton* radio4 = new QRadioButton("DashDotLine");
    radio1->setChecked(true);
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addWidget(radio4);
    gbPenStyle->setLayout(vbox);



    // Связывание виджетов-кнопок стилей линии с виджетом m_lineWidget посредством лямбда-функций.
    // По сигналу от каждой кнопки QRadioButton слот m_lineWidget вызывается с 
    // передачей конкретного значения стиля линии.
    connect(radio1, &QRadioButton::clicked, [this] { m_lineWidget->setPenStyle(Qt::SolidLine); });
    connect(radio2, &QRadioButton::clicked, [this] { m_lineWidget->setPenStyle(Qt::DashLine); });
    connect(radio3, &QRadioButton::clicked, [this] { m_lineWidget->setPenStyle(Qt::DotLine); });
    connect(radio4, &QRadioButton::clicked, [this] { m_lineWidget->setPenStyle(Qt::DashDotLine); });

    // Группа виджетов для задания типа фигуры
    QGroupBox* gbFigureType = new QGroupBox("&Тип фиругы", this);
    gbFigureType->setGeometry(LEFT_OFS + IMG_W + 20, TOP_OFS + 120 + 20, 150, 120);
    QRadioButton* fig_radio1 = new QRadioButton("Line");
    QRadioButton* fig_radio2 = new QRadioButton("Triangle");
    QRadioButton* fig_radio3 = new QRadioButton("Rectangle");
    fig_radio1->setChecked(true);
    QVBoxLayout* vbox2 = new QVBoxLayout;
    vbox2->addWidget(fig_radio1);
    vbox2->addWidget(fig_radio2);
    vbox2->addWidget(fig_radio3);
    gbFigureType->setLayout(vbox2);

    connect(fig_radio1, &QRadioButton::clicked, [this] { m_lineWidget->setFigureType(Enums::FigureType::Line); });
    connect(fig_radio2, &QRadioButton::clicked, [this] { m_lineWidget->setFigureType(Enums::FigureType::Triangle); });
    connect(fig_radio3, &QRadioButton::clicked, [this] { m_lineWidget->setFigureType(Enums::FigureType::Rectangle); });

    // Указание текущих значений свойств отрезка - посредством сигналов от 
    // LineWidget эти значения будут переданы в виджеты-ползунки, а от 
    // них - в виджеты-счетчики. 
    const int LINE_W = 5, LINE_ANGLE = 45;
    m_lineWidget->setWidth(LINE_W);
    m_lineWidget->setAngle(LINE_ANGLE);
}