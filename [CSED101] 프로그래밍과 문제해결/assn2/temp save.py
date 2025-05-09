import os
import random

Category_index = {"1":0, "2":1, "3":2, "4":3, "5":4, "6":5, "C":6, "4K":7, "FH":8, "SS":9, "LS":10, "Y":11}
reverse_category_index = {0:"1", 1:"2", 2:"3", 3:"4", 4:"5", 5:"6", 6:"C", 7:"4K", 8:"FH", 9:"SS", 10:"LS", 11:"Y"}

# 메뉴 출력. 메뉴 선택값 반환.
def menu():
    print("[Yacht Dice]")
    print("----------------------------------")
    print("1. New Game 2. Load Game 3. Exit")
    print("----------------------------------")
    while True:
        menu = input("Select a menu: ")
        if menu == '1' or menu == '2' or menu == '3': return menu
        else:
            print("Wrong Input!\n")
            continue

# 입력시 Q를 입력받았는지 확인. Q입력시 전달받은 스코어 리스트를 파일의 형태로 저장.
def input_(score_list, text=''):
    i = input(text).upper()
    if i=='Q':
        while True:
            fn = input("\nGame paused. Enter the filename to save: ")
            err = False

            # 파일 이름은 빈칸이 될 수 없음.
            if fn == '': err = True
            check_punc = True

            # 파일명은 구두점으로만 이루어질 수 없음.
            for letter in fn:
                if letter != '.': check_punc = False
            if check_punc == True: err = True

            # 특정 문자는 파일명으로 사용될 수 없음.
            banned_letter = ('\\', '/', ':', '*', '?', '"', '<', '>', '|')
            for letter in fn:
                if letter in banned_letter: err = True
            if err:
                print("Wrong input!")
                continue
            with open(fn, 'w') as fw:
                for i in range(0, 12):
                    player, computer = score_list[0][i], score_list[1][i]
                    if there_is_not(score_list[0][i]): player = 'x'
                    if there_is_not(score_list[1][i]): computer = 'x'
                    data = "%s: %s %s\n" % (reverse_category_index[i], player, computer)
                    fw.write(data)
            print("File saved\n")
            break
        main()
    else:
        return i

# 스코어 리스트에서 값이 저장되었는가?
def there_is(string):
    return string != ''

# 저장되지 않았는가?
def there_is_not(string):
    return string == ''

# 현재 스코어 리스트를 정해진 형식으로 출력함.
def print_score_board(score_list):
    player_sub_total, computer_sub_total = 0, 0
    player_total, computer_total = 0, 0
    for i in range(0, 6):
        if there_is(score_list[0][i]): player_sub_total += int(score_list[0][i])
        if there_is(score_list[1][i]): computer_sub_total += int(score_list[1][i])
    player_bonus, computer_bonus = '', ''
    player_num_compl, computer_num_compl = False, False
    p, c = 0, 0 # 1~6이 모두 채워졌는지 확인
    for i in range(0, 6):
        if there_is(score_list[0][i]): p += 1
        if there_is(score_list[1][i]): c += 1
    if p == 6: player_num_compl = True
    if c == 6: computer_num_compl = True
    if player_sub_total >= 63: player_bonus = 35
    elif player_num_compl: player_bonus = 0
    if computer_sub_total >= 63: computer_bonus = 35 # 63점 넘겼을때 보너스 35점 저장.
    elif computer_num_compl: computer_bonus = 0 # 1~6이 모두 채워졌다면 63점 못넘겼을 때 0 저장.
    for i in range (0, 12):
        if there_is(score_list[0][i]): player_total += int(score_list[0][i])
        if there_is(score_list[1][i]): computer_total += int(score_list[1][i])
    if there_is(player_bonus): player_total += player_bonus
    if there_is(computer_bonus): computer_total += computer_bonus
    print("┌──────────────────┬──────────────────┐")
    print("│      Player      │     Computer     │")
    print("├──────────────────┴──────────────────┤")
    print("│  1:         %2s   │  1:         %2s   │" % (score_list[0][0], score_list[1][0]))
    print("│  2:         %2s   │  2:         %2s   │" % (score_list[0][1], score_list[1][1]))
    print("│  3:         %2s   │  3:         %2s   │" % (score_list[0][2], score_list[1][2]))
    print("│  4:         %2s   │  4:         %2s   │" % (score_list[0][3], score_list[1][3]))
    print("│  5:         %2s   │  5:         %2s   │" % (score_list[0][4], score_list[1][4]))
    print("│  6:         %2s   │  6:         %2s   │" % (score_list[0][5], score_list[1][5]))
    print("├─────────────────────────────────────┤")
    print("│ Sub total: %2s/63 │ Sub total: %2s/63 │" % (player_sub_total, computer_sub_total))
    print("│ +35 bonus: %2s    │ +35 bonus: %2s    │" % (player_bonus, computer_bonus))
    print("├─────────────────────────────────────┤")
    print("│  C:         %2s   │  C:         %2s   │" % (score_list[0][6], score_list[1][6]))
    print("├─────────────────────────────────────┤")
    print("│  4K:        %2s   │  4K:        %2s   │" % (score_list[0][7], score_list[1][7]))
    print("│  FH:        %2s   │  FH:        %2s   │" % (score_list[0][8], score_list[1][8]))
    print("│  SS:        %2s   │  SS:        %2s   │" % (score_list[0][9], score_list[1][9]))
    print("│  LS:        %2s   │  LS:        %2s   │" % (score_list[0][10], score_list[1][10]))
    print("│  Yacht:     %2s   │  Yacht:     %2s   │" % (score_list[0][11], score_list[1][11]))
    print("├─────────────────────────────────────┤")
    print("│  Total:    %3s   │  Total:    %3s   │" % (player_total, computer_total))
    print("└─────────────────────────────────────┘")

# 매개변수 없으면, 5개 모두 굴림. 매개변수가 주어졌을 시 선택된 주사위만 다시 굴림.
def roll_dice(dice_set=[], reroll_indices=[]):
    if dice_set == []: return [random.randint(1, 6) for i in range(5)]
    for i in reroll_indices:
        if 1 <= i <= 5: dice_set[i-1] = random.randint(1, 6)
    return dice_set

# 점수 계산.
def calc_score(dice_set, sel):
    if sel == "1": return dice_set.count(1)
    elif sel == "2": return dice_set.count(2)*2
    elif sel == "3": return dice_set.count(3)*3
    elif sel == "4": return dice_set.count(4)*4
    elif sel == "5": return dice_set.count(5)*5
    elif sel == "6": return dice_set.count(6)*6 # 1~6: 개수에 숫자 곱한 값.
    elif sel == "C": return sum(dice_set) # C: 총합.
    elif sel == "4K":
        success = False
        for i in range(1, 7):
            if dice_set.count(i) >= 4: success = True # 4K: 개수가 4개 이상인 경우-
        if success: return sum(dice_set) # 총합을 반환
        else: return 0
    elif sel == "FH":
        success = False
        if dice_set.count(dice_set[0]) == 5: return sum(dice_set)
        for i in range(1, 7):
            if dice_set.count(i) == 3: # FH: 개수가 3개인 수가 있을 경우-
                for j in range(1, 7):
                    if i == j: continue
                    if dice_set.count(j) == 2: success = True # 다른 수의 개수가 2개인 것이 있다면-
        if success: return sum(dice_set) # 총합을 반환.
        else: return 0
    elif sel == "SS":
        success = False
        success_criteria = ([1, 2, 3, 4], [2, 3, 4, 5], [3, 4, 5, 6], [1, 2, 3, 4, 5], [1, 2, 3, 4, 6], [2, 3, 4, 5, 6], [1, 3, 4, 5, 6])
        if sorted(list(set(dice_set))) in success_criteria: success = True
        if success: return 15 # SS: 중복이 제거된 순서쌍이 가능한 순서쌍 집합 내에 있다면 15를 반환
        else: return 0
    elif sel == "LS":
        success = False
        success_criteria = ([1, 2, 3, 4, 5], [2, 3, 4, 5, 6])
        if sorted(list(set(dice_set))) in success_criteria: success = True
        if success: return 30 # LS: 중복이 제거된 순서쌍이 가능한 순서쌍 집합 내에 있다면 30를 반환
        else: return 0
    elif sel == "Y":
        if dice_set.count(dice_set[0]) == 5: return 50 # Y: 모두 같은 수라면 50을 반환
        else: return 0

# 플레이어 턴
def player_turn(round, score_list):
    print(f"\n[Player's Turn ({round}/12)]")
    reRoll = roll_dice()
    j = 2
    while j > 0:
        Roll = reRoll
        print("Roll: [%d, %d, %d, %d, %d]" % (Roll[0], Roll[1], Roll[2], Roll[3], Roll[4]))
        while True:
            try:
                sel_reroll = list(map(int, input_(score_list, "Which dice to reroll (1~5)? ").split()))
                break
            except Exception:
                print("Wrong input!")
                continue
        reRoll = roll_dice(Roll, sel_reroll)
        j -= 1
    print(f"Roll: [%d, %d, %d, %d, %d]\n" % (Roll[0], Roll[1], Roll[2], Roll[3], Roll[4]))
    sorted_Roll = sorted(Roll)
    print("Sorted Roll: ", end="")
    print(sorted_Roll)
    Category = ['1', '2', '3', '4', '5', '6', 'C', '4K', 'FH', 'SS', 'LS', 'Y']
    for i in range(11, -1, -1):
        if there_is(score_list[0][i]): del Category[i]
    while True:
        Cate = input_(score_list, "Choose a category: ").upper()
        if Cate not in Category:
            print("Wrong Input!")
            continue
        else:
            score_list[0][Category_index[Cate]] = calc_score(sorted_Roll, Cate)
            break
    return score_list

# 현재 주사위 조합과 스코어 리스트를 보고 컴퓨터의 판단을 결정하는 함수.
# calc_score함수와 유사한 알고리즘을 통해 확인함.
def computer_pattern(dice_set, score_list):
    computed_score = [-1 for i in range(0, 12)]
    for i in range(0, 12):
        if there_is_not(score_list[1][i]): computed_score[i] = calc_score(dice_set, reverse_category_index[i]) # 점수 계산
    if there_is_not(score_list[1][6]): # C 항목에 대한 전처리
        rounds = 0
        for i in range (0, 12):
            if there_is(score_list[1][i]): rounds += 1
        if rounds < 11:
            if sum(dice_set) < 20: computed_score[6] = -1  # 20점 미만일 때 C항목 무시, C만 남으면 그대로 유지.
        else: pass
    temp = -1
    Cate_index = 0
    for i in range(0, 12):
        if temp < computed_score[i]:
            temp = computed_score[i]
            Cate_index = i
    sel_reroll = [] # sel_reroll은 1~6, C인 경우 append를 통해 다시 굴릴 주사위 목록을 저장함.
    all_reroll = False # all_reroll은 나머지 경우 만족되지 않으면 True, [1, 2, 3, 4, 5]를 반환
    if 0 <= Cate_index <=5:
        for i in range(0, 5):
            if dice_set[i] != int(reverse_category_index[Cate_index]): sel_reroll.append(i+1)
    elif Cate_index == 6:
        for i in range(0, 5):
            if dice_set[i] <= 3: sel_reroll.append(i+1)
    elif Cate_index == 7:
        all_reroll = True
        for i in range(1, 7):
            if dice_set.count(i) >= 4: all_reroll = False
    elif Cate_index == 8:
        all_reroll = True
        for i in range(1, 7):
            if dice_set.count(i) == 3:
                for j in range(1, 7):
                    if i == j: continue
                    if dice_set.count(j) == 2: all_reroll = False
    elif Cate_index == 9:
        all_reroll = True
        success_criteria = ([1, 2, 3, 4], [2, 3, 4, 5], [3, 4, 5, 6], [1, 2, 3, 4, 5], [1, 2, 3, 4, 6], [2, 3, 4, 5, 6], [1, 3, 4, 5, 6])
        if sorted(list(set(dice_set))) in success_criteria: all_reroll = False
    elif Cate_index == 10:
        all_reroll = True
        success_criteria = ([1, 2, 3, 4, 5], [2, 3, 4, 5, 6])
        if sorted(list(set(dice_set))) in success_criteria: all_reroll = False
    elif Cate_index == 11:
        all_reroll = True
        if dice_set.count(dice_set[0]) == 5: all_reroll = False
    if all_reroll: sel_reroll = [1, 2, 3, 4, 5]
    return reverse_category_index[Cate_index], sel_reroll

# 컴퓨터 턴.
def computer_turn(round, score_list):
    print(f"\n[Computer's Turn ({round}/12)]")
    Roll=[]
    reRoll = roll_dice()
    j = 2
    while j > 0:
        Roll = reRoll
        print("Roll: [%d, %d, %d, %d, %d]" % (Roll[0], Roll[1], Roll[2], Roll[3], Roll[4]))
        Cate, sel_reroll = computer_pattern(Roll, score_list)
        print("Which dice to reroll (1~5)? ", end = '')
        for i in sel_reroll:
            print(str(i) + ' ', end='')
        print()
        reRoll = roll_dice(Roll, sel_reroll)
        j -= 1
    print("Roll: [%d, %d, %d, %d, %d]" % (Roll[0], Roll[1], Roll[2], Roll[3], Roll[4]))
    Cate, sel_reroll = computer_pattern(Roll, score_list)
    sorted_Roll = sorted(Roll)
    print(f"\nSorted Roll: [{sorted_Roll[0]}, {sorted_Roll[1]}, {sorted_Roll[2]}, {sorted_Roll[3]}, {sorted_Roll[4]}]")
    print(f"Choose a category: {Cate}")
    score_list[1][Category_index[Cate]] = calc_score(sorted_Roll, Cate)
    return score_list

# 게임을 종료하는 함수.
def endgame(score_list):
    player_sub_total, computer_sub_total = 0, 0
    player_total, computer_total = 0, 0
    for i in range(0, 6):
        player_sub_total += int(score_list[0][i])
        computer_sub_total += int(score_list[1][i])
    player_bonus, computer_bonus = 0, 0
    if player_sub_total >= 63: player_bonus = 35
    if computer_sub_total >= 63: computer_bonus = 35
    for i in range (0, 12):
        player_total += int(score_list[0][i])
        computer_total += int(score_list[1][i])
    player_total += player_bonus
    computer_total += computer_bonus  # 여기까지 최종점수 계산.
    print("\n<Final Score Board>")
    print_score_board(score_list)
    if player_total > computer_total: print("You win!\n")
    elif player_total < computer_total: print("You lose!\n")
    else: print("Draw\n")
    a = input("Press Enter to continue...") # 마무리.
    print()

# 스코어리스트에서 진행된 라운드 수를 반환하는 함수.
def calc_round_from_score_list(score_list, who='player'):
    rounds = 1
    if who == "player": who_index = 0
    else: who_index = 1
    for i in range(0, 12):
        if there_is(score_list[who_index][i]): rounds += 1
    return rounds

# 파일의 스코어를 리스트로 생성
def load_file2list(fn):
    score_list = []
    transpose_score_list = [['n' for i in range(2)] for j in range(12)] # 초기값 n, 특정 카테고리에 입력이 없으면 n이 남아서 check_error에서 확인함.
    with open(fn, 'r') as fr:
        # i = 0
        for line in fr.readlines():
            Cate8, player, computer = line.split()
            Cate, _ = Cate8.split(":")
            if player == 'x': player = ''
            if computer == 'x': computer = ''
            if Cate in Category_index: # 정해진 카테고리는 인덱스 0~11, 그외 카테고리는 12번부터 할당.
                transpose_score_list[Category_index[Cate]][0], transpose_score_list[Category_index[Cate]][1] = player, computer
            else: transpose_score_list.append([player, computer])
        for x in zip(*transpose_score_list): # 12(+a)*2리스트를 2*12(+a)리스트로 변환
            score_list.append(list(x))
    return score_list

# 파일에서 생성된 스코어 리스트가 유효한지 확인(T/F 반환)
def check_error(score_list):
    err = False
    # 줄 수가 일치하지 않을 시 에러
    if not (len(score_list[0]) == 12 and len(score_list[1]) == 12): err = True

    # 모두 정수인지 테스트
    check2_score_list = [[i if i != ''  else '0' for i in j] for j in score_list]

    for i in range(0, len(check2_score_list[0])): # int가 아니거나, 초깃값 n이 그대로 들어있다면
        try:
            a, b = str(int(check2_score_list[0][i])), str(int(check2_score_list[1][i])) # int형이 아닐 경우 에러
            # if a != check2_score_list[0][i]: err = True  # 문자열일 경우 에러를 발생, 따라서 에러
            # if b != check2_score_list[1][i]: err = True  # 실수형일 경우 int로 바꿨
        except Exception as e:
            err = True
            print(e)
            break

    if not err: # 줄 수나 입력되지 않은 값, 타입 에러가 없을시 각 점수가 가능한지 판단.
        check_score_list = [[int(i) if i != ''  else 0 for i in j] for j in score_list]
        # 서로 진행한 라운드 수가 다르면 에러
        if calc_round_from_score_list(score_list, "player") != calc_round_from_score_list(score_list, "computer"): err = True
        # 1~6의 경우를 확인하기 위한 2차원 튜플 선언
        check_num = tuple(tuple(i for i in range(0, 5*(j+1)+1, (j+1))) for j in range(0, 6))
        for i in range(0, 6):
            if not ((check_score_list[0][i] in check_num[i]) and (check_score_list[1][i] in check_num[i])): err = True
        # C~Y의 경우, 가능한 조합인지 확인. 특히 index = 8, FH인 경우 5~30 중 6과 29는 불가능함을 유의.
        if not (((5 <= check_score_list[0][6] <= 30) or check_score_list[0][6] == 0) and ((5 <= check_score_list[1][6] <= 30) or check_score_list[1][6] == 0)): err = True
        if not (((5 <= check_score_list[0][7] <= 30) or check_score_list[0][7] == 0) and ((5 <= check_score_list[1][7] <= 30) or check_score_list[1][7] == 0)): err = True
        if not (((7 <= check_score_list[0][8] <= 28) or check_score_list[0][8] in (0, 5, 30)) and ((7 <= check_score_list[1][8] <= 28) or check_score_list[1][8] in (0, 5, 30))): err = True
        if not ((check_score_list[0][9] in (15, 0)) and (check_score_list[1][9] in (15, 0))): err = True
        if not ((check_score_list[0][10] in (30, 0)) and (check_score_list[1][10] in (30, 0))): err = True
        if not ((check_score_list[0][11] in (50, 0)) and (check_score_list[1][11] in (50, 0))): err = True
    return err

def main():
    while True:
        score_list = [['' for i in range(12)] for j in range(2)]  # 점수를 저장하는 (문자열)리스트 선언
        selected_menu = menu() # 메뉴 출력후 값을 입력 받음.
        if selected_menu == '1':  # 1을 입력 받을시,
            print("\nStarting a game...")
            for round in range(1, 13): # 12라운드 동안 턴을 반복하며 진행
                print_score_board(score_list)
                score_list = player_turn(round, score_list)
                print_score_board(score_list)
                score_list = computer_turn(round, score_list)
            endgame(score_list) # 12라운드를 모두 진행한 후, 게임을 끝냄. 이후 메뉴로 돌아옴.
        if selected_menu == '2': ## 2를 입력 받을시,
            while True:
                fn = input("Enter filename to load: ")  ## 파일 이름을 입력 받음.
                if not os.path.exists(fn):   ## 파일이 없을시 에러 출력, 재입력 요청
                    print("File does not exsit.\n")
                    continue
                elif check_error(load_file2list(fn)):   ## 파일에 문제가 있을시 에러 출력, 재입력 요청
                    print("Invalid file content.\n")
                    continue  ## 파일에 문제가 없다면 진행.
                else: break
            score_list = load_file2list(fn)  ## 점수 리스트 계산
            rounds = calc_round_from_score_list(score_list)  ## 현재까지 진행한 라운드 수 계산
            for round in range(rounds, 13):  ## 남은 라운드 동안 턴을 반복하며 진행.
                print_score_board(score_list)
                score_list = player_turn(round, score_list)
                print_score_board(score_list)
                score_list = computer_turn(round, score_list)
            endgame(score_list)  ## 남은 라운드 끝나면 게임 종료, 이후 메뉴로 돌아옴.
        if selected_menu == '3': ### 3을 선택시,
            print("Program ended. Bye!")
            exit(0) ### 프로그램을 종료함.

if __name__ == "__main__":
    main()