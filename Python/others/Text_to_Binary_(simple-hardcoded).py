#  Copyright: ©Ahnaf Shariar 2025
#
#  Code originally wrote 01 January 2025
#  by Md. Ahnaf Shariar
#
#  This example code is in the public domain.

Text_to_Binary_dictonary = {
    "A": 0b00001,
    "B": 0b00010,
    "C": 0b00011,
    "D": 0b00100,
    "E": 0b00101,
    "F": 0b00110,
    "G": 0b00111,
    "H": 0b01000,
    "I": 0b01001,
    "J": 0b01010,
    "K": 0b01011,
    "L": 0b01100,
    "M": 0b01101,
    "N": 0b01110,
    "O": 0b01111,
    "P": 0b10000,
    "Q": 0b10001,
    "R": 0b10010,
    "S": 0b10011,
    "T": 0b10100,
    "U": 0b10101,
    "V": 0b10110,
    "W": 0b10111,
    "X": 0b11000,
    "Y": 0b11001,
    "Z": 0b11010,
    "a": 0b00001,
    "b": 0b00010,
    "c": 0b00011,
    "d": 0b00100,
    "e": 0b00101,
    "f": 0b00110,
    "g": 0b00111,
    "h": 0b01000,
    "i": 0b01001,
    "j": 0b01010,
    "k": 0b01011,
    "l": 0b01100,
    "m": 0b01101,
    "n": 0b01110,
    "o": 0b01111,
    "p": 0b10000,
    "q": 0b10001,
    "r": 0b10010,
    "s": 0b10011,
    "t": 0b10100,
    "u": 0b10101,
    "v": 0b10110,
    "w": 0b10111,
    "x": 0b11000,
    "y": 0b11001,
    "z": 0b11010
} # Create a dictonary for storing the binary values of the alphabet's letters.

user_input_text = input("Enter some text: ") # input the text form user.
valid_character_capital = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]
 # Create a list for storing the valid capital letters.
valid_character_small = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]
 # Create a list for storing the valid small letters.

for character in user_input_text: # loop through all the characters of user_input_text
    if character in valid_character_capital  or  character in valid_character_small: # checks whether the character exists in (valid_character_capital or valid_character_small) or not.
        if character in valid_character_small: # checks whether the character exists in valid_character_small or not.
            print(f"{character} ({valid_character_small.index(character)+1}) -> {Text_to_Binary_dictonary[character]:05b}")
             # if the character exists in valid_character_small then it prints the character then character's serial No and then prints binary value of the character after converting it into normal number.
        elif character in valid_character_capital: # checks whether the character exists in valid_character_capital or not.
            print(f"{character} ({valid_character_capital.index(character)+1}) -> {Text_to_Binary_dictonary[character]:05b}")
             # if the character exists in valid_character_capital then it prints the character then character's serial No and then prints binary value of the character after converting it into normal number.
    elif character == " ": # if character is " "(space) then print "\n"
        print("")
    else: # if the character is not a letter or space then print "Invalid character. . . !" and then prints the character. (then simply... CONTINUE!)
        print(f"Invalid character. . . !\t-> {character}")
        continue