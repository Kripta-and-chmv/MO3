#include "Penalty.h"
#include <conio.h>
void main()
{
	string path = "input.txt";
	Point result;
	Penalty_func A;
	A.Read(path);
	double k;
	result = A.DoAlgorithm();

	cout << result.x << "  " << result.y << "\n"<<A.Function(result.x, result.y);
	_getch();
}