if (   n := int(input("Enter: "))   ) > 100: # walrus operator assigns the value even if it's in if-elif-else or something else.
    print("n > 100")
else:
    print("!(n > 100)")

print(f"n = {n}")