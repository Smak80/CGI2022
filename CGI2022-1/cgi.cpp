#include "cgi.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>

/**
 * ����������� ������, � ������� �������� ������ ������
 */
bool is_get()
{
	size_t realsize;
	char* value = new char[5];
	getenv_s(&realsize, value, 5, "REQUEST_METHOD");
	bool res = !_strcmpi(value, "GET");
	delete[] value;
	return res;
}

/**
 * ��������� ���������� � ����� ��������� �� ������������, �����������
 * ������� POST
 */
size_t get_content_length()
{
	size_t realsize;
	char* value = new char[11];
	getenv_s(&realsize, value, 11, "CONTENT_LENGTH");
	size_t size;
	if (!realsize) size = 0;
	else sscanf_s(value, "%d", &size);
	delete[] value;
	return size;
}

/**
 * ��������� ������ �� ����� � �������������� ����
 */
void get_form_data(char*& data)
{
	delete[] data;
	if (is_get())
	{
		size_t realsize;
		char* value = new char[65536];
		getenv_s(&realsize, value, 65536, "QUERY_STRING");
		data = new char[realsize + 1];
		strcpy_s(data, realsize + 1, value);
		delete[] value;
	}
	else
	{
		size_t buf_size = get_content_length();
		data = new char[buf_size + 1];
		fread_s(
			data, 
			buf_size + 1, 
			sizeof(char), 
			buf_size, 
			stdin
		);
		data[buf_size] = 0;
	}
}

/**
 * ��������� �������� ����������� ���������, ����������� �� ������������
 */
void get_param_value(char*& value, const char* param_name, const char* data)
{
	delete[] value;
	char* str = _strdup(data);
	char* tmp = str;
	char* cont;
	while (char* part = strtok_s(tmp, "&", &cont))
	{
		tmp = nullptr;
		char* val;
		char* key = strtok_s(part, "=", &val);
		if (!_strcmpi(param_name, key))
		{
			//str_decode(value, val);
			value = _strdup(val);
			delete[] str;
			return;
		}
	}
	delete[] str;
	value = new char[1];
	value[0] = 0;
}