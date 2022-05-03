#!/bin/sh
//usr/bin/env rustc -C opt-level=3 $0 -o a.out && ./a.out && rm ./a.out ; exit

use std::time::{Instant};

const LEN: usize = 10000;

fn main() {
    let now = Instant::now();

    for _ in 0..100 {
        let mut arr = [0; LEN];
        for i in arr {
            arr[i] = i * 2;
        }

        println!("[0]={}", arr[0]);
        println!("[1]={}", arr[1]);
        println!("[{}]={}", LEN - 1, arr[LEN - 1]);
    }
    
    println!("Array: {}ms", (now.elapsed().as_micros() as f64) / 1000.0);
}