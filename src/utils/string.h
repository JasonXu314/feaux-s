#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include "decls.h"

class string {
public:
	string() : _length(0), _capacity(0), _str(nullptr) {}
	string(const char* str);

	bool operator==(const string* other);

	operator char*() const;

	~string();

private:
	ui32 _length;
	ui32 _capacity;
	char* _str;

	void _resize();

	void _insert(char c);
};

#endif