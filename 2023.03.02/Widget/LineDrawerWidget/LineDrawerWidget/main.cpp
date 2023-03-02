#include <QApplication>
#include <QStyleFactory>
#include "MainForm.h"

int main(int argc, char** argv)
{
    // ������-����������
    QApplication app(argc, argv);

    app.setStyle(QStyleFactory::create("Fusion"));      // ����� �����������
    app.setApplicationName("LineDrawerWidget");    // ��� ����������

    // ������ �������� ������ (parent == nullptr).
    MainForm* mainForm = new MainForm;
    mainForm->show();

    // ���� � ������� ���� �������/��������� ���������
    return app.exec();
}