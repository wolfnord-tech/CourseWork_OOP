#include <iostream>
#include <algorithm>
#include "cl_base.h"
using namespace std;

// Конструктор с указателем на родительский объект и именем объекта
cl_base::cl_base(cl_base* p_head_object, string s_name)
{
	this->p_head_object = p_head_object;
	this->s_name = s_name;
	// Если родительский объект существует, то добавляем текущий объект в его вектор дочерних объектов
	if (p_head_object != nullptr) {
		p_head_object->p_sub_objects.push_back(this);
	}
}

// Деструктор
cl_base::~cl_base()
{
	destroy_connects(this);
	// Удаляем все дочерние объекты
	// for (int i = 0; i < p_sub_objects.size(); i++)
		// delete p_sub_objects[i];
}

// Метод получения нового имени
string cl_base::get_name()
{
	return s_name;
}

// Метод получения указателя на родительский объект
cl_base* cl_base::get_head()
{
	return p_head_object;
}

// Метод получения указателя на дочерний объект
cl_base* cl_base::get_sub_object(string s_name)
{
	for (int i = 0; i < p_sub_objects.size(); i++)
		if (p_sub_objects[i]->get_name() == s_name)
			return p_sub_objects[i];
	return nullptr;
}

// Метод печати древа объектов
void cl_base::print_tree()
{
	// Если текущий объект имеет дочерние объекты
	if (!p_sub_objects.empty())
	{
		// Печатаем имя текущего объекта и имени его дочерних объектов
		cout << endl << get_name();
		for (int i = 0; i < p_sub_objects.size(); i++)
		{
			cout << "  " << p_sub_objects[i]->get_name();
			// Рекурсивно печатем дерево дочерних объектов
			p_sub_objects[i]->print_tree();
		}
	}
}

// Метод установки нового имени
bool cl_base::set_name(string s_new_name)
{
	// Если родительский объект существует, то проверяем, что новое имя не совпадает с именами дочерних объектов
	if (p_head_object != nullptr)
		for (int i = 0; i < get_head()->p_sub_objects.size(); i++)
			if (get_head()->p_sub_objects[i]->get_name() == s_new_name)
				return false;
	// Устанавливаем новое имя объекта
	this->s_name = s_new_name;
	return true;
}

int cl_base::count(string s_name)
{
	// ---------------------------------------
	// Метод определения количества вхождений объектов 
	// с данным именем от текущего
	// ---------------------------------------

	int counter = 0; // Счетчик

	if (this->get_name() == s_name) // Проверка текущего элемента
		counter++;

	for (auto p_sub_object : p_sub_objects)   // Цикл по подчиненным объектам
		counter += p_sub_object->count(s_name); // Метод вызывается для подчиненного объекта

	return counter;
}

cl_base* cl_base::search_object(string s_name)
{
	// ---------------------------------------
	// Метод осуществляет поиск объекта по имени
	// от текущего и возращает указатель на первое
	// вхождение объекта c требуемым именем.
	// ---------------------------------------

	if (this->get_name() == s_name)
		return this;

	for (auto p_sub_object : p_sub_objects)   // Цикл по подчиненным объектам
	{
		cl_base* p_found = p_sub_object->find_object_from_current(s_name);
		if (p_found != nullptr)
			return p_found;
	}
	return nullptr;
}

cl_base* cl_base::find_object_from_current(string s_name)
{
	if (this->count(s_name) != 1)
		return nullptr;
	return search_object(s_name);
}

void cl_base::print_status(string tab)
{
	string state_str;
	if (this->state != 0)
		state_str = " is ready";
	else
		state_str = " is not ready";
	cout << tab << this->s_name << state_str;

	for (auto p_sub_object : p_sub_objects)
	{
		cout << endl;
		p_sub_object->print_status(tab + "    ");
	}
}

cl_base* cl_base::find_object_from_root(string s_name)
{
	cl_base* temp = this;
	while (temp->get_head() != nullptr)
		temp = temp->get_head();
	return temp->find_object_from_current(s_name);
}

void cl_base::print_tree_from_current(string tab)
{
	cout << tab << this->s_name;
	for (auto p_sub_object : p_sub_objects) {
		cout << endl;
		p_sub_object->print_tree_from_current(tab + "    ");
	}
}

void cl_base::set_status(int state_num)
{
	bool p_head_ready = true;
	if (get_head() != nullptr) {
		cl_base* current_obj = get_head();
		while (current_obj != nullptr) {
			if (current_obj->state == 0) {
				p_head_ready = false;
				break;
			}
			current_obj = current_obj->get_head();
		}
	}
	if (p_head_ready || state_num == 0)
	{
		this->state = state_num;
		if (state_num == 0)
			for (auto p_sub_object : p_sub_objects)
				p_sub_object->set_status(0);
	}
}

cl_base* cl_base::get_root()
{
	cl_base* p_root = this;
	while (p_root->get_head() != nullptr)
		p_root = p_root->get_head();
	return p_root;
}

cl_base* cl_base::find_obj_by_coord(string s_coord)
{
	// ---------------------------------------
	// Метод осуществляет поиск объекта по координате
	// ---------------------------------------
	string 		s_name;
	int 		i_slash_2;
	cl_base* p_obj = nullptr;
	// ---------------------------------------

	if (s_coord == "")
		return nullptr;

	if (s_coord == "/")
		return get_root();

	if (s_coord == ".")
		return this;

	if (s_coord[0] == '/' && s_coord[1] == '/')
	{
		s_name = s_coord.substr(2);
		return this->find_object_from_root(s_name);
	}

	if (s_coord[0] == '.')
	{
		s_name = s_coord.substr(1);
		return this->find_object_from_current(s_name);
	}

	i_slash_2 = s_coord.find("/", 1);

	if (s_coord[0] == '/')
	{
		if (i_slash_2 != -1)
		{
			s_name = s_coord.substr(1, i_slash_2 - 1);

			p_obj = this->get_sub_object(s_name);

			if (p_obj != nullptr)
				return p_obj->find_obj_by_coord(s_coord.substr(i_slash_2 + 1));
			else
				return p_obj;
		}
		else
		{
			s_name = s_coord.substr(1);
			return get_root()->get_sub_object(s_name);
		}
	}
	else
	{
		if (i_slash_2 != -1)
		{
			s_name = s_coord.substr(0, i_slash_2);
			p_obj = this->get_sub_object(s_name);

			if (p_obj != nullptr) {
				return p_obj->find_obj_by_coord(s_coord.substr(i_slash_2 + 1));
			}
			else
				return p_obj;
		}
		else
		{
			s_name = s_coord;
			return this->get_sub_object(s_name);
		}
	}
}

bool cl_base::is_not_sub_of_current(cl_base* new_head, cl_base* cur_obj)
{
	if (new_head != cur_obj && new_head != get_root())
		return is_not_sub_of_current(new_head->get_head(), cur_obj);
	else if (new_head == get_root())
		return true;
	else
		return false;
}

bool cl_base::move_current_object_from_head(cl_base* new_obj)
{
	if (this != get_root())
		if (new_obj != get_root())
			if (new_obj->get_sub_object(s_name) == nullptr)
				if (is_not_sub_of_current(new_obj, this)) {
					cl_base* obj = search_object(this->get_name());
					if (obj != nullptr) {
						for (int i = 0; i < obj->get_head()->p_sub_objects.size(); i++)
							if (obj->get_head()->p_sub_objects[i]->get_name() == s_name)
								obj->get_head()->p_sub_objects.erase(obj->get_head()->p_sub_objects.begin() + i);
						p_head_object = new_obj;
						new_obj->p_sub_objects.push_back(this);
						cout << "New head object: " << new_obj->get_name() << endl;
						return true;
					}
				}
				else
					cout << coord << "     " << "Redefining the head object failed" << endl;
			else
				cout << coord << "     " << "Dubbing the names of subordinate objects" << endl;
		else
			cout << coord << "     " << "Redefining the head object failed" << endl;
	else
		cout << coord << "     " << "Redefining the head object failed" << endl;
	return false;
}

void cl_base::delete_sub_obj_from_current(string s_name)
{
	cl_base* obj = search_object(s_name);
	if (obj == nullptr)
		return;
	else {
		cout << "The object " << cur_coord + '/' + s_name << " has been deleted" << endl;
		for (int i = 0; i < obj->get_head()->p_sub_objects.size(); i++)
			if (obj->get_head()->p_sub_objects[i]->get_name() == s_name)
				obj->get_head()->p_sub_objects.erase(obj->get_head()->p_sub_objects.begin() + i);
		delete search_object(s_name);
	}
}

void cl_base::set_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler) // Метод установки соединения
{
	if (p_signal != nullptr && p_target != nullptr && p_handler != nullptr) {
		o_sh* p_value;
		for (int i = 0; i < connects.size(); i++)
			if (connects[i]->p_signal == p_signal && connects[i]->p_target == p_target && connects[i]->p_handler == p_handler)
				return;
		p_value = new o_sh();
		p_value->p_signal = p_signal;
		p_value->p_target = p_target;
		p_value->p_handler = p_handler;
		connects.push_back(p_value);
	}
}

void cl_base::delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler) // Метод удаления соединения
{
	if (p_signal != nullptr && p_target != nullptr && p_handler != nullptr) {
		for (int i = 0; i < connects.size(); i++)
			if (connects[i]->p_signal == p_signal && connects[i]->p_target == p_target && connects[i]->p_handler == p_handler)
				connects.erase(connects.begin() + i);
	}
}

void cl_base::emit_connection(TYPE_SIGNAL p_signal, string s_message) // Запуск сигнала на текущем объекте
{
	if (p_signal != nullptr) {
		if (get_class_num() == 0) return;
		(this->*p_signal)(s_message);
		for (auto connection : connects)
		{
			if (connection->p_signal == p_signal && connection->p_target->get_class_num() != 0)
			{
				cl_base* p_target = connection->p_target;
				TYPE_HANDLER p_handler = connection->p_handler;

				(p_target->*p_handler)(s_message);
			}
		}
	}
}

string cl_base::abs_coord_of_obj()
{
	if (!p_head_object)
		return "/";
	if (p_head_object->p_head_object == nullptr)
		return "/" + get_name();
	return p_head_object->abs_coord_of_obj() + "/" + get_name();
}

int cl_base::get_class_num()
{
	return state;
}

void cl_base::destroy_connects(cl_base* p_target)
{
	for (int i = 0; i < connects.size(); i++)
		if (connects[i]->p_target == p_target)
		{
			delete this->connects[i];
			connects.erase(connects.begin() + i);
		}
	for (auto p_sub_object : p_sub_objects)
		p_sub_object->destroy_connects(p_target);
}
