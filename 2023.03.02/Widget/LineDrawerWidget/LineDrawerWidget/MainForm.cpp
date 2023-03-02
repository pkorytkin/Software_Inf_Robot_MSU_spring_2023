#include <QVBoxLayout>
#include <QPen>
#include <QGroupBox>
#include <QPushButton>
#include "MainForm.h"
MainForm::MainForm(QWidget* parent) :
    QWidget(parent)
{
    const int LEFT_OFS = 10, TOP_OFS = 10;
    const int IMG_W = 200, IMG_H = 200;

    m_lineDrawerWidget = new LineDrawerWidget(this);
    m_lineDrawerWidget->setGeometry(LEFT_OFS, TOP_OFS, IMG_W, IMG_H);

    QPushButton* button = new QPushButton("Clean",this);
    button->setGeometry(LEFT_OFS, TOP_OFS*2+ IMG_H, 150, 40);
    connect(button, &QPushButton::clicked, [this] {m_lineDrawerWidget->cleanPoints(); });
}
