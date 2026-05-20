class Employee:
    language = "Assembly" # This a class attribute.
    salary = 12000 # This a class attribute.

ahnaf = Employee()
ahnaf.name = "Ahnaf" # This a object attribute.
print(ahnaf.language, ahnaf.salary, ahnaf.name)

saad = Employee()
saad.name = "Saad" # This a object attribute.
saad.salary = 15000 # Changing class attribute.
print(saad.salary, saad.language, saad.name)

# Here name is object attribute and salary and language are class attributes as they directly belongs to the class.

# Note: object attributes are called instance attributes.