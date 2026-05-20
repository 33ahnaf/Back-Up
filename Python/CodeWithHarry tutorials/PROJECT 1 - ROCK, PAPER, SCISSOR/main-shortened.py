import random

'''
1 --> Rock
2 --> Paper
3 --> Scissor
'''

print("Welcome to rock, paper, scissor game")
print("------------------------------------")
print("1 --> Rock\n2 --> Paper\n3 --> Scissor")

player = int(input("Enter 1 or 2 or 3 to start the game: "))
computer = random.randint(1, 3)

myDict = {1: "Rock", 2: "Paper", 3: "Scissor"}
print(f"You chose: {myDict[player]}\tComputer chose: {myDict[computer]}")

# The below logic is written on the basis of the value of player - computer. (this method can decrease the size of the code, however it also decreases readeblity.)

if player == computer:
    print("-----------------------------------------------")
    print("It's a draw!")
elif (player - computer) == 1 or (player - computer) == -2:
    print("-----------------------------------------------")
    print("You won!")
elif (player - computer) == -1 or (player - computer) == 2:
    print("-----------------------------------------------")
    print("You lose!")
else:
    print("Something went Wrong!")

''' Player - Computer:
It's a draw! --> 0
You won! --> 1, -2
You lose! --> -1, 2
'''