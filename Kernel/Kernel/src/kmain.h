#pragma once

#include <stddef.h>

struct KERNEL_BOOT_HEADER {
	uint32 kernelStartAddress;
	uint32 kernelSize;
	uint32 smapAddress;
};