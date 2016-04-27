#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>

#define E 2.718281

using namespace std;

int i;
class pv
{
public:
	pv(double p, double v);
	bool operator <(const pv& rhs) const;
	double point;
	double value;
};

pv::pv(double p, double v) :
point(p),
value(v)
{}


bool pv::operator <(const pv& rhs) const
{
	return point < rhs.point;
}

const double a = 0; // нижняя граница отрезка
const double b = 100; // верхняя граница отрезка
const double es[] = { 3, 1, 0.1, 0.05 }; // эпсилон

double f(double x) // функция
{
	return pow(E, x);
}

double g(double x, double xn, double L)
{
	return f(xn) - L * fabs(x - xn);
}

double u(double x1, double x2, double L)
{
	return (f(x1) - f(x2) + L * (x1 + x2)) / (2.0 * L);
}


double l()
{
	int n = 1000;
	double h = fabs(b - a) / double(n - 1);

	double* X = new double[n];
	double* FX = new double[n];
	double* T = new double[n];

	double x = a;
	for (int i = 0; i < n; i++, x += h)
	{
		X[i] = x;
		FX[i] = f(x);
	}

	for (i = 1; i < n; i++)
	{
		T[i] = fabs(FX[i] - FX[i - 1]) / (X[i] - X[i - 1]);
	}

	delete[] X;
	delete[] FX;

	double L = T[1];
	for (i = 2; i < n; i++)
	{
		if (T[i] > L)
		{
			L = T[i];
		}
	}
	//cout << L << endl;

	delete[] T;
	return L;
}

double *loman_optimize(int nnn, string path)
{
	double L = l();
	cout << L << endl;
	vector<pv> v;

	vector<double> xs;
	vector<double> fxs;

	xs.push_back(5); // добавл€ем x0
	fxs.push_back(f(5));
	xs.push_back(b);
	fxs.push_back(f(b));

	v.push_back(pv(a, f(a)));
	v.push_back(pv(b, f(b)));


	double up = b;
	double un = u(a, b, L);

	v.push_back(pv(un, f(un)));

	xs.push_back(un);
	fxs.push_back(f(un));

	int k = 3;

	while (fabs(f(un) - f(up)) >= es[nnn])
	{
		k++;

		sort(v.begin(), v.end(), less<pv>());

		int p;

		for (i = 0; i < static_cast<int> (v.size()); i++)
		{
			if (un == v[i].point)
			{
				p = i;
				break;
			}
		}

		if (un != a)
		{
			double ul = u(v[p - 1].point, v[p].point, L);
			v.push_back(pv(ul, g(un, ul, L)));
		}
		if (un != b)
		{
			double ur = u(v[p].point, v[p + 1].point, L);
			v.push_back(pv(ur, g(un, ur, L)));
		}

		up = un;

		double min = v[0].value;
		int min_p = 0;
		for (int i = 1; i < static_cast<int> (v.size()); i++)
		{
			if (v[i].value < min)
			{
				min = v[i].value;
				min_p = i;
			}
		}

		un = v[min_p].point;
		v[min_p].value = f(un);

		xs.push_back(un);
		fxs.push_back(f(un));
	}

	ofstream table(path);
	table << "f(x) =  exp(x), e = " << es[nnn] << "; ћетод ломаных" << endl;
	table << "ѕоследовательность xi";
	for (int i = 0; i < xs.size(); i++)
	{
		table << ";x" << i;
	}
	table << endl;
	table << "xi";
	for (int i = 0; i < xs.size(); i++)
	{
		table << ";" << xs[i];
	}
	table << endl;
	table << "f(xi)";
	for (int i = 0; i < xs.size(); i++)
	{
		table << ";" << fxs[i];
	}
	table << endl;
	table.close();

	double *results = new double[3];
	results[0] = un;
	results[1] = f(un);
	results[2] = k;
	return results;
}

int main()
{
	double **all_results = new double*[4];
	all_results[0] = loman_optimize(0, "table1.csv");
	all_results[1] = loman_optimize(1, "table2.csv");
	all_results[2] = loman_optimize(2, "table3.csv");
	all_results[3] = loman_optimize(3, "table4.csv");

	ofstream table5("table5.csv");
	table5 << "ћетод ломаных" << endl;
	table5 << "e" << ";" << 3 << ";" << 1 << ";" << 0.1 << ";" << 0.05 << endl; // "e;e1;e2;e3;e4"
	table5 << "xn;" << all_results[0][0] << ";" << all_results[1][0] << ";" << all_results[2][0] << ";" << all_results[3][0] << endl;
	table5 << "f(xn);" << all_results[0][1] << ";" << all_results[1][1] << ";" << all_results[2][1] << ";" << all_results[3][1] << endl;
	table5 << "n;" << (int)all_results[0][2] << ";" << (int)all_results[1][2] << ";" << (int)all_results[2][2] << ";" << (int)all_results[3][2] << endl;
	table5.close();
	system("pause");
	return 0;
}
