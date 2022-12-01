#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solutions.h"

int main(int argc, char *argv[]) {
	if (strcmp(argv[1], "easy") == 0) {
		easy(argv[2]);
	} else if (strcmp(argv[1], "hard") == 0) {
		hard(argv[2]);
	} else {
		printf("Erreur : mauvais argument\n");
		return 1;
	}
	return 0;
}
