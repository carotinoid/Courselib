# 20230499 KIMJaeHwan
# Programming ASSN #1
# terminal / cmd font : consolas (recommanded)

import os
import random
# from IPython.display import clear_output
# delete annotation if you run on jupyter notebook

def clear_screen():
    os.system('cls')   # add '#' if you notrun on windows
    # os.system('clear')  # delete annotation if you run on linux
    # clear_output()   # delete annotation if you run on jupyter notebook
    return

def wait_enter():
    # "a = " : enter 이외 입력이 들어왔을때 오류 발생을 방지함.
    a = input("\n계속하려면 엔터를 눌러주세요...")

def next():
    wait_enter()
    clear_screen()

def print_scissors():
    print("┌──────────────────────────────────────┐")
    print("│                         ▩ ▩          │")
    print("│         ▩ ▩         ▩ ▩ ▩ ▩ ▩        │")
    print("│     ▩ ▩ ▩ ▩ ▩     ▩ ▩ ▩ ▩ ▩ ▩ ▩      │")
    print("│   ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩        │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩              │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩                    │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩                │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩            │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩        │")
    print("│   ▩ ▩ ▩ ▩ ▩ ▩ ▩   ▩ ▩ ▩ ▩ ▩ ▩ ▩      │")
    print("│     ▩ ▩ ▩ ▩ ▩ ▩         ▩ ▩ ▩ ▩ ▩    │")
    print("│       ▩ ▩ ▩                 ▩ ▩      │")
    print("└──────────────────────────────────────┘")


def print_rock():
    print("┌──────────────────────────────────────┐")
    print("│                                      │")
    print("│       ▩ ▩ ▩ ▩ ▩                      │")
    print("│     ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩                │")
    print("│   ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩              │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩              │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩            │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩            │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩            │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩              │")
    print("│   ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩                │")
    print("│     ▩ ▩ ▩ ▩ ▩ ▩ ▩                    │")
    print("│                                      │")
    print("└──────────────────────────────────────┘")


def print_paper():
    print("┌──────────────────────────────────────┐")
    print("│                                      │")
    print("│       ▩ ▩ ▩ ▩ ▩                      │")
    print("│     ▩ ▩ ▩                            │")
    print("│   ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩        │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩                  │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩      │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩                  │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩        │")
    print("│ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩                  │")
    print("│   ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩ ▩            │")
    print("│     ▩ ▩ ▩ ▩ ▩                        │")
    print("│                                      │")
    print("└──────────────────────────────────────┘")

def print_choice_of(choice):
    if choice == "가위": print_scissors()
    if choice == "바위": print_rock()
    if choice == "보": print_paper()

def print_intro():
    print("======================")
    print("[묵찌빠 계단 오르기]")
    print("======================")
    print("○                   ●")
    print("▨                   ▨")
    print("▨ ▨               ▨ ▨")
    print("▨ ▨ ▨           ▨ ▨ ▨")
    print("▨ ▨ ▨ ▨       ▨ ▨ ▨ ▨")
    print("▨ ▨ ▨ ▨ ▨   ▨ ▨ ▨ ▨ ▨")
    print("▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨")

def input_stairs_number():
    n = 0
    while n < 10 or n > 30:
        n = int(input("게임을 위한 계단의 개수를 입력해주세요. <10 - 30> >> "))
    return n

def print_stairs(stairs_number, player, computer):
    print("총 계단 수:", stairs_number)
    print("PLAYER:   ○ <%2d>" % player)
    print("COMPUTER: ● <%2d>" % computer)    # 계단수, 현 점수 출력
    rows = (stairs_number + 1) // 2 + 1
    cols = stairs_number + 1
    stairs = [[" " for j in range(0, cols)] for i in range(0, rows)]     # 계단 출력을 위한 리스트 선언
    for i in range(1, rows):
        for j in range(0, i):
            stairs[i][j] = '▨'
        for j in range(stairs_number, stairs_number - i, -1):
            stairs[i][j] = '▨'                                         # 계단 그리기
    if player <= stairs_number // 2:
        stairs[player][player] = '○'
    else:
        stairs[rows - 1 - player + stairs_number//2][player] = '○'    # 플레이어 위치 찍기
    if computer <= stairs_number // 2:
        if stairs[computer][stairs_number - computer] == '○':
            stairs[computer][stairs_number - computer] = '◑'
        else:
            stairs[computer][stairs_number - computer] = '●'
    else:
        if stairs[rows - 1 - computer + stairs_number//2][stairs_number - computer] == '○':
            stairs[rows - 1 - computer + stairs_number//2][stairs_number - computer] = '◑'
        else:                                                                                 # 컴퓨터 위치 찍기
            stairs[rows - 1 - computer + stairs_number//2][stairs_number - computer] = '●'    # 플레이어 위치와 같은지 검사
    for i in range(rows):
        for j in range(cols):
            print(stairs[i][j], end = " ")
        print("")                              # 계단 그림 출력

def player_choice():
    choice = "string"
    while True:
        choice = input("가위, 바위, 보 중 하나 선택: ")
        if choice == "가위" or choice == "바위" or choice == "보": break
    return choice

def computer_choice():
    rand = random.randint(1, 3)
    if rand == 1: return "가위"
    if rand == 2: return "바위"
    if rand == 3: return "보"

def calculate_result(computer, player):
    print("\n[컴퓨터 선택]")
    print_choice_of(computer)
    print("[플레이어 선택]")
    print_choice_of(player)
    if computer == player: return "same"
    if computer == "가위":
        if player == "바위": return "플레이어"
        if player == "보": return "컴퓨터"
    if computer == "바위":
        if player == "가위": return "컴퓨터"
        if player == "보": return "플레이어"
    if computer == "보":
        if player == "바위": return "컴퓨터"
        if player == "가위": return "플레이어"

def initial_RSP():
    while True:
        print("[공격권 결정 가위바위보]")
        player_chosen = player_choice()
        computer_chosen = computer_choice()  # 플레이어, 컴퓨터 선택
        attacker = calculate_result(computer_chosen, player_chosen)  # 고른거 출력 및 결과계산
        if attacker == "플레이어":
            print("[결과] 플레이어 공격, 컴퓨터 수비입니다.")
            return attacker
        elif attacker == "컴퓨터":
            print("[결과] 컴퓨터 공격, 플레이어 수비입니다.")
            return attacker
        else:
            print("[결과] 무승부입니다.")  # 결과에 따라서 반환
            next()

def Mukchippa(attacker):
    round = 0
    while True:
        round += 1
        clear_screen()
        print("[묵찌빠]")
        print(f"승리 시 이동 칸 수: {round}")
        if attacker == "플레이어": print("플레이어 공격, 컴퓨터 수비입니다.")
        elif attacker == "컴퓨터": print("컴퓨터 공격, 플레이어 수비입니다.")  # 이전 정보 출력
        next_attacker = calculate_result(computer_choice(), player_choice())  # 플레이어, 컴퓨터 선택 및 출력 및 결과계산
        if next_attacker == "플레이어": print("[결과] 플레이어 공격, 컴퓨터 수비입니다.")
        elif next_attacker == "컴퓨터": print("[결과] 컴퓨터 공격, 플레이어 수비입니다.")
        elif next_attacker == 'same':
            print("[결과] 묵찌빠 종료")
            break # 결과에 따른 출력, 둘의 선택이 같을때까지 라운드 반복
        attacker = next_attacker
        next()
    print(f"{attacker}승, {round} 칸 이동합니다.")
    return attacker, round

################
# 프로그램 시작 #
################
def main():
    game_winner, attacker, win, player_score, computer_score = '', '', '', 0, 0   # 초기값 선언
    print_intro()   # 초기화면 출력
    stairs_number = input_stairs_number()   # 계단 수 입력
    clear_screen()
    # 게임 시작
    while True:
        print_stairs(stairs_number, player_score, computer_score)  # 현재 상황 및 계단 출력
        next()
        attacker = initial_RSP()   # 공격권 결정 가위바위보
        next()
        win, round = Mukchippa(attacker)   # 묵찌빠
        next()
        # 계단 이동
        if win == "플레이어": player_score += round
        if win == "컴퓨터": computer_score += round
        # 누군가 이기면 종료, 이후 점수를 최대 계단수로 조정
        if player_score >= stairs_number:
            game_winner = "플레이어"
            player_score = stairs_number
            break
        if computer_score >= stairs_number:
            game_winner = "컴퓨터"
            computer_score = stairs_number
            break
    print_stairs(stairs_number, player_score, computer_score)
    print("\n▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨")
    print(f" {game_winner} 최종 승리!!!")
    print("▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨ ▨\n")
    print("게임을 종료합니다...")   # 최종 결과 출력

if __name__ == "__main__":
    main()