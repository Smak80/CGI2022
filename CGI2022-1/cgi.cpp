#include "cgi.h"

#include <cstdlib>
#include <cstring>

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