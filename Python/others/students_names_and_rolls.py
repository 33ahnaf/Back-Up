students = ("Meghna", "Rupto", "Takia", "Ahnaf")
number_of_students = len(students)
i = 0
roll = []
while i < number_of_students:
    roll.append(f"roll{i+1}")
    roll.append(students[i])
    i+=1
print(roll)