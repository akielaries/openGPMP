#include "../lib/sys.hpp"
#include <iostream>
#include <cuda_runtime_api.h>

int System::_gpu_arch(int major, int minor) {
    // defs for GPU arch types using streaming multiprocessor to determine
    // # of cores per proc
    struct ARCHInfo {
        int sm;  // 0xMm (hex), M = SM Major version, and m = SM minor version
        int cores;
    };

    ARCHInfo cores_per_proc[] = {
        {0x10, 8},  // Tesla Generation (SM 1.0) G80 class
        {0x11, 8},  // Tesla Generation (SM 1.1) G8x class
        {0x12, 8},  // Tesla Generation (SM 1.2) G9x class
        {0x13, 8},  // Tesla Generation (SM 1.3) GT200 class
        {0x20, 32}, // Fermi Generation (SM 2.0) GF100 class
        {0x21, 48}, // Fermi Generation (SM 2.1) GF10x class
        {0x30, 192},// Kepler Generation (SM 3.0) GK10x class
        {0x32, 192},// Kepler Generation (SM 3.2) GK20A class
        {0x35, 192},// Kepler Generation (SM 3.5) GK11x class
        {0x37, 192},// Kepler Generation (SM 3.7) GK21x class
        {0x50, 128},// Maxwell Generation (SM 5.0) GM10x class
        {0x52, 128},// Maxwell Generation (SM 5.2) GM20x class
        {0x53, 128},// Maxwell Generation (SM 5.3) GM20x class
        {0x60, 64}, // Pascal Generation (SM 6.0) GP100 class
        {0x61, 128},// Pascal Generation (SM 6.1) GP10x class
        {0x62, 128},// Pascal Generation (SM 6.2) GP10x class
        {0x70, 64}, // Volta Generation (SM 7.0) GV100 class
        {0x72, 64}, // Volta Generation (SM 7.2) GV10B class
        {0x75, 64}, // Turing Generation (SM 7.5) TU10x class
        {0x80, 64}, // Ampere Generation (SM 8.0) GA100 class
        {0x86, 64}, // Ampere Generation (SM 8.6) GA10x class
        // add more archs here???
        {-1, -1}    // Indicates unknown SM
    };

    int index = 0;
    while (cores_per_proc[index].sm != -1) {
        if (cores_per_proc[index].sm == ((major << 4) + minor)) {
            return cores_per_proc[index].cores;
        }
        index++;
    }

    // if we get here we got an invalid arch
    return -1;
}

void System::gpu_info() {
    int deviceCount;
    cudaGetDeviceCount(&deviceCount);

    if (deviceCount == 0) {
        std::cerr << "No CUDA-compatible GPU found." << std::endl;
        return;
    }

    // Assuming you want information about the first GPU
    int dev = 0;
    cudaSetDevice(dev);
    cudaDeviceProp deviceProp;
    cudaGetDeviceProperties(&deviceProp, dev);

    int nvd_driver_version, cuda_version;
    size_t gpu_mem_total, gpu_mem_free;

    /** GPU DEVICE INFORMATION */
    System::name                = deviceProp.name;

    cudaDriverGetVersion(&nvd_driver_version);
    cudaRuntimeGetVersion(&cuda_version);
    System::nvd_driver_version  = nvd_driver_version;
    System::cuda_version        = cuda_version;
    System::major               = deviceProp.major;
    System::minor               = deviceProp.minor;
    
    System::shared_mem_pb       = deviceProp.sharedMemPerBlock;
    System::total_const_mem     = deviceProp.totalConstMem;
    System::total_glbl_mem      = static_cast<float>(deviceProp.totalGlobalMem / 1048576.0f);
    cudaMemGetInfo(&gpu_mem_free, &gpu_mem_total);
    
    System::gpu_mem_total       = static_cast<float>(gpu_mem_total / 1048576.0f);
    System::gpu_mem_free        = static_cast<float>(gpu_mem_free / 1048576.0f);
    System::gpu_mem_used        = static_cast<float>(gpu_mem_total - gpu_mem_free);

    System::gpu_mp_count        = deviceProp.multiProcessorCount;
    System::cuda_cores          = _gpu_arch(deviceProp.major, 
                                                        deviceProp.minor);
    System::max_clock_rt        = deviceProp.clockRate * 1e-6f;
    
    System::max_mp_threads      = deviceProp.maxThreadsPerMultiProcessor;
    System::max_pb_threads      = deviceProp.maxThreadsPerBlock;
    
    System::max_dim_threads[0]  = deviceProp.maxThreadsDim[0];
    System::max_dim_threads[1]  = deviceProp.maxThreadsDim[1];
    System::max_dim_threads[2]  = deviceProp.maxThreadsDim[2];
    System::max_grid_size[0]    = deviceProp.maxGridSize[0];
    System::max_grid_size[1]    = deviceProp.maxGridSize[1];
    System::max_grid_size[2]    = deviceProp.maxGridSize[2];
}

void System::gpu_info_print() {
    std::cout << "\nDevice: \"" << System::name << "\"" << std::endl;

    std::cout << "  CUDA Driver Version / Runtime Version          "
              << System::nvd_driver_version / 1000 << "."
              << (System::nvd_driver_version % 100) / 10
              << " / " << System::cuda_version / 1000 << "."
              << (System::cuda_version % 100) / 10 << std::endl;

    std::cout << "  CUDA Capability Major/Minor version number:    "
              << System::major << "." << System::minor << std::endl;

    std::cout << "  Total amount of global memory:                 "
              << System::total_glbl_mem << " MBytes" << std::endl;

    std::cout << "  ( " << System::gpu_mp_count << ") Multiprocessors, ("
              << System::gpu_mp_count * System::cuda_cores
              << ") CUDA Cores/MP:     " << System::cuda_cores
              << " CUDA Cores" << std::endl;

    std::cout << "  GPU Max Clock rate:                            "
              << System::max_clock_rt << " GHz" << std::endl;

    std::cout << "  Total amount of constant memory:               "
              << System::total_const_mem << " bytes" << std::endl;

    std::cout << "  Total amount of shared memory per block:       "
              << System::shared_mem_pb << " bytes" << std::endl;

    std::cout << "  Maximum number of threads per multiprocessor:  "
              << System::max_mp_threads << std::endl;

    std::cout << "  Maximum number of threads per block:           "
              << System::max_pb_threads << std::endl;

    std::cout << "  Max dimension size of a thread block (x,y,z): ("
              << System::max_dim_threads[0] << ", " << System::max_dim_threads[1] << ", "
              << System::max_dim_threads[2] << ")" << std::endl;

    std::cout << "  Max dimension size of a grid size    (x,y,z): ("
              << System::max_grid_size[0] << ", " << System::max_grid_size[1] << ", "
              << System::max_grid_size[2] << ")" << std::endl;

    std::cout << "  GPU MEMORY TOTAL" << System::gpu_mem_total << "\n";

    std::cout << "  GPU MEMORY USED" << System::gpu_mem_used << "\n";

    std::cout << "  GPU MEMORY FREE" << System::gpu_mem_free << "\n";

}

