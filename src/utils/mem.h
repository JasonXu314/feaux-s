#ifdef MEM_POLYFILL

#ifndef UTILS_MEM_H
#define UTILS_MEM_H

#include "decls.h"

#define PAGESIZE 4096
#define F_ALLOC_ADDR PAGESIZE * 2
#define MEMSIZE 0x1000000
#define NPAGES (MEMSIZE / PAGESIZE)

#define SEGSIZE 64
#define NSEGS (PAGESIZE / SEGSIZE)

namespace __MEM_IMPL {
struct SegInfo {
	SegInfo() : refCount(0), size(0) {}

	ui16 refCount;
	ui16 size;

	bool used() const { return refCount != 0; }
};

struct PageInfo {
	PageInfo() : refCount(0) {}

	ui8 refCount;

	bool used() const { return refCount != 0; }
};

extern ui64 nextAddr;
extern PageInfo* pages;

void __init();

void* __kalloc(ui16 size);

void __kfree(void* addr);

ui64 __pageOf(ui64 addr);

ui64 __segmentOf(ui64 addr);

bool __isFree(ui64 addr);

bool __isFree(ui64 addr, ui16 size);

ui64 __segAlignRoundUp(ui64 addr);
}  // namespace __MEM_IMPL

void memset(void* addr, ui64 size, i8 byte);

void memcpy(void* src, void* dest, ui64 size);

void* malloc(ui16 size);

void* calloc(ui16 count, ui16 size);

void free(void* ptr);

void* operator new(ul32 size);

void* operator new[](ul32 size);

void operator delete(void* ptr) noexcept;

void operator delete[](void* ptr) noexcept;

browser { expose void __init_mem(); }

#endif

#endif