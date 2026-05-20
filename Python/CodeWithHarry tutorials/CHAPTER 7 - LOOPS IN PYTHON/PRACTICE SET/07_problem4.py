num = int(input("Enter a number: "))
is_prime = False

if(num == 0 or num == 1):
    is_prime = False
elif(num == 2):
    is_prime = True
else:
    for i in range(2, num):
        if(num % i == 0):
            is_prime = False
            break
        else:
            is_prime = True


if(is_prime):
    print(f"{num} is a prime number.")
else:
    print(f"{num} is not a prime number.")