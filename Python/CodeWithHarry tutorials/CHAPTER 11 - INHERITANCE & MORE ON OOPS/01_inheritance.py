class Employee:
    company = "Microsoft"
    def show(self):
        print(f"Name: {self.name} and Salary: {self.salary}")

# class Programmer:
#     company = "Open AI"
#     def show(self):
#         print(f"Name: {self.name} and Salary: {self.salary}")
    
#     def showLanguage(self):
#         print(f"{self.name}'s favourite language is: {self.language}")

class Programmer(Employee):
    company = "Open AI"
    def showLanguage(self):
        print(f"{self.name}'s favourite language is: {self.language}")

# Note: By doing the upper thingy we can inheritate "Programmer" with "Employee". What is inheritance, you ask? Inheritance means now "Programmer" will contain all the things that "Employee" contains. If we update the things in "Employee" then it will also update that things in "Programmer". However we can change or add some thing(s) in "Programmer" like the above thing: company = "Open AI"
# The type of "Employee" classes are called "Base/Parent Class" and the type of "Programmer" classes are called "Derived/Child Class".

a = Employee()
b = Programmer()

print(a.company, b.company)