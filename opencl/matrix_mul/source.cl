#define N 8

__kernel void matrix_mul(__global float *b, __global float *a, __global float *c, int cz, int bz, int az)
{
    __local float ant[N * N];
    __local float bnt[N * N];
    int i = get_global_id(0);
    int j = get_global_id(1);
    int lx = get_local_id(0);
    int ly = get_local_id(1);

    float g = 0;

    for (int k = 0; k < bz / N; ++k)
    {
        ant[ly * N + lx] = 0;
        if ((i < az) && (k * N + ly < bz))
            ant[ly * N + lx] = a[(k * N + ly) * az + i];
        if ((k * N + lx < bz) && (j < cz))
            bnt[ly * N + lx] = b[j * bz + k * N + lx];
        barrier(CLK_LOCAL_MEM_FENCE);
        for (int d = 0; d < N; ++d)
            g += ant[d * N + lx] * bnt[ly * N + d];
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    c[az * j + i] = g;
}

