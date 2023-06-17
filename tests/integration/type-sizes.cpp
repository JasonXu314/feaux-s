#include "../../src/utils/decls.h"

browser {
	expose i16 i8s() { return sizeof(i8); }
	expose i16 i16s() { return sizeof(i16); }
	expose i16 i32s() { return sizeof(i32); }
	expose i16 i64s() { return sizeof(i64); }
	expose i16 ui8s() { return sizeof(ui8); }
	expose i16 ui16s() { return sizeof(ui16); }
	expose i16 ui32s() { return sizeof(ui32); }
	expose i16 ui64s() { return sizeof(ui64); }
}