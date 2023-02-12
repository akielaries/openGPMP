/*
 * testing OpenCL
 */

#include <CL/cl.h>
#include <iostream>

int main() {
    cl_int CL_err        = CL_SUCCESS;
    cl_uint numPlatforms = 0;

    CL_err = clGetPlatformIDs(0, NULL, &numPlatforms);

    if (CL_err == CL_SUCCESS)
        std::cout << "Platforms: " << numPlatforms << std::endl;
    else
        printf("clGetPlatformIDs(%i)\n", CL_err);
    std::cout << "PlatformIDS " << CL_err << std::endl;

    return 0;
}
