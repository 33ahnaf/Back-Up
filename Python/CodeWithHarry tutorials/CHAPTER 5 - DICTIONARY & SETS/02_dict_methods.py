marks = {
    "Ahnaf": 99,
    "Afrina": 99,
    "Saad": 95,
    "Pi": 3.1415,
    "even_nums": [2, 4, 6, 8, 10, 12],
    0: "Harry"
}

print(marks.items())

print(marks.keys())

print(marks.values())


marks.update({"Ahnaf": 97, "Hasin": 88}) # update() function updates a key's value and if the key is not present then it also append.


print(marks.items())


print(marks.get("Ahnaf")) # Same as print(marks["Ahnaf"]) but if we write this --> print(marks["Ahnaf2"]) then we will get an error.
#                                                         but if we write this --> print(marks.get("Ahnaf2")) then it will print "None" instead of throwing an error.