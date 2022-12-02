#include "dynArray.h"

dynArray initDynArray(size_t length, size_t sizeOfElement) {
	dynArray res;
	res.length = length;
	res.sizeOfElement = sizeOfElement;
	res.data = malloc(length * sizeOfElement);
	return res;
}

void resizeDynArray(dynArray arr, size_t newLength) {
	arr.data = realloc(arr.data, newLength * arr.sizeOfElement);
	arr.length = newLength;
}

void freeDynArray(dynArray arr) {
	free(arr.data);
}
