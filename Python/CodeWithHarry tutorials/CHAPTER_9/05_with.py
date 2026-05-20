f1 = open("F:/VS Code Projects/Python Projects/CHAPTER_9/05_with.txt")
print(f1.read())
f1.close()

# The upper thing can be done by writing this: (also, we don't have to f.close() )

with open("F:/VS Code Projects/Python Projects/CHAPTER_9/05_with.txt") as f2:
    print(f2.read())