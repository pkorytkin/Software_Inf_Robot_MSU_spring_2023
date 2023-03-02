// Заголовочные файлы для используемых классов Qt
#include <QApplication>
#include <QLabel>
int main(int argc, char** argv)
{
	// Объект-приложение
	QApplication app(argc, argv);
	// Объект-виджет "текстовая метка"
	QLabel* lbl = new QLabel("Hello, Qt!");
	QLabel* lbl2 = new QLabel("Привет, Qt!");
	lbl->show();
	lbl2->show();
	// Вход в цикл выборки/обработки сообщений
	return app.exec();
}
