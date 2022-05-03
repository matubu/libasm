#define COM /*
gcc -O3 $0
./a.out
rm a.out
exit
*/

#define LEN 10000

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	clock_t start = clock();

	for (int _ = 0; _ < 100; _++) {
		int *arr = malloc(LEN * sizeof(int));
		for (int i = 0; i < LEN; i++)
			arr[i] = i * 2;
		free(arr);

		printf("[0]=%d\n", arr[0]);
		printf("[1]=%d\n", arr[1]);
		printf("[%d]=%d\n", LEN - 1, arr[LEN - 1]);
	}

	printf("Array: %.9fms\n", ((double) (clock() - start)) / CLOCKS_PER_SEC * 1000);
}
