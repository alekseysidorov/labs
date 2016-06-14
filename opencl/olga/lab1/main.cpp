#pragma comment(lib, "opencl.lib")

#include <CL/cl.h>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;


void pm(float *a, float *b, float *c, int az, int bz, int cz)
{
	for (int i = 0; i < az; ++i)
		for (int j = 0; j < cz; ++j)
		{
			float g = 0;
			for (int k = 0; k < bz; ++k)
			{
				g += a[bz * i + k] * b[cz * k + j];
			}
			c[cz * i + j] = g;
		}
}

int main()
{
	cl_uint numEnt;
	cl_platform_id *platforms;
	cl_platform_id plat;
	cl_uint numPl;
	cl_int ret = clGetPlatformIDs(0, NULL, &numPl);
	platforms = new cl_platform_id[numPl];
	ret = clGetPlatformIDs(numPl, platforms, NULL);
	cl_int dev;
	cl_device_id *devices;
	cl_device_id devic;
	cl_uint numDev;
	int k = 0;
	for (int i = 0; i < numPl; i++)
	{
		dev = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &numDev);
		devices = new cl_device_id[numDev];
		dev = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, numDev, devices, NULL);
		cout << platforms[i] << " ";
		for (int j = 0; j < numDev; j++)
		{
			cl_device_type oo;
			clGetDeviceInfo(devices[j], CL_DEVICE_TYPE, sizeof(oo), &oo, NULL);
			if (oo == CL_DEVICE_TYPE_GPU) { plat = platforms[i]; devic = devices[j]; k = 117; break; }
			cout << devices[j] << " ";
		}
		if (k == 117) break;
		cout << endl;
	}
	ifstream fin("source.cl");
	char *buff;
	char b;

	int count = 0;
	while (!fin.eof())
	{
		fin.read(&b, 1);
		count++;
	}
	buff = new char[count];
	count = 0;
	fin.close();
	fin.open("source.cl");
	while (!fin.eof())
	{
		fin.read(&buff[count], 1);
		count++;
	}
	buff[count - 1] = 0;
	
	for (int i = 0; i < count; i++)
	{
		cout << buff[i];
	}
	cout << endl;
	char **codeptr = &buff;
	char log[1000];
	cl_int error;
	const cl_context_properties contextProperties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)plat, 0};
	cl_context context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_GPU, nullptr, nullptr, nullptr);

	cl_program program = clCreateProgramWithSource(context, 1, (const char **)codeptr, (const size_t *) &count, &error);
	cl_int out = clBuildProgram(program, 1, devices, "", nullptr, nullptr);
	clGetProgramBuildInfo(program, devic, CL_PROGRAM_BUILD_LOG, 1000, &log, nullptr);
	std::cout << log;
	cl_float a[12];
	cl_float bb[12];
	cl_float c[16];
	int e = 4, o = 3;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 3; ++j)
		{
			a[3 * i + j] = 2;
			bb[4 * j + i] = 3;
		}
	cl_kernel kernel = clCreateKernel(program, "sum", nullptr);
	cl_mem buff1 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(a), nullptr, nullptr);
	cl_mem buff2 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(bb), nullptr, nullptr);
	cl_mem buff3 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(c), nullptr, nullptr);

	cl_command_queue queue1 = clCreateCommandQueue(context, devic, 0, nullptr);
	clEnqueueWriteBuffer(queue1, buff1, CL_FALSE, 0, sizeof(a), &a, 0, nullptr, nullptr);
	clEnqueueWriteBuffer(queue1, buff2, CL_FALSE, 0, sizeof(bb), &bb, 0, nullptr, nullptr);
	
	clSetKernelArg(kernel, 0, sizeof(cl_mem), &buff1);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &buff2);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), &buff3);
	clSetKernelArg(kernel, 3, sizeof(cl_int), &e);
	clSetKernelArg(kernel, 4, sizeof(cl_int), &o);
	clSetKernelArg(kernel, 5, sizeof(cl_int), &e);
	size_t five[2] = {4, 4};
	
	clEnqueueNDRangeKernel(queue1, kernel, 2, nullptr, five, NULL, 0, nullptr, nullptr);
	clEnqueueReadBuffer(queue1, buff3, CL_TRUE, 0, sizeof(c), &c, 0, nullptr, nullptr);
	for (int p = 0; p < 4; ++p)
		for (int i = 0; i < 4; ++i)
	{
		cout << c[4 * p + i] << endl;
	}

	//pm();

	delete[]platforms;
	delete[]buff;
	system("pause");
	return 0;
}