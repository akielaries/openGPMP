# Benchmark documentation...

TODO

This project serves as a simple way to benchmark and monitor a given linux system. The
primary focsus on the NVIDIA Jetson Nano and the Rapsberry Pi series. 

# Installation & Usage
## Prerequisites
For running on bare system:
- gcc/g++ v10+
- C++-20
- nvcc v10.2+
- [openGPMP](https://github.com/akielaries/openGPMP/tree/main)
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

