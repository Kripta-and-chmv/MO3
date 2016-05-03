#include "Penalty.h"
#include <conio.h>
#include "barrier.h"
#include <iomanip>  
void main()
{
	string path = "input.txt", path2 = "input2.txt";
	PointP result1;
	Point result2;
	Penalty_func A;
	Barrier_func B;
	A.Read(path);
	B.Read(path2);
	result1 = A.DoAlgorithm();
	result2 = B.DoAlgorithm();
	cout << "Penalty:";
	cout << setprecision(16)<<result1.x << "  " << result1.y << "\n" << A.Function(result1.x, result1.y) << " " << A.countIter << endl;
	cout << "Barrier:";
	cout << setprecision(16) << result2.x << "  " << result2.y << "\n" << B.Function(result2.x, result2.y) << " " << B.countIter << endl;
	_getch();
}
