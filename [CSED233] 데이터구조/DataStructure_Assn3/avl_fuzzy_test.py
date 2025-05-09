import random
import string
import collections
import subprocess
import shlex
import os

class CaseFailed(Exception):
    pass

def rand_str():
    # generate random string
    # between length 1~100
    inp = ""
    for i in range(random.randrange(1, 100)):
        inp += random.choice(string.ascii_letters)
    inp = inp.lower()
    return inp

def make_testcase(inp) -> tuple[str, str]:
    # create counter
    counter = collections.Counter(inp)

    # generate expected output
    out = "Frequencies of alphabetic letters in the given string\r\n"
    out += ' '.join('({}, {})'.format(c, counter[c]) for c, i in sorted(counter.most_common(), key=lambda pair: (pair[1], ord(pair[0].lower())), reverse=True))

    return inp, out

def run_test(case: tuple[str, str]):
    inp, expected = case

    actual = "(UNKNOWN)"
    try:
        # run program, get output
        proc = subprocess.run(shlex.split(f'./q4.exe {inp}'), stdout=subprocess.PIPE)
        if (proc.returncode != 0):
            raise CaseFailed(f"Process returned error code: {proc.returncode}")
        actual = proc.stdout.decode('utf-8')

        # run assertion
        if (expected + "\r\n" != actual):
            raise CaseFailed("Assertion Failed")

    except CaseFailed as ex:
        print("Failed!")
        print(f"Reason: {ex}")
        print("[Input]")
        print(inp)
        print("[Expected]")
        print(expected)
        print("[Actual]")
        print(actual)
        raise ex

if __name__ == '__main__':
    i = 0
    while True:
        run_test(make_testcase(rand_str()))
        i += 1
        print(i, end='\r')
    # run_test(make_testcase("qykqzxdryxauyfayzrkdgttrdlceefwbq"))