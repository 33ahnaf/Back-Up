class Programmer:
    company = "Microsoft"
    def __init__(self, name, salary, id_No):
        self.name = name
        self.salary = salary
        self.id_No = id_No
    
    def getInfo(self):
        print(f"Name: {self.name}\nCompany: {self.company}\nSalary: {self.salary}\nID No.: {self.id_No}")

ahnaf = Programmer("Md. Ahnaf Shariar", 50000, 2947)
ahnaf.getInfo()