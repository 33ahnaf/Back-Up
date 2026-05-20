with open("Tables.txt", "w") as f:
    num = int(input("Enter: "))
    multiplication_table = [num*i for i in range(1, 11)]
    f.write(str(multiplication_table))