class Employee:
    def __init__(self): # will only print "Constructor of Employee".
        print("Constructor of Employee")
    a = 1

class Coder(Employee):
    def __init__(self): # will print Employee's __init__() then "Constructor of Coder".
        super().__init__()
        print("Constructor of Coder")
    b = 2

class Programmer(Coder):
    def __init__(self): # will print Coder's __init__() then "Constructor of Programmer".
        super().__init__()
        print("Constructor of Programmer")
    c = 3

o1 = Employee()
# print(o1.a) # we can only print a as Employee only contain a.

o2 = Coder()
# print(o2.a, o2.b) # we can only print a and b as Coder only contain a and b.

o3 = Programmer()
# print(o3.a, o3.b, o3.c) # we can print a, b and c as Programmer contain them all.