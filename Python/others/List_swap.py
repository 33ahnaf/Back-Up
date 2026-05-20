def reverse(eg_list):
    x = int(len(eg_list) / 2)
    i = 0
    for i in range(x):
        temp = eg_list[i]
        eg_list[i] = eg_list[len(eg_list) - i - 1]
        eg_list[len(eg_list) - i - 1] = temp


list = [1, 2, 3, 4, 5, 6, 7]
print(f"List = {list}")
reverse(list)
print(f"List = {list}")
