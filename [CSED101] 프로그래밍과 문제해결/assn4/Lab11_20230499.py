# tkinter 모듈 import
import tkinter as tk
import random

#---------------------------------------------------------------------#
# 전역변수
height = 2
width = 3
rand_list = []  # 2차원 리스트 (카드 숫자 저장)
button_list = []  # 2차원 리스트 (버튼 저장)
selected_cards = []  # 게임 시, 2개의 카드 관련 정보 저장

#---------------------------------------------------------------------#
# 함수 정의
def reset_board(height, width):
    print(height, width)
    make_board(height, width)

def make_board(height, width):
    # 기존 버튼 위젯 삭제
    for widget in body_frame.winfo_children():
        widget.destroy()

    # 버튼 생성 (height x width)개 및 배치
    i = 0
    for r in range(height):
        for c in range(width):
            button = tk.Button(body_frame, width = 4, height = 2, text = "%d" % i)
            button.grid(row = r, column = c)
            i += 1
    pairs_left = height * width // 2 # 맞춰야 할 카드 쌍의 수
    temp_list = list(range(pairs_left)) * 2
    random.shuffle(temp_list)
    rand_list.clear() # 2차원 리스트 전역변수
    button_list.clear() # 2차원 리스트 전역변수
    i = 0
    for r in range(height):
        row_list_rand = []
        row_list_btn = []
        for c in range(width):
            button=tk.Button(body_frame, width=4, height=2, text = "%d" % temp_list[i])
            button.grid(row=r, column=c)
            button.bind("<Button-1>", lambda event, row=r, col=c : on_left_click(row, col) )
            row_list_rand.append(temp_list[i])
            row_list_btn.append(button)
            i += 1
        rand_list.append(row_list_rand)
        button_list.append(row_list_btn)
    # 2초(2000밀리 초) 동안 카드 보여준 후, 물음표로 가리기
    window.after(2000, hide_card_list)

def on_left_click(row, col):
    print(row, col, rand_list[row][col])
    selected_cards.append([row, col, rand_list[row][col]])
    if len(selected_cards) == 2:
        if selected_cards[0][2] == selected_cards[1][2]:
            reveal_card(selected_cards[0][0], selected_cards[0][1])
            reveal_card(selected_cards[1][0], selected_cards[1][1])
        else:
            hide_card(selected_cards[0][0], selected_cards[0][1])
            hide_card(selected_cards[1][0], selected_cards[1][1])
        selected_cards.clear()

def hide_card_list():
    for row_list in button_list:
        for button in row_list:
            button.config(text="?")

def hide_card(row, col):  # 카드 물음표 출력, 버튼 활성화
    button = button_list[row][col]
    button.config(text='?', state=tk.NORMAL, relief=tk.RAISED)

def reveal_card(row, col):  # 카드 숫자 보이기, 버튼 비활성화, 누른 상태 유지
    button = button_list[row][col]
    button.config(text=rand_list[row][col], state=tk.DISABLED, relief=tk.SUNKEN)

#---------------------------------------------------------------------#
# 0. 기본창 생성
window = tk.Tk()
window.title("기억력 게임")

# 이미지 로드
img1 = tk.PhotoImage(file="imgs/smile.png")
img2 = tk.PhotoImage(file="imgs/sunglasses.png")

# 1. Header 프레임: 초기화 버튼 --------------------------------------#
header_frame = tk.Frame(window)
header_frame.pack()

reset_button = tk.Button(header_frame, image = img1)
reset_button.pack()

reset_button.bind("<Button-1>", lambda e: reset_button.config(image = img1))
reset_button.bind("<Button-3>", lambda e: reset_button.config(image = img2))

# 2. Body 프레임: 게임 보드(n행 x m열 개수의 버튼으로 구성) ----------#
body_frame = tk.Frame(window)
body_frame.pack()
make_board(height, width)

# 3. 메뉴 바 구성: 난이도(초급, 중급) --------------------------------#
# 3-1. 메뉴 바 생성
menu_bar = tk.Menu(window)
window.config(menu = menu_bar)

# 3-2. 난이도 메뉴 생성
level_menu = tk.Menu(menu_bar, tearoff = 0)
menu_bar.add_cascade(label = "난이도", menu = level_menu)

# 3-3. 난이도 메뉴에 옵션 추가 (초급, 중급)
level_menu.add_command(label="초급", command=lambda: reset_board(2, 3)) # 2행 3열
level_menu.add_command(label="중급", command=lambda: reset_board(4, 4)) # 4행 4열

#---------------------------------------------------------------------#
window.mainloop()
