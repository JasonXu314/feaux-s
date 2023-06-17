#include "string.h"

string::string(const char* str) : _length(0), _capacity(10), _str(new char[10]) {
	ui32 i = 0;
	char c;
	while ((c = str[i++])) {
		_insert(c);
	}
}

bool string::operator==(const string& other) {
	if (_length != other._length) {
		return false;
	}

	for (ui32 i = 0; i < _length; i++) {
		if (_str[i] != other._str[i]) {
			return false;
		}
	}

	return true;
}

string::operator char*() const {
	char* cstr = new char[_length];

	for (ui32 i = 0; i < _length; i++) {
		cstr[i] = _str[i];
	}

	return cstr;
}

string::~string() {
	if (_str != nullptr) {
		delete[] _str;
	}
}

void string::_resize() {
	ui32 newCapacity = _capacity * 2;
	char* newStr = new char[newCapacity];

	for (ui32 i = 0; i < _capacity; i++) {
		newStr[i] = _str[i];
	}

	delete[] _str;
	_str = newStr;
	_capacity = newCapacity;
}

void string::_insert(char c) {
	if (_length == _capacity) {
		_resize();
	}

	_str[_length++] = c;
}