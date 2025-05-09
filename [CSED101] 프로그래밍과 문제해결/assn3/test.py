def list2instance(posmon_list):
    posmon = []
    for i in posmon_list:
        instance = globals()[i]()
        posmon.append(instance)
    return posmon

class Exception():
    def __init__(self):
        self.a = 1
    def ab(self):
        print("a")

posmon_list = ["Exception"]
b = list2instance(posmon_list)[0]
b.ab()
for i in list2instance(posmon_list):
    print(i)

try:
    a = int("asdf")
except Exception as e:
    print(e)