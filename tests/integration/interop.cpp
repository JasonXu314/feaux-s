#include "../../src/hardware/registers.h"
#include "../../src/utils/decls.h"

browser {
	void clg(const char* str);

	expose void cprint() { clg("hi str"); }
	expose ui64 noopregs() { return reinterpret_cast<ui64>(&hw::NOOP_REGS); }
}