#ifndef __CL_5__H
#define __CL_5__H
#include "cl_base.h"

// ��������� ����� cl_1, ������� ��������� ����� cl_base
class cl_5 : public cl_base
{
public:
	// �����������, ����������� ��������� �� ������������ ������ � ��� �������
	cl_5(cl_base* p_head_object, string s_name);
	void signal_f(string& msg);
	void handler_f(string msg);
};

#endif
