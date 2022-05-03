#!/usr/bin/env node

const LEN = 10000

console.time('Array')

for (let _ = 0; _ < 100; _++) {
	let arr = new Uint32Array(LEN).map((_, i) => i * 2)

	console.log(`[0]=${arr[0]}`)
	console.log(`[1]=${arr[1]}`)
	console.log(`[${LEN - 1}]=${arr[LEN - 1]}`)
}

console.timeEnd('Array')