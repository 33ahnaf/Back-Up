class Calculator:
    def __init__(self, num):
        self.num = num
    
    def square(self):
        print(f"The square is: {self.num ** 2}")
    
    def cube(self):
        print(f"The cube is: {self.num ** 3}")
    
    def square_root(self):
        print(f"The square root is: {self.num ** 1/2}")

a = Calculator(9)
a.square()
a.cube()
a.square_root()