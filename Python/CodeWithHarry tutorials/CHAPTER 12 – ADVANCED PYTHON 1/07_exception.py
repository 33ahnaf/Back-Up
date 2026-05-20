try:
    a = int(input("Enter a integer: "))
    print(f"a = {a}")

except Exception as OUR_exception:
    print(f"\n{OUR_exception}\n")

print("Thank you for using OUR program!")

# there are a lotta error types, like "ValueError", "ZeroDivisionError" and we can also do something for a specific error like below:

# except ZeroDivisionError as zde:
#     print("This is a ZeroDivisionError!")

# or another one like below:

# except ValueError as ve:
#     print("This is a value error!")