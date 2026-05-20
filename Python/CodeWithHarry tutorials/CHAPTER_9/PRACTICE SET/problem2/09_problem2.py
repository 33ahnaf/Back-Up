import random

def game():
    random_int = random.randint(1, 100)
    print(f"Your score: {random_int}")
    return random_int

with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem2/09_problem2(Hi-score.txt).txt") as f:
    data = f.read()

hi_score = game()

if data == "" or int(data) < hi_score:
    with open("F:/VS Code Projects/Python Projects/CHAPTER_9/PRACTICE SET/problem2/09_problem2(Hi-score.txt).txt", "w") as f:
        f.write(str(hi_score))