# CORRECTNESS

## Generate data

## Build & Run

```
g++ src/timSort.cpp tests/correctness/correctness.cpp -o correctness_tests.exe
./correctness_tests.exe
```

# ADAPTIVENESS

## Generate data
```
g++ src/timSort.cpp generator/generate_adaptiveness.cpp -o generate_adaptiveness.exe
./generate_adaptiveness.exe
```


## Build & Run

```
g++ src/timSort.cpp tests/adaptiveness/adaptiveness.cpp -o adaptiveness_tests.exe
./adaptiveness_tests.exe
```

# PERFORMANCE

## Generate data

```
g++ src/timSort.cpp generator/generate_performance.cpp -o generate_performance.exe
./generate_performance.exe
```

# Build & Run

```
g++ src/timSort.cpp tests/performance/performance.cpp -o performance_tests.exe
./performance_tests.exe
```
