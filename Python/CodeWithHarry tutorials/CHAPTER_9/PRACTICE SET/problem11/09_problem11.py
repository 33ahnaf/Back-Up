with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem11/09_problem11.txt") as f1:
    content = f1.read()

with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem11/renamed_by_python.txt", "w") as f2:
    f2.write(content)

# Note: To rename a file we have to copy a file and paste that in a file that made by the program and then delete the old file which we copyed from. (to delete a file we have to use the "os" module but we are doing that manualy now, because we don't know how to use "os" module right now.)