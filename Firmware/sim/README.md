# Simulator

This project can be simulated using (https://github.com/mackorone/mms)[mms].

# Configuration for MMS

## Build

```shell
g++ -g -I lib/mms-cpp/ -I ../lib/algorithm/ ../lib/algorithm/algorithm.cpp lib/mms-cpp/API.cpp main.cpp -o main.bin
```

## Run
```shell
./main.bin
```
