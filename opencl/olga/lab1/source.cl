__kernel void sum(__global float *a, __global float *b, __global float *c, int az, int bz, int cz)
{
	size_t i = get_global_id(0);
	size_t j = get_global_id(1);
	float g = 0;
	for (int k = 0; k < 3; ++k)
	{
		g += a[3 * i + k] * b[4 * k + j];
	}
	c[4 * i + j] = g;
}