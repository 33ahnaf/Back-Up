def multiplication_table_of(num):
    for i in range(1, 11):
        print(f"{num} X {i} = {num * i}")

num = int(input("Enter a number: "))

multiplication_table_of(num)