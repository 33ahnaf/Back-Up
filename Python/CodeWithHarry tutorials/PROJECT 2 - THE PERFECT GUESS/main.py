from random import randint

print("Welcome to, The Purfect Guess")
print("-----------------------------")

random_num = randint(1, 100)

user_input_num = int(input("Enter a number to start the game: "))

number_of_guesses = 1

while(random_num != user_input_num):
    if random_num > user_input_num:
        print(f"The number is higher than {user_input_num}")
        user_input_num = int(input("Enter: "))
        number_of_guesses += 1
    elif user_input_num > random_num:
        print(f"The number is lower than {user_input_num}")
        user_input_num = int(input("Enter: "))
        number_of_guesses += 1

print("You guessed the number correctly!")
print("---------------------------------")
print(f"Number of guesses: {number_of_guesses}")