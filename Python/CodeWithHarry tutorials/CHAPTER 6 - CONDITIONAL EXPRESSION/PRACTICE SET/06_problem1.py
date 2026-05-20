num1 = int(input("Enter number 1: "))
num2 = int(input("Enter number 2: "))
num3 = int(input("Enter number 3: "))
num4 = int(input("Enter number 4: "))

if(num1 > num2 and num1 > num3 and num1 > num4):
    print("Num 1 is the greatest.")
elif(num2 > num1 and num2 > num3 and num2 > num4):
    print("Num 2 is the greatest.")
elif(num3 > num1 and num3 > num2 and num3 > num4):
    print("Num 3 is the greatest.")
elif(num4 > num1 and num4 > num2 and num4 > num3):
    print("Num 4 is the greatest.")
else:
    print("All the numbers are equal.")