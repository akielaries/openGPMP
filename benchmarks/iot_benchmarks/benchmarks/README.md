# Benchmarks
Simple repository comparing the Raspberry Pi 4, Raspberry Pi IO Board compute module
and the NVIDIA Jetson Nano.

# TODO, add a table here with some result


Tests for RPI's and Jetson Nano:
* Sequential performance 
* CPU multithreading performance
* GPU multithreading
* SIMD(CPU) and cache performance
* SIMT(GPU) performance
* SIMD/SIMT + CPU/GPU multithreading performance

Tools used and needed:
* gprof for baseline benchmarks and code execution performance
* perf for flamegraphs showing CPU utilization and stack performance
* NVCC for CUDA compilation
* g++ for C++ compilation
* `std::chrono` for naive time logging

Logic/algorithms implemented
* Matrix arithmetic (addition, subtraction, multiplication)
* Primality Tests & Generation
* TODO...

# Installation & Usage
## Prerequisites
For running on bare system:
- gcc/g++ v10+
- C++-20
- nvcc v10.2+
- [gprof](https://ftp.gnu.org/old-gnu/Manuals/gprof-2.9.1/html_mono/gprof.html)
- [perf](https://perf.wiki.kernel.org/index.php/Main_Page)
- [Flamegraph](https://github.com/brendangregg/FlameGraph)

```
# compile
$ make compile
# install binary to /usr/bin
$ make install
# uninstall
$ make uninstall
```

Otherwise, use Docker...
```
# create docker image
$ make docker_img
# run
$ make docker_run
```

```
$ ./benchsys 
Usage: benchsys [-d | -b]
  -d : daemon mode to monitor system information
  -b : benchmark mode to run system stress tests with live monitoring
```

# Installing CUDA

See here: https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=arm64-sbsa&Compilation=Native&Distribution=Ubuntu&target_version=20.04&target_type=deb_network

### Base installation
```
$ wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/sbsa/cuda-keyring_1.1-1_all.deb
$ sudo dpkg -i cuda-keyring_1.1-1_all.deb
$ sudo apt-get update
$ sudo apt-get -y install cuda-toolkit-12-3
```

### NVIDIA CUDA Drivers
```
$ sudo apt-get install -y cuda-drivers
$ sudo apt-get install -y nvidia-kernel-open-545
$ sudo apt-get install -y cuda-drivers-545
```
See here: https://docs.nvidia.com/cuda/cuda-installation-guide-linux/#switching-between-driver-module-flavors
