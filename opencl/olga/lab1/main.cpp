#pragma comment(lib, "opencl.lib")

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include <iostream>
#include <stdio.h>
#include <fstream>

#define NikonorIvanich 8

using namespace std;

inline void checkErr(cl_int err, const char * name) {
	if (err != CL_SUCCESS) {
		std::cerr << "ERROR: " << name << " (" << err << ")" << std::endl;
		exit(EXIT_FAILURE);
	}
}


int pm(float *first, float *second, float *third, int fsize, int ssize, int tsize)
{
    float num;
    for (int i = 0; i < fsize; i++)
        for (int j = 0; j < ssize; j++)
        {
            num = 0;
            for (int k = 0; k < tsize; k++)
                num += first[tsize * i + k] * second[ssize * k + j];
            third[ssize * i + j] = num;
        }
}

int main()
{
	cl_uint kop;
	cl_int ret = clGetPlatformIDs(0, NULL, &kop);
    cl_platform_id *plot;
	plot = new cl_platform_id[kop];
	ret = clGetPlatformIDs(kop, plot, NULL);
	cl_device_id *ustrica;
	cl_device_id omar;
	cl_uint mobilka;
    cl_int devushka;
    cl_platform_id oplata;
	int krot = 0;
	for (int i = 0; i < kop; ++i)
	{
		devushka = clGetDeviceIDs(plot[i], CL_DEVICE_TYPE_ALL, 0, NULL, &mobilka);
		ustrica = new cl_device_id[mobilka];
		devushka = clGetDeviceIDs(plot[i], CL_DEVICE_TYPE_ALL, mobilka, ustrica, NULL);
		for (int j = 0; j < mobilka; ++j)
		{
			cl_device_type viskar;
			clGetDeviceInfo(ustrica[j], CL_DEVICE_TYPE, sizeof(viskar), &viskar, NULL);
			if (viskar == CL_DEVICE_TYPE_GPU)
			{
				oplata = plot[i];
				omar = ustrica[j];
				krot = 117;
				break;
			}
		}
		if (krot == 117) break;
	}
	FILE *frog = fopen("source.cl", "rb");
	fseek(frog, 0, SEEK_END);
	size_t BigFrog = ftell(frog);
	fseek(frog, 0, SEEK_SET);
	char *stringi = new char[BigFrog];
	fread(stringi, BigFrog, 1, frog);
	
    fclose(frog);
	char logarifm[1000];
	cl_int eretik;
	const cl_context_properties MisterProper[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)oplata, 0};
	cl_context cotex = clCreateContextFromType(MisterProper, CL_DEVICE_TYPE_GPU, nullptr, nullptr, nullptr);

	cl_program proNature = clCreateProgramWithSource(cotex, 1, (const char **)&stringi, (const size_t *) &BigFrog, &eretik);
	checkErr(eretik, "clCreateProgramWithSource()");
	eretik = clBuildProgram(proNature, 1, ustrica, "", nullptr, nullptr);
	checkErr(eretik, "clBuildProgram()");
	clGetProgramBuildInfo(proNature, omar, CL_PROGRAM_BUILD_LOG, 1000, &logarifm, nullptr);
	const int azon = 2, bizon = 4, cizon = 8;
	static cl_float arghangelsk[azon * bizon];
	static cl_float bobik[bizon * cizon];
	static cl_float vinishko[azon * cizon];
	for (int i = 0; i < azon; ++i)
		for (int j = 0; j < bizon; ++j)
			arghangelsk[bizon * i + j] = 2;

	for (int i = 0; i < bizon; ++i)
		for (int j = 0; j < cizon; ++j)
			bobik[cizon * i + j] = 3;

	cl_kernel panic = clCreateKernel(proNature, "sum", nullptr);
	cl_mem vampir = clCreateBuffer(cotex, CL_MEM_WRITE_ONLY, sizeof(arghangelsk), nullptr, nullptr);
	cl_mem zombi = clCreateBuffer(cotex, CL_MEM_WRITE_ONLY, sizeof(bobik), nullptr, nullptr);
	cl_mem oboroten = clCreateBuffer(cotex, CL_MEM_WRITE_ONLY, sizeof(vinishko), nullptr, nullptr);

	cl_command_queue babulka1 = clCreateCommandQueue(cotex, omar, 0, nullptr);
	clEnqueueWriteBuffer(babulka1, vampir, CL_FALSE, 0, sizeof(arghangelsk), &arghangelsk, 0, nullptr, nullptr);
	clEnqueueWriteBuffer(babulka1, zombi, CL_FALSE, 0, sizeof(bobik), &bobik, 0, nullptr, nullptr);
	
	clSetKernelArg(panic, 0, sizeof(cl_mem), &vampir);
	clSetKernelArg(panic, 1, sizeof(cl_mem), &zombi);
	clSetKernelArg(panic, 2, sizeof(cl_mem), &oboroten);
	clSetKernelArg(panic, 3, sizeof(cl_int), &azon);
	clSetKernelArg(panic, 4, sizeof(cl_int), &bizon);
	clSetKernelArg(panic, 5, sizeof(cl_int), &cizon);
	size_t DartVader[2] = {azon, cizon};
	size_t filfack[2] = {NikonorIvanich, NikonorIvanich};
	
	clEnqueueNDRangeKernel(babulka1, panic, 2, nullptr, DartVader, filfack, 0, nullptr, nullptr);
	clEnqueueReadBuffer(babulka1, oboroten, CL_TRUE, 0, sizeof(vinishko), &vinishko, 0, nullptr, nullptr);
	for (int kuyakuya = 0; kuyakuya < azon; ++kuyakuya)
		for (int i = 0; i < cizon; ++i)
		cout << vinishko[cizon * kuyakuya + i] << "\n";
	return 0;
}
