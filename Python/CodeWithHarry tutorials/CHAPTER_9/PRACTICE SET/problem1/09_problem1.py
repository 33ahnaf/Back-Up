with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem1/09_problem1(poems.txt).txt") as f:
    poem = f.read()

    if "twinkle" in poem:
        print("TRUE")
    else:
        print("FALSE")