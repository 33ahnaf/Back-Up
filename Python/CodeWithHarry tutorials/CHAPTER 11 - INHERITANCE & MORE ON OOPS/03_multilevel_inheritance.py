class Employee:
    a = 1

class Coder(Employee):
    b = 2

class Programmer(Coder):
    c = 3

o1 = Employee()
print(o1.a) # we can only print a as Employee only contain a.

o2 = Coder()
print(o2.a, o2.b) # we can only print a and b as Coder only contain a and b.

o3 = Programmer()
print(o3.a, o3.b, o3.c) # we can print a, b and c as Programmer contain them all.