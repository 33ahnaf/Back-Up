# "type definition" or "type hint" is used to say which type of variable is this. syntax -->> VariableName: Type = Value
# Note: "type definition" or "type hint" only help us to understand what type of variable is this, but it does not define a variable's type like C/C++

n: int = 5

name: str = "Ahnaf"


def sum(a: int, b: int) -> int: # only help us to understand which type of of value it inputs and returns.
    return int(a+b)

a = 5.3
b = 7.2
print(sum(a, b))