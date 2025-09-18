# 2Q Cache Implementation in C++

A C++ implementation of the 2Q cache replacement algorithm with comprehensive testing framework.

## To run app

```bash
cmake -B build
cmake --build build
cd build
./TwoQCache.x
```
## To run tests
```bash
cd build
ctest
```

## Input Format
```
<cache_size> <number_of_requests> <request1> <request2> <request3> ...
```
## Ideal to 2Q caching comparisson

test case | 2Q cache hits | Ideal cache hits |
|-------- | -------------- | ---------------- |
| 1       |       4        |       4          |
| 2       |       2        |       1          |
| 3       |       13       |       15         |
| 4       |       5        |       5          |
| 5       |       6        |       6          |
| 6       |       5        |       6          |
| 7       |       0        |       6          |
| 8       |       7        |       7          |
| 9       |       8        |       8          |
| 10      |       4        |       4          |