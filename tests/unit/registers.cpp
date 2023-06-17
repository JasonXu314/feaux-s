#define CATCH_CONFIG_MAIN
#include "../../src/hardware/registers.h"

#include <lib/catch.hpp>

TEST_CASE("Prelims") {
	SECTION("Type sizes") {
		REQUIRE(sizeof(i8) == 1);
		REQUIRE(sizeof(i16) == 2);
		REQUIRE(sizeof(i32) == 4);
		REQUIRE(sizeof(i64) == 8);
	}
}

TEST_CASE("Register fundamentals") {
	SECTION("Construction and assignment") {
		hw::Registers regs;

		regs.rax = 0xCCCCCCCC;

		REQUIRE(regs.rax == 0xCCCCCCCC);
	}

	SECTION("Partial register access") {
		hw::Registers regs;

		regs.rax = 0xCCCCCCCCCC;

		REQUIRE(regs.eax == (i32)0xCCCCCCCC);
		REQUIRE(regs.ax == (i16)0xCCCC);
		REQUIRE(regs.al == (i8)0xCC);
	}

	SECTION("Register isolation") {
		hw::Registers regs;

		regs.rax = 0xCCCCCCCCCC;
		regs.rcx = static_cast<i64>((ui64)(-1));

		REQUIRE(regs.rax == 0xCCCCCCCCCC);
		REQUIRE(regs.eax == (i32)0xCCCCCCCC);
		REQUIRE(regs.ax == (i16)0xCCCC);
		REQUIRE(regs.al == (i8)0xCC);
	}

	SECTION("Flags register") {
		hw::Registers regs;

		srand(time(nullptr));

		for (int i = 0; i < 8; i++) {
			hw::flag f = (hw::flag)(rand() % 24);

			while (f == 1 || f == 3 || f == 5 || f == 21) {	 // unused flag bits (reroll)
				f = (hw::flag)(rand() % 24);
			}

			hw::set(regs, f);

			for (int cf = 0; cf < 24; cf++) {
				if (cf == f) {
					REQUIRE(hw::get(regs, (hw::flag)cf));
				} else if (cf != 1 && cf != 3 && cf != 5 && cf != 21) {
					REQUIRE_FALSE(hw::get(regs, (hw::flag)cf));
				}
			}

			hw::clr(regs, f);
		}
	}
}

TEST_CASE("Register utilities") {
	SECTION("get utility") {
		hw::Registers regs;

		srand(time(nullptr));

		regs.rax = ((i64)rand() << 32) + rand();
		regs.rcx = ((i64)rand() << 32) + rand();
		regs.rdx = ((i64)rand() << 32) + rand();

		REQUIRE(regs.rax == hw::get(regs, hw::gpr::RAX));
		REQUIRE(regs.eax == hw::get(regs, hw::gpr::EAX));
		REQUIRE(regs.ax == hw::get(regs, hw::gpr::AX));
		REQUIRE(regs.al == hw::get(regs, hw::gpr::AL));

		REQUIRE(regs.rcx == hw::get(regs, hw::gpr::RCX));
		REQUIRE(regs.ecx == hw::get(regs, hw::gpr::ECX));
		REQUIRE(regs.cx == hw::get(regs, hw::gpr::CX));
		REQUIRE(regs.cl == hw::get(regs, hw::gpr::CL));

		REQUIRE(regs.rdx == hw::get(regs, hw::gpr::RDX));
		REQUIRE(regs.edx == hw::get(regs, hw::gpr::EDX));
		REQUIRE(regs.dx == hw::get(regs, hw::gpr::DX));
		REQUIRE(regs.dl == hw::get(regs, hw::gpr::DL));
	}

	SECTION("set utility") {
		hw::Registers regs;

		srand(time(nullptr));

		i64 rax = rand() << 32 + rand(), rcx = rand() << 32 + rand(), rdx = rand() << 32 + rand();

		hw::set(regs, hw::gpr::RAX, rax);
		hw::set(regs, hw::gpr::RCX, rcx);
		hw::set(regs, hw::gpr::RDX, rdx);

		REQUIRE(regs.rax == hw::get(regs, hw::gpr::RAX));
		REQUIRE(regs.eax == hw::get(regs, hw::gpr::EAX));
		REQUIRE(regs.ax == hw::get(regs, hw::gpr::AX));
		REQUIRE(regs.al == hw::get(regs, hw::gpr::AL));

		REQUIRE(regs.rcx == hw::get(regs, hw::gpr::RCX));
		REQUIRE(regs.ecx == hw::get(regs, hw::gpr::ECX));
		REQUIRE(regs.cx == hw::get(regs, hw::gpr::CX));
		REQUIRE(regs.cl == hw::get(regs, hw::gpr::CL));

		REQUIRE(regs.rdx == hw::get(regs, hw::gpr::RDX));
		REQUIRE(regs.edx == hw::get(regs, hw::gpr::EDX));
		REQUIRE(regs.dx == hw::get(regs, hw::gpr::DX));
		REQUIRE(regs.dl == hw::get(regs, hw::gpr::DL));
	}
}