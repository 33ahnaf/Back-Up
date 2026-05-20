try:
    a = int(input("Enter a integer: "))
    print(f"a = {a}")

except Exception as OUR_exception:
    pass # do nothing
else:
    print("Thank you for using OUR program!") # else only run when try is succesful.