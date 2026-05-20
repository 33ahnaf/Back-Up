characters = {
    "Male": {


        "Teacher": {


            "Alive": {

                "Head Master": {
                    "Current": "Md. ??????????????",
                    "Retired": {
                        "Was school in 2023": "Md. Abdul Hamid",
                        "Was for less then 1 year": "Md. Faruq Hossan"
                    }

                }

            },


            "Dead": {

                "Assistant Head Master": "Md. Enamul Karim"
            
            }


        },


        "Student": {
            "Section A": {},
            "Section B": {


                "Programmer": "Md. Ahnaf Shariar"

            },
            "Sectino C": {}
        }



    },



    "Female": {
        "Teacher": "Miss. Nahida Sultana",
        "Student": "Mst. Afrina Rahman"
    }
}



def invalid_option():
    print("Invalid option! Exiting...")



print("Welcome to character guessing game")
print("----------------------------------")


print("Is your character a Male or a Female?")
print("1 --> Male\n2 --> Female")
user_input = int(input("Enter: "))

if user_input == 1:
    gender = "Male"
elif user_input == 2:
    gender = "Female"
else:
    invalid_option()
    exit()


print("Is your character a Teacher or a Student?")
print("1 --> Teacher\n2 --> Student")
user_input = int(input("Enter: "))

if user_input == 1:
    teacher_or_student = "Teacher"
elif user_input == 2:
    teacher_or_student = "Student"
else:
    invalid_option()
    exit()


if teacher_or_student == "Teacher":
    print("Is your character still alive?")
    print("1 --> Yes\n2 --> No")
    is_alive = int(input("Enter: "))

    if is_alive == 1:
        pass################!????
    elif is_alive == 2:
        print("The character is Md. Enamul Karim")
    else:
        invalid_option()
        exit()