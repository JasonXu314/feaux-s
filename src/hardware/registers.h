#ifndef HARDWARE_REGISTERS_H
#define HARDWARE_REGISTERS_H

#include "../utils/decls.h"
#include "../utils/hardware.h"

namespace hw {
struct Registers {
	Registers()
		: flags(0), rip(0), rax(0), rcx(0), rdx(0), rbx(0), rsi(0), rdi(0), rsp(0), rbp(0), r8(0), r9(0), r10(0), r11(0), r12(0), r13(0), r14(0), r15(0) {}
	Registers(const Registers& other) = default;

	Registers& operator=(const Registers& other) = default;

	i64 flags;
	i64 rip;

	union {
		i64 rax;
		i32 eax;
		i16 ax;
		i8 al;
	};
	union {
		i64 rcx;
		i32 ecx;
		i16 cx;
		i8 cl;
	};
	union {
		i64 rdx;
		i32 edx;
		i16 dx;
		i8 dl;
	};
	union {
		i64 rbx;
		i32 ebx;
		i16 bx;
		i8 bl;
	};
	union {
		i64 rsi;
		i32 esi;
		i16 si;
		i8 sil;
	};
	union {
		i64 rdi;
		i32 edi;
		i16 di;
		i8 dil;
	};
	union {
		i64 rsp;
		i32 esp;
		i16 sp;
		i8 spl;
	};
	union {
		i64 rbp;
		i32 ebp;
		i16 bp;
		i8 bpl;
	};
	union {
		i64 r8;
		i32 r8d;
		i16 r8w;
		i8 r8b;
	};
	union {
		i64 r9;
		i32 r9d;
		i16 r9w;
		i8 r9b;
	};
	union {
		i64 r10;
		i32 r10d;
		i16 r10w;
		i8 r10b;
	};
	union {
		i64 r11;
		i32 r11d;
		i16 r11w;
		i8 r11b;
	};
	union {
		i64 r12;
		i32 r12d;
		i16 r12w;
		i8 r12b;
	};
	union {
		i64 r13;
		i32 r13d;
		i16 r13w;
		i8 r13b;
	};
	union {
		i64 r14;
		i32 r14d;
		i16 r14w;
		i8 r14b;
	};
	union {
		i64 r15;
		i32 r15d;
		i16 r15w;
		i8 r15b;
	};
};

const Registers NOOP_REGS;

bool get(const Registers& regs, flag f);

void set(Registers& regs, flag f);

void clr(Registers& regs, flag f);

void* addr(Registers& regs, gpr reg);

i64 get(const Registers& regs, gpr reg);

void set(Registers& regs, gpr reg, i64 value);
}  // namespace hw

#endif