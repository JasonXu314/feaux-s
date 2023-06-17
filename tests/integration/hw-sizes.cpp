#include "../../src/hardware/registers.h"

browser {
	expose i16 registers() { return sizeof(hw::Registers); }
}