def pattern(n):
    if n == 0:
        print("Invalid option!")
        return # return is kinda break of functions.

    if n == 1:
        print("*")
    else:
        print("*" * n)
        pattern(n-1)

n = int(input("Enter a number: "))

pattern(n)