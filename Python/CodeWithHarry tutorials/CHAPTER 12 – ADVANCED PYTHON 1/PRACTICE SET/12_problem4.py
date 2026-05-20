try:
    a = int(input("Enter: "))
    b = int(input("Enter: "))
    print(f"a/b = {a/b}")
except ZeroDivisionError:
    print("Can't divide by zero!\t(Undefined)")