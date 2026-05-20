myList = [5, 1, 4, 9, 3]

squaredList = [num**2 for num in myList]

print(myList)
print(squaredList)


print("\n", end="")   # after CodeWithHarry teached me how the upper code works, I wrote the below code with my own RAW creativity. (even I didn't know the code will work! ! !)


friends = ["Ahnaf", "Afrina ?!", "Saad", "Bashirul"]

friends_A = [friend for friend in friends if friend.startswith("A") == True]

print(friends)
print(friends_A)