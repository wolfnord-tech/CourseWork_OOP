#include "cl_application.h"
#include "cl_1.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"

// Конструктор с указателем на родительский объект
cl_application::cl_application(cl_base* p_head_object) : cl_base(p_head_object)
{

}

// Метод построения дерева объектов
void cl_application::build_tree_objects()
{
	string s_sub_name, s_head_name;
	cl_base* p_head = this;
	cl_base* p_sub = nullptr;
	p_head->set_status(1);
	int i_class, i_state;

	// Считываем имя родительского объекта
	cin >> s_head_name;
	this->set_name(s_head_name);

	// Ввод иерархии объектов
	while (cin >> s_head_name)
	{
		// Считываем имя родительского объекта и дочернего объектов
		// cin >> s_head_name;
		// Если имена совпадают, то прекращаем считывание
		if (s_head_name == "endtree")
			break;

		cin >> s_sub_name >> i_class;

		if (find_obj_by_coord(s_head_name) != nullptr) {
			p_head = find_obj_by_coord(s_head_name);
			s_head_name = p_head->get_name();
		}
		else {
			errors.push_back("The head object " + s_head_name + " is not found");
			continue;
		}

		if (i_class < 2 || i_class > 6)
			exit(0);

		p_sub = p_head->get_sub_object(s_sub_name);
		if (p_sub == nullptr && p_head != nullptr)
		{
			switch (i_class)
			{
			case 2: p_sub = new cl_2(p_head, s_sub_name); p_sub->set_status(2); break;
			case 3: p_sub = new cl_3(p_head, s_sub_name); p_sub->set_status(3); break;
			case 4: p_sub = new cl_4(p_head, s_sub_name); p_sub->set_status(4); break;
			case 5: p_sub = new cl_5(p_head, s_sub_name); p_sub->set_status(5); break;
			case 6: p_sub = new cl_6(p_head, s_sub_name); p_sub->set_status(6); break;
			default: break;
			}
		}
	}
}

TYPE_SIGNAL cl_application::get_signal(int num)
{
	switch (num) {
	case 1:
		return SIGNAL_D(cl_1::signal_f); break;
	case 2:
		return SIGNAL_D(cl_2::signal_f); break;
	case 3:
		return SIGNAL_D(cl_3::signal_f); break;
	case 4:
		return SIGNAL_D(cl_4::signal_f); break;
	case 5:
		return SIGNAL_D(cl_5::signal_f); break;
	case 6:
		return SIGNAL_D(cl_6::signal_f); break;
	default:
		return nullptr;
		break;
	}
}

TYPE_HANDLER cl_application::get_handler(int num)
{
	switch (num) {
	case 1:
		return HANDLER_D(cl_1::handler_f); break;
	case 2:
		return HANDLER_D(cl_2::handler_f); break;
	case 3:
		return HANDLER_D(cl_3::handler_f); break;
	case 4:
		return HANDLER_D(cl_4::handler_f); break;
	case 5:
		return HANDLER_D(cl_5::handler_f); break;
	case 6:
		return HANDLER_D(cl_6::handler_f); break;
	default:
		return nullptr;
		break;
	}
}

// Метод запуска приложения
int cl_application::exec_app()
{
	// Печатаем имя текущего объекта и дерево его дочерних объектов
	cout << "Object tree" << endl;
	print_tree_from_current();
	for (int i = 0; i < errors.size(); i++)
		if (i == errors.size() - 1)
			cout << errors[i];
		else
			cout << errors[i] << endl;
	string cmd, coord, args;
	string coord1, coord2;
	// cl_base* cur_obj = this;
	cl_base* p_obj = this;
	cl_base* p_target = this;
	// int i_cur_class = p_obj->get_class_num();
	// int i_target_class = p_obj->get_class_num();
	while (cin >> coord1)
	{
		if (coord1 == "end_of_connections")
		{
			break;
		}
		else
		{
			cin >> coord2;
			if (find_obj_by_coord(coord1) == nullptr)
			{
				cout << endl << "Object " + coord1 + " not found";
			}
			if (find_obj_by_coord(coord2) == nullptr)
			{
				cout << endl << "Object " + coord2 + " not found";
			}
			else
			{
				p_obj = find_obj_by_coord(coord1);
				p_target = find_obj_by_coord(coord2);
				p_obj->set_connection(get_signal(p_obj->get_class_num()), p_target, get_handler(p_target->get_class_num()));
			}
		}
	}
	cin.ignore();
	while (cin >> cmd >> coord)
	{
		getline(cin, args);
		if (cmd == "END")
		{
			break;
		}
		if (cmd == "EMIT")
		{
			p_obj = find_obj_by_coord(coord);
			if (p_obj == nullptr)
				cout << endl << "Object " + coord + " not found";
			else
				p_obj->emit_connection(get_signal(p_obj->get_class_num()), args);
		}
		else if (cmd == "SET_CONNECT")
		{
			args = args.substr(1);
			p_obj = find_obj_by_coord(coord);
			p_target = find_obj_by_coord(args);
			if (p_obj == nullptr)
				cout << endl << "Object " << coord << " not found";
			if (p_target == nullptr)
				cout << endl << "Handler object " << args << " not found";
			else
				p_obj->set_connection(get_signal(p_obj->get_class_num()), p_target, get_handler(p_target->get_class_num()));
		}
		else if (cmd == "DELETE_CONNECT")
		{
			args = args.substr(1);
			p_obj = find_obj_by_coord(coord);
			p_target = find_obj_by_coord(args);
			if (p_obj == nullptr)
				cout << endl << "Object " << coord << " not found";
			if (p_target == nullptr)
				cout << endl << "Handler object " << p_target << " not found";
			else
				p_obj->delete_connection(get_signal(p_obj->get_class_num()), p_target, get_handler(p_target->get_class_num()));
		}
		else if (cmd == "SET_CONDITION")
		{
			args = args.substr(1);
			p_obj = find_obj_by_coord(coord);
			if (p_obj == nullptr)
				cout << endl << "Object " << coord << " not found";
			else
				p_obj->set_status(stoi(args));
		}
	}
	return 0;
}