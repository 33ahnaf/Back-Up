name = input("Enter name: ")
marks = int(input("Enter mark: "))
phone_number = int(input("Enter phone number: "))

formated_string = "The name of the student is {}, his/her marks: {} and phone number is {}".format(name, marks, phone_number)

print(formated_string)