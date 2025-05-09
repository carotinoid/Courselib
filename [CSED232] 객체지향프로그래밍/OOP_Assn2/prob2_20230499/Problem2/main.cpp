#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	cout.precision(5); // ��ȿ���� ����
	cout << "Enter a cyphertext\n"; // Enter a cypher text
	int totalc = 0, noisec = 0; // totalc : ��ü ���ڼ�, noisec : ������ ���ڼ�
	string encode; // �Է� �ӿ��� ã�Ƴ� 16���� ��(�ص����� ���� ��ȣ��)
	while (true)
	{
		string input; //�� �� �Է� �ޱ� ���� string
		bool stop = false; // .. �Է½� true -> break������ �ݺ��� Ż��.
		getline(cin, input); // �� �� �Է� ����
		for (int i = 0; i <= input.length() - 1; i++) // string Ÿ�� ���� input�� �� ���ھ� ��ȸ. (���๮�� ����)
		{
			totalc++; // ��ü���ڼ� ����.
			if (input[i] == '#' or input[i] == '$' or input[i] == '%' or input[i] == '&' or input[i] == '*') noisec++; // ������ ���� üũ
			if ('0' <= input[i] && input[i] <= '9' || 'A' <= input[i] && input[i] <= 'F') encode += input[i]; // 16���� �� üũ
			if (i - 1 >= 0 && input[i] == '.' && input[i - 1] == '.') stop = true; // ���� ���� üũ
		}
		if (stop) break; // .. �Է½� ����
		totalc++; // ��ȸ���� ���� ���๮�� ���ڼ� ����.
	}
	cout << "Ciphertext noise rate: " << double(noisec) / totalc * 100 << "%\n"; // ������ ���� ���.
	if (encode == "") cout << "Undecryptable: where are the hexadecimal digits!\n"; // ã�� 16���� ���� ���ٸ� �����ڵ� ���
	else cout << "Hexadecimal digits: " << encode << "\n"; // �ص����� ���� ��ȣ�� ���
	string decode; // ����� ���� ���� 
	bool asciicheck = false; //�ƽ�Ű �ڵ� �� ���� �ִ��� Ȯ��
	if (encode == "");
	else if (encode.length() % 2 != 0) cout << "Undecryptable: the number of hexadecimal digits is odd!\n"; // Ȧ������� ����
	else
	{
		for (int i = 0; i < encode.length(); i += 2) // �� ���ھ� ��ȸ�ϸ鼭 �ƽ�Ű �ڵ�� ��ȯ.
		{
			int hex = 0;
			if ('0' <= encode[i] && encode[i] <= '9') hex += 16 * int(encode[i] - '0');
			else hex += 16 * (int(encode[i] - 'A') + 10);
			if ('0' <= encode[i + 1] && encode[i + 1] <= '9') hex += int(encode[i + 1] - '0');
			else hex += (int(encode[i + 1] - 'A') + 10);
			if (!(0 <= hex && hex < 128)) asciicheck = true;
			else decode += char(hex);
		}
		if (asciicheck) cout << "Undecryptable: invalid hexadecimal digits pair!\n"; // �ƽ�Ű �ڵ尡 �ƴ϶�� ����
		else cout << "Decryption result: " << decode << "\n"; // ������ ���ٸ� ������
	}
	cout << "Decryptor turn off!";
}
