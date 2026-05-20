from functools import reduce
nums = [2, 1, 3, 5, 4]


# Map function
square = lambda x : x**2
Squared_Nums = map(square, nums)
print(list(Squared_Nums))


# Filter function
def is_even(n):
    if n % 2 == 0:
        return True
    return False

even_s = filter(is_even, nums)
print(list(even_s))


# Reduce function
def sum(a, b):
    return a+b

sum_of_things = reduce(sum, nums)
print(sum_of_things)