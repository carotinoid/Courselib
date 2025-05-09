#include <iostream>

using namespace std;

int main()
{
	char A[5], B[5];
	int arr[4];
	cin >> A >> B;
	cout << A[0] << " " << B[0] << " " << A[1] << " " << B[1] << endl;
	arr[0] = int(A[0]) % 10;
	arr[2] = int(A[1]) % 10;
	arr[1] = int(B[0]) % 10;
	arr[3] = int(B[1]) % 10;
	cout << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << endl;
	cout << (arr[0] + arr[1]) % 10 << " " << (arr[1] + arr[2]) % 10 << " " << (arr[2] + arr[3]) % 10<< endl;
	int tendigit = (arr[0] + 2 * arr[1] + arr[2]) % 10, onedigit = (arr[1] + 2 * arr[2] + arr[3]) % 10;
	cout << tendigit << " " << onedigit<< endl;
	int chem = tendigit * 10 + onedigit;
	chem = (chem + 99) % 100 + 1; // for making 00 to 100
	cout << "The Chemistry between " << A << " and " << B << " is " << chem << "%";
}