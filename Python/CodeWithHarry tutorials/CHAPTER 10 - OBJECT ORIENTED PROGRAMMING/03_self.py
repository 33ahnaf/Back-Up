class Employee:
    language = "Assembly"
    salary = 12000
    def getInfo(self):
        print(f"The language is: {self.language} and the salary is: {self.salary}")
    
    def greet_using_self(self):
        print("Good morning!")
    
    @staticmethod                   # decorator to mark a function as a static method.
    def greet_using_staticmethod():
        print("Good morning!")

ahnaf = Employee()
ahnaf.name = "Ahnaf"
ahnaf.getInfo()
ahnaf.language = "C++"
print(ahnaf.language, ahnaf.salary, ahnaf.name)

ahnaf.getInfo()
# converts to Employee.getInfo(ahnaf)
Employee.greet_using_self(ahnaf)
ahnaf.greet_using_self()

ahnaf.greet_using_staticmethod() # no need to use self