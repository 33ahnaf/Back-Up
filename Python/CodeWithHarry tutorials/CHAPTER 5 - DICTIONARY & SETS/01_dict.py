di = {} # This is an empty dictionary.

marks = {
    "Ahnaf": 97,
    "Afrina": 99,
    "Saad": 98,
    "Pi": 3.1415,
    "even_nums": [2, 4, 6, 8, 10, 12],
    0: "Harry"
}

print(marks, type(marks)) # Simply prints marks then prints type of marks.
print(marks["Afrina"])
print(marks["Ahnaf"])
print(marks["Saad"])
print(marks["even_nums"])
print(marks["Pi"])
print(marks[0])



# Note: Dictionarys are mutable.
#       "Ahnaf": 97 <-- in this "Ahnaf" is called "key" and 97 is called "value"
#       Dictionarys can't contain duplicate keys.