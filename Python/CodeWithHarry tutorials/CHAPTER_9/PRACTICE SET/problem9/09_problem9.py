with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem9/09_problem9_1.txt") as f1:
    cnotent_of_file_1 = f1.read()

with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem9/09_problem9_2.txt") as f2:
    cnotent_of_file_2 = f2.read()

if cnotent_of_file_1 == cnotent_of_file_2:
    print("Both are same.")
else:
    print("Both are different.")