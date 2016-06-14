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
void matrix_mul(float *a, float *b, float *c, size_t az, size_t bz, size_t cz)
{
    for (size_t i = 0; i < az; ++i) {
        for (size_t j = 0; j < bz; ++j) {
            float sum = 0;
            for (size_t k = 0; k < cz; ++k) {
                sum += a[cz * i + k] * b[bz * k + j];
            }
            c[bz * i + j] = sum;
        }
    }
}

/// перемножение двух матриц при помощи opencl
void matrix_mul_cl(float *a, float *b, float *c, size_t az, size_t bz, size_t cz)
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

            /// берем первую попавшуюся видеокарту
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
    std::cout << out << std::endl;
    assert(ret == CL_SUCCESS);

    /// вычисляем размеры буферов
    size_t ab = sizeof(float) * az * bz;
    size_t bb = sizeof(float) * bz * cz;
    size_t cb = sizeof(float) * az * cz;

    /// а теперь выделяем память под массивы и создаем kernel и очередь команд
    cl_kernel kernel = clCreateKernel(program, "matrix_mul", &ret);
    assert(ret == CL_SUCCESS);
    cl_mem am = clCreateBuffer(context, CL_MEM_READ_ONLY, ab, nullptr, nullptr);
    cl_mem bm = clCreateBuffer(context, CL_MEM_READ_ONLY, bb, nullptr, nullptr);
    cl_mem cm = clCreateBuffer(context, CL_MEM_READ_WRITE, cb, nullptr, nullptr);

    cl_command_queue queue = clCreateCommandQueue(context, dev, 0, nullptr);
    clEnqueueWriteBuffer(queue, am, CL_FALSE, 0, ab, a, 0, nullptr, nullptr);
    clEnqueueWriteBuffer(queue, bm, CL_FALSE, 0, bb, b, 0, nullptr, nullptr);

    /// Забиваем аргументы функции
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &am);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &bm);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &cm);
    clSetKernelArg(kernel, 3, sizeof(cl_int), &az);
    clSetKernelArg(kernel, 4, sizeof(cl_int), &bz);
    clSetKernelArg(kernel, 5, sizeof(cl_int), &cz);

    size_t DartVader[2] = { az, cz };
    size_t filfack[2] = { NikonorIvanich, NikonorIvanich };

    clEnqueueNDRangeKernel(queue, kernel, 2, nullptr, DartVader, filfack, 0, nullptr, nullptr);
    clEnqueueReadBuffer(queue, cm, CL_TRUE, 0, cb, c, 0, nullptr, nullptr);
}

int main()
{
    /// заполнение матрицы
    const int an = 2, bn = 4, cn = 8;
    cl_float a[an * bn];
    cl_float b[bn * cn];

    for (int i = 0; i < an; ++i)
        for (int j = 0; j < bn; ++j)
            a[bn * i + j] = 2;

    for (int i = 0; i < bn; ++i)
        for (int j = 0; j < cn; ++j)
            b[cn * i + j] = 3;

    /// перемножения матриц двумя способами, результаты должны совпасть

    cl_float c1[an * cn] = {};
    matrix_mul(a, b, c1, an, bn, cn);

    cl_float c2[an * cn] = {};
    matrix_mul_cl(a, b, c2, an, bn, cn);

    for (int i = 0; i < an; ++i) {
        for (int j = 0; j < cn; ++j) {
            std::cout << "c1=" << c1[cn * i + j] << " c2=" << c2[cn * i + j] << "\n";
        }
    }
    return 0;
}



//using namespace std;

//inline void checkErr(cl_int err, const char * name) {
//	if (err != CL_SUCCESS) {
//		std::cerr << "ERROR: " << name << " (" << err << ")" << std::endl;
//		exit(EXIT_FAILURE);
//	}
//}


//int pm(float *first, float *second, float *third, int fsize, int ssize, int tsize)
//{
//    float num;
//    for (int i = 0; i < fsize; i++)
//        for (int j = 0; j < ssize; j++)
//        {
//            num = 0;
//            for (int k = 0; k < tsize; k++)
//                num += first[tsize * i + k] * second[ssize * k + j];
//            third[ssize * i + j] = num;
//        }
//}

//int main()
//{
//    cl_uint kop;
//    cl_int ret = clGetPlatformIDs(0, NULL, &kop);
//    cl_platform_id *plot;
//    plot = new cl_platform_id[kop];
//    ret = clGetPlatformIDs(kop, plot, NULL);
//    cl_device_id *ustrica;
//    cl_device_id omar;
//    cl_uint mobilka;
//    cl_int devushka;
//    cl_platform_id oplata;
//    int krot = 0;
//    for (int i = 0; i < kop; ++i)
//    {
//        devushka = clGetDeviceIDs(plot[i], CL_DEVICE_TYPE_ALL, 0, NULL, &mobilka);
//        ustrica = new cl_device_id[mobilka];
//        devushka = clGetDeviceIDs(plot[i], CL_DEVICE_TYPE_ALL, mobilka, ustrica, NULL);
//        for (int j = 0; j < mobilka; ++j)
//        {
//            cl_device_type viskar;
//            clGetDeviceInfo(ustrica[j], CL_DEVICE_TYPE, sizeof(viskar), &viskar, NULL);
//            if (viskar == CL_DEVICE_TYPE_GPU)
//            {
//                oplata = plot[i];
//                omar = ustrica[j];
//                krot = 117;
//                break;
//            }
//        }
//        if (krot == 117) break;
//    }
//    FILE *frog = fopen("source.cl", "rb");
//    fseek(frog, 0, SEEK_END);
//    size_t BigFrog = ftell(frog);
//    fseek(frog, 0, SEEK_SET);
//    char *stringi = new char[BigFrog];
//    fread(stringi, BigFrog, 1, frog);

//    fclose(frog);
//    char logarifm[1000];
//    cl_int eretik;
//    const cl_context_properties MisterProper[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)oplata, 0};
//    cl_context cotex = clCreateContextFromType(MisterProper, CL_DEVICE_TYPE_GPU, nullptr, nullptr, nullptr);

//    cl_program proNature = clCreateProgramWithSource(cotex, 1, (const char **)&stringi, (const size_t *) &BigFrog, &eretik);
//    checkErr(eretik, "clCreateProgramWithSource()");
//    eretik = clBuildProgram(proNature, 1, ustrica, "", nullptr, nullptr);
//    checkErr(eretik, "clBuildProgram()");
//    clGetProgramBuildInfo(proNature, omar, CL_PROGRAM_BUILD_LOG, 1000, &logarifm, nullptr);
//    const int azon = 2, bizon = 4, cizon = 8;
//    static cl_float arghangelsk[azon * bizon];
//    static cl_float bobik[bizon * cizon];
//    static cl_float vinishko[azon * cizon];
//    for (int i = 0; i < azon; ++i)
//        for (int j = 0; j < bizon; ++j)
//            arghangelsk[bizon * i + j] = 2;

//    for (int i = 0; i < bizon; ++i)
//        for (int j = 0; j < cizon; ++j)
//            bobik[cizon * i + j] = 3;

//    cl_kernel panic = clCreateKernel(proNature, "sum", nullptr);
//    cl_mem vampir = clCreateBuffer(cotex, CL_MEM_WRITE_ONLY, sizeof(arghangelsk), nullptr, nullptr);
//    cl_mem zombi = clCreateBuffer(cotex, CL_MEM_WRITE_ONLY, sizeof(bobik), nullptr, nullptr);
//    cl_mem oboroten = clCreateBuffer(cotex, CL_MEM_WRITE_ONLY, sizeof(vinishko), nullptr, nullptr);

//    cl_command_queue babulka1 = clCreateCommandQueue(cotex, omar, 0, nullptr);
//    clEnqueueWriteBuffer(babulka1, vampir, CL_FALSE, 0, sizeof(arghangelsk), &arghangelsk, 0, nullptr, nullptr);
//    clEnqueueWriteBuffer(babulka1, zombi, CL_FALSE, 0, sizeof(bobik), &bobik, 0, nullptr, nullptr);

//    clSetKernelArg(panic, 0, sizeof(cl_mem), &vampir);
//    clSetKernelArg(panic, 1, sizeof(cl_mem), &zombi);
//    clSetKernelArg(panic, 2, sizeof(cl_mem), &oboroten);
//    clSetKernelArg(panic, 3, sizeof(cl_int), &azon);
//    clSetKernelArg(panic, 4, sizeof(cl_int), &bizon);
//    clSetKernelArg(panic, 5, sizeof(cl_int), &cizon);
//    size_t DartVader[2] = {azon, cizon};
//    size_t filfack[2] = {NikonorIvanich, NikonorIvanich};

//    clEnqueueNDRangeKernel(babulka1, panic, 2, nullptr, DartVader, filfack, 0, nullptr, nullptr);
//    clEnqueueReadBuffer(babulka1, oboroten, CL_TRUE, 0, sizeof(vinishko), &vinishko, 0, nullptr, nullptr);
//    for (int kuyakuya = 0; kuyakuya < azon; ++kuyakuya)
//        for (int i = 0; i < cizon; ++i)
//        cout << vinishko[cizon * kuyakuya + i] << "\n";
//    return 0;
//}
