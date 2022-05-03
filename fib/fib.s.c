#define COM /*
nasm -f macho64 fib.s -o fib.o
gcc -O3 $0 fib.o
./a.out
rm fib.o a.out
exit
*/

#define LEN 10000

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int *op(void);

int main()
{
	clock_t start = clock();

	for (int _ = 0; _ < 100; _++) {
		int *arr = op();

		printf("[0]=%d\n", arr[0]);
		printf("[1]=%d\n", arr[1]);
		printf("[%d]=%d\n", LEN - 1, arr[LEN - 1]);
	}

	printf("Array: %.9fms\n", ((double) (clock() - start)) / CLOCKS_PER_SEC * 1000);
}
