with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem5/09_problem5.txt") as f1:
    content = f1.read()

list_of_words_to_be_censored = ["Fuck", "LGBTQ+"]

for word_to_be_censored in list_of_words_to_be_censored:
    if word_to_be_censored in content:
        content = content.replace(word_to_be_censored, "#" * len(word_to_be_censored))

with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem5/09_problem5.txt", "w") as f2:
    f2.write(content)