#include <iostream>

using namespace std;

int main()
{
	// ��������
	char A[5], B[5];
	int arr[4];

	// �Է�
	cin >> A >> B;

	//��� 1 (������ �̴ϼ�).
	cout << A[0] << " " << B[0] << " " << A[1] << " " << B[1] << endl;

	// �ƽ�Ű�ڵ�� ��ȯ �� ���� �ڸ��� ��������
	arr[0] = int(A[0]) % 10;
	arr[2] = int(A[1]) % 10;
	arr[1] = int(B[0]) % 10;
	arr[3] = int(B[1]) % 10;

	// ��� 2 (�ƽ�Ű�ڵ� �����ڸ�)
	cout << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << endl;

	// ��� 3 (�̿��� ���� ���� �� ���� �ڸ��� ��������
	cout << (arr[0] + arr[1]) % 10 << " " << (arr[1] + arr[2]) % 10 << " " << (arr[2] + arr[3]) % 10 << endl;

	// �ܰ踦 �ݺ��Ͽ� ���� �� ���
	int tendigit = (arr[0] + 2 * arr[1] + arr[2]) % 10, onedigit = (arr[1] + 2 * arr[2] + arr[3]) % 10;

	// ��� 4. ���� ���� ���
	cout << tendigit << " " << onedigit<< endl;

	// ������ ���ڸ� ������ ��ȯ
	int chem = tendigit * 10 + onedigit;

	// 99�� ���ϰ� mod 100 ������ ���� ��, 1�� �������ν� 00 -> 100������ ��ȯ��.
	chem = (chem + 99) % 100 + 1; 

	// ��� 5. ���� ������ ���.
	cout << "The Chemistry between " << A << " and " << B << " is " << chem << "%";
}