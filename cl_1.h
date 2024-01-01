#ifndef CL_1__H
#define CL_1__H
#include "cl_base.h"

// Объявляем класс cl_1, который наследует класс cl_base
class cl_1 : public cl_base
{
public:
	// Конструктор, принимающий указатель на родительский объект и имя объекта
	cl_1(cl_base* p_head_object, string s_name);
	void signal_f(string& msg);
	void handler_f(string msg);
};

#endif

