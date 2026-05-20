with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem6/09_problem6(log.txt).txt") as f:
    content = f.read()

if "python" in content:
    print("TRUE")
else:
    print("FALSE")