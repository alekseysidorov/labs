/* #define N 8

__kernel void matrix_mul(__global float *a, __global float *b, __global float *c, int az, int bz, int cz)
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
*/

__kernel void matrix_mul(__global const float *x, __global const float *y, __global float *z, uint size1, uint size2, uint size3)
{
        size_t xx = get_global_id(0);
        size_t yy = get_global_id(1);
        size_t localX = get_local_id(0);
        size_t localY = get_local_id(1);
        float sum = 0;
        __local float locMatrix1[8 * 8], locMatrix2[8 * 8];
        for (size_t i = 0; i < size2; i += 8) {
                size_t xy = i + localY;
                size_t yx = i + localX;
                locMatrix1[8 * localY + localX] = 0;
                if (xx < size1 && xy < size2) {
                        locMatrix1[8 * localY + localX] = x[xy * size1 + xx];
                }
                if (yx < size2 && yy < size3) {
                        locMatrix2[8 * localY + localX] = y[yy * size2 + yx];
                }
                barrier(CLK_LOCAL_MEM_FENCE);
                for (size_t j = 0; j < 8; ++j) {
                        sum += locMatrix1[8 * j + localX] * locMatrix2[8 * localY + j];
                }
                barrier(CLK_LOCAL_MEM_FENCE);
        }
                z[size1 * yy + xx] = sum;

}
