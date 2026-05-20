class Employee:
    language = "Assembly"
    salary = 12000

    def __init__(self, name, language, salary): # this is a dunder method which is automatically called.
        print("I'm creating a object")
        self.name = name
        self.language = language
        self.salary = salary
    
    def getInfo(self):
        print(f"Name: {self.name}\nSalary: {self.salary}\nLanguage: {self.language}")


ahnaf = Employee("Ahnaf", "C++", 16000)
ahnaf.getInfo()