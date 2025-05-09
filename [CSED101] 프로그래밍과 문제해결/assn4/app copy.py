import tkinter as tk
from model import Board
# import sys
# sys.setrecursionlimit(10000)


TITLE = "Minesweeper"
BTN_WIDTH = 30
BTN_HEIGHT = 30
BORDER_SIZE = 2
OUTTER_PADDING_SIZE = 10
BACKGROUND_COLOR = "#DCDCDC"

class App(tk.Frame):
    def __init__(self, master):
        super(App, self).__init__(master)
        master.title(TITLE)
        self.window = master
        self.board = Board()

        self.height = 10
        self.width = 10
        self.num_mines = 10
        self.first_click = True
        # self.geometry = (self.width * BTN_WIDTH + OUTTER_PADDING_SIZE * 2, self.height * BTN_HEIGHT + OUTTER_PADDING_SIZE * 2)
        # self.window.geometry(str(self.geometry[0]) + "x" + str(self.geometry[1]))

        self.img_bomb = tk.PhotoImage(file="imgs/bomb.png")
        self.img_flag = tk.PhotoImage(file="imgs/flag.png")
        self.img_skull = tk.PhotoImage(file="imgs/skull.png")
        self.img_smile = tk.PhotoImage(file="imgs/smile.png")
        self.img_sunglasses = tk.PhotoImage(file="imgs/sunglasses.png")

        self.board.reset(self.num_mines, self.height, self.width)
        self.setGUI()

    def setGUI(self):
        menu_bar = tk.Menu(self.window)
        self.window.config(menu = menu_bar)
        level_menu = tk.Menu(menu_bar, tearoff = 0)
        menu_bar.add_cascade(label = "난이도", menu = level_menu)
        level_menu.add_command(label = "Easy", command = lambda: self.Easy())
        level_menu.add_command(label = "Normal", command = lambda: self.Normal())
        level_menu.add_command(label = "Hard", command = lambda: self.Hard())


        self.header_frame = tk.Frame(self.window, bg=BACKGROUND_COLOR, relief=tk.SUNKEN, bd=BORDER_SIZE)
        self.header_frame.grid(row=0, column=0, columnspan=self.width, pady=(0, OUTTER_PADDING_SIZE), sticky='ew')
        # self.header_frame.pack(padx = OUTTER_PADDING_SIZE, pady = OUTTER_PADDING_SIZE)
        reset_wrapper = tk.Frame(self.header_frame, width=BTN_WIDTH, height=BTN_HEIGHT)
        reset_wrapper.pack_propagate(0)
        reset_wrapper.pack(padx=OUTTER_PADDING_SIZE, pady=OUTTER_PADDING_SIZE)

        self.reset_button = tk.Button(reset_wrapper, image = self.img_smile)
        self.reset_button.pack()
        self.reset_button.bind("<Button-1>", lambda e: self.board_reset())


        self.body_frame = tk.Frame(self.window, bg=BACKGROUND_COLOR, relief=tk.SUNKEN, bd=BORDER_SIZE)
        self.body_frame.grid(row=1, column=0, columnspan=self.width)
        # self.body_frame.pack(padx = OUTTER_PADDING_SIZE, pady = OUTTER_PADDING_SIZE)
        self.board_reset()

    def board_reset(self):
        self.board.reset(self.num_mines, self.height, self.width)
        self.reset_button.config(image = self.img_smile)
        try:
            for widget in self.body_frame.winfo_children():
                widget.destroy()
        except:
            pass
        self.make_board()
        # btn all unrevealed

    def Easy(self):
        self.num_mines = 10
        self.height = 10
        self.width = 10
        self.first_click = True
        self.board_reset()

    def Normal(self):
        self.num_mines = 30
        self.height = 15
        self.width = 15
        self.first_click = True
        self.board_reset()

    def Hard(self):
        self.num_mines = 50
        self.height = 20
        self.width = 20
        self.first_click = True
        self.board_reset()

    def make_board(self):
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

    def defeat(self):
        # all reveal
        for j in range(self.width):
            for i in range(self.height):
                if self.board.checkMine(j, i):
                    self.button_list[j][i].config(image = self.img_bomb, state=tk.DISABLED, relief=tk.SUNKEN)
                else:
                    if self.board.getNumOfNearMines(j, i) == 0:
                        self.button_list[j][i].config(text = '', state=tk.DISABLED, relief=tk.SUNKEN)
                    else : self.button_list[j][i].config(text = self.board.getNumOfNearMines(j, i), state=tk.DISABLED, relief=tk.SUNKEN)
        self.reset_button.config(image = self.img_skull)

    def victory(self):
        self.reset_button.config(image = self.img_sunglasses)

    def left_click(self, r, c):
        # print("l" + str(r) + str(c))
        if self.first_click:
            while True:
                if self.board.checkMine(r, c):
                    self.board_reset()
                else:
                    self.first_click = False
                    break
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
                        if self.board.checkReveal(j, i) and not self.board.checkMine(j, i):
                            if self.board.getNumOfNearMines(j, i) == 0:
                                self.button_list[j][i].config(text = '', state=tk.DISABLED, relief=tk.SUNKEN)
                            else: self.button_list[j][i].config(text = self.board.getNumOfNearMines(j, i), state=tk.DISABLED, relief=tk.SUNKEN)
        if self.board.getNumOfRevealedPanels() == self.height * self.width - self.num_mines: self.victory()

    def right_click(self, r, c):
        # print("r" + str(r) + str(c))
        if self.board.checkReveal(r, c):
            pass
        else:
            self.toggleFlag(r, c)

    def toggleFlag(self, y, x):
        self.board.panels[y][x].toggleFlag()
        if self.board.checkFlag(y, x):
            self.button_list[y][x].config(image = self.img_flag)
        else:
            self.button_list[y][x].config(image = "")

if __name__ == '__main__':
    root = tk.Tk()
    app = App(root)
    app.mainloop()