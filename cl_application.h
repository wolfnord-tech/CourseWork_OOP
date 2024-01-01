#ifndef CL_APPLICATION
#define CL_APPLICATION
#include "cl_base.h"
#include "cl_1.h"

// ����������� ����� cl_application, ������� ��������� ����� cl_base
class cl_application : public cl_base
{
private:
	vector <string> errors;
public:
	cl_application(cl_base* p_head_object); // ����������� � ���������� �� ������������ ������
	void build_tree_objects(); // ����� ���������� ����� ��������
	int exec_app(); // ����� ������� ����������
	TYPE_SIGNAL get_signal(int num);
	TYPE_HANDLER get_handler(int num);
};

#endif