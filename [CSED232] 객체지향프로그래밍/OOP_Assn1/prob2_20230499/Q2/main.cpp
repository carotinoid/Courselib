#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	// ��������
	double x0, x, h;

	// �Է�
	cin >> x0 >> x >> h;

	// ��ȿ���� ����
	cout << setprecision(5);

	// ���
	cout << "Exact answer is " << x * x << endl;
	double fpx0 = ((x0 + h)*(x0 + h) - (x0 * x0)) / h; // ��� �߰�����
	cout << "Approximateanswer is " << (x0 * x0) + fpx0 * (x - x0);
}