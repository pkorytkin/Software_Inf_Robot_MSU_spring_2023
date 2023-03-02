#include <QApplication>
#include <QStyleFactory>
#include "MainForm.h"

int main(int argc, char** argv)
{
    // Объект-приложение
    QApplication app(argc, argv);

    app.setStyle(QStyleFactory::create("Fusion"));      // Стиль отображения
    app.setApplicationName("LineDrawerWidget");    // Имя приложения

    // Виджет верхнего уровня (parent == nullptr).
    MainForm* mainForm = new MainForm;
    mainForm->show();

    // Вход в главный цикл выборки/обработки сообщений
    return app.exec();
}