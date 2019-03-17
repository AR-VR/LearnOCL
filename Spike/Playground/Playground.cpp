#include <iostream>

#define CL_USE_DEPRECATED_OPENCL_2_0_APIS

#include <CL/cl.hpp>
#include <fstream>
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
    
    std::ifstream helloWorldFile("opencl\\HelloWorld.cl");
    std::string src(std::istreambuf_iterator<char>(helloWorldFile), (std::istreambuf_iterator<char>()));
    cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));
    
    cl::Context context(device);
    cl::Program program(context, sources);
    cl_int error = program.build("-cl-std=CL1.2");
    char buf[12];
    cl::Buffer memBuf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buf));
    cl::Kernel kernel(program, "HelloWorld", &error);
    kernel.setArg(0, memBuf);

    cl::CommandQueue queue(context, device);
    queue.enqueueTask(kernel);
    queue.enqueueReadBuffer(memBuf, GL_TRUE, 0, sizeof(buf), buf);
    
    std::cout << buf <<std::endl;
    system("pause");
    return 0;
}