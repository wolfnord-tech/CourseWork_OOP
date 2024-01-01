#ifndef CL_APPLICATION
#define CL_APPLICATION
#include "cl_base.h"
#include "cl_1.h"

// Объявляется класс cl_application, который наследует класс cl_base
class cl_application : public cl_base
{
private:
	vector <string> errors;
public:
	cl_application(cl_base* p_head_object); // Конструктор с указателем на родительский объект
	void build_tree_objects(); // Метод построения древа объектов
	int exec_app(); // Метод запуска приложения
	TYPE_SIGNAL get_signal(int num);
	TYPE_HANDLER get_handler(int num);
};

#endif