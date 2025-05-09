#include <iostream>

using namespace std;

int main()
{
	// 변수 선언
	const int year = 2024;
	char name[200];
	int birth, stu_id;

	// 입력
	cin.getline(name, sizeof(name)); // 변수명에 공백(space) 포함하여 한줄을 받음.
	cin >> birth >> stu_id;

	// 출력
	cout << "My name is " << name << endl;
	cout << "I am " << year - birth + 1 << " years old." << endl;
	cout << "My student ID is " << stu_id;
}