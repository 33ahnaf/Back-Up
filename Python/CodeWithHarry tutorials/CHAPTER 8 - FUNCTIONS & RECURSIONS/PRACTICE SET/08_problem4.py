'''
sum(1) = 1
sum(2) = 1 + 2
sum(3) = 1 + 2 + 3
sum(4) = 1 + 2 + 3 + 4
sum(5) = 1 + 2 + 3 + 4 + 5

sum(n) = n + sum(n-1)

'''

def sum(n):
    if n == 0 or n == 1:
        return n
    return n + sum(n-1)

num = int(input("Enter a number: "))

print("Sum of natural numbers:", sum(num))