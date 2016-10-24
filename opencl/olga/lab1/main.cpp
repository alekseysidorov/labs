#pragma comment(lib, "opencl.lib")

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

#define NikonorIvanich 8

/// перемножение двух матриц на процессоре
void matrix_mul(cl_float *a, cl_float *b, cl_float *c, int az, int bz, int cz)
{
    for (size_t i = 0; i < az; ++i) {
        for (size_t j = 0; j < cz; ++j) {
            float sum = 0;
            for (size_t k = 0; k < bz; ++k) {
                sum += a[bz * i + k] * b[cz * k + j];
            }
            c[cz * i + j] = sum;
        }
    }
}

/// перемножение двух матриц при помощи opencl
void matrix_mul_cl(cl_float *a, cl_float *b, cl_float *c, int az, int bz, int cz)
{
    /// получить доступные платформы
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(0, NULL, &ret_num_platforms);

    /// получить список устройств
    std::vector<cl_platform_id> platforms(ret_num_platforms);
    ret = clGetPlatformIDs(ret_num_platforms, platforms.data(), NULL);

    cl_device_id dev = NULL;
    cl_platform_id plat = NULL;
    cl_device_type dev_type = 0;
    /// перебираем устройства, привязаные к платформе в поисках видеокарты
    for (size_t i = 0; i < platforms.size(); ++i) {
        /// по аналогии с платформами перебираем устройства
        cl_uint ret_num_devices;
        ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 0, NULL, &ret_num_devices);
        std::vector<cl_device_id> devices(ret_num_devices);
        ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, ret_num_devices, devices.data(), NULL);

        /// берем первую попавшуюся видеокарту
        if (!devices.empty()) {
            plat = platforms[i];
            dev = devices[0];
            dev_type = CL_DEVICE_TYPE_GPU;
            break;
        }
    }

    if (!dev) {
        /// если нет видеокарты, то пробуем найти процессор
        for (size_t i = 0; i < platforms.size(); ++i) {
            /// по аналогии с платформами перебираем устройства
            cl_uint ret_num_devices;
            ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_CPU, 0, NULL, &ret_num_devices);
            std::vector<cl_device_id> devices(ret_num_devices);
            ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_CPU, ret_num_devices, devices.data(), NULL);

            /// берем первую попавшуюся процессору
            if (!devices.empty()) {
                plat = platforms[i];
                dev = devices[0];
                dev_type = CL_DEVICE_TYPE_CPU;
                break;
            }
        }
    }

    /// читаем код cl программы
    std::ifstream file("source.cl");
    std::stringstream ss;
    ss << file.rdbuf(); //read the file
    std::string str = ss.str();
    const char *code = str.c_str(); //str holds the content of the file

    /// создаем контекст и компилируем нашу программу
    const cl_context_properties props[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)plat, 0};
    cl_context context = clCreateContextFromType(props, dev_type, nullptr, nullptr, nullptr);

    cl_program program = clCreateProgramWithSource(context, 1, &code, 0, &ret);
    assert(ret == CL_SUCCESS);
    ret = clBuildProgram(program, 1, &dev, nullptr, nullptr, nullptr);
    char out[1000];
    clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, 1000, &out, nullptr);
    assert(ret == CL_SUCCESS);
    std::cout << out << std::endl;

    /// вычисляем размеры буферов
    int ab = sizeof(cl_float) * az * bz;
    int bb = sizeof(cl_float) * bz * cz;
    int cb = sizeof(cl_float) * az * cz;

    /// а теперь выделяем память под массивы и создаем kernel и очередь команд
    cl_kernel kernel = clCreateKernel(program, "matrix_mul", &ret);
    assert(ret == CL_SUCCESS);
    cl_mem am = clCreateBuffer(context, CL_MEM_READ_ONLY, ab, nullptr, &ret);
    assert(ret == CL_SUCCESS);
    cl_mem bm = clCreateBuffer(context, CL_MEM_READ_ONLY, bb, nullptr, &ret);
    assert(ret == CL_SUCCESS);
    cl_mem cm = clCreateBuffer(context, CL_MEM_READ_WRITE, cb, nullptr, &ret);
    assert(ret == CL_SUCCESS);

    cl_command_queue queue = clCreateCommandQueue(context, dev, 0, nullptr);
    ret = clEnqueueWriteBuffer(queue, am, CL_FALSE, 0, ab, a, 0, nullptr, nullptr);
    assert(ret == CL_SUCCESS);
    ret = clEnqueueWriteBuffer(queue, bm, CL_FALSE, 0, bb, b, 0, nullptr, nullptr);
    assert(ret == CL_SUCCESS);

    /// Забиваем аргументы функции
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &am);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &bm);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &cm);
    clSetKernelArg(kernel, 3, sizeof(cl_int), &az);
    clSetKernelArg(kernel, 4, sizeof(cl_int), &bz);
    clSetKernelArg(kernel, 5, sizeof(cl_int), &cz);

    size_t global_work_size[2] = { size_t(az), size_t(cz) };
    size_t local_work_size[2] = { NikonorIvanich, NikonorIvanich };

    ret = clEnqueueNDRangeKernel(queue, kernel, 2, nullptr, global_work_size, local_work_size, 0, nullptr, nullptr);
    assert(ret == CL_SUCCESS);
    ret = clEnqueueReadBuffer(queue, cm, CL_TRUE, 0, cb, c, 0, nullptr, nullptr);
    assert(ret == CL_SUCCESS);
}

int main()
{
    /// заполнение матрицы
    const int an = 8, bn = 16, cn = 24;
    cl_float a[an * bn];
    cl_float b[bn * cn];

    for (int i = 0; i < an; ++i)
        for (int j = 0; j < bn; ++j)
            a[bn * i + j] = i + 1;

    for (int i = 0; i < bn; ++i)
        for (int j = 0; j < cn; ++j)
            b[cn * i + j] = j + 1;

    /// перемножения матриц двумя способами, результаты должны совпасть

    cl_float c1[an * cn] = {};
    matrix_mul(a, b, c1, an, bn, cn);

    cl_float c2[an * cn] = {};
    matrix_mul_cl(a, b, c2, an, bn, cn);


    for (int i = 0; i < an; ++i) {
        for (int j = 0; j < bn; ++j)
            std::cout << a[bn * i + j] << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;



    for (int i = 0; i < bn; ++i) {
        for (int j = 0; j < cn; ++j)
            std::cout << b[cn * i + j] << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;


    for (int i = 0; i < an; ++i) {
        for (int j = 0; j < cn; ++j)
            std::cout << c2[cn * i + j] << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;


    for (int i = 0; i < an; ++i) {
        for (int j = 0; j < cn; ++j)
            std::cout << c1[cn * i + j] << " ";
        std::cout << std::endl;
    }

    return 0;
}
