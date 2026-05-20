def greatest_of_three(num1, num2, num3):
    if num1 > num2 and num1 > num3:
        return num1
    elif num2 > num1 and num2 > num3:
        return num2
    elif num3 > num1 and num3 > num2:
        return num3
    elif num1 == num2 == num3:
        return num2

num1 = int(input("Enter a number: "))
num2 = int(input("Enter a number: "))
num3 = int(input("Enter a number: "))

print(f"The greatest number is: {greatest_of_three(num1, num2, num3)}")