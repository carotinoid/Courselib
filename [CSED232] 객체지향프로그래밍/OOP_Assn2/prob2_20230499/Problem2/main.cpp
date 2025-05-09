#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	cout.precision(5); // 유효숫자 설정
	cout << "Enter a cyphertext\n"; // Enter a cypher text
	int totalc = 0, noisec = 0; // totalc : 전체 글자수, noisec : 노이즈 글자수
	string encode; // 입력 속에서 찾아낸 16진수 수(해독되지 않은 암호문)
	while (true)
	{
		string input; //한 줄 입력 받기 위한 string
		bool stop = false; // .. 입력시 true -> break문으로 반복문 탈출.
		getline(cin, input); // 한 줄 입력 받음
		for (int i = 0; i <= input.length() - 1; i++) // string 타입 변수 input의 각 글자씩 순회. (개행문자 제외)
		{
			totalc++; // 전체글자수 증가.
			if (input[i] == '#' or input[i] == '$' or input[i] == '%' or input[i] == '&' or input[i] == '*') noisec++; // 노이즈 글자 체크
			if ('0' <= input[i] && input[i] <= '9' || 'A' <= input[i] && input[i] <= 'F') encode += input[i]; // 16진수 수 체크
			if (i - 1 >= 0 && input[i] == '.' && input[i - 1] == '.') stop = true; // 종료 여부 체크
		}
		if (stop) break; // .. 입력시 종료
		totalc++; // 순회하지 않은 개행문자 글자수 포함.
	}
	cout << "Ciphertext noise rate: " << double(noisec) / totalc * 100 << "%\n"; // 노이즈 비율 출력.
	if (encode == "") cout << "Undecryptable: where are the hexadecimal digits!\n"; // 찾은 16진수 수가 없다면 에러코드 출력
	else cout << "Hexadecimal digits: " << encode << "\n"; // 해독되지 않은 암호문 출력
	string decode; // 결과를 담을 변수 
	bool asciicheck = false; //아스키 코드 내 수가 있는지 확인
	if (encode == "");
	else if (encode.length() % 2 != 0) cout << "Undecryptable: the number of hexadecimal digits is odd!\n"; // 홀수개라면 에러
	else
	{
		for (int i = 0; i < encode.length(); i += 2) // 두 글자씩 순회하면서 아스키 코드로 변환.
		{
			int hex = 0;
			if ('0' <= encode[i] && encode[i] <= '9') hex += 16 * int(encode[i] - '0');
			else hex += 16 * (int(encode[i] - 'A') + 10);
			if ('0' <= encode[i + 1] && encode[i + 1] <= '9') hex += int(encode[i + 1] - '0');
			else hex += (int(encode[i + 1] - 'A') + 10);
			if (!(0 <= hex && hex < 128)) asciicheck = true;
			else decode += char(hex);
		}
		if (asciicheck) cout << "Undecryptable: invalid hexadecimal digits pair!\n"; // 아스키 코드가 아니라면 에러
		else cout << "Decryption result: " << decode << "\n"; // 에러가 없다면 결과출력
	}
	cout << "Decryptor turn off!";
}
