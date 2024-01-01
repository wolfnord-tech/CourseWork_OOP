#include "cl_6.h"

// Конструктор, принимающий указатель на родительский объект и имя объекта
cl_6::cl_6(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name)
{

}

void cl_6::signal_f(string& msg)
{
	cout << endl << "Signal from " << abs_coord_of_obj();
	msg += " (class: 6)";
}

void cl_6::handler_f(string msg)
{
	cout << endl << "Signal to " << abs_coord_of_obj() << " Text: " << msg;
}