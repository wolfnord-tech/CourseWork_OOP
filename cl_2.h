#ifndef __CL_2__H
#define __CL_2__H
#include "cl_base.h"

// ��������� ����� cl_1, ������� ��������� ����� cl_base
class cl_2 : public cl_base
{
public:
	// �����������, ����������� ��������� �� ������������ ������ � ��� �������
	cl_2(cl_base* p_head_object, string s_name);
	void signal_f(string& msg);
	void handler_f(string msg);
};

#endif
