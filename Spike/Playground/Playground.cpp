// Playground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define CL_USE_DEPRECATED_OPENCL_2_0_APIS

#include <CL/cl.hpp>

int main(void)
{
    //Make sure we get platform
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    _ASSERT(platforms.size() > 0);

    //Make sure we get device
    cl::Platform platform = platforms.front();
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
    _ASSERT(devices.size() > 0);

    cl::Device device = devices.front();
    std::string vendor = device.getInfo<CL_DEVICE_VENDOR>();
    std::string version = device.getInfo<CL_DEVICE_VERSION>();

    std::cout << "Vendor: " << vendor <<std::endl;
    std::cout << "Version: " << version << std::endl;

    system("pause");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
