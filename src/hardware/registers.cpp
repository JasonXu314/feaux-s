#include "registers.h"

void* hw::addr(Registers& regs, gpr reg) {
	switch (reg) {
		case gpr::RAX:
			return &regs.rax;
		case gpr::EAX:
			return &regs.eax;
		case gpr::AX:
			return &regs.ax;
		case gpr::AL:
			return &regs.al;
		case gpr::RCX:
			return &regs.rcx;
		case gpr::ECX:
			return &regs.ecx;
		case gpr::CX:
			return &regs.cx;
		case gpr::CL:
			return &regs.cl;
		case gpr::RDX:
			return &regs.rdx;
		case gpr::EDX:
			return &regs.edx;
		case gpr::DX:
			return &regs.dx;
		case gpr::DL:
			return &regs.dl;
		case gpr::RBX:
			return &regs.rbx;
		case gpr::EBX:
			return &regs.ebx;
		case gpr::BX:
			return &regs.bx;
		case gpr::BL:
			return &regs.bl;
		case gpr::RSI:
			return &regs.rsi;
		case gpr::ESI:
			return &regs.esi;
		case gpr::SI:
			return &regs.si;
		case gpr::SIL:
			return &regs.sil;
		case gpr::RDI:
			return &regs.rdi;
		case gpr::EDI:
			return &regs.edi;
		case gpr::DI:
			return &regs.di;
		case gpr::DIL:
			return &regs.dil;
		case gpr::RSP:
			return &regs.rsp;
		case gpr::ESP:
			return &regs.esp;
		case gpr::SP:
			return &regs.sp;
		case gpr::SPL:
			return &regs.spl;
		case gpr::RBP:
			return &regs.rbp;
		case gpr::EBP:
			return &regs.ebp;
		case gpr::BP:
			return &regs.bp;
		case gpr::BPL:
			return &regs.bpl;
		case gpr::R8:
			return &regs.r8;
		case gpr::R8D:
			return &regs.r8d;
		case gpr::R8W:
			return &regs.r8w;
		case gpr::R8B:
			return &regs.r8b;
		case gpr::R9:
			return &regs.r9;
		case gpr::R9D:
			return &regs.r9d;
		case gpr::R9W:
			return &regs.r9w;
		case gpr::R9B:
			return &regs.r9b;
		case gpr::R10:
			return &regs.r10;
		case gpr::R10D:
			return &regs.r10d;
		case gpr::R10W:
			return &regs.r10w;
		case gpr::R10B:
			return &regs.r10b;
		case gpr::R11:
			return &regs.r11;
		case gpr::R11D:
			return &regs.r11d;
		case gpr::R11W:
			return &regs.r11w;
		case gpr::R11B:
			return &regs.r11b;
		case gpr::R12:
			return &regs.r12;
		case gpr::R12D:
			return &regs.r12d;
		case gpr::R12W:
			return &regs.r12w;
		case gpr::R12B:
			return &regs.r12b;
		case gpr::R13:
			return &regs.r13;
		case gpr::R13D:
			return &regs.r13d;
		case gpr::R13W:
			return &regs.r13w;
		case gpr::R13B:
			return &regs.r13b;
		case gpr::R14:
			return &regs.r14;
		case gpr::R14D:
			return &regs.r14d;
		case gpr::R14W:
			return &regs.r14w;
		case gpr::R14B:
			return &regs.r14b;
		case gpr::R15:
			return &regs.r15;
		case gpr::R15D:
			return &regs.r15d;
		case gpr::R15W:
			return &regs.r15w;
		case gpr::R15B:
			return &regs.r15b;
		default:
			return nullptr;
	}
}

i64 hw::get(const Registers& regs, gpr reg) {
	i8* regPtr = (i8*)addr((Registers&)regs, reg);

	switch (reg % 4) {
		case 0:
			return *((i64*)regPtr);
		case 1:
			return *((i32*)regPtr);
		case 2:
			return *((i16*)regPtr);
		case 3:
			return *((i8*)regPtr);
		default:
			return -1;
	}
}

void hw::set(Registers& regs, gpr reg, i64 value) {
	i8* regPtr = (i8*)addr((Registers&)regs, reg);

	switch (reg % 4) {
		case 0:
			*((i64*)regPtr) = value;
			break;
		case 1:
			*((i32*)regPtr) = (i32)value;
			break;
		case 2:
			*((i16*)regPtr) = (i16)value;
			break;
		case 3:
			*((i8*)regPtr) = (i8)value;
			break;
	}
}

bool hw::get(const Registers& regs, flag f) {
	switch (f) {
		case flag::CF:
			return regs.flags & 0x1;
		case flag::PF:
			return regs.flags & 0x4;
		case flag::AF:
			return regs.flags & 0x10;
		case flag::ZF:
			return regs.flags & 0x40;
		case flag::SF:
			return regs.flags & 0x80;
		case flag::TF:
			return regs.flags & 0x100;
		case flag::IF:
			return regs.flags & 0x200;
		case flag::DF:
			return regs.flags & 0x400;
		case flag::OF:
			return regs.flags & 0x800;
		case flag::IOPL:
			return regs.flags & 0x3'000;
		case flag::NT:
			return regs.flags & 0x4'000;
		case flag::MD:
			return regs.flags & 0x8'000;
		case flag::RF:
			return regs.flags & 0x10'000;
		case flag::VM:
			return regs.flags & 0x20'000;
		case flag::AC:
			return regs.flags & 0x40'000;
		case flag::VIF:
			return regs.flags & 0x80'000;
		case flag::VIP:
			return regs.flags & 0x100'0000;
		case flag::ID:
			return regs.flags & 0x200'000;
		case flag::AESK:
			return regs.flags & 0x40'000'000;
		case flag::AI:
			return regs.flags & 0x80'000'000;
		default:
			return false;
	}
}

void hw::set(Registers& regs, flag f) {
	switch (f) {
		case flag::CF:
			regs.flags |= 0x1;
			break;
		case flag::PF:
			regs.flags |= 0x4;
			break;
		case flag::AF:
			regs.flags |= 0x10;
			break;
		case flag::ZF:
			regs.flags |= 0x40;
			break;
		case flag::SF:
			regs.flags |= 0x80;
			break;
		case flag::TF:
			regs.flags |= 0x100;
			break;
		case flag::IF:
			regs.flags |= 0x200;
			break;
		case flag::DF:
			regs.flags |= 0x400;
			break;
		case flag::OF:
			regs.flags |= 0x800;
			break;
		case flag::IOPL:
			regs.flags |= 0x3'000;
			break;
		case flag::NT:
			regs.flags |= 0x4'000;
			break;
		case flag::MD:
			regs.flags |= 0x8'000;
			break;
		case flag::RF:
			regs.flags |= 0x10'000;
			break;
		case flag::VM:
			regs.flags |= 0x20'000;
			break;
		case flag::AC:
			regs.flags |= 0x40'000;
			break;
		case flag::VIF:
			regs.flags |= 0x80'000;
			break;
		case flag::VIP:
			regs.flags |= 0x100'0000;
			break;
		case flag::ID:
			regs.flags |= 0x200'000;
			break;
		case flag::AESK:
			regs.flags |= 0x40'000'000;
			break;
		case flag::AI:
			regs.flags |= 0x80'000'000;
			break;
	}
}

void hw::clr(Registers& regs, flag f) {
	switch (f) {
		case flag::CF:
			regs.flags &= ~0x1;
			break;
		case flag::PF:
			regs.flags &= ~0x4;
			break;
		case flag::AF:
			regs.flags &= ~0x10;
			break;
		case flag::ZF:
			regs.flags &= ~0x40;
			break;
		case flag::SF:
			regs.flags &= ~0x80;
			break;
		case flag::TF:
			regs.flags &= ~0x100;
			break;
		case flag::IF:
			regs.flags &= ~0x200;
			break;
		case flag::DF:
			regs.flags &= ~0x400;
			break;
		case flag::OF:
			regs.flags &= ~0x800;
			break;
		case flag::IOPL:
			regs.flags &= ~0x3'000;
			break;
		case flag::NT:
			regs.flags &= ~0x4'000;
			break;
		case flag::MD:
			regs.flags &= ~0x8'000;
			break;
		case flag::RF:
			regs.flags &= ~0x10'000;
			break;
		case flag::VM:
			regs.flags &= ~0x20'000;
			break;
		case flag::AC:
			regs.flags &= ~0x40'000;
			break;
		case flag::VIF:
			regs.flags &= ~0x80'000;
			break;
		case flag::VIP:
			regs.flags &= ~0x100'0000;
			break;
		case flag::ID:
			regs.flags &= ~0x200'000;
			break;
		case flag::AESK:
			regs.flags &= ~0x40'000'000;
			break;
		case flag::AI:
			regs.flags &= ~0x80'000'000;
			break;
	}
}