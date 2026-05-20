f1 = open("F:/VS Code Projects/Python Projects/CHAPTER_9/03_file_functions.txt")
lines = f1.readlines()
print(lines)
f1.close()

f2 = open("F:/VS Code Projects/Python Projects/CHAPTER_9/03_file_functions.txt")
line1 = f2.readline()
line2 = f2.readline()
line3 = f2.readline()
line4 = f2.readline()
print(line1)
print(line2)
print(line3)
print(line4)
f2.close()

# using while loop:

f3 = open("F:/VS Code Projects/Python Projects/CHAPTER_9/03_file_functions.txt")
line = f3.readline()
while line != "":
    print(line)
    line = f3.readline()



# Note: The output is like this:
# Ahnaf is a good boy

# He study in class VI

# His dream car is BMW M2

# And his all time favourite car is Koenigsegg Jesko (Carbon Fiber Edition)

# because, all the lines have \n at their end and print() function also adds a \n at the end. (if we do this: print(line, end="") then it would not prints two \n)