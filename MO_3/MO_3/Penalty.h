
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iomanip>  
using namespace std;
struct Point
{
	double x;
	double y;
	Point(double x, double y) : x(x), y(y) {};
	Point() {};

};
double F_1(double x, double y, double _r);

class Penalty_func
{
private:
	double _EPS, _EPS1, _r, _C;
	Point x_0;

public:
	int countIter = 0;
	static int countCalc;

	static double Function(double x, double y)
	{
		int A1 = 1, A2 = 3;
		int a1 = 2, a2 = 1;
		int b1 = 3, b2 = 1;
		int c1 = 2, c2 = 1;
		int d1 = 3, d2 = 2;
		countCalc++;
		return -((A1 / (1 + pow(((x - a1) / b1), 2) + pow(((y - c1) / d1), 2))) + (A2 / (1 + pow(((x - a2) / b2), 2) + pow(((y - c2) / d2), 2))));
	}
	static double Penalty_F(double x, double y, double _r)
	{
		return (_r /2)*pow(max(0, (x + y - 1)),2);
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
			_r *= _C;
			countIter++;
		} while (Penalty_F(_xk.x, _xk.y, _r) > _EPS);
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
			GetFunction = bind(F_1, placeholders::_1, _xk.y, _r);
			pair<double, double> interval_x = search_interval(_xk.y);
			_xk.x = Dihotomy(interval_x, EPS);
			GetFunction = bind(F_1, _xk.x, placeholders::_1, _r);
			pair<double, double> interval_y = search_interval(_xk.x);
			_xk.y = Dihotomy(interval_y, EPS);
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


	double Dihotomy(pair<double, double> interval, double EPS)
	{
		double x1, x2;
		double DELTA = EPS / 2.0;
		double a = interval.first, b = interval.second;
		int iter = 0;
		while (abs(b - a) > EPS)
		{

			x1 = (a + b - DELTA) / 2;
			x2 = (a + b + DELTA) / 2;
			if (GetFunction(x1) < GetFunction(x2))
			{
				b = x2;
			}
			else
			{
				a = x1;
			}
			iter++;
		}
		return (a + b) / 2.0;
	}
	void Read(string path)
	{
		ifstream read(path, ios_base::in);
		countCalc = 0;
		read >> x_0.x >> x_0.y >> _r >> _C >> _EPS >> _EPS1;
		read.close();
	}

};
int Penalty_func::countCalc = 0;
double F_1(double x, double y, double _r)
{

	double f_x = Penalty_func::Function(x, y),
		p_x = Penalty_func::Penalty_F(x, y, _r);
	return f_x + p_x;
}