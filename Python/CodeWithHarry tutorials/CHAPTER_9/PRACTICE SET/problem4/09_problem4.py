with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem4/09_problem4.txt") as f1:
    data = f1.read()

if "Donkey" in data:
    data = data.replace("Donkey", "######")

with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem4/09_problem4.txt", "w") as f2:
    f2.write(data)