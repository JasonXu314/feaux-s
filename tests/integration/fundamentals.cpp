#define MEM_DEBG_VERBOSE
#include "../../src/utils/mem.h"

browser {
	expose ui64 allocAndWrite() {
		ui64* mem = reinterpret_cast<ui64*>(malloc(sizeof(ui64) * 4));

		mem[0] = 69;
		mem[1] = 420;
		mem[2] = 0xAB;
		mem[3] = 0xCD;

		memset(mem + 8, sizeof(ui64) * 4, 0xFF);

		return reinterpret_cast<ui64>(mem);
	}

	expose ui64 tcalloc() { return reinterpret_cast<ui64>(calloc(2, sizeof(ui64))); }

	expose ui64 tnew() {
		ui64* mem = new ui64[2];

		mem[0] = 69;
		mem[1] = 420;

		return reinterpret_cast<ui64>(mem);
	}

	expose void fassert() { assert(false); }
}