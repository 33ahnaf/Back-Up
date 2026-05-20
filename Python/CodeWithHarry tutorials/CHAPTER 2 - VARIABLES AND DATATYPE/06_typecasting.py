int_a = 24
float_a = float(int_a)
print("int_a: ", int_a)
print("float_a: " + str(float_a))

float_b = 3.14
int_b = int(float_b)
print("float_b: " + str(float_b))
print("int_b: " + str(int_b))

str_c = "31.23"
float_c = float(str_c)
int_c = int(float(str_c))
print("str_c: " + str_c)
print("float_c: " + str(float_c))
print("int_c: " + str(int_c))

# We have to use str() function to convert anything to string before printing, like this --> print("The value of a is: " + str(a) )
#                                                               or we can simply do this --> print(f"The value of a is: {a}")
#                                                               or we can simply do this --> print("The value of a is: ", a)
#                                                                          not like this --> print("The value of a is: " + a)  X
#                                           Remember "+" sign only connect strings not str + int. That's why we use "," sign insteed.

# We can do this typecasting: str --> float
# We can't do this typecasting: str --> int  X
# We can do this insteed:       str --> float --> int

a = True
int_a = int(a) # valid
float_a = float(a) # valid
print(int_a)
print(float_a)

# Remember 0 is False and any non-zero value is True
a = -24
b = 3.1415
bool_a = bool(a) # valid
bool_b = bool(b) # valid
print(bool_a)
print(bool_b)

str_a = "Ahnaf" # this is a non-zero value
bool_a = bool(str_a) # valid
print(bool_a) # output --> True

str_a = "0" # this is a non-zero value
bool_a = bool(str_a) # valid
print(bool_a) # output --> True