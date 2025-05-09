import random

class Posmon:
    # __init__을 이용하여 초기에 필요한 변수를 초기화
    def __init__(self, max_health, attack, defence, name, moves):
        self.max_health, self.health = max_health, max_health
        self.attack, self.original_attack = attack, attack
        self.defence, self.original_defence = defence, defence
        self.name = name
        self.moves = moves
    def get_name(self) -> str: # 이름(문자열) 반환
        return self.name
    def get_max_health(self) -> int: # 최대체력(정수) 반환
        return self.max_health
    def get_type(self) -> str: # 타입(문자열) 반환, 각 하위 클래스에서 오버라이딩 하여 사용함.
        pass # will overide
    def reset_status(self, reset_health:bool = False): # 공격력, 방어력, (체력)을 초기화하는 메서드
        if reset_health: self.health = self.max_health
        self.attack = self.original_attack
        self.defence = self.original_defence
    def is_knocked_out(self) -> bool: # 추가됨, 해당 포스몬이 죽은 상태인지 확인하는 메서드
        return self.health <= 0
    def get_health(self) -> int: # 추가됨, 포스몬의 체력(정수)를 반환하는 메서드
        return self.health
    def get_moves(self) -> list: # 추가됨, 포스몬이 가진 능력(리스트)를 반환하는 메서드
        return self.moves

class Ponix(Posmon): # Posmon을 상속하여 자세한 스테이터스 세팅.
    def __init__(self):
        super().__init__(max_health = 86, attack = 20, defence = 23, name = "Ponix", moves = [Tackle(), Growl(), SwordDance()])
    def get_type(self) -> str:
        return "Paper"

class Normie(Posmon): # Posmon을 상속하여 자세한 스테이터스 세팅.
    def __init__(self):
        super().__init__(max_health = 80, attack = 20, defence = 20, name = "Normie", moves = [Tackle(), Swift(), TailWhip()])
    def get_type(self) -> str:
        return "Nothing"

class Rocky(Posmon): # Posmon을 상속하여 자세한 스테이터스 세팅.
    def __init__(self):
        super().__init__(max_health = 80, attack = 15, defence = 25, name = "Rocky", moves = [Tackle(), Growl()])
    def get_type(self) -> str:
        return "Rock"

class Swania(Posmon): # Posmon을 상속하여 자세한 스테이터스 세팅.
    def __init__(self):
        super().__init__(max_health = 80, attack = 30, defence = 10, name = "Swania", moves = [ScissorsCross(), SwordDance()])
    def get_type(self) -> str:
        return "Scissors"

class Move:
    def __init__(self, name): # __init__ 을 이용하여 이름을 초기화
        self.name = name
    def get_name(self) -> str: # 기술의 이름을 반환하는 메서드
        return self.name
    def get_speed(self) -> int: # 기술의 속도를 반환하는 메서드, 각 하위 클래스에서 오버라이딩하여 사용.
        pass # will overide
    def use(self, our_posmon:Posmon, opponent_posmon:Posmon, is_player_move=True): # 기술을 사용하는 메서드, 오버라이딩하여 사용
        pass # will overide

class PhyscialMove(Move): # 대분류 : 공격 기술
    def __init__(self, power, name): # 이름, 위력 초기화
        super().__init__(name)
        self.power = power
    def get_power(self) -> int: # 기술의 위력(정수)를 반환하는 메서드
        return self.power
    def use(self, our_posmon:Posmon, opponent_posmon:Posmon, is_player_move=True): # 현재 배틀 중인 포스몬이 기술을 사용하여, 정해진 수식에 따라 데미지를 계산하여 상대 체력을 깍는 메서드
        advantage_set = (("Paper", "Rock"), ("Rock", "Scissors"), ("Scissors", "Paper")) # 상성상 우위에 있다면 배율 2배.
        if (our_posmon.get_type(), opponent_posmon.get_type()) in advantage_set: magnification = 2
        else: magnification = 1
        damage = max(0, self.power + our_posmon.attack - opponent_posmon.defence) * magnification # 정해진 계산식을 따름.
        opponent_posmon.health -= damage
        if is_player_move:
            user, subj = "당신의", "컴퓨터"
        else:
            user, subj = "컴퓨터", "당신"
        print("%s %s: %s 기술 사용" % (user, our_posmon.get_name(), self.get_name()))
        print("- %s 포스몬의 [체력] %d 감소 (%d -> %d)" % (subj, damage, opponent_posmon.health + damage, opponent_posmon.health)) # 정해진 형식에 맞게 설명문 출력함.

class Tackle(PhyscialMove): # 세부 기술의 이름과 위력 설정
    def __init__(self):
        super().__init__(power = 25, name = "Tackle")
    def get_speed(self): # 속도를 반환하는 메서드(다른 클래스에서도 동일)
        return 0

class ScissorsCross(PhyscialMove): # 세부 기술의 이름과 위력 설정
    def __init__(self):
        super().__init__(power = 30, name = "ScissorsCross")
    def get_speed(self):
        return 0

class Swift(PhyscialMove): # 세부 기술의 이름과 위력 설정
    def __init__(self):
        super().__init__(power = 0, name = "Swift")
    def get_speed(self):
        return 3

class StatusMove(Move): # 변화기술 클래스 정의
    pass

class Growl(StatusMove): # 세부 기술의 이름과 효과 설정
    def __init__(self):
        super().__init__(name = "Growl")
        self.amount = -5
    def get_speed(self) -> int:
        return 1
    def use(self, our_posmon:Posmon, opponent_posmon:Posmon, is_player_move = True):
        if is_player_move: user, subj = "당신의", "컴퓨터"
        else: user, subj = "컴퓨터", "당신" # 사용 주체에 따라서 다른 설명문 출력
        if opponent_posmon.attack + self.amount < 0: self.after_attack = 0 # 공격력이 0보다 작아질 수 없으므로, 3->-2 와 같은 출력을 방지하기 위함
        else: self.after_attack = opponent_posmon.attack + self.amount
        print("%s %s: %s 기술 사용" % (user, our_posmon.get_name(), self.get_name()))
        print("- %s 포스몬의 [공격력] %d 감소 (%d -> %d)" % (subj, abs(self.amount), opponent_posmon.attack, self.after_attack)) # 정해진 형식에 맞게 설명문 출력함.
        opponent_posmon.attack += self.amount
        if opponent_posmon.attack < 0: opponent_posmon.attack = 0

class SwordDance(StatusMove):
    def __init__(self):
        super().__init__(name = "SwordDance")
        self.amount = 10
    def get_speed(self) -> int:
        return 0
    def use(self, our_posmon:Posmon, opponent_posmon:Posmon, is_player_move = True):
        if is_player_move: user, subj = "당신의", "당신의"
        else: user, subj = "컴퓨터", "컴퓨터" # 사용 주체에 따라서 다른 설명문 출력
        print("%s %s: %s 기술 사용" % (user, our_posmon.get_name(), self.get_name()))
        print("- %s 포스몬의 [공격력] %d 증가 (%d -> %d)" % (subj, abs(self.amount), our_posmon.attack, our_posmon.attack + self.amount)) # 정해진 형식에 맞게 설명문 출력함.
        our_posmon.attack += self.amount

class TailWhip(StatusMove):
    def __init__(self):
        super().__init__(name = "TailWhip")
        self.amount = -5
    def get_speed(self) -> int:
        return 1
    def use(self, our_posmon:Posmon, opponent_posmon:Posmon, is_player_move = True):
        if is_player_move: user, subj = "당신의", "컴퓨터"
        else: user, subj = "컴퓨터", "당신" # 사용 주체에 따라서 다른 설명문 출력
        if opponent_posmon.defence + self.amount < 0: self.after_defence = 0 # 방어력이 0보다 작아질 수 없으므로, 3->-2 와 같은 출력을 방지하기 위함
        else: self.after_defence = opponent_posmon.defence + self.amount
        print("%s %s: %s 기술 사용" % (user, our_posmon.get_name(), self.get_name()))
        print("- %s 포스몬의 [방어력] %d 감소 (%d -> %d)" % (subj, abs(self.amount), opponent_posmon.defence, self.after_defence)) # 정해진 형식에 맞게 설명문 출력함.
        opponent_posmon.defence += self.amount
        if opponent_posmon.defence < 0: opponent_posmon.defence = 0

def menu(): # 메뉴를 출력하고, 올바른 메뉴 선택값을 반환하는 함수
    print("\n____    ___    _____ ___ ___   ___   __  __")
    print("|   \  /   \  / ___/|   T   T /   \ |    \\ ")
    print("| o  )Y     Y(   \_ |  _ _  |Y     Y|  _  Y")
    print("|  _/ |  O  | \__  T|  \_/  ||  O  ||  |  |")
    print("|  |  |     | /  \ ||   |   ||     ||  |  |")
    print("|  |  l     ! \    ||   |   |l     !|  |  |")
    print("l__j   \___/   \___jl___j___j \___/ l__j__j")
    print("============================================")
    print("0. 포스몬 선택")
    print("1. 배틀하기")
    print("2. 종료하기")
    print("============================================")
    while True:
        selected = input("입력: ")
        if selected in ("0", "1", "2"): return selected
        else: print("잘못된 입력입니다. 다시 입력하세요.")

def add_player_posmon(player_posmon_list): # 메뉴에서 0을 입력받을시 실행되며, 정해진 규칙에 따라 포스몬을 추가하고 메뉴로 돌아오는 함수
    posmon_index_dict = {0:"Ponix", 1:"Normie", 2:"Swania", 3:"Rocky"}
    numforcheck = (0, 1, 2, 3, -1)
    while True:
        print("\n============================================")
        print("당신이 사용할 포스몬을 선택하세요. 현재 %d 마리/최대 3 마리" % len(player_posmon_list))
        for i in range(len(posmon_index_dict)):
            print("%d. %s" % (i, posmon_index_dict[i])) # 이후 확장성을 고려
        # print("0. Ponix")
        # print("1. Normie")
        # print("2. Swania")
        # print("3. Rocky")
        if len(player_posmon_list) != 0: print("-1. 그만두기")
        print("============================================")
        try: # 예외처리
            selected = int(input("입력: "))
        except Exception:
            print("잘못된 입력입니다. 다시 입력하세요.")
            continue
        if selected not in numforcheck: print("잘못된 입력입니다. 다시 입력하세요.")
        else:
            if selected == -1:
                if len(player_posmon_list) == 0: print("잘못된 입력입니다. 다시 입력하세요.")
                else:
                    print("\n============================================")
                    print("당신의 포스몬 목록: %s" % ' '.join(player_posmon_list))
                    print("============================================\n")
                    return player_posmon_list
            else:
                if len(player_posmon_list) == 3: print("포스몬을 더 이상 추가할 수 없습니다.")
                # elif posmon_index_dict[selected] not in player_posmon_list: player_posmon_list.append(posmon_index_dict[selected]) # 중복이 불가능할 때 추가할 코드.
                else: player_posmon_list.append(posmon_index_dict[selected])

def print_battle_screen(player_posmon, computer_posmon, p_index, c_index): # 현재 싸우는 포스몬의 현황을 출력하는 함수
    computer_status = ''
    c_count = 0
    for posmon in computer_posmon:
        if posmon.is_knocked_out(): computer_status += "X"
        else:
            computer_status += "O"
            c_count += 1
    player_status = ''
    p_count = 0
    for posmon in player_posmon:
        if posmon.is_knocked_out():
            player_status += "X"
        else:
            player_status += "O"
            p_count += 1
    # for i in range(0, 3 - len(player_posmon)): player_status += " "
    cp = computer_posmon[c_index]
    pp = player_posmon[p_index]
    selecting_move = ''
    for i in range(len(player_posmon[p_index].get_moves())): # 현재 배틀에 나온 사용자 포스몬의 기술
        selecting_move += " (" + str(i) + ") " + player_posmon[p_index].get_moves()[i].get_name()
    print("\n############################################")
    print("컴퓨터 포스몬: [%-3s] %d / %d" % (computer_status, c_count, len(computer_posmon))) # 컴퓨터가 보유한 포스몬들의 상태 정보
    print("%s           \t<|%-9s %d / %d|" % (cp.get_name(), cp.get_type(), cp.get_health(), cp.get_max_health())) # 현재 배틀에 나온 컴퓨터 포스몬 정보
    print("                  VS")
    print("%s           \t<|%-9s %d / %d|" % (pp.get_name(), pp.get_type(), pp.get_health(), pp.get_max_health())) # 현재 배틀에 나온 사용자 포스몬 정보
    print("당신의 포스몬: [%-3s] %d / %d" % (player_status, p_count, len(player_posmon))) # 사용자가 보유한 포스몬들의 상태 정보
    print("++++++++++++++++++++++++++++++++++++++++++++")
    print("기술:%s" % (selecting_move)) # 현재 배틀에 나온 사용자 포스몬의 기술
    print("############################################")

def player_turn(player_posmon, p_index): # 플레이어 차례에서 올바른 명령을 입력받고 명령을 반환하는 함수(교체일 경우 처리하고 None을 반환)
    player_move = None
    while True:
        command = input("입력: ")
        if command == '': # 미입력 -> 잘못된 입력
            print("잘못된 입력입니다. 다시 입력하세요.")
            continue
        command = command.split()
        if len(command) > 2: # 2개 이상 항목 입력 -> 잘못된 입력
            print("잘못된 입력입니다. 다시 입력하세요.")
            continue
        if command[0] == 'e': # entry
            print("############################################")
            for i in range(len(player_posmon)):
                pp = player_posmon[i]
                print("(%d) %s   \t <|%-9s %d / %d |" % (i, pp.get_name(), pp.get_type(), pp.get_health(), pp.get_max_health()))
            print()
        elif command[0] == 'o': # order
            print("############################################")
            pp = player_posmon[p_index]
            try: # 예외처리
                command[1] = int(command[1])
            except Exception:
                print("잘못된 입력입니다. 다시 입력하세요.")
                continue
            if command[1] in range(len(pp.get_moves())):
                player_move = pp.get_moves()[command[1]]
                break
            print("잘못된 입력입니다. 다시 입력하세요.")
            continue
        elif command[0] == 's': # switch out
            print("############################################")
            try: # 예외처리
                command[1] = int(command[1])
            except Exception:
                print("잘못된 입력입니다. 다시 입력하세요.")
                continue
            if command[1] == p_index:
                print("자기자신과는 교대할 수 없습니다. 다시 입력하세요.")
                continue
            if player_posmon[command[1]].is_knocked_out():
                print("이미 쓰러진 포스몬입니다. 다시 입력하세요.")
                continue
            if command[1] in range(len(player_posmon)):
                player_posmon[p_index].reset_status(False)
                print("당신의 포스몬 %s로 교대" % (player_posmon[command[1]].get_name()))
                p_index = command[1]
                break
            print("잘못된 입력입니다. 다시 입력하세요.")
            continue
        else:
            print("잘못된 입력입니다. 다시 입력하세요.")
            continue
    return player_move, p_index

def computer_turn(computer_posmon, c_index): # 컴퓨터의 포스몬의 기술중 임의로 하나를 선택해 반환하는 함수
    return random.choice(computer_posmon[c_index].get_moves())

def battle(player_posmon, computer_posmon): # 메뉴에서 1을 입력받을시 실행되며, 승자가 결정날때까지 배틀을 진행.
    player, computer = '', ''
    for i in player_posmon: player += (i.get_name() + ' ')
    for i in computer_posmon: computer += (i.get_name() + ' ')
    print("\n============================================")
    print("당신의 포스몬 목록: %s" % (player))
    print("컴퓨터 포스몬 목록: %s" % (computer))
    print("============================================\n")
    print("배틀이 시작됩니다.")
    c_index, p_index = 0, 0
    winner = ''
    while True: # 한번 반복 -> 한 턴
        print_battle_screen(player_posmon, computer_posmon, p_index, c_index)
        player_move, p_index = player_turn(player_posmon, p_index)
        computer_move = computer_turn(computer_posmon, c_index)
        if player_move == None: # 플레이어가 교체했다면 컴퓨터 명령을 실행. # TODO 플레이어 죽는지 확인
            computer_move.use(computer_posmon[c_index], player_posmon[p_index], False)
            if player_posmon[p_index].is_knocked_out(): # 플레이어의 포스몬이 죽었다면
                cnt = len(player_posmon)
                for i in range(len(player_posmon)):
                    if player_posmon[i].is_knocked_out(): cnt -= 1
                if cnt == 0: #@@@ 플레이어의 포스몬이 모두 죽었다면
                    print("당신의 %s: 쓰러짐" % (player_posmon[p_index].get_name()))
                    print_battle_screen(player_posmon, computer_posmon, p_index, c_index)
                    winner = "computer"
                    break
                else: #@@@ 플레이어에게 남은 포스몬이 있으면
                    print("당신의 %s: 쓰러짐" % (player_posmon[p_index].get_name()))
                    while True:
                        p_index += 1 # 자동으로 다음 포스몬으로 교체
                        if p_index == len(player_posmon): p_index = 0
                        if not player_posmon[p_index].is_knocked_out(): break
        else: # 둘 각자 명령이 있다면,
            if player_move.get_speed() >= computer_move.get_speed(): #@ 플레이어의 속도가 빠른경우.
                player_move.use(player_posmon[p_index], computer_posmon[c_index], True) # 플레이어의 행동 실행.
                if computer_posmon[c_index].is_knocked_out(): #@@ 컴퓨터의 포스몬이 죽었다면4
                    if c_index <= 1: # 다음 인덱스, 마지막 포스몬일 경우 승자를 결정하고 종료.
                        print("컴퓨터 %s: 쓰러짐" % (computer_posmon[c_index].get_name()))
                        c_index += 1
                        print("컴퓨터 포스몬 %s 로 교대" % (computer_posmon[c_index].get_name()))
                    else:
                        print("컴퓨터 %s: 쓰러짐" % (computer_posmon[c_index].get_name()))
                        print_battle_screen(player_posmon, computer_posmon, p_index, c_index)
                        winner = "you"
                        break
                else: #@@ 컴퓨터의 포스몬이 죽지 않았다면
                    computer_move.use(computer_posmon[c_index], player_posmon[p_index], False) # 컴퓨터의 행동 실행.
                    if player_posmon[p_index].is_knocked_out(): # 플레이어의 포스몬이 죽었다면
                        cnt = len(player_posmon)
                        for i in range(len(player_posmon)):
                            if player_posmon[i].is_knocked_out(): cnt -= 1
                        if cnt == 0: #@@@ 플레이어의 포스몬이 모두 죽었다면
                            print("당신의 %s: 쓰러짐" % (player_posmon[p_index].get_name()))
                            print_battle_screen(player_posmon, computer_posmon, p_index, c_index)
                            winner = "computer"
                            break
                        else: #@@@ 플레이어에게 남은 포스몬이 있으면
                            print("당신의 %s: 쓰러짐" % (player_posmon[p_index].get_name()))
                            while True:
                                p_index += 1 # 자동으로 다음 포스몬으로 교체
                                if p_index == len(player_posmon): p_index = 0
                                if not player_posmon[p_index].is_knocked_out(): break
            else: # 컴퓨터의 속도가 빠른경우.
                computer_move.use(computer_posmon[c_index], player_posmon[p_index], False) # 컴퓨터의 행동 실행.
                if player_posmon[p_index].is_knocked_out(): # 플레이어의 포스몬이 죽었다면
                    cnt = len(player_posmon)
                    for i in range(len(player_posmon)):
                        if player_posmon[i].is_knocked_out(): cnt -= 1
                    if cnt == 0: #@@@ 플레이어의 포스몬이 모두 죽었다면
                        print("당신의 %s: 쓰러짐" % (player_posmon[p_index].get_name()))
                        print_battle_screen(player_posmon, computer_posmon, p_index, c_index)
                        winner = "computer"
                        break
                    else: #@@@ 플레이어에게 남은 포스몬이 있으면
                        print("당신의 %s: 쓰러짐" % (player_posmon[p_index].get_name()))
                        while True:
                            p_index += 1 # 자동으로 다음 포스몬으로 교체
                            if p_index == len(player_posmon): p_index = 0
                            if not player_posmon[p_index].is_knocked_out(): break
                else: # 플레이어의 포스몬이 죽지 않았다면
                    player_move.use(player_posmon[p_index], computer_posmon[c_index], True) # 플레이어의 행동 실행.
                    if computer_posmon[c_index].is_knocked_out(): #@@ 컴퓨터의 포스몬이 죽었다면
                        if c_index <= 1: # 다음 인덱스, 마지막 포스몬일 경우 승자를 결정하고 종료.
                            print("컴퓨터 %s: 쓰러짐" % (computer_posmon[c_index].get_name()))
                            c_index += 1
                            print("컴퓨터 포스몬 %s 로 교대" % (computer_posmon[c_index].get_name()))
                        else:
                            print("컴퓨터 %s: 쓰러짐" % (computer_posmon[c_index].get_name()))
                            print_battle_screen(player_posmon, computer_posmon, p_index, c_index)
                            winner = "you"
                            break
    return winner

# 문자열 리스트를 받아 리스트를 구성하는 문자열의 이름을 가진 클래스로 리스트를 만들어 반환하는 함수.
# 포스몬의 이름이 Exception과 같이 예외적인 이름일 경우 문제가 생길 수 있는 방법이므로, 더 안전한 방법을 추후 모색할 것임.
def list2instance(posmon_list):
    posmon = []
    for i in posmon_list:
        instance = globals()[i]()
        posmon.append(instance)
    return posmon

def main(): # 메인
    player_posmon_list, computer_posmon_list, player_posmon, computer_posmon = [], [], [], []
    posmon_list = ("Ponix", "Normie", "Rocky", "Swania")
    while True:
        choice = menu() # 메뉴 선택 type(choice) = int
        if choice == "0": # 0을 선택했을 경우,
            player_posmon_list = add_player_posmon(player_posmon_list)
            # add_player_posmon 함수를 호출하여 player_posmon리스트에 포스몬 추가
        elif choice == "1": # 1을 선택했을 경우,
            if len(player_posmon_list) == 0: # 포스몬을 선택하지 않을 경우 중지.
                print("\n싸울 포스몬이 없습니다! 먼저 포스몬을 선택해 주세요.")
                continue
            # computer_posmon_list = random.sample(posmon_list, 3) # 컴퓨터 포스몬 선택 중복 고려
            for i in range(0, 3):
                sample = random.choice(posmon_list)
                computer_posmon_list.append(sample)
            player_posmon = list2instance(player_posmon_list)
            computer_posmon = list2instance(computer_posmon_list)
            winner = battle(player_posmon, computer_posmon) # battle 함수를 호출하여 시작
            if winner == "you": print("\n[배틀 결과] 당신이 이겼습니다!")
            elif winner == "computer": print("[배틀 결과] 컴퓨터가 이겼습니다!")
            player_posmon_list, computer_posmon_list, player_posmon, computer_posmon = [], [], [], []
        elif choice == "2":
            print("Program ended. Bye!") # 3을 선택했을 경우,
            exit(0) # 프로그램 종료
        else:
            print("잘못된 입력입니다. 다시 입력하세요.")

if __name__ == "__main__":
    main()