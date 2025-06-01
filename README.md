# My CPP Application

Simple application written in C++ with purposedly sabotaged code for a C++ interview

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build . --target all
```

## Test

```bash
ctest --output-on-failure
```

## Run

Figure it out yourself 😉

## Environment

### Amazon Linux 2

```bash
sudo yum update -y
sudo yum groupinstall "Development Tools" -y
sudo yum install -y epel-release
sudo yum install -y git nc vim valgrind
sudo yum install -y cmake3
sudo ln -s /usr/bin/cmake3 /usr/bin/cmake
sudo ln -s /usr/bin/ctest3 /usr/bin/ctest
```
