#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double x0, x, h;
	cin >> x0 >> x >> h;
	double asdf = 3.1415926535, fdsa = 0.0000000152;
	cout << setprecision(5); // << scientific; 
	cout << "Exact answer is " << x * x << endl;
	double fpx0 = ((x0 + h)*(x0 + h) - (x0 * x0)) / h;
	cout << "Approximateanswer is " << (x0 * x0) + fpx0 * (x - x0);
}