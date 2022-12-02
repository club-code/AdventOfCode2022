#include <stdlib.h>

typedef struct {
	size_t length;
	size_t sizeOfElement;
	void* data;
} dynArray;

dynArray initDynArray(size_t length, size_t sizeOfElement);

void resizeDynArray(dynArray arr, size_t newLength);

void freeDynArray(dynArray arr);
