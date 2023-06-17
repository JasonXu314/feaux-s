#ifdef MEM_POLYFILL
#include "mem.h"

ui64 __MEM_IMPL::nextAddr = PAGESIZE;  // nullptr page is inaccessible and should be entirely blank
__MEM_IMPL::PageInfo* __MEM_IMPL::pages = nullptr;

void __MEM_IMPL::__init() {
	// Initialize page page (the memory page to keep track of other memory pages :P)
	pages = reinterpret_cast<PageInfo*>(nextAddr);
	nextAddr += PAGESIZE;

	pages[1].refCount++;

	memset(0, MEMSIZE, 0);
}

// TODO: handle mem allocation edge case(s)
// namely: when wrapping back, does not detect out-of-memory scenarios
void* __MEM_IMPL::__kalloc(ui16 size) {
	if (size > PAGESIZE - SEGSIZE) jsthrow("Attempting to allocate more than a page");
	if (nextAddr >= MEMSIZE) nextAddr = F_ALLOC_ADDR;

	if (size > SEGSIZE) {
		while (!__isFree(nextAddr, size)) {
			nextAddr += SEGSIZE;
			if (nextAddr >= MEMSIZE) nextAddr = F_ALLOC_ADDR;
		}

		ui64 page = __pageOf(nextAddr), seg = __segmentOf(nextAddr);
		SegInfo* segdata = reinterpret_cast<SegInfo*>(page * PAGESIZE);

		for (ui64 i = 0; i < (size / SEGSIZE) + 1u; i++) {
			segdata[seg + i].refCount++;
		}
		segdata[seg].size = size;

		void* addr = reinterpret_cast<void*>(nextAddr);
		nextAddr = __segAlignRoundUp(nextAddr + size);

		return addr;
	} else {
		while (!__isFree(nextAddr)) {
			nextAddr += SEGSIZE;
			if (nextAddr >= MEMSIZE) nextAddr = F_ALLOC_ADDR;
		}

		ui64 page = __pageOf(nextAddr), seg = __segmentOf(nextAddr);
		SegInfo* segdata = reinterpret_cast<SegInfo*>(page * PAGESIZE);

		if (!segdata[0].used()) {  // time to allocate a new page
			// First 3 segments will be used (segment data segments and the actually allocated segment)
			segdata[0].refCount++;
			segdata[1].refCount++;
			segdata[2].refCount++;
			segdata[2].size = size;
			pages[page].refCount++;
		} else {
			segdata[seg].refCount++;
			segdata[seg].size = size;
		}

		void* addr = reinterpret_cast<void*>(nextAddr);
		nextAddr += SEGSIZE;

		return addr;
	}
}

void __MEM_IMPL::__kfree(void* addr) {
	ui64 address = reinterpret_cast<ui64>(addr), page = __pageOf(address), seg = __segmentOf(address);
	SegInfo* segdata = reinterpret_cast<SegInfo*>(page * PAGESIZE);

	if (!segdata[seg].used()) {
		jsthrow("Double free");
		return;
	} else if (!segdata[seg].size) {
		jsthrow("Address not head of alloc'd block");
		return;
	}

	for (ui64 i = 0; i < (segdata[seg].size / SEGSIZE) + 1u; i++) {
		segdata[seg + i].refCount--;
	}

	if (!segdata[seg].used()) {
		segdata[seg].size = 0;
	}
}

ui64 __MEM_IMPL::__pageOf(ui64 addr) { return addr / PAGESIZE; }

ui64 __MEM_IMPL::__segmentOf(ui64 addr) { return (addr % PAGESIZE) / SEGSIZE; }

bool __MEM_IMPL::__isFree(ui64 addr) {
	ui64 page = __pageOf(addr), seg = __segmentOf(addr);

	if (seg < 2) return false;	// That's the segment data segments

	SegInfo* segdata = reinterpret_cast<SegInfo*>(page * PAGESIZE);

	return !segdata[seg].used();
}

bool __MEM_IMPL::__isFree(ui64 addr, ui16 size) {
	for (ui8 i = 0; i * SEGSIZE < size; i++) {
		if (!__isFree(addr + (i * SEGSIZE))) {
			return false;
		}
	}

	return true;
}

ui64 __MEM_IMPL::__segAlignRoundUp(ui64 addr) {
	ui64 segc = addr / SEGSIZE;

	return (segc + 1) * SEGSIZE;
}

void memset(void* addr, ui64 size, i8 byte) {
	ui64 end = reinterpret_cast<ui64>(addr) + size;

	for (ui64 a = reinterpret_cast<ui64>(addr); a < end; a++) {
		*((i8*)a) = byte;
	}
}

void memcpy(void* src, void* dest, ui64 size) {
	i8 *s = reinterpret_cast<i8*>(src), *d = reinterpret_cast<i8*>(dest);

	for (ui64 i = 0; i < size; i++) {
		d[i] = s[i];
	}
}

void* malloc(ui16 size) { return __MEM_IMPL::__kalloc(size); }

void* calloc(ui16 count, ui16 size) {
	void* addr = malloc(count * size);

	memset(addr, count * size, 0);

	return addr;
}

void free(void* ptr) { __MEM_IMPL::__kfree(ptr); }

void* operator new(ul32 size) { return malloc(size); }

void* operator new[](ul32 size) { return calloc(size, 1); }

void operator delete(void* ptr) noexcept { free(ptr); }

void operator delete[](void* ptr) noexcept { free(ptr); }

browser {
	expose void __init_mem() { __MEM_IMPL::__init(); }
}
#endif