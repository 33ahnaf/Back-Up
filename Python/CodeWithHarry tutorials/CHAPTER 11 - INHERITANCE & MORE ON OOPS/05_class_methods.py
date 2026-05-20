class Employee:
    a = 3
    @classmethod
    def show(cls):
        print(f"The value of class attribute a is: {cls.a}")

emp = Employee()

emp.a = 45

emp.show()

# without @classmethod    Employee.show(emp)
# with @classmethod       Employee.show(Employee)
#                         Employee.show() --> will throw an error.