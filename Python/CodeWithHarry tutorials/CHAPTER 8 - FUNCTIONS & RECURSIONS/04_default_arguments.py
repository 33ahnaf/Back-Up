def add_5(a, b = 5):
    return a + b

print(f"2 + 7 = {add_5(2, 7)}")
print(f"2 + add_5 = {add_5(2)}")