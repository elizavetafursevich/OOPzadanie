#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <map>
#include <vector>
using namespace std;
class phonebook
{
public:
	vector <pair<string, string>> list;
	int get(string);
	int show();
	int size();
	int find(string);
	int save(string);
	int already_here(string);
	int del(string);
	int sort_by_name();
	int sort_by_number();
};
int phonebook::get(string sinp)
{
	string sany;
	sany = sinp;
	sinp.erase(sinp.find("-"), sinp.size());
	sany.erase(0, sany.find("-") + 1);
	list.push_back(pair<string, string>(sinp, sany));
	return 0;
}
int phonebook::show()
{
	cout << endl << "Телефонная книга:";
	cout << endl << "__________________________________________________" << endl<<endl;
	for (int i = 0; i != list.size(); i++)
	{
		cout << list[i].first << "-" << list[i].second << endl;
	}
	cout << "__________________________________________________" << endl;
	return 0;
}
int phonebook::size()
{
	return list.size();
}
int phonebook::sort_by_name()
{
	map <string, string>list_prefab;
	map <string, string>::iterator it;
	stringstream ssflow;
	string sinp;
	for (int i = 0; i != list.size(); i++)
	{
		list_prefab.insert(pair<string, string>(list[i].first, list[i].second));
	}
	list.clear();
	for (it = list_prefab.begin(); it != list_prefab.end(); ++it)
	{
		ssflow << (*it).first << "-" << (*it).second;
		ssflow >> sinp;
		ssflow.clear();
		get(sinp);
	}
	return 0;
}
int phonebook::sort_by_number()
{
	map <string, string>list_prefab;
	map <string, string>::iterator it;
	stringstream ssflow;
	string sinp;
	for (int i = 0; i != list.size(); i++)
	{
		list_prefab.insert(pair<string, string>(list[i].second, list[i].first));
	}
	list.clear();
	for (it = list_prefab.begin(); it != list_prefab.end(); ++it)
	{
		ssflow << (*it).second << "-" << (*it).first;
		ssflow >> sinp;
		ssflow.clear();
		get(sinp);
	}
	return 0;
}
int phonebook::find(string sinp)
{
	cout << endl << "__________________________________________________" << endl;
	int iflag = 1;
	for (int i = 0; iflag == 1; i++)
	{
		if (list[i].first == sinp)
		{
			cout << "По имени абонента (" << list[i].first << ") найден номер: " << list[i].second << endl;
			iflag = 0;
		}
		if (list[i].second == sinp)
		{
			cout << "По имени абонента (" << list[i].first << ") найден номер: " << list[i].second << endl;
			iflag = 0;
		}
		if (i == list.size() - 1 && iflag != 0)
		{
			cout << "Ошибка: для введенных данных (" << sinp << ") не найдено соответствий.";
			iflag = 0;
		}
	}

	return 0;
}
int phonebook::save(string sname)
{
	ofstream fs_clear(sname);
	fs_clear << "";
	fstream fs_save(sname);
	if (fs_save)
	{
		string str = "";
		for (int i = 0; i != list.size(); i++)
		{
			str = str + (list[i].first + "-" + list[i].second + "\n");
		}
		fs_save << str;
		cout << endl << "Книга сохранена.";
	}
	return 0;
}
int phonebook::already_here(string sinp)
{
	int iflag = 0, irez;
	for (int i = 0; iflag == 0; i++)
	{
		if (list[i].first == sinp)
		{
			iflag = 1;
			irez = 1;
		}
		if (list[i].second == sinp)
		{
			iflag = 1;
			irez = 1;
		}
		if (i == list.size() - 1 && iflag != 1)
		{
			iflag = 1;
			irez = 0;
		}
	}
	return irez;
}
int phonebook::del(string sinp)
{
	cout << endl << "__________________________________________________" << endl;
	int iflag = 1;
	map <string, string>list_prefab;
	map <string, string>::iterator it;
	string swtdel;
	stringstream ssflow;
	for (int i = 0; iflag == 1; i++)
	{
		if (list[i].first == sinp)
		{
			iflag = 0;
			swtdel = "name";
		}
		if (list[i].second == sinp)
		{
			iflag = 0;
			swtdel = "number";
		}
		if (i == list.size() - 1 && iflag != 0)
		{
			cout << "Ошибка: для введенных данных (" << sinp << ") не найдено соответствий.";
			iflag = 0;
		}
		if (swtdel == "name")
		{
			for (int i = 0; i != list.size(); i++)
			{
				if (list[i].first != sinp)
				{
					list_prefab.insert(pair<string, string>(list[i].first, list[i].second));
				}
			}
			list.clear();
			for (it = list_prefab.begin(); it != list_prefab.end(); ++it)
			{
				ssflow << (*it).first << "-" << (*it).second;
				ssflow >> sinp;
				ssflow.clear();
				get(sinp);
			}
		}
		if (swtdel == "number")
		{
			for (int i = 0; i != list.size(); i++)
			{
				if (list[i].second != sinp)
				{
					list_prefab.insert(pair<string, string>(list[i].second, list[i].first));
				}
			}
			list.clear();
			for (it = list_prefab.begin(); it != list_prefab.end(); ++it)
			{
				ssflow << (*it).second << "-" << (*it).first;
				ssflow >> sinp;
				ssflow.clear();
				get(sinp);
			}
		}
	}
	return 0;
}

int main()
{
	phonebook phonebook_base;
	string sfnm, sinp, stask, sany;
	setlocale(LC_ALL, "russian");
	cout << "Введите название телефонной книги:" <<endl << "Ввод: ";
	cin >> sfnm;
	fstream fs_base(sfnm);
	if (fs_base) {
		while (getline(fs_base, sinp, '\n'))
		{
			phonebook_base.get(sinp);
		}
		fs_base.close();
		int iflag = 1, ich;
		while (iflag == 1)
		{
			ich = 0;
			cout <<"==================================================" << endl;
			cout << "Выберите желаемую операцию:" << endl;
			cout << "1. Add - дбавить элемент " << endl;
			cout << "2. Delete - вывести элементы на экран." << endl;
			cout << "3. Find - найти элемент." << endl;
			cout << "4. Show - вывести элементы на экран." << endl;
			cout << "5. Name -  сортировка телефонной книги по имени." << endl;
			cout << "6. Number - сортировка телефонной книги по номеру." << endl;
			cout <<"Ваш выбор: ";
			cin >> stask;
			cout << "==================================================" << endl;

			if (stask == "add" || stask == "Add" || stask == "ADD" || stask == "1")
			{
				ich = 1;
				int icheck = phonebook_base.size();
				cout <<endl<< "Введите имя абонента." << endl << "Ввод:  ";
				cin >> sinp;
				if (phonebook_base.already_here(sinp) == 0)
				{
					cout <<"Введите номер абонента." <<endl << "Ввод:  ";
					cin >> sany;
					if (phonebook_base.already_here(sany) == 0)
					{
						phonebook_base.get(sinp + "-" + sany);
						icheck -= phonebook_base.size();
						if (icheck == -1)
						{
							cout << endl << "__________________________________________________" << endl;
							cout << "Телефон абонента под именем " << sinp << " с номером " << sany <<"."<< endl;
						}
						else
						{
							exit(1);
						}
					}
					else
					{
						cout << endl << "Ошибка: Данный номер уже сущетсвует в телефонной книге." << endl;
					}
				}
				else
				{
					cout << endl << "Ошибка: Данный абонент уже существует в телефонной книге." << endl;
				}
			}
			if (stask == "delete" || stask == "Delete" || stask == "DELETE" || stask == "2")
			{
				ich = 1;
				cout << "Введите номер или имя абонента для удаления." << endl << endl << "Ввод:  ";
				cin >> sinp;
				phonebook_base.del(sinp);
			}
			if (stask == "find" || stask == "Find" || stask == "FIND" || stask == "3")
			{
				ich = 1;
				cout << "Введите номер или имя абонента для поиска." << endl << "Ввод:  ";
				cin >> sinp;
				phonebook_base.find(sinp);
			}
			if (stask == "show" || stask == "Show" || stask == "SHOW" || stask == "4")
			{
				ich = 1;
				phonebook_base.show();
			}
			if (stask == "name" || stask == "Name" || stask == "NAME" || stask == "5")
			{
				ich = 1;
				phonebook_base.sort_by_name();
				cout <<"Книга отсортирована по именам." << endl;
			}
			if (stask == "number" || stask == "Number" || stask == "NUMBER" || stask == "6")
			{
				ich = 1;
				phonebook_base.sort_by_number();
				cout << "Книга отсортирована по номерам." << endl;
			}
			if (ich == 1)
			{
				cout << "Если желаете продолжить, введите Y." << endl << endl << "Ввод:  ";
				cin >> stask;
				if (stask == "y" || stask == "Y")
				{
					iflag = 1;
				}
				else
				{
					iflag = 0;
				}
			}
			else
			{
				iflag = 0;
			}
		}
		cout << "Если хотите сохранить телефонную книгу, введите Y." << endl  << "Ввод:  ";
		cin >> stask;
		if (stask == "y" || stask == "Y")
		{
			phonebook_base.save(sfnm);
		}
		cout << endl << endl;
	}
	else
	{
		cout << endl << "Ошибка: Файл " << sfnm << " не найден.";
	}
	return 0;
}