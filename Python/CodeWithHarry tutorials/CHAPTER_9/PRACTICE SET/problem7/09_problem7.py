with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem7/09_problem7.txt") as f:
    lines = f.readlines()

for i in range(0, len(lines)):
    if "python" in lines[i]:
        print(f"Line: {i+1} = TRUE")
    else:
        print(f"Line: {i+1} = FALSE")