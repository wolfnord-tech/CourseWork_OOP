#ifndef CL_BASE_H
#define CL_BASE_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class cl_base;

#define SIGNAL_D(signal_f) (TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f) (TYPE_HANDLER)(&handler_f)
typedef void (cl_base::* TYPE_SIGNAL) (string& msg);
typedef void (cl_base::* TYPE_HANDLER) (string msg);

struct o_sh
{
	TYPE_SIGNAL p_signal;
	cl_base* p_target;
	TYPE_HANDLER p_handler;
};

class cl_base {
private:
	string s_name; // ��� �������
	cl_base* p_head_object; // ��������� �� ������������ ������
	vector <cl_base*> p_sub_objects; // ������ ���������� �� �������� �������
	vector <o_sh*> connects;
	int state = 0;
public:
	string coord;
	string cur_coord;
	cl_base(cl_base* p_head_object, string s_name = "Base object"); // ����������� � ���������� �� ������������ ������ � ������ �������
	~cl_base(); // ����������
	bool set_name(string s_new_name); // ����� ��������� ������ ����� �������
	string get_name(); // ����� ��������� ����� �������
	cl_base* get_head(); // ����� ��������� ��������� �� ������������ ������
	void print_tree(); // ����� ������ ����� ��������
	cl_base* get_sub_object(string s_name); // ����� ��������� ��������� �� �������� ������

	int count(string s_name);
	cl_base* search_object(string name);
	cl_base* find_object_from_current(string s_name);
	cl_base* find_object_from_root(string s_name);

	void set_status(int state_num);
	void print_tree_from_current(string tab = "");
	void print_status(string tab = "");

	cl_base* find_obj_by_coord(string s_coord);
	bool move_current_object_from_head(cl_base* new_obj);
	void delete_sub_obj_from_current(string s_name);
	bool is_not_sub_of_current(cl_base* new_head, cl_base* cur_obj);
	cl_base* get_root();

	void set_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler); // ����� ��������� ����������
	void delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler); // ����� �������� ����������
	void emit_connection(TYPE_SIGNAL p_signal, string s_message); // ������ ������� �� ������� �������
	int get_class_num();
	string abs_coord_of_obj();
	void destroy_connects(cl_base* p_target);
};

#endif