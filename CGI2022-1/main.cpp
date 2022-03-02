#include <iostream>
#include <fstream>
using namespace std;

void show_content();
void show_menu();

void show_header();

void main()
{
	cout << "Content-type: text/html; charset=Windows-1251\n\n";
	ifstream f("_index");
	if (f.is_open())
	{
		auto sz = 65536;
		auto buf = new char[sz];
		while (!f.eof())
		{
			f.getline(buf, sz);
			if (strcmp(buf, "<!--#CONTENT#-->")==0)
			{
				show_content();
			} else if (!strcmp(buf, "<!--#MENU#-->"))
			{
				show_menu();
			} else if (!strcmp(buf, "<!--#HEADER#-->"))
			{
				show_header();
			}
			cout << buf;
		}
		delete[] buf;
		f.close();
	} else
	{
		cout << "Не удалось вывести страницу :(";
	}
	
}

void show_header()
{
	cout << "Главная страница";
}
void show_menu()
{
	ifstream f("menu");
	if (f.is_open())
	{
		auto sz = 1024;
		auto buf = new char[sz];
		while (!f.eof())
		{
			f.getline(buf, sz);
			char* name;
			char* addrr = strtok_s(buf, " ", &name);
			cout << "<div class='menu-item'>"
			"<a href='" << addrr << "'>" <<
			name << "</a>"
			"</div>";
		}
	}
	f.close();
}

void show_content()
{
	cout << "А это дополнительный текст на первой странице";
}