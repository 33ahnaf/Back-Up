nums = [34, 23, 45, 15, 20]

def is_divisible_by_5(n):
    if n % 5 == 0:
        return True
    return False

divisible_by_5 = filter(is_divisible_by_5, nums)
print(list(divisible_by_5))