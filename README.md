Format
======

Minimal C++ type-safe formatting ( inspired by boost-format ), requires C++11


Usage
-----


```cpp
cout << Format("format {} example") % "string";             // format string example
cout << Format("{} {} {} {}") % "hello" % 1 % 3.14 % 2.4f;  // hello 1 3.140000 2.400000
cout << Format("{}{}{}{}{}") % 'h' % 'e' % 'l' % 'l' % 'o'; // hello

char *ptr = (char *)"test";
cout << Format("char pointer : {} ") % ptr;                 // char pointer : test
ptr = nullptr;
cout << Format("null char pointer : {} ") % ptr;            // null char pointer : (null)
	
auto * test = new int;
cout << Format("pointer : {}") % test;                      // pointer : 0x00007f815a4000e0
delete test;
test = nullptr;
cout << Format("null pointer : {}") % test;                 // null pointer : 0x0000000000000000
	
auto test2 = make_shared<int>();
cout << Format("shared_ptr : {}") % test2;                  // shared_ptr : 0x00007fa610403958
```

Tested Environments
-------------------

* XCode 4.5.2 on Mac OS X 10.8.2
* GCC 4.7.2 on Ubuntu 12.10
* Visual Studio 2012 on Windows 7

License
-------

Free

