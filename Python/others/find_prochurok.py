def find_prochurok(list):
    x = 1
    list_of_prochurok = []
    for i in list:              #
        if list.count(i) >= x:  # Finds the highest number of the repeted numbers.
            x = list.count(i)   #
    for j in list:                                              #
        if list.count(j) == x and j not in list_of_prochurok:   # Append numbers to prochurok list if they are.
            list_of_prochurok.append(j)                         #
    return list_of_prochurok    # Return the list of prochurok.


list = []
while(True):
    user_input = input("Enter a number: ")          # Input a number from user.
    if user_input == "end" or user_input == "exit": # Stop taking number(s) if user input is end or exit.
        break
    else:
        input_number = int(user_input)
        list.append(input_number)   # Append user inputed number to list.
list_of_prochurok = find_prochurok(list)
print(f"List of integer(s): {list}")
print(f"Number of integer(s): {len(list)}")
print(f"Prochurok(s): {list_of_prochurok}")