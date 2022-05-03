#!/usr/bin/env python3

import time

LEN = 10000

start = time.perf_counter()

for _ in range(100):
	arr = [i * 2 for i in range(LEN)]

	print(f'[0]={arr[0]}')
	print(f'[1]={arr[1]}')
	print(f'[{LEN - 1}]={arr[LEN - 1]}')


end = time.perf_counter()
print(f'Array: {(end - start) * 1000}ms')
