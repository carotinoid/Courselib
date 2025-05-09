#include <iostream>
#include <iomanip>

using namespace std;

struct student // student 구조체 선언
{
	int id;
	char name[20];
	int midterm_exam_score;
	int final_exam_score;
	bool retake;
};

int main()
{
	cout.precision(5); // 유효숫자 설정
	student stu_list[105]; // 구조체 리스트 선언(학생수 입력 : 최대 100), numofstu가 사용되는 리스트의 크기로 사용됨.
	int numofstu = 0; // 현재 추가된 학생 수.
	int selection = 0; // 번호 선택 입력용 변수
	while (true)
	{
		selection = 0;
		//-----------menu------------; 초기화면
		cout << "----------MENU----------\n";
		cout << "1. Add a student\n";
		cout << "2. Edit the score of a student\n";
		cout << "3. Print average score\n";
		cout << "4. Print scores list\n";
		cout << "5. Print grades list\n";
		cout << "6. Exit\n";
		cout << "------------------------\n";
		cout << "Selection: ";
		cin >> selection; // 번호 입력
		if(selection == 1) // add a student.
		{
			long long id, midterm_exam_score, final_exam_score, retake;
			char name[30]; // 추가용 변수 선언
			cout << "Student id: ";
			cin >> id; // 학번 입력후 검사, 잘못된 형식일 경우 에러 로그 출력 후 메뉴로 돌아감
			if (!(id >= 10000000 and id < 100000000))
			{	
				cout << "Failed to add : invalid student id!\n";
				continue;
			}
			cout << "Name: ";
			cin >> name; // 이름 입력후 검사, 잘못된 형식일 경우 에러 로그 출력 후 메뉴로 돌아감
			int err = false;
			for (int i = 0; i < strlen(name); i++)
				if (!('A' <= name[i] && name[i] <= 'Z' || 'a' <= name[i] && name[i] <= 'z')) err = true;

			if (strlen(name) > 10 || err) 
			{
				cout << "Failed to add : invalid name!\n";
				continue;
			}
			cout << "Midterm exam score: ";
			cin >> midterm_exam_score; // 중간고사 점수 입력후 검사, 잘못된 형식일 경우 에러 로그 출력 후 메뉴로 돌아감
			if (midterm_exam_score > 100 || midterm_exam_score < 0)
			{
				cout << "Failed to add: invalid midterm exam score!\n";
				continue;
			}
			cout << "Final exam score: ";
			cin >> final_exam_score; // 기말고사 점수 입력후 검사, 잘못된 형식일 경우 에러 로그 출력 후 메뉴로 돌아감
			if (final_exam_score > 100 || final_exam_score < 0)
			{
				cout << "Failed to add: invalid final exam score!\n";
				continue;
			}
			cout << "Retake: ";
			cin >> retake; // 재수강 여부 입력후 검사, 잘못된 형식일 경우 에러 로그 출력 후 메뉴로 돌아감
			if (!(retake == 0 || retake == 1))
			{
				cout << "Failed to add: invalid retake value!\n";
				continue;
			} 
			// 모든 입력이 유효할 경우, 학생 구조체 리스트에 넣고 numofstu 증가.
			stu_list[numofstu].id = id;
			strcpy_s(stu_list[numofstu].name, name); // <iostream>
			stu_list[numofstu].midterm_exam_score = midterm_exam_score;
			stu_list[numofstu].final_exam_score = final_exam_score;
			stu_list[numofstu].retake = retake;
			numofstu++;
			cout << "The student is added!\n";
		}
		else if (selection == 2) // 학생 점수 수정
		{
			cout << "--------Function--------\n";
			cout << "1. Edit the midterm exam score\n";
			cout << "2. Edit the final exam score\n";
			cout << "------------------------\n";
			int select, score, stu_id; 
			cout << "Selection: ";
			cin >> select; // select 입력, 1 : 중간고사, 2 : 기말고사 점수 수정.
			if (!(select == 1 || select == 2))
			{
				cout << "Invalid selection!\n";
				continue;
			}
			cout << "Student id: ";
			cin >> stu_id;
			if (!(stu_id >= 10000000 and stu_id < 100000000)) 
			{ // 학번 입력후 검사, 잘못된 형식일 경우 에러 로그 출력 후 메뉴로 돌아감
				cout << "Failed to edit : invalid student id!\n";
				continue;
			}
			bool thereisid = false;
			int findidx = 0;
			// 입력된 학번이 있는지 확인. 
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
			// 입력된 Id가 없을 경우, 에러 로그 출력 후 메뉴로 돌아감
			if (!thereisid)
			{
				cout << "Can't find the student id: " << stu_id << "\n";
				continue;
			}
			cout << "Score: ";
			cin >> score; // 수정하고자 하는 점수 입력
			// 점수가 잘못된 형식일 경우 에러 로그 출력 후 메뉴로 돌아감
			if (score > 100 || score < 0)
			{
				cout << "Failed to edit: invalid exam score!\n";
				continue;
			}
			// 수정된 점수 반영 후 종료
			if (select == 1) stu_list[findidx].midterm_exam_score = score;
			if (select == 2) stu_list[findidx].final_exam_score = score;
			cout << "Score editing done!\n";
		}
		else if (selection == 3) // 평균점수 및 표준편차 출력.
		{
			int sum = 0;
			double mean = 0, standard = 0, sqaurediffmean = 0;
			if(numofstu != 0)
			{ // 평균, 표준편차 계산
				for (int i = 0; i < numofstu; i++) sum += (stu_list[i].midterm_exam_score + stu_list[i].final_exam_score);
				mean = double(sum) / numofstu;
				for (int i = 0; i < numofstu; i++)
					sqaurediffmean += (double(stu_list[i].midterm_exam_score + stu_list[i].final_exam_score) - mean)
					* (double(stu_list[i].midterm_exam_score + stu_list[i].final_exam_score) - mean);
				standard = sqrt(sqaurediffmean / numofstu);
			}
			// 평균, 표준편차 출력
			cout << "Average score: " << mean << "\n";
			cout << "Standard deviation: " << double(standard) << "\n";
			
		}
		else if (selection == 4) // 학생 점수 리스트 출력.
		{
			for(int i = 0; i < numofstu; i++) // Bubble sort 알고리즘. 정렬기준 : 중간, 기말 점수 총합 내림차순, 점수가 같다면 학번 오름차순
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
			for (int i = 0; i < numofstu; i++) // 정렬된 학생 점수 리스트 출력
				cout << stu_list[i].id << " " << stu_list[i].name << " " << stu_list[i].midterm_exam_score << " " << stu_list[i].final_exam_score << " " << stu_list[i].midterm_exam_score + stu_list[i].final_exam_score << "\n";
			cout << "Finished printing the list!\n";
		}
		else if (selection == 5) // 학생 등급 리스트 출력.
		{
			for (int i = 0; i < numofstu; i++) // Bubble sort 알고리즘. 정렬기준 : 중간, 기말 점수 총합 내림차순, 점수가 같다면 학번 오름차순
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
			int grade = 0; // 등급. 1:A, 2:B, 3:C, otherwise:D.
			for (int i = 0; i < numofstu; i++)
			{
				student now = stu_list[i];
				if (now.midterm_exam_score + now.final_exam_score > 150			// 총 점수 150 이상,
					&& (double(i+1) / numofstu <= 0.3					// 상위 30% 이내,
					|| (double(numofstu) * 0.3 < 1 && numofstu - i == 1)))		// (사람이 적을 경우)
					grade = 1;													// A등급
				else if (now.midterm_exam_score + now.final_exam_score > 100	// 총 점수 100 이상,
					&& (double(i+1) / numofstu <= 0.7					// 상위 70% 이내,
					|| (double(numofstu) * 0.7 < 2 && numofstu - i == 2)))		// (사람이 적을 경우)
					grade = 2;													// B등급
				else if (now.midterm_exam_score + now.final_exam_score > 50		// 총 점수 50 이상,
					&& (double(i+1) / numofstu < 0.9					// 하위 10% 이내에 들지 않을 경우
					|| (double(numofstu) * 0.9 < 3 && numofstu - i == 3)))		// (사람이 적을 경우)
					grade = 3;													// C 등급.
				else grade = 4;													// 그 이외는 D 등급.
				if (now.retake) grade++;										// 재수강시 한 등급 내리기.
				cout << now.id << " " << now.name << " " << now.midterm_exam_score + now.final_exam_score << " " << int(now.retake) << " ";
				if (grade == 1) cout << "A\n"; // 출력
				else if (grade == 2) cout << "B\n";
				else if (grade == 3) cout << "C\n";
				else cout << "D\n";

			}
			cout << "Finished printing the list!\n";
		}
		else if (selection == 6) // 프로그램 종료
		{
			cout << "Good Bye!\n";
			exit(0);
		}
	}
}