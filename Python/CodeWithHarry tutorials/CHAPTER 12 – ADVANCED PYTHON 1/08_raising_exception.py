a = int(input("Enter: "))
b = int(input("Enter: "))

if b == 0:
    raise ZeroDivisionError("Undefined!")  # error raising is like custom-error. :D
else:
    print(f"a/b = {a/b}")