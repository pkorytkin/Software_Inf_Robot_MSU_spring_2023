#pragma once
#include <QWidget>
#include "LineDrawerWidget.h"
class MainForm : public QWidget {
    Q_OBJECT

public:
    explicit MainForm(QWidget* parent = nullptr);

private:
    LineDrawerWidget* m_lineDrawerWidget{ nullptr };
};