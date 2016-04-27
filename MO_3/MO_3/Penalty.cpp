////#include "Penalty.h"
#include "barrier.h"
#include <conio.h>


void main()
{
	string path = "input.txt";
	Point result;
	//Penalty_func A;
	barrier A;
	A.Read(path);
	double k;
	result = A.DoAlgorithm();

	cout << result.x << "  " << result.y << "\n"<<A.Function(result.x, result.y)<<" "<<A.countIter<<" "<<A.countCalc;
	_getch();
}
