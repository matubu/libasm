#define COM /*
g++ -O3 $0
./a.out
rm a.out
exit
*/

#define LEN 10000

#include <time.h>
#include <iostream>
#include <vector>

int main()
{
	clock_t start = clock();

	for (int _ = 0; _ < 100; _++) {
		std::vector<int> arr;
		arr.resize(LEN);
		for (int i = 0; i < LEN; i++)
			arr[i] = i * 2;

		std::cout << "[0]=" << arr[0] << std::endl;
		std::cout << "[1]=" << arr[1] << std::endl;
		std::cout << "[" << LEN - 1 << "]=" << arr[LEN - 1] << std::endl;
	}

	std::cout << "Array: " << (((double) (clock() - start)) / CLOCKS_PER_SEC * 1000) << "ms" << std::endl;
}