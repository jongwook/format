
#include <iostream>

#include "format.h"

using namespace std;

int main() {
	cout << Format("format {} example") % "string" << endl;
	cout << Format("{} {} {} {}") % "hello" % 1 % 3.14 % 2.4f << endl;
	cout << Format("{}{}{}{}{}") % 'h' % 'e' % 'l' % 'l' % 'o' << endl;
	
	char *ptr = (char *)"test";
	cout << Format("char pointer : {} ") % ptr << endl;
	ptr = nullptr;
	cout << Format("null char pointer : {} ") % ptr << endl;
	
	auto * test = new int;
	cout << Format("pointer example : {}") % test << endl;
	delete test;
	test = nullptr;
	cout << Format("null pointer example : {}") % test << endl;
	
	auto test2 = make_shared<int>();
	cout << Format("shared_ptr example : {}") % test2 << endl;
	
	return 0;
}


