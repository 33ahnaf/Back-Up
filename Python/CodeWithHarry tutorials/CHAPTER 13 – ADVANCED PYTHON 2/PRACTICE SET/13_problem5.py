from functools import reduce

nums = [1, 4, 2, 5, 9, 5, 7]

def compare_2D(a, b):
    if a > b:
        return a
    elif b > a:
        return b
    elif a == b:
        return a

greatest = reduce(compare_2D, nums)
print(greatest)