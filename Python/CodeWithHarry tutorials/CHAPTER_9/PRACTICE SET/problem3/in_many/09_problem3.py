# open(f"F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE_SET/problem3/in_many/tables/table_of_{n}", "w")

for i in range(2, 21):
    with open(f"F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem3/in_many/tables/table_of_{i}", "w") as f:
        for j in range(1, 11):
            f.write(f"{i} X {j} = {i * j}\n")