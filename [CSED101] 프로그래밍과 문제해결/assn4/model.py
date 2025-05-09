###########################################
#
#   model.py : Board 클래스를 정의하는 파일
#
###########################################

import random

class Panel:
    def __init__(self):
        self.isRevealed = False # 패널이 밝혀졌는지 나타내는 변수
        self.hasFlag = False # 플래그가 있는지 나타내는 변수

    def toggleFlag(self): # 플래그를 토글하는 메서드
        if self.hasFlag: self.hasFlag = False
        else: self.hasFlag = True

    def unveil(self): # 해당 panel을 밝혀진 상태로 변경하는 메서드
        self.isRevealed = True


class EmptyPanel(Panel):
    def __init__(self):
        super().__init__()
        self.numOfNearMines = 0 # 근처 지뢰 개수

    def addNumOfNearMines(self): # 근처 지뢰 개수를 1 증가시키는 메서드
        self.numOfNearMines += 1

    def unveil(self): # 해당 panel을 밝혀진 상태로 변경하고, 근처 지뢰 개수를 반환하는 메서드
        super().unveil()
        # self.isRevealed = True
        return self.numOfNearMines


class MinePanel(Panel):
    def __init__(self): #
        super().__init__()

    def unveil(self): # 해당 panel을 밝혀진 상태로 변경하고, -1을 반환하는 메서드
        super().unveil()
        # self.isRevealed = True
        return -1


class Board:
    def reset(self, numMine, height, width): # Board를 초기화하는 메서드
        self.oneDimPanels = [EmptyPanel() for _ in range(height * width)]
        for i in range(numMine): self.oneDimPanels[i] = MinePanel()
        random.shuffle(self.oneDimPanels)
        self.panels = [[self.oneDimPanels[j * width + i] for i in range(width)] for j in range(height)] # panels 변수에 2차원 배열 형태로 패널들을 저장

        for j in range(height):
            for i in range(width):
                if isinstance(self.panels[j][i], MinePanel):
                    for y in range(j - 1, j + 2):
                        for x in range(i - 1, i + 2):
                            if 0 <= y < height and 0 <= x < width and isinstance(self.panels[y][x], EmptyPanel):
                                self.panels[y][x].addNumOfNearMines()

    def getNumOfRevealedPanels(self): # 현재 밝혀져 있는 panel의 개수를 반환하는 메서드
        self.numofRevealedPanels = 0
        for row in self.panels:
            for panel in row:
                if panel.isRevealed: self.numofRevealedPanels += 1
        return self.numofRevealedPanels

    # x행 y열에 위치한 panel을 밝히는 메서드. 이때 x와 y는 zero-based index임. 이하 모든 메서드에서도 마찬가지. unveil 메서드를 실행한 패널이 근처에 지뢰가 없는 empty panel이면, 근처 8칸에 대해 재귀적으로 unveil 메서드를 실행함.
    def unveil(self, y, x):
        value = self.panels[y][x].unveil()
        if value == -1: return -1
        elif value == 0:
            for j in range(y - 1, y + 2):
                for i in range(x - 1, x + 2):
                    if 0 <= j < len(self.panels) and 0 <= i < len(self.panels[0]) and not self.panels[j][i].isRevealed:
                        self.unveil(j, i)

    def toggleFlag(self, y, x): # x행 y열에 위치한 panel의 플래그를 토글하는 메서드.
        self.panels[y][x].toggleFlag()

    def checkReveal(self, y, x): # x행 y열에 위치한 panel이 밝혀졌는지 확인하는 메서드
        return self.panels[y][x].isRevealed

    def checkFlag(self, y, x): # x행 y열에 위치한 panel에 플래그가 있는지 확인하는 메서드
        return self.panels[y][x].hasFlag

    def checkMine(self, y, x): # x행 y열에 위치한 panel이 지뢰인지 확인하는 메서드
        return isinstance(self.panels[y][x], MinePanel)

    def getNumOfNearMines(self, y, x): # x행 y열에 위치한 panel의 근처 지뢰 개수를 반환하는 메서드
        return self.panels[y][x].numOfNearMines