num = int(input("Enter a number: "))

sum = 1
for i in range(1, num+1):
    sum = sum * i

print(f"{num}! = {sum}")