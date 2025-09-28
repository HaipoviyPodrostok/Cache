# 2Q Cache Implementation in C++

A C++ implementation of the 2Q cache replacement algorithm with comprehensive testing framework.

## To run 2q cache:

```bash
cmake -S . -B build && cmake --build ./build
./build/two_q_cache.x
```

## To run 2q cache:

```bash
cmake -S . -B build && cmake --build ./build
./build/ideal_cache.x
```

## To run tests
```bash
ctest --test-dir build --output-on-failure
```

## Input Format
```
<cache_size> <number_of_requests> <request1> <request2> <request3> ...
```
## Ideal to 2Q caching comparison

test case | 2Q cache hits | Ideal cache hits |
|-------- | -------------- | ---------------- |
| 1       |       4        |       9          |
| 2       |       189      |       327        |
| 3       |       12       |       17         |
| 4       |       5        |       5          |
| 5       |       5        |       6          |
| 6       |       8        |       9          |
| 7       |       0        |       6          |
| 8       |       7        |       7          |
| 9       |       8        |       13         |
| 10      |       4        |       4          |