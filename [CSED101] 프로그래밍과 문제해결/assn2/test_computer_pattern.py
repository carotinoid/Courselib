from assn2 import computer_pattern

def game_state_init():
    return [[''] * 12] * 2

def test_fives():
    # 5 선택시 15점, C == 19 -> 5 선택이 제일 유리
    score_list = game_state_init()
    dice_set = [5, 3, 5, 1, 5]
    sel, reroll_list = computer_pattern(dice_set, score_list)
    assert sel == "5"
    assert reroll_list == [2, 4]


def test_fives_score_list_filled():
    score_list = game_state_init()
    score_list[1][4] = 10
    dice_set = [5, 3, 5, 1, 5]
    # 위와 같은 상황이나 5 선택 불가 -> 3 선택해야 함
    sel, reroll_list = computer_pattern(dice_set, score_list)
    assert sel == "3"
    assert reroll_list == [1, 3, 4, 5]


def test_c():
    score_list = game_state_init()
    # C - 20점으로 C 선택해야 함
    dice_set = [5, 3, 5, 2, 5]
    sel, reroll_list = computer_pattern(dice_set, score_list)
    assert sel == "C"
    assert reroll_list == [2, 4]


def test_two_same():
    score_list = game_state_init()
    # C와 4K가 모두 22점 -> 둘중 하나 임의로 선택
    dice_set = [5, 2, 5, 5, 5]
    sel, reroll_list = computer_pattern(dice_set, score_list)
    assert sel in ("C", "4K")
    if sel == "C":
        assert reroll_list == [2]
    else:
        assert reroll_list == []


def test_yacht():
    score_list = game_state_init()
    dice_set = [6, 6, 6, 6, 6]
    sel, reroll_list = computer_pattern(dice_set, score_list)
    assert sel == "Y"
    assert reroll_list == []
