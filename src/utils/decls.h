#ifndef UTILS_DECLS_H
#define UTILS_DECLS_H

typedef char i8;
typedef unsigned char ui8;
typedef short int i16;
typedef unsigned short int ui16;
typedef int i32;
typedef unsigned int ui32;
typedef long l32;
typedef unsigned long ul32;
typedef long long i64;
typedef unsigned long long ui64;

#define browser extern "C"
#define expose __attribute__((visibility("default")))

browser {
	void jslog(const char* msg);
	void jslogn(ui64 num);
	void jsthrow(const char* msg);
	void jsfassert(const char* expr, const char* file, ui64 line, const char* fn);
}

#define assert(expr) (static_cast<bool>(expr) ? void(0) : jsfassert(#expr, __FILE__, __LINE__, __PRETTY_FUNCTION__))

#endif