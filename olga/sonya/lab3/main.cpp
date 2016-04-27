#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

int fr = 0, ix = 1, iy = 1, dc = 1;
//int fry = 0;

double f(double x, double y)
{
	return (5 * atan(pow((x + 3), 2)) + pow(x, 2) + atan(pow((2 * y - 1), 2)));
}

double f_dx(double x, double y)
{
	return (2 * x + 10 * (x + 3) / (pow((x + 3), 4) + 1));
}

double f_dy(double x, double y)
{
	return (4 * (2 * y - 1) / (pow((2 * y - 1), 4) + 1));
}

double norma(double x, double y) // двумерная норма
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

void gradient(double bx0, double by0, double eps, ofstream *fout, ofstream *fout1)
{
	vector<double> x(0);
	vector<double> y(0);
	x.push_back(bx0);
	y.push_back(by0);
	int i = 0;
	int k = 3;
	bool del = true, a, b, c;
	//double bx = bx0, by = by0;
	double alpha1 = 0.02, alpha2 = 0.03; // d - скорость спуска
	double x1, y1;
	double dx, dy, n;
	double ax1 = 0, ay1 = 0, ax2 = 0, ay2 = 0, a3 = 0, a4 = 0;
	//ofstream fout("GradientAlpha1.csv");
	do
	{
		dx = f_dx(x.at(i), y.at(i));
		dy = f_dy(x.at(i), y.at(i));
		n = norma(x.at(i), y.at(i));
		x1 = x.at(i) - alpha1 * (dx / abs(n));
		y1 = y.at(i) - alpha1 * (dy / abs(n));
		x.push_back(x1);
		y.push_back(y1);
		*fout << i << ';' << x.at(i) << ';' << y.at(i) << ';' << endl;
		i++;
		if (i < k)
		{
			continue;
		}
		else
		{
			ax1 = abs(x.at(i) - x.at(i - 1));
			ay1 = abs(y.at(i) - y.at(i - 1));
			ax2 = abs(x.at(i) - x.at(i - k)) / (k * alpha1);
			ay2 = abs(y.at(i) - y.at(i - k)) / (k * alpha1);
		}
		if (ax1 < eps && ay1 < eps)
		{
			a = false;
		}
		else
		{
			a = true;
		}
		if (ax2 < alpha1 && ay2 < alpha1)
		{
			b = false;
		}
		else
		{
			b = true;
		}
		if ((i < k) || b || a)
		{
			del = true;
		}
		else
		{
			del = false;
		}
	} while (del);
	//fout.close();
	x.clear();
	y.clear();
	x.push_back(bx0);
	y.push_back(by0);
	i = 0;
	del = true;
	//ofstream fout1("GradientAlpha2.csv");
	do
	{
		dx = f_dx(x.at(i), y.at(i));
		dy = f_dy(x.at(i), y.at(i));
		n = norma(x.at(i), y.at(i));
		x1 = x.at(i) - alpha2 * (dx / abs(n));
		y1 = y.at(i) - alpha2 * (dy / abs(n));
		x.push_back(x1);
		y.push_back(y1);
		*fout1 << i << ';' << x.at(i) << ';' << y.at(i) << ';' << endl;
		i++;
		if (i < k)
		{
			continue;
		}
		else
		{
			ax1 = abs(x.at(i) - x.at(i - 1));
			ay1 = abs(y.at(i) - y.at(i - 1));
			ax2 = abs(x.at(i) - x.at(i - k)) / (k * alpha2);
			ay2 = abs(y.at(i) - y.at(i - k)) / (k * alpha2);
		}
		if (ax1 < eps && ay1 < eps)
		{
			a = false;
		}
		else
		{
			a = true;
		}
		if (ax2 < alpha2 && ay2 < alpha2)
		{
			b = false;
		}
		else
		{
			b = true;
		}
		if ((i < k) || b || a)
		{
			del = true;
		}
		else
		{
			del = false;
		}
	} while (del);
	//fout1.close();
}

void grad_adapt(double bx0, double by0, double eps, ofstream *fout)
{
	vector<double> x(0);
	vector<double> y(0);
	x.push_back(bx0);
	y.push_back(by0);
	int i = 0;
	int k = 3;
	bool del = true, a, b, c;
	//double bx = bx0, by = by0;
	double alpha = 0.02; // d - скорость спуска
	double x1[3], y1[3], x2, y2;
	double al[3] = { alpha }; // = { alpha, alpha / w, alpha * w };
	double dx, dy, n;
	double w, f_;
	double ax1 = 0, ay1 = 0, ax2 = 0, ay2 = 0, a3 = 0, a4 = 0;
	do
	{
		f_ = INT_MAX;
		w = (1 + pow(10, -7)) + rand() % 2;
		al[1] = alpha / w;
		al[2] = alpha * w;
		dx = f_dx(x.at(i), y.at(i));
		dy = f_dy(x.at(i), y.at(i));
		n = norma(x.at(i), y.at(i));
		for (int j = 0; j < 3; j++)
		{
			x1[j] = x.at(i) - al[j] * (dx / abs(n));
			y1[j] = y.at(i) - al[j] * (dy / abs(n));
		}
		for (int k = 0; k < 3; k++)
		{
			if (f(x1[k], y1[k]) < f_)
			{
				f_ = f(x1[k], y1[k]);
				x2 = x1[k];
				y2 = y1[k];
			}
		}
		x.push_back(x2);
		y.push_back(y2);
		*fout << i << ';' << x.at(i) << ';' << y.at(i) << ';' << endl;
		if (i >= k)
		{
			ax1 = abs(x.at(i) - x.at(i - 1));
			ay1 = abs(y.at(i) - y.at(i - 1));
			ax2 = abs(x.at(i) - x.at(i - k)) / (k * alpha);
			ay2 = abs(y.at(i) - y.at(i - k)) / (k * alpha);
		}
		/*else
		{
			ax1 = abs(x.at(i) - x.at(i - 1));
			ay1 = abs(y.at(i) - y.at(i - 1));
			ax2 = abs(x.at(i) - x.at(i - k)) / (k * alpha);
			ay2 = abs(y.at(i) - y.at(i - k)) / (k * alpha);
		}*/
		if (ax1 < eps && ay1 < eps)
		{
			a = false;
		}
		else
		{
			a = true;
		}
		if (ax2 < alpha && ay2 < alpha)
		{
			b = false;
		}
		else
		{
			b = true;
		}
		if ((i < k) || b || a)
		{
			del = true;
		}
		else
		{
			del = false;
		}
		i++;
	} while (del);
}

double coordx(double x, double y, double e)
{
	while (f(x, y) - f(x - 1, y) > e)
	{
		if (f(x, y) < f(x + dc, y))
		{
			x += dc;
		}
		else if (f(x - dc, y) < f(x, y))
		{
			x -= dc;
		}
		ix++;
	}
	return x;
}

double coordy(double x, double y, double e)
{
	while (f(x, y) - f(x, y - 1) > e)
	{
		if (f(x, y) < f(x, y + dc))
		{
			y += dc;
		}
		else if (f(x, y - dc) < f(x, y))
		{
			y -= dc;
		}
		iy++;
	}
	return y;
}

void grad_coord(double bx0, double by0, double eps)
{
	double x0 = bx0, y0 = by0, x, y;
	ofstream fout("GradientCoord.csv");
	x = coordx(x0, y0, eps);
	y = coordy(x, y0, eps);
	fout << ix << ";" << iy << ";" << x << ";" << y << ";" << f(x, y) << ";" << endl;
	fout.close();
}
/*
double min_func(double x0, double y0, double step)
{
	int count = 0;
	double x = x0, y = y0;
	while (true)
	{
		if (f(x, y) < f(x + step, y + step))
		{
			break;
		}
		x += step;
		y += step;
		count++;
	}
	return point;
}

void search_min_of_func(double x0, double y0, double step)
{
	double x = x0, y = y0;
	int count = 0;
	if (f(x + step, y + step) < f(x - step, y - step))
	{
		while (true)
		{
			if (f(x, y) < f(x + step, y + step))
			{
				break;
			}
			x += step;
			y += step;
			count++;
		}
		//return min_func(point, step);
	}
	else if (f(x + step, y + step) == f(x - step, y - step))
	{
		if (f(x + step, y + step) > f(x, y))
		{
			return f(x, y);
		}
		else
		{
			count = 0;
			while (true)
			{
				if (f(x, y) < f(x + step, y + step))
				{
					break;
				}
				x += step;
				y += step;
				count++;
			}
			//return min_func(point, step);
		}
	}
	else
	{
		count = 0;
		while (true)
		{
			if (f(x, y) < f(x - step, y - step))
			{
				break;
			}
			x -= step;
			y -= step;
			count++;
		}
		//return min_func(point, step * (-1));
	}
}
*/
int main()
{
	srand(time(NULL));
	double x = -3, y = 2; // начальная точка. Изменены знаки, т.к. точка (3; -2) находится правее точки минимума графика! (см. рис.)
	double eps1 = 0.5, eps2 = 0.1, eps3 = 0.01;
	ofstream fout("GradientAlpha1.csv");
	ofstream fout1("GradientAlpha2.csv");
	//int t0 = clock()
	gradient(x, y, eps3, &fout, &fout1);
	//int t1 = clock();
	fout.close();
	fout1.close();
	ofstream fout2("GradientAdapt.csv");
	grad_adapt(x, y, eps3, &fout2);
	fout2.close();
	grad_coord(x, y, eps3);
	//ofstream fout2("GradientF2.csv");
	//gradient(x, y, eps3);
	//fout2.close();
	//cout << "Time for gradient: " << (double)(t1 - t0) / CLOCKS_PER_SEC << endl;
	cout << "Excellent!" << endl;
	system("pause");
	return 0;
}
