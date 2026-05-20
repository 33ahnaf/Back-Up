f = open("F:/VS Code Projects/Python Projects/CHAPTER_9/01_file.txt", "r") # Note: open("file.txt") is same as open("file.txt", "r") because read is by default parameter.
data = f.read()
print(data)
f.close()