
#include <stdio.h>

#include <iostream>
#include <math.h>

#include <functional>
#include <fstream>

#include<vector>

using namespace std;
struct Point
{
	double x;
	double y;
	Point(double x, double y) : x(x), y(y) {};
	Point() {};

};
double F_2(double x, double y, double _r);
int countCalc =0;
class Barrier_func
{
private:
	double _EPS, _EPS1, _r, _C;
	Point x_0;

public:
	int countIter = 0;
	static double Function(double x, double y)
	{
		int A1 = 1, A2 = 3;
		int a1 = 2, a2 = 1;
		int b1 = 3, b2 = 1;
		int c1 = 2, c2 = 1;
		int d1 = 3, d2 = 2;

		return -((A1 / (1 + pow(((x - a1) / b1), 2) + pow(((y - c1) / d1), 2))) + (A2 / (1 + pow(((x - a2) / b2), 2) + pow(((y - c2) / d2), 2))));
		//return pow(x, 2) + pow(y, 2);
	}
	static double Penalty_F(double x, double y, double _r)
	{
		//return (1 - x - y <= 0) ? (-_r / (1 - x - y)) : DBL_MAX;
		return (x + y - 1 <= 0) ? (-_r / (x + y - 1)) : DBL_MAX;
		//return (x + y - 1 <= 0) ? (-_r*log(-(x + y - 1))) : DBL_MAX;
	}
	double F(double x, double y, double _r)
	{
		double f_x = Function(x, y),
			p_x = Penalty_F(x, y, _r);
		return f_x + p_x;
	}
	Point DoAlgorithm()
	{
		Point _xk = x_0;
		do
		{		
			_xk = find_min_Gauss(_xk, _EPS, _EPS1);
			_r /= _C;
			//_r = pow(_r, 5)/2;
			countIter++;
		} while (abs(Penalty_F(_xk.x, _xk.y, _r)) > _EPS);
		return _xk;
	}
	Point find_min_Gauss(Point x0, double EPS, double EPS1)
	{
		Point _xk, _xk_1;
		double DELTA = 0.5;
		_xk = x0;
		do
		{
			_xk_1 = _xk;
		
			GetFunction = bind(F_2, _xk.x, placeholders::_1, _r);
			pair<double, double> interval_y = search_interval(_xk.y);
			_xk.y = Fibbonachi(interval_y, EPS);

			GetFunction = bind(F_2, placeholders::_1, _xk.y, _r);
			pair<double, double> interval_x = search_interval(_xk.x);
			_xk.x = Fibbonachi(interval_x, EPS);
		} while (abs(_xk.x - _xk_1.x) > EPS1 || abs(_xk.y - _xk_1.y) > EPS1
			&& abs(F(_xk.x, _xk.y, _r) - F(_xk_1.x, _xk_1.y, _r)) > EPS);
		return _xk;
	}
	function<double(double)>GetFunction;
	pair<double, double> search_interval(double x0)
	{	
		pair<double, double> res;
		double DELTA = 0.5;
		double h, x1, x2;
		double f1 = GetFunction(x0);
		double f2 = GetFunction(x0 + DELTA);
		double f3 = GetFunction(x0 - DELTA);
		x1 = x0;
		if (f1 > f2)
		{
			h = DELTA;
		}
		else
			if (f1 > f3)
			{
				h = -DELTA;
			}
			else
			{
				res.first = x0 - DELTA;
				res.second = x0 + DELTA;
				return res;
			}
		x2 = x1 + h;
		while (GetFunction(x1) > GetFunction(x2))
		{
			h *= 2;
			x0 = x1;
			x1 = x2;
			x2 = x1 + h;
		}
		if (x0 > x2)
		{
			res.first = x2;
			res.second = x0;
		}
		else
		{
			res.first = x0;
			res.second = x2;
		}
		return res;
	}


	double Fibbonachi(pair<double, double> interval, double EPS)
	{
		pair<double, double> s = interval;
		double f1, f2;
		double fib_max = (s.second - s.first) / EPS;
		long long int add_fib = 0;
		vector<long long int> fibs;
		fibs.push_back(1);
		fibs.push_back(1);
		int n = 2;
		while (fib_max > add_fib)
		{
			add_fib = fibs[n - 1] + fibs[n - 2];
			fibs.push_back(add_fib); 
			n++;
		}
		n = fibs.size() - 3;

		double x1 = s.first + ((float)fibs[n] / (float)fibs[n + 2]) * (s.second - s.first);
		double x2 = s.first + s.second - x1;
		f1 = GetFunction(x1);
		f2 = GetFunction(x2);

		for (int k = 1; k < n; k++)
		{
			if (f1 < f2)
			{
				s.second = x2;
				x2 = x1;
				f2 = f1;
				x1 = s.first + ((float)fibs[n - k+1] / (float)fibs[n - k + 3]) * (s.second - s.first);
				f1 = GetFunction(x1);
			}
			else
			{
				s.first = x1;
				x1 = x2;
				f1 = f2;
				x2 = s.first + ((float)fibs[n - k + 2] / (float)fibs[n - k + 3])*(s.second - s.first);
				f2 = GetFunction(x2);
			}
		}
		return (s.first + s.second) / 2;
	}

	void Read(string path)
	{
		ifstream read(path, ios_base::in);
		
		read >> x_0.x >> x_0.y >> _r >> _C >> _EPS >> _EPS1;
		read.close();


	}

};

double F_2(double x, double y, double _r)
{

	double f_x = Barrier_func::Function(x, y),
		p_x = Barrier_func::Penalty_F(x, y, _r);
	return f_x + p_x;
}