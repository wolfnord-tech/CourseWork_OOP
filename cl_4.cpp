#include "cl_4.h"

// Конструктор, принимающий указатель на родительский объект и имя объекта
cl_4::cl_4(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name)
{

}

void cl_4::signal_f(string& msg)
{
	cout << endl << "Signal from " << abs_coord_of_obj();
	msg += " (class: 4)";
}

void cl_4::handler_f(string msg)
{
	cout << endl << "Signal to " << abs_coord_of_obj() << " Text: " << msg;
}