#include "../../src/utils/string.h"

browser {
	expose char* mkstr() {
		string str("test str");

		return str;
	}
}