#include <iostream>

using namespace std;

int main()
{
	// ���� ����
	const int year = 2024;
	char name[200];
	int birth, stu_id;

	// �Է�
	cin.getline(name, sizeof(name)); // ������ ����(space) �����Ͽ� ������ ����.
	cin >> birth >> stu_id;

	// ���
	cout << "My name is " << name << endl;
	cout << "I am " << year - birth + 1 << " years old." << endl;
	cout << "My student ID is " << stu_id;
}