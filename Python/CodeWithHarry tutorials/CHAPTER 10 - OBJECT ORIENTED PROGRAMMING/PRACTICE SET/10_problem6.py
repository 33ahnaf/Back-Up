class Student:
    def __init__(sl, name, grade, roll):
        sl.name = name
        sl.grade = grade
        sl.roll = roll
    
    def getInfo(sl):
        print(f"{sl.name} study in class {sl.grade} and his/her roll is: {sl.roll}")

me = Student("Ahnaf", "VI", 4)
me.getInfo()