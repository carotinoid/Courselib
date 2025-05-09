#include <iostream>

using namespace std;

int main()
{
	// 변수선언
	char A[5], B[5];
	int arr[4];

	// 입력
	cin >> A >> B;

	//출력 1 (교차된 이니셜).
	cout << A[0] << " " << B[0] << " " << A[1] << " " << B[1] << endl;

	// 아스키코드로 변환 후 일의 자리만 가져오기
	arr[0] = int(A[0]) % 10;
	arr[2] = int(A[1]) % 10;
	arr[1] = int(B[0]) % 10;
	arr[3] = int(B[1]) % 10;

	// 출력 2 (아스키코드 일의자리)
	cout << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << endl;

	// 출력 3 (이웃한 값을 더한 후 일의 자리만 가져오기
	cout << (arr[0] + arr[1]) % 10 << " " << (arr[1] + arr[2]) % 10 << " " << (arr[2] + arr[3]) % 10 << endl;

	// 단계를 반복하여 최종 값 계산
	int tendigit = (arr[0] + 2 * arr[1] + arr[2]) % 10, onedigit = (arr[1] + 2 * arr[2] + arr[3]) % 10;

	// 출력 4. 최종 숫자 출력
	cout << tendigit << " " << onedigit<< endl;

	// 궁합을 두자리 정수로 변환
	int chem = tendigit * 10 + onedigit;

	// 99를 더하고 mod 100 연산을 취한 후, 1을 더함으로써 00 -> 100점으로 변환함.
	chem = (chem + 99) % 100 + 1; 

	// 출력 5. 최종 궁합을 출력.
	cout << "The Chemistry between " << A << " and " << B << " is " << chem << "%";
}