num = int(input("Enter a number: "))

for i in range(1, num+1):
    print(" " * (num-i), end="")
    print("*" * (2*i-1), end="")
    print("")



'''

for n = 3:
  *
 ***
*****

for n = 5:
    *
   ***
  *****
 *******
*********

'''