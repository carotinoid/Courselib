#include <iostream>

using namespace std;

int main()
{
	const int year = 2024;
	char name[100];
	int birth, stu_id;
	cin >> name;
	cin >> birth >> stu_id;
	cout << "My name is " << name << endl;
	cout << "I am " << year - birth + 1 << " years old." << endl;
	cout << "My student ID is " << stu_id;
}