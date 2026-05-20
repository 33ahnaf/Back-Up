with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem3/in_one/09_problem3(multiplication_tables.txt).txt", "a") as f:
    for i in range(2, 21):
        for j in range(1, 11):
            f.write(f"{i} X {j} = {i * j}\n")
        f.write("\n")