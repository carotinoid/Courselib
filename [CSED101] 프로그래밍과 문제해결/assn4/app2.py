import tkinter as tk
from model2 import Board

BTN_WIDTH = 30
BTN_HEIGHT = 30
BORDER_SIZE = 2
OUTTER_PADDING_SIZE = 10
BACKGROUND_COLOR = "#DCDCDC"

# def get_size(origin_size, border_size, padding_size):
#     return origin_size + border_size * (2 + 1) + padding_size * (2 + 1)

class App(tk.Frame):
    def __init__(self, master, title, height, width):
        super(App, self).__init__(master)
        master.title(title)

        # master.geometry(
        #     f"{width * (BTN_WIDTH) + (OUTTER_PADDING_SIZE + BORDER_SIZE) * 2}x{(height + 1) * (BTN_HEIGHT) + (OUTTER_PADDING_SIZE + BORDER_SIZE) * 5}")

        self.base_icon = tk.PhotoImage(file="imgs/smile.png")
        self.success_icon = tk.PhotoImage(file="imgs/sunglasses.png")
        self.fail_icon = tk.PhotoImage(file="imgs/skull.png")
        self.flag_icon = tk.PhotoImage(file="imgs/flag.png")
        self.bomb_icon = tk.PhotoImage(file="imgs/bomb.png")

        self["bg"] = BACKGROUND_COLOR
        self["relief"] = tk.SUNKEN
        self["bd"] = BORDER_SIZE
        self["padx"] = OUTTER_PADDING_SIZE
        self["pady"] = OUTTER_PADDING_SIZE
        
        menu_bar = tk.Menu(master)
        master.config(menu =menu_bar)

        level_menu = tk.Menu(menu_bar, tearoff=0)
        menu_bar.add_cascade(label='난이도', menu=level_menu)
        
        # 난이도 메뉴와 기능 추가
        level_menu.add_command(label="Easy", command=lambda: self.reset_board(10,10, 10))
        level_menu.add_command(label="Normal", command=lambda: self.reset_board(30,15, 15))
        level_menu.add_command(label="Hard", command=lambda: self.reset_board(50,20, 20))

        head = tk.Frame(self, bg=BACKGROUND_COLOR,
                        relief=tk.SUNKEN, bd=BORDER_SIZE)
        head.grid(row=0, column=0, columnspan=width,
                  pady=(0, OUTTER_PADDING_SIZE), sticky='ew')
        start_wrapper = tk.Frame(head, width=BTN_WIDTH, height=BTN_HEIGHT)
        start_wrapper.pack_propagate(0)
        start_wrapper.pack(padx=OUTTER_PADDING_SIZE, pady=OUTTER_PADDING_SIZE)
        start = tk.Button(start_wrapper, image=self.base_icon, bd=BORDER_SIZE)
        start.pack(expand=True, fill='both')

        self.body = tk.Frame(self, bg=BACKGROUND_COLOR,
                        relief=tk.SUNKEN, bd=BORDER_SIZE)
        self.body.grid(row=1, column=0, columnspan=width)
        
        
        self.reset_board(10,10,10)
    def reset_board(self, numMine, height, width):
        self.board = Board()
        self.height = height
        self.width = width
        self.numMine =numMine
            
        if self.numMine == 10:
            self.board.reset(numMine=10,height=10,width=10)
            self.make_board(height=10,width=10)
                
        elif self.numMine == 30:
            self.board.reset(numMine=30,height=15,width=15)
            self.make_board(height=15,width=15)
                
        elif self.numMine == 50:
            self.board.reset(numMine=50,height=30,width=30)
            self.make_board(height=30,width=30)
            
            
    def make_board(self, height, width):
        for row in range(height):
            for col in range(width):
                btn_wrapper = tk.Frame(
                    self.body, width=BTN_WIDTH, height=BTN_HEIGHT)
                btn_wrapper.pack_propagate(0)
                btn_wrapper.grid(row=row, column=col)

                btn = tk.Button(
                    btn_wrapper, bg=BACKGROUND_COLOR, bd=BORDER_SIZE)
                btn.bind("<ButtonRelease-1>", lambda e, r=row, c=col: self.onLeftClicky(r, c))
                btn.bind("<ButtonRelease-3>", lambda e, r=row, c=col: self.onRightClicky(r, c))
                    
                panel = self.board.panels[row][col]
                    
                if self.board.checkFlag(row, col):
                    btn.config(image=self.flag_icon)
                # if panel.isRevealed is True:
                #     if isinstance(panel, MinePanel) is True:
                #         btn["image"] = self.bomb_icon

                #     elif isinstance(panel, MinePanel) is False:
                #         if panel.numOfNearMines ==0:
                #             btn["text"] = ""
                #         else:
                #             btn["text"] = str(panel.numOfNearMines)

                            
                # elif panel.isRevealed is False:
                #     if panel.hasFlag is True:
                #         btn["image"] = self.flag_icon

                #     if panel.hasFlag is False:
                #         btn["text"] = ""

                btn.pack(expand=True, fill='both')
        self.pack()
        
        
        #if self.onLeftClicky(self,row,col) == 100:
        #    make_board(self, height, width)
            
        #elif self.onRightClicky(self,row,col) == 100:
        #    make_board(self, height, width)
            
    def onLeftClicky(self,row,col):
        panel = self.board.panels[row][col]
        if not panel.isRevealed:
            panel.unveil()
            if panel.hasFlag:
                panel.toggleFlag()
            if isinstance(panel, MinePanel):
                self.game_over()
            else:
                if isinstance(panel, EmptyPanel) and panel.numOfNearMines == 0:
                    self.unveil_empty_panels_around(row, col)
                    
        return 100
                       
    def onRightClicky(self,row,col):
        panel = self.board.panels[row][col]
        if not panel.isRevealed:
            panel.toggleFlag()
        self.make_board(self.height, self.width)
        return 100
        
        
        
    def unveil_empty_panels_around(self, row, col):
        directions = [
            (-1, -1), (-1, 0), (-1, 1),
            (0, -1),           (0, 1),
            (1, -1), (1, 0), (1, 1)
        ]

       # def reveal_panels(row, col):
            # 각 방향의 주변 패널을 확인하고 오픈
        for d_row, d_col in directions:
            new_row, new_col = row + d_row, col + d_col
            if 0 <= new_row < self.height and 0 <= new_col < self.width:
                panel = self.board.panels[new_row][new_col]
                if not panel.isRevealed and not panel.hasFlag:
                    panel.unveil()
                    if isinstance(panel, EmptyPanel) and panel.numOfNearMines == 0:
                        self.board.reveal_panels(new_row, new_col)

#         reveal_panels(row, col)
            
                
        
    

    def game_over(self):
        for row in range(self.height):
             for col in range(self.width):
                panel = self.board.panels[row][col]
                panel.unveil()
            
        
     

if __name__ == '__main__':
    TITLE = "Minesweeper"
    HEIGHT = 10
    WIDTH = 10

    root = tk.Tk()
    app = App(root, TITLE, HEIGHT, WIDTH)
    app.mainloop()