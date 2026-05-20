def main():
    try:
        a = int(input("Enter a integer: "))
        print(f"a = {a}")
        return

    except Exception as OUR_exception:
        return # do nothing
    finally:
        print("Thank you for using OUR program!") # finally will run at any cost. no matter what.

main()