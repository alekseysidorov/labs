#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cassert>
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "opencl.lib")
#define BLOCK_SIZE 8
#define A_HEIGHT 512
#define A_WIDTH_B_HEIGHT 512
#define B_WIDTH 512
#define ARRAY_SIZE_1 B_WIDTH * A_WIDTH_B_HEIGHT
#define ARRAY_SIZE_2 A_WIDTH_B_HEIGHT * A_HEIGHT
#define ARRAY_SIZE_3 B_WIDTH * A_HEIGHT
#define OPERATIONS B_WIDTH * A_WIDTH_B_HEIGHT * A_HEIGHT * 2

void generateMatrix(size_t size1, size_t size2, float *matrix) {
	for (int j = 0; j < size1; ++j) {
		for (int i = 0; i < size2; ++i) {
			matrix[i * size1 + j] = rand() % 10;
		}
	}
}

bool checkMultipliedMatrix(float *x, float *y, float *z) {
	for (int i = 0; i < A_HEIGHT; ++i) {
		for (int j = 0; j < B_WIDTH; ++j) {
			float sum = 0;
			for (int k = 0; k < A_WIDTH_B_HEIGHT; ++k) {
				sum += x[k * B_WIDTH + j] * y[i * A_WIDTH_B_HEIGHT + k];
			}
			if (z[i * B_WIDTH + j] != sum) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	srand(time(NULL));
	cl_uint platformIdCount = 0;
	clGetPlatformIDs(0, nullptr, &platformIdCount);
	std::vector<cl_platform_id> platformIds(platformIdCount);
	clGetPlatformIDs(platformIdCount, platformIds.data(), nullptr);
	if (platformIdCount == 0) {
		std::cout << "Error. No OpenCL platforms found." << std::endl;
		return 0;
	}
	cl_device_type type;
	size_t preferredDeviceId = 0;
	cl_uint deviceIdCount = 0;
	size_t currentPlatform = 0;
	char name[100];
	while (deviceIdCount == 0 && currentPlatform < platformIdCount) {
		clGetDeviceIDs(platformIds[currentPlatform++], CL_DEVICE_TYPE_ALL, 0, nullptr, &deviceIdCount);
	}
	currentPlatform--;
	if (deviceIdCount == 0) {
		std::cout << "Error. No OpenCL devices found." << std::endl;
		return 0;
	}
	clGetPlatformInfo(platformIds[currentPlatform], CL_PLATFORM_NAME, 100, name, nullptr);
	std::cout << "Platform found: " << name << std::endl;
	std::vector<cl_device_id> deviceIds(deviceIdCount);
	clGetDeviceIDs(platformIds[currentPlatform], CL_DEVICE_TYPE_ALL, deviceIdCount, deviceIds.data(), nullptr);
	for (int i = 0; i < deviceIdCount; ++i) {
		clGetDeviceInfo(deviceIds[i], CL_DEVICE_TYPE, 100, &type, nullptr);
		if (type == CL_DEVICE_TYPE_GPU) {
			preferredDeviceId = i;
			break;
		}
	}
	clGetDeviceInfo(deviceIds[preferredDeviceId], CL_DEVICE_NAME, 100, name, nullptr);
	std::cout << "Device found: " << name;
	if (type == CL_DEVICE_TYPE_GPU) {
		std::cout << " (GPU)" << std::endl;
	}
	else {
		std::cout << " (CPU)" << std::endl;
	}
	const cl_context_properties contextProperties[] = {
		CL_CONTEXT_PLATFORM, (cl_context_properties)platformIds[currentPlatform], 0
	};
	cl_context context = clCreateContextFromType(contextProperties, type, nullptr, nullptr, nullptr);
    /// читаем код cl программы
    std::ifstream file("kernel.cl");
    std::stringstream ss;
    ss << file.rdbuf(); //read the file
    std::string str = ss.str();
    const char *code = str.c_str(); //str holds the content of the file

	char log[1000];
    cl_program program = clCreateProgramWithSource(context, 1, &code, 0, nullptr);
	cl_int out = clBuildProgram(program, 1, deviceIds.data(), "", nullptr, nullptr);
	clGetProgramBuildInfo(program, deviceIds[preferredDeviceId], CL_PROGRAM_BUILD_LOG, 1000, &log, nullptr);
	float *x = new float[ARRAY_SIZE_1];
	float *y = new float[ARRAY_SIZE_2];
	generateMatrix(B_WIDTH, A_WIDTH_B_HEIGHT, x);
	generateMatrix(A_WIDTH_B_HEIGHT, A_HEIGHT, y);
	float *z = new float[ARRAY_SIZE_3];
	cl_kernel kernel = clCreateKernel(program, "sum", nullptr);
	cl_mem buff1 = clCreateBuffer(context, CL_MEM_READ_ONLY, ARRAY_SIZE_1 * sizeof(float), nullptr, nullptr);
	cl_mem buff2 = clCreateBuffer(context, CL_MEM_READ_ONLY, ARRAY_SIZE_2 * sizeof(float), nullptr, nullptr);
	cl_mem buff3 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, ARRAY_SIZE_3 * sizeof(float), nullptr, nullptr);
	cl_command_queue queue1 = clCreateCommandQueue(context, deviceIds[preferredDeviceId], CL_QUEUE_PROFILING_ENABLE, nullptr);
	clEnqueueWriteBuffer(queue1, buff1, CL_FALSE, 0, ARRAY_SIZE_1 * sizeof(float), x, 0, nullptr, nullptr);
	clEnqueueWriteBuffer(queue1, buff2, CL_FALSE, 0, ARRAY_SIZE_2 * sizeof(float), y, 0, nullptr, nullptr);
	unsigned int size1 = B_WIDTH;
	unsigned int size2 = A_WIDTH_B_HEIGHT;
	unsigned int size3 = A_HEIGHT;
	clSetKernelArg(kernel, 0, sizeof(cl_mem), &buff1);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &buff2);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), &buff3);
	clSetKernelArg(kernel, 3, sizeof(cl_mem), &size1);
	clSetKernelArg(kernel, 4, sizeof(cl_mem), &size2);
	clSetKernelArg(kernel, 5, sizeof(cl_mem), &size3);
	size_t block[2] = { BLOCK_SIZE, BLOCK_SIZE };
	if (size1 % 8 != 0) {
		size1 += 8 - B_WIDTH % 8;
	}
	if (size3 % 8 != 0) {
		size3 += 8 - A_HEIGHT % 8;
	}
	size_t threads[2] = { size1, size3 };
	cl_event event;
	clEnqueueNDRangeKernel(queue1, kernel, 2, nullptr, threads, block, 0, nullptr, &event);
	clEnqueueReadBuffer(queue1, buff3, CL_TRUE, 0, ARRAY_SIZE_3 * sizeof(float), z, 0, nullptr, nullptr);

    cl_ulong start, end, time;
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, nullptr);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, nullptr);
    time = end - start;

	float ratio;
	if (time == 0) {
		ratio = 0;
	}
	else {
		ratio = (float)OPERATIONS / (float)time;
	}
	if (checkMultipliedMatrix(x, y, z)) {
		std::cout << "Matrices multiplied correctly." << std::endl;
	}
	else {
		std::cout << "Matrices multiplied incorrectly." << std::endl;
	}
	std::cout << "Gigaflops: " << ratio << std::endl;
	delete[] x;
	delete[] y;
	delete[] z;
	return 0;
}
