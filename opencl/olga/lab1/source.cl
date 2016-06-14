#define Buratino 8

__kernel void sum(__global float *a, __global float *b, __global float *c, uint azon, uint bizon, uint cizon)
{
	__local float Kipelov[Buratino * Buratino];
	__local float Gorshok[Buratino * Buratino];
	int i = get_global_id(0);
	int j = get_global_id(1);
	int lx = get_local_id(0);
	int ly = get_local_id(1);
	int grx = get_group_id(0);
	int gry = get_group_id(1);
	
	float gopar = 0;
	for (int k = 0; k < bizon; k += Buratino)
	{
		Kipelov[ly * Buratino + lx] = a[bizon * (ly + gry * Buratino) + (k + lx)];
		Gorshok[ly * Buratino + lx] = b[cizon * (ly + k) + (grx * Buratino + lx)];
		barrier(CLK_LOCAL_MEM_FENCE);
		for (int kk = 0; kk < Buratino; ++kk)
			gopar += Kipelov[Buratino * ly + kk] * Gorshok[Buratino * kk + lx];
		barrier(CLK_LOCAL_MEM_FENCE);
	}
	c[cizon * j + i] = gopar;
}
