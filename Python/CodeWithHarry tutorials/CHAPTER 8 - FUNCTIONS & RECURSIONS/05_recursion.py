'''
1! = 1                  = 1
2! = 2 X 1              = 2
3! = 3 X 2 X 1          = 6
4! = 4 X 3 X 2 X 1      = 24
5! = 5 X 4 X 3 X 2 X 1  = 120

n! = n X (n-1)!

'''

def factorial(n):
    if n == 1 or n == 0:
        return 1
    else:
        return n * factorial(n-1)

num = int(input("Enter a number: "))
print(f"{num}! = {factorial(num)}")