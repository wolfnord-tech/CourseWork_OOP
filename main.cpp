#include "cl_application.h"

int main() // Основная функция программы
{
	cl_application ob_cl_application(nullptr); // Создания объекта приложения с передачей ему указателя на родительский объект
	ob_cl_application.build_tree_objects(); // Построение древа объектов
	return ob_cl_application.exec_app(); // Запуск приложения
}
