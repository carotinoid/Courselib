class Panel:
    def __init__(self):
        self.isRevealed = False
        self.hasFlag = False

    def toggleFlag(self):
        if self.hasFlag is True:
            self.hasFlag = False
        elif self.hasFlag is False:
            self.hasFlag = True

    def unveil(self):
        self.isRevealed = True



class EmptyPanel(Panel):
    def __init__(self):
        super().__init__()
        self.numOfNearMines = 0
        
    def addNumOfNearMines(self):
        self.numOfNearMines += 1
        
    def unveil(self):
        super().unveil()
        return self.numOfNearMines

class MinePanel(Panel):
    def unveil(self):
        super().unveil()
        return -1


import random

class Board:
    def __init__(self):
        self.width = 0
        self.height = 0
        self.panels = []
    def reset(self, numMine, height, width):
        self.width = width
        self.height = height

        self.panels = [[EmptyPanel() for _ in range(width)] for _ in range(height)]

        # Mine distribution
        mine_positions = random.sample(range(height * width), numMine)
        for position in mine_positions:
            y = position // width
            x = position % width
            self.panels[y][x] = MinePanel()

        #Update numOfNearMines for EmptyPanels
        for y in range(height):
            for x in range(width):
                 if not isinstance(self.panels[y][x], MinePanel):
                    self.update_near_mines(y, x, height, width)
     

    def update_near_mines(self, x, y, height, width):
        if isinstance(self.panels[y][x], EmptyPanel):
            directions = [(dy, dx) for dy in range(-1, 2) for dx in range(-1, 2) if dy != 0 or dx != 0]
            for dy, dx in directions:
                ny, nx = y + dy, x + dx
                if 0 <= ny < height and 0 <= nx < width and not isinstance(self.panels[ny][nx], EmptyPanel):
                    self.panels[y][x].addNumOfNearMines()


    def getNumOfRevealedPanels(self):
        return sum(panel.isRevealed for row in self.panels for panel in row)
        

    def unveil(self, y, x):
        def reveal_panels(y, x):
            if not (0 <= y < len(self.panels)) or not (0 <= x < len(self.panels[0])) or self.panels[y][x].isRevealed:
                return

            if isinstance(self.panels[y][x], MinePanel):
                return -1

            if self.panels[y][x].hasFlag and not isinstance(self.panels[y][x], MinePanel):
                self.panels[y][x].toggleFlag()  # Remove flag if revealed panel is not a mine
                return  # Stop revealing if a flagged non-mine panel is encountered

            self.panels[y][x].unveil()

            if isinstance(self.panels[y][x], EmptyPanel) and self.panels[y][x].numOfNearMines == 0:
                directions = [(dy, dx) for dy in range(-1, 2) for dx in range(-1, 2) if dy != 0 or dx != 0]
                for dy, dx in directions:
                    reveal_panels(y + dy, x + dx)

        reveal_panels(y, x)
        return sum(panel.isRevealed for row in self.panels for panel in row)

        

    def toggleFlag(self, y, x):
        self.panels[y][x].toggleFlag()
    

    def checkReveal(self, y, x):
        return self.panels[y][x].isRevealed
    

    def checkFlag(self, y, x):
        return self.panels[y][x].hasFlag
    

    def checkMine(self, y, x):
        return isinstance(self.panels[y][x], MinePanel)
    

    def getNumOfNearMines(self, y, x):
        return self.panels[y][x].numOfNearMines if isinstance(self.panels[y][x], EmptyPanel) else None
  
