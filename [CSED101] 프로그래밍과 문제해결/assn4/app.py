#############################
#
#   app.py : GUI를 구현하는 파일
#
#############################

import tkinter as tk
from model import Board # model.py에서 Board 클래스를 import

TITLE = "Minesweeper"
BTN_WIDTH = 30
BTN_HEIGHT = 30
BORDER_SIZE = 2
OUTTER_PADDING_SIZE = 10
BACKGROUND_COLOR = "#DCDCDC"

class App(tk.Frame): # 사용되는 인스턴스 변수를 정의, 보드를 리셋하고 setGUI 메서드 호출.
    def __init__(self, master):
        super(App, self).__init__(master)
        master.title(TITLE)
        self.window = master # 다른 메서드에서도 사용하기 위해 window 인스턴스 변수에 저장
        self.board = Board()

        self.height = 10 # 난이도가 변경될 때마다 변경되는 인스턴스 변수
        self.width = 10
        self.num_mines = 10

        self.img_bomb = tk.PhotoImage(file="imgs/bomb.png") # 이미지를 불러오는 인스턴스 변수
        self.img_flag = tk.PhotoImage(file="imgs/flag.png")
        self.img_skull = tk.PhotoImage(file="imgs/skull.png")
        self.img_smile = tk.PhotoImage(file="imgs/smile.png")
        self.img_sunglasses = tk.PhotoImage(file="imgs/sunglasses.png")

        self.board.reset(self.num_mines, self.height, self.width)
        self.setGUI()

    def setGUI(self): # 지뢰찾기 모양에 맞게 GUI를 구성하고, button에 bind를 이용해서 클릭 이벤트를 할당. 이후 board_reset 메서드 호출.
        # 메뉴바 설정
        menu_bar = tk.Menu(self.window)
        self.window.config(menu = menu_bar)
        level_menu = tk.Menu(menu_bar, tearoff = 0)
        menu_bar.add_cascade(label = "난이도", menu = level_menu)
        level_menu.add_command(label = "Easy", command = lambda: self.change_level(0))
        level_menu.add_command(label = "Normal", command = lambda: self.change_level(1))
        level_menu.add_command(label = "Hard", command = lambda: self.change_level(2))

        # 헤더 프레임 설정. 헤더 프레임에는 reset_button이 들어감.
        self.header_frame = tk.Frame(self.window, bg=BACKGROUND_COLOR, relief=tk.SUNKEN, bd=BORDER_SIZE)
        self.header_frame.grid(row=0, column=0, columnspan=self.width, pady=(0, OUTTER_PADDING_SIZE), sticky='ew')
        reset_wrapper = tk.Frame(self.header_frame, width=BTN_WIDTH, height=BTN_HEIGHT)
        reset_wrapper.pack_propagate(0)
        reset_wrapper.pack(padx=OUTTER_PADDING_SIZE, pady=OUTTER_PADDING_SIZE)
        # 헤더에 있는 리셋 버튼
        self.reset_button = tk.Button(reset_wrapper, image = self.img_smile)
        self.reset_button.pack()
        self.reset_button.bind("<Button-1>", lambda e: self.board_reset())

        # 바디 프레임 설정. 바디 프레임에는 버튼들이 들어갈 예정이며, 이는 Board_reset 메서드 ( -> make_board)에서 만들어짐.
        self.body_frame = tk.Frame(self.window, bg=BACKGROUND_COLOR, relief=tk.SUNKEN, bd=BORDER_SIZE)
        self.body_frame.grid(row=1, column=0, columnspan=self.width)
        self.board_reset()

    def board_reset(self): # 보드를 리셋하고, body_frame에 있는 모든 위젯을 삭제한 후 make_board 메서드 호출. (body_frame만 리셋함)
        self.board.reset(self.num_mines, self.height, self.width)
        self.reset_button.config(image = self.img_smile)
        try:
            for widget in self.body_frame.winfo_children():
                widget.destroy()
        except:
            pass
        self.make_board()

    def make_board(self): # 보드를 만드는 함수로, body_frame에 버튼을 배치하고, 각 버튼에 클릭 이벤트를 할당. button_list 인스턴스 변수에 2차원 버튼 리스트를 저장함. 버튼 리스트에 .config를 이용해 이미지를 설정할 수 있음.
        self.button_list = []
        for r in range(self.height):
            button_row = []
            for c in range(self.width):
                btn_wrapper = tk.Frame(self.body_frame, width=BTN_WIDTH, height=BTN_HEIGHT)
                btn_wrapper.pack_propagate(0)
                btn_wrapper.grid(row=r, column=c)

                button = tk.Button(btn_wrapper, bg=BACKGROUND_COLOR, bd=BORDER_SIZE)
                button.bind("<Button-1>", lambda e, row = r, col = c: self.left_click(row, col))
                button.bind("<Button-3>", lambda e, row = r, col = c: self.right_click(row, col))
                # button.grid(row = r, column = c)
                button.pack(expand=True, fill='both')
                button_row.append(button)
            self.button_list.append(button_row)

    def change_level(self, level): # 레벨을 변경하는 함수로, 0, 1, 2는 각각 easy, normal, hard를 의미함. 변경 후에는 board_reset 메서드 호출하여 보드를 리셋.
        if level == 0: self.num_mines, self.height, self.width = 10, 10, 10
        if level == 1: self.num_mines, self.height, self.width = 30, 15, 15
        if level == 2: self.num_mines, self.height, self.width = 50, 20, 20
        self.board_reset()

    def defeat(self): # MinePanel을 좌클릭 했을 떄 (플래그 없이) 패배한 경우를 처리하는 함수로, 모든 패널을 밝혀주고 reset_button의 이미지를 skull로 변경.
        # all reveal
        for j in range(self.width):
            for i in range(self.height):
                if self.board.checkFlag(j, i):
                    self.board.toggleFlag(j, i) # 패배할 때, 플래그는 모두 제거하고 모든 칸을 밝혀야 함.
                    self.button_list[j][i].config(image = '', state=tk.DISABLED, relief=tk.SUNKEN)
        for j in range(self.width):
            for i in range(self.height):
                if self.board.checkMine(j, i): # 지뢰가 있는 칸은 지뢰 이미지로 표시
                    self.button_list[j][i].config(image = self.img_bomb, state=tk.DISABLED, relief=tk.SUNKEN)
                else: # 지뢰가 없는 칸은
                    if self.board.getNumOfNearMines(j, i) == 0: # 근처 지뢰가 없는 칸은 빈칸으로 표시
                        self.button_list[j][i].config(text = '', state=tk.DISABLED, relief=tk.SUNKEN) # 근처 지뢰가 없으면 0 이 아니라 빈칸으로 표시
                    else : self.button_list[j][i].config(text = self.board.getNumOfNearMines(j, i), state=tk.DISABLED, relief=tk.SUNKEN) # 근처 지뢰가 있으면 근처 지뢰 개수로 표시
        self.reset_button.config(image = self.img_skull)

    def victory(self): # 모든 EmptyPanel을 좌클릭 했을 때 승리한 경우를 처리하는 함수로, reset_button의 이미지를 sunglasses로 변경.
        self.reset_button.config(image = self.img_sunglasses)

    def left_click(self, r, c): # 버튼 리스트의 각 버튼 좌클릭에 바인드 되는 메서드. 좌클릭한 버튼이 MinePanel이면 패배, EmptyPanel이면 unveil()하는데, unveil()이후 몇개의 패널이 밝혀질지 알 수 없으므로 전체 보드를 순회하면서 그에 맞게 버튼을 변경함. 모든 패널을 밝혔을 때 승리.
        # print("l" + str(r) + str(c))
        if self.board.checkReveal(r, c):
            pass
        else:
            if self.board.checkFlag(r, c):
                pass
            elif self.board.checkMine(r, c):
                self.board.unveil(r, c)
                self.defeat()
            else:
                self.board.unveil(r, c)
                for j in range(self.width):
                    for i in range(self.height):
                        # 만약 플래그를 둔 칸 주변에 지뢰가 없어서 한번에 연속해서 밝혀지는 상황이라면, 플래그가 제거된다.
                        if self.board.checkFlag(j, i) and self.board.checkReveal(j, i): self.button_list[j][i].config(image = '', state=tk.DISABLED, relief=tk.SUNKEN)

                        if self.board.checkReveal(j, i) and not self.board.checkMine(j, i):
                            if self.board.getNumOfNearMines(j, i) == 0:
                                self.button_list[j][i].config(text = '', state=tk.DISABLED, relief=tk.SUNKEN)
                            else: self.button_list[j][i].config(text = self.board.getNumOfNearMines(j, i), state=tk.DISABLED, relief=tk.SUNKEN)
                if self.board.getNumOfRevealedPanels() == self.height * self.width - self.num_mines: self.victory()

    def right_click(self, r, c): # 버튼 리스트의 각 버튼이 우클릭 되었을 때 실행되는 메서드로, 플래그를 토글하고, 플래그가 있으면 플래그 이미지를, 없으면 빈칸으로 변경.
        # print("r" + str(r) + str(c))
        if self.board.checkReveal(r, c):
            pass
        else:
            self.board.panels[r][c].toggleFlag()
            if self.board.checkFlag(r, c):
                self.button_list[r][c].config(image = self.img_flag)
            else:
                self.button_list[r][c].config(image = "")

if __name__ == '__main__':
    root = tk.Tk()
    app = App(root)
    app.mainloop() # GUI를 실행하는 메서드