class Employee:
    company = "Microsoft"
    def __init__(self, name, salary):
        self.name = name
        self.salary = salary
    def show(self):
        print(f"Name: {self.name} and Salary: {self.salary}")

class Coder:
    company = "None"
    language = "C#"
    def __init__(self, name):
        self.name = name
    def showLanguage(self):
        print(f"{self.name}'s favourite language is: {self.language}")

class Programmer(Employee, Coder):
    company = "Open AI"

a = Employee("Ahnaf", 12000)
b = Coder("Ahnaf")
c = Programmer("Ahnaf", 12000) # Note: "Employee" takes two arguments(name and salary) and "Coder" takes only one argument(name) but "Programmer" takes two arguments(name and salary) as "Employee" because in the class "Programmer", it is inheritated with "Employee" and "Coder" like this --> class Programmer (Employee, Coder) --> notice something? "Employee" is in the first and "Coder" is in the second, that's why "Employee" is more important according to the program.

print(a.company, b.company, c.company)

a.show()
b.showLanguage()
c.show()
c.showLanguage()