b = 0
while b < 10:
    x = input("Seconds:")
    a = int(x)
    y = a // 60
    z = a % 60
    if y <= 1:
        minute = "minute"
    if y > 1:
        minute = "minutes"
    if z <= 1:
        second = "second"
    if z > 1:
        second = "seconds"
    print(f"{y} {minute} {z} {second}")
    b += 1