try:
    with open("file1.txt", "r") as f1:
        print(f1.read())
except Exception as e1:
    print(e1)

try:
    with open("file1.txt", "r") as f2:
        print(f2.read())
except Exception as e2:
    print(e2)

try:
    with open("file1.txt", "r") as f3:
        print(f3.read())
except Exception as e3:
    print(e3)

print("The program failed successfully!")