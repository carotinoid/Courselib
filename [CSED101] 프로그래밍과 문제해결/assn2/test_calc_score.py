import pytest

import assn2
from assn2 import calc_score


def test_aces():
    dice_set = [1, 1, 1, 1, 4]
    score = calc_score(dice_set, "1")
    assert score == 4


def test_deuces():
    dice_set = [2, 2, 2, 3, 6]
    score = calc_score(dice_set, "2")
    assert score == 6


def test_threes():
    dice_set = [1, 3, 3, 3, 5]
    score = calc_score(dice_set, "3")
    assert score == 9


def test_fours():
    dice_set = [1, 1, 1, 4, 4]
    score = calc_score(dice_set, "4")
    assert score == 8


def test_fives():
    dice_set = [2, 3, 4, 5, 6]
    score = calc_score(dice_set, "5")
    assert score == 5


def test_sixes():
    dice_set = [2, 3, 6, 6, 6]
    score = calc_score(dice_set, "6")
    assert score == 18


def test_choice():
    dice_set = [1, 1, 2, 5, 5]
    score = calc_score(dice_set, "C")
    assert score == 14


def test_4k():
    dice_set = [5, 5, 5, 5, 6]
    score = calc_score(dice_set, "4K")
    assert score == 26


def test_4k_zero():
    dice_set = [1, 1, 2, 2, 2]
    score = calc_score(dice_set, "4K")
    assert score == 0


def test_full_house():
    dice_set = [5, 5, 6, 6, 6]
    score = calc_score(dice_set, "FH")
    assert score == 28


def test_full_house_all_eq():
    dice_set = [6, 6, 6, 6, 6]
    score = calc_score(dice_set, "FH")
    assert score == 30


def test_full_house_zero():
    dice_set = [1, 2, 3, 3, 3]
    score = calc_score(dice_set, "FH")
    assert score == 0


def test_small_straight():
    dice_set = [1, 3, 4, 5, 6]
    score = calc_score(dice_set, "SS")
    assert score == 15


def test_small_straight_dups():
    dice_set = [1, 2, 2, 3, 4]
    score = calc_score(dice_set, "SS")
    assert score == 15


def test_small_straight_zero():
    dice_set = [2, 3, 3, 5, 6]
    score = calc_score(dice_set, "SS")
    assert score == 0


def test_small_straight_zero2():
    dice_set = [1, 2, 3, 5, 6]
    score = calc_score(dice_set, "SS")
    assert score == 0


def test_small_straight_zero_dups():
    dice_set = [1, 1, 3, 5, 6]
    score = calc_score(dice_set, "SS")
    assert score == 0


def test_small_straight_zero_dups_at_end():
    dice_set = [2, 3, 4, 6, 6]
    score = calc_score(dice_set, "SS")
    assert score == 0


def test_large_straight():
    dice_set = [1, 2, 3, 4, 5]
    score = calc_score(dice_set, "LS")
    assert score == 30


def test_large_straight_zero():
    dice_set = [1, 1, 2, 2, 2]
    score = calc_score(dice_set, "LS")
    assert score == 0


def test_yacht():
    dice_set = [1, 1, 1, 1, 1]
    score = calc_score(dice_set, "Y")
    assert score == 50


def test_yacht_zero():
    dice_set = [1, 1, 1, 1, 4]
    score = calc_score(dice_set, "Y")
    assert score == 0
