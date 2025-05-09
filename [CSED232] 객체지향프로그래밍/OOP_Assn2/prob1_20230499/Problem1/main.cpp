#include <iostream>
#include <iomanip>

using namespace std;

struct student // student ����ü ����
{
	int id;
	char name[20];
	int midterm_exam_score;
	int final_exam_score;
	bool retake;
};

int main()
{
	cout.precision(5); // ��ȿ���� ����
	student stu_list[105]; // ����ü ����Ʈ ����(�л��� �Է� : �ִ� 100), numofstu�� ���Ǵ� ����Ʈ�� ũ��� ����.
	int numofstu = 0; // ���� �߰��� �л� ��.
	int selection = 0; // ��ȣ ���� �Է¿� ����
	while (true)
	{
		selection = 0;
		//-----------menu------------; �ʱ�ȭ��
		cout << "----------MENU----------\n";
		cout << "1. Add a student\n";
		cout << "2. Edit the score of a student\n";
		cout << "3. Print average score\n";
		cout << "4. Print scores list\n";
		cout << "5. Print grades list\n";
		cout << "6. Exit\n";
		cout << "------------------------\n";
		cout << "Selection: ";
		cin >> selection; // ��ȣ �Է�
		if(selection == 1) // add a student.
		{
			long long id, midterm_exam_score, final_exam_score, retake;
			char name[30]; // �߰��� ���� ����
			cout << "Student id: ";
			cin >> id; // �й� �Է��� �˻�, �߸��� ������ ��� ���� �α� ��� �� �޴��� ���ư�
			if (!(id >= 10000000 and id < 100000000))
			{	
				cout << "Failed to add : invalid student id!\n";
				continue;
			}
			cout << "Name: ";
			cin >> name; // �̸� �Է��� �˻�, �߸��� ������ ��� ���� �α� ��� �� �޴��� ���ư�
			int err = false;
			for (int i = 0; i < strlen(name); i++)
				if (!('A' <= name[i] && name[i] <= 'Z' || 'a' <= name[i] && name[i] <= 'z')) err = true;

			if (strlen(name) > 10 || err) 
			{
				cout << "Failed to add : invalid name!\n";
				continue;
			}
			cout << "Midterm exam score: ";
			cin >> midterm_exam_score; // �߰���� ���� �Է��� �˻�, �߸��� ������ ��� ���� �α� ��� �� �޴��� ���ư�
			if (midterm_exam_score > 100 || midterm_exam_score < 0)
			{
				cout << "Failed to add: invalid midterm exam score!\n";
				continue;
			}
			cout << "Final exam score: ";
			cin >> final_exam_score; // �⸻��� ���� �Է��� �˻�, �߸��� ������ ��� ���� �α� ��� �� �޴��� ���ư�
			if (final_exam_score > 100 || final_exam_score < 0)
			{
				cout << "Failed to add: invalid final exam score!\n";
				continue;
			}
			cout << "Retake: ";
			cin >> retake; // ����� ���� �Է��� �˻�, �߸��� ������ ��� ���� �α� ��� �� �޴��� ���ư�
			if (!(retake == 0 || retake == 1))
			{
				cout << "Failed to add: invalid retake value!\n";
				continue;
			} 
			// ��� �Է��� ��ȿ�� ���, �л� ����ü ����Ʈ�� �ְ� numofstu ����.
			stu_list[numofstu].id = id;
			strcpy_s(stu_list[numofstu].name, name); // <iostream>
			stu_list[numofstu].midterm_exam_score = midterm_exam_score;
			stu_list[numofstu].final_exam_score = final_exam_score;
			stu_list[numofstu].retake = retake;
			numofstu++;
			cout << "The student is added!\n";
		}
		else if (selection == 2) // �л� ���� ����
		{
			cout << "--------Function--------\n";
			cout << "1. Edit the midterm exam score\n";
			cout << "2. Edit the final exam score\n";
			cout << "------------------------\n";
			int select, score, stu_id; 
			cout << "Selection: ";
			cin >> select; // select �Է�, 1 : �߰����, 2 : �⸻��� ���� ����.
			if (!(select == 1 || select == 2))
			{
				cout << "Invalid selection!\n";
				continue;
			}
			cout << "Student id: ";
			cin >> stu_id;
			if (!(stu_id >= 10000000 and stu_id < 100000000)) 
			{ // �й� �Է��� �˻�, �߸��� ������ ��� ���� �α� ��� �� �޴��� ���ư�
				cout << "Failed to edit : invalid student id!\n";
				continue;
			}
			bool thereisid = false;
			int findidx = 0;
			// �Էµ� �й��� �ִ��� Ȯ��. 
			if (numofstu != 0)
			{
				for (; findidx < numofstu; findidx++)
				{
					if (stu_id == stu_list[findidx].id)
					{
						thereisid = true;
						break;
					}
				}
			}
			// �Էµ� Id�� ���� ���, ���� �α� ��� �� �޴��� ���ư�
			if (!thereisid)
			{
				cout << "Can't find the student id: " << stu_id << "\n";
				continue;
			}
			cout << "Score: ";
			cin >> score; // �����ϰ��� �ϴ� ���� �Է�
			// ������ �߸��� ������ ��� ���� �α� ��� �� �޴��� ���ư�
			if (score > 100 || score < 0)
			{
				cout << "Failed to edit: invalid exam score!\n";
				continue;
			}
			// ������ ���� �ݿ� �� ����
			if (select == 1) stu_list[findidx].midterm_exam_score = score;
			if (select == 2) stu_list[findidx].final_exam_score = score;
			cout << "Score editing done!\n";
		}
		else if (selection == 3) // ������� �� ǥ������ ���.
		{
			int sum = 0;
			double mean = 0, standard = 0, sqaurediffmean = 0;
			if(numofstu != 0)
			{ // ���, ǥ������ ���
				for (int i = 0; i < numofstu; i++) sum += (stu_list[i].midterm_exam_score + stu_list[i].final_exam_score);
				mean = double(sum) / numofstu;
				for (int i = 0; i < numofstu; i++)
					sqaurediffmean += (double(stu_list[i].midterm_exam_score + stu_list[i].final_exam_score) - mean)
					* (double(stu_list[i].midterm_exam_score + stu_list[i].final_exam_score) - mean);
				standard = sqrt(sqaurediffmean / numofstu);
			}
			// ���, ǥ������ ���
			cout << "Average score: " << mean << "\n";
			cout << "Standard deviation: " << double(standard) << "\n";
			
		}
		else if (selection == 4) // �л� ���� ����Ʈ ���.
		{
			for(int i = 0; i < numofstu; i++) // Bubble sort �˰���. ���ı��� : �߰�, �⸻ ���� ���� ��������, ������ ���ٸ� �й� ��������
				for (int j = 0; j < numofstu - i - 1; j++)
				{
					int pre = stu_list[j].midterm_exam_score + stu_list[j].final_exam_score;
					int next = stu_list[j + 1].midterm_exam_score + stu_list[j + 1].final_exam_score;
					if (pre < next)
					{
						student tmp = stu_list[j];
						stu_list[j] = stu_list[j + 1];
						stu_list[j + 1] = tmp;
					}
					else if(pre == next && stu_list[i].id > stu_list[i+1].id)
					{
						student tmp = stu_list[j];
						stu_list[j] = stu_list[j + 1];
						stu_list[j + 1] = tmp;
					}
				}
			for (int i = 0; i < numofstu; i++) // ���ĵ� �л� ���� ����Ʈ ���
				cout << stu_list[i].id << " " << stu_list[i].name << " " << stu_list[i].midterm_exam_score << " " << stu_list[i].final_exam_score << " " << stu_list[i].midterm_exam_score + stu_list[i].final_exam_score << "\n";
			cout << "Finished printing the list!\n";
		}
		else if (selection == 5) // �л� ��� ����Ʈ ���.
		{
			for (int i = 0; i < numofstu; i++) // Bubble sort �˰���. ���ı��� : �߰�, �⸻ ���� ���� ��������, ������ ���ٸ� �й� ��������
				for (int j = 0; j < numofstu - i - 1; j++)
				{
					int pre = stu_list[j].midterm_exam_score + stu_list[j].final_exam_score;
					int next = stu_list[j + 1].midterm_exam_score + stu_list[j + 1].final_exam_score;
					if (pre < next)
					{
						student tmp = stu_list[j];
						stu_list[j] = stu_list[j + 1];
						stu_list[j + 1] = tmp;
					}
					else if (pre == next && stu_list[i].id > stu_list[i + 1].id)
					{
						student tmp = stu_list[j];
						stu_list[j] = stu_list[j + 1];
						stu_list[j + 1] = tmp;
					}
				}
			int grade = 0; // ���. 1:A, 2:B, 3:C, otherwise:D.
			for (int i = 0; i < numofstu; i++)
			{
				student now = stu_list[i];
				if (now.midterm_exam_score + now.final_exam_score > 150			// �� ���� 150 �̻�,
					&& (double(i+1) / numofstu <= 0.3					// ���� 30% �̳�,
					|| (double(numofstu) * 0.3 < 1 && numofstu - i == 1)))		// (����� ���� ���)
					grade = 1;													// A���
				else if (now.midterm_exam_score + now.final_exam_score > 100	// �� ���� 100 �̻�,
					&& (double(i+1) / numofstu <= 0.7					// ���� 70% �̳�,
					|| (double(numofstu) * 0.7 < 2 && numofstu - i == 2)))		// (����� ���� ���)
					grade = 2;													// B���
				else if (now.midterm_exam_score + now.final_exam_score > 50		// �� ���� 50 �̻�,
					&& (double(i+1) / numofstu < 0.9					// ���� 10% �̳��� ���� ���� ���
					|| (double(numofstu) * 0.9 < 3 && numofstu - i == 3)))		// (����� ���� ���)
					grade = 3;													// C ���.
				else grade = 4;													// �� �ܴ̿� D ���.
				if (now.retake) grade++;										// ������� �� ��� ������.
				cout << now.id << " " << now.name << " " << now.midterm_exam_score + now.final_exam_score << " " << int(now.retake) << " ";
				if (grade == 1) cout << "A\n"; // ���
				else if (grade == 2) cout << "B\n";
				else if (grade == 3) cout << "C\n";
				else cout << "D\n";

			}
			cout << "Finished printing the list!\n";
		}
		else if (selection == 6) // ���α׷� ����
		{
			cout << "Good Bye!\n";
			exit(0);
		}
	}
}