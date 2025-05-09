#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	// 변수선언
	double x0, x, h;

	// 입력
	cin >> x0 >> x >> h;

	// 유효숫자 설정
	cout << setprecision(5);

	// 출력
	cout << "Exact answer is " << x * x << endl;
	double fpx0 = ((x0 + h)*(x0 + h) - (x0 * x0)) / h; // 계산 중간과정
	cout << "Approximateanswer is " << (x0 * x0) + fpx0 * (x - x0);
}