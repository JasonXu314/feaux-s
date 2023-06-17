#ifndef HARDWARE_CPU_H
#define HARDWARE_CPU_H

#include "../utils/decls.h"
#include "registers.h"

namespace hw {
class CPU {
public:
	CPU() = default;

	Registers regs() const { return _regs; }
	Registers replaceRegs(const Registers& regs);
	void setRegs(const Registers& regs) { _regs = regs; }

	void tick();

private:
	Registers _regs;
};
}  // namespace hw

#endif