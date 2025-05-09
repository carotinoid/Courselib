# import pytest

# import assn2
# from assn2 import game_state_init, game_state_load, game_state_save

# # TODO: test all accessor functions!


# def test_game_state_init():
#     score_list = game_state_init()
#     assert score_list == [
#         [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
#         [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
#     ]


# @pytest.mark.parametrize("path", ["test1.txt", "test_valid_transposed.txt"])
# def test_game_state_load(path):
#     score_list, code = game_state_load(path)
#     assert score_list == [
#         [-1, -1, 6, -1, -1, 18, -1, -1, -1, 15, 30, 50],
#         [-1, -1, -1, 8, 10, 24, 21, 26, -1, -1, -1, -1],
#     ]
#     assert code == assn2.LOAD_SUCCESS


# def test_game_state_load_nonexistant():
#     score_list, code = game_state_load("nonexists.txt")
#     assert code == assn2.LOAD_FAIL_FILE_NOTFOUND


# @pytest.mark.parametrize(
#     "path",
#     [
#         "test_w1.txt",
#         "test_w2.txt",
#         "test_fives_invalid_range.txt",
#         "test_invalid_c.txt",
#         "test_invalid_4k.txt",
#         "test_invalid_fh.txt",
#         "test_invalid_ss.txt",
#         "test_invalid_ls.txt",
#         "test_invalid_yacht.txt",
#         "test_invalid_transposed_unknown_sel.txt",
#         "test_invalid_turn_idx_not_matching.txt",
#     ],
# )
# def test_game_state_load_invalid_score(path):
#     score_list, code = game_state_load(path)
#     assert code == assn2.LOAD_FAIL_INVALID_FORMAT


# def test_game_state_save():
#     score_list = [
#         [-1, -1, 6, -1, -1, 18, -1, -1, -1, 15, 30, 50],
#         [-1, -1, -1, 8, 10, 24, 21, 26, -1, -1, -1, -1],
#     ]
#     game_state_save(score_list, "__test_game_state_save__.txt")
#     with open("__test_game_state_save__.txt", "r") as f1:
#         with open("test1.txt", "r") as f2:
#             assert f1.read() == f2.read()
