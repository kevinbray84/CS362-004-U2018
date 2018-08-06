/*******************
* Greg Doolittle
* CS362 Aburas
* 7/22/2018
* Assignment 3
********************/

#include <string.h>
#include <stdio.h>

int assertCompare(int A, int B) {
	if (A == B) {
		printf("PASSES 1 TEST.\n");
		return 0;
	}
	else {
		printf("FAILS 1 TEST.\n");
		return 1;
	}
}

int assertEqual(int A) {
	if (A == 1) {
		return assertCompare(1, 1);
	}
	else {
		return assertCompare(1, 0);
	}
}

void assertCompareMessage(int A, int B, char* msg) {
	assertCompare(A, B);
	printf("%s", msg);
}
