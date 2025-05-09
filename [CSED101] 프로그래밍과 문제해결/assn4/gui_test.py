import tkinter as tk

BTN_WIDTH = 30
BTN_HEIGHT = 30
BORDER_SIZE = 2
OUTTER_PADDING_SIZE = 10
BACKGROUND_COLOR = "#DCDCDC"


def get_size(origin_size, border_size, padding_size):
    return origin_size + border_size * (2 + 1) + padding_size * (2 + 1)


class App(tk.Frame):
    def __init__(self, master, title, height, width):
        super(App, self).__init__(master)
        master.title(title)

        master.geometry(
            f"{width * (BTN_WIDTH) + (OUTTER_PADDING_SIZE + BORDER_SIZE) * 2}x{(height + 1) * (BTN_HEIGHT) + (OUTTER_PADDING_SIZE + BORDER_SIZE) * 5}")

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

        head = tk.Frame(self, bg=BACKGROUND_COLOR,
                        relief=tk.SUNKEN, bd=BORDER_SIZE)
        head.grid(row=0, column=0, columnspan=width,
                  pady=(0, OUTTER_PADDING_SIZE), sticky='ew')
        start_wrapper = tk.Frame(head, width=BTN_WIDTH, height=BTN_HEIGHT)
        start_wrapper.pack_propagate(0)
        start_wrapper.pack(padx=OUTTER_PADDING_SIZE, pady=OUTTER_PADDING_SIZE)
        start = tk.Button(start_wrapper, image=self.base_icon, bd=BORDER_SIZE)
        start.pack(expand=True, fill='both')

        body = tk.Frame(self, bg=BACKGROUND_COLOR,
                        relief=tk.SUNKEN, bd=BORDER_SIZE)
        body.grid(row=1, column=0, columnspan=width)

        def onLeftClick(y, x):
            print(f"Left Click at {y}, {x}")

        def onRightClick(y, x):
            print(f"Right Click at {y}, {x}")

        w = width
        h = height
        for row in range(h):
            for col in range(w):
                btn_wrapper = tk.Frame(
                    body, width=BTN_WIDTH, height=BTN_HEIGHT)
                btn_wrapper.pack_propagate(0)
                btn_wrapper.grid(row=row, column=col)

                btn = tk.Button(
                    btn_wrapper, bg=BACKGROUND_COLOR, bd=BORDER_SIZE)
                btn.bind("<ButtonRelease-1>", lambda e,
                         y=row, x=col: onLeftClick(y, x))
                btn.bind("<ButtonRelease-3>", lambda e,
                         y=row, x=col: onRightClick(y, x))
                if col % 2 == 0:
                    btn["background"] = BACKGROUND_COLOR
                    btn["relief"] = tk.GROOVE
                    if row % 2 == 0:
                        btn["image"] = self.bomb_icon
                    else:
                        btn["text"] = "4"
                        btn["font"] = ("Arial", 15, "bold")
                        btn["foreground"] = "orange"
                else:
                    if row % 2 == 1:
                        btn["image"] = self.flag_icon
                btn.pack(expand=True, fill='both')
        self.pack()


if __name__ == '__main__':
    TITLE = "Minesweeper"
    HEIGHT = 10
    WIDTH = 10

    root = tk.Tk()
    app = App(root, TITLE, HEIGHT, WIDTH)
    app.mainloop()
