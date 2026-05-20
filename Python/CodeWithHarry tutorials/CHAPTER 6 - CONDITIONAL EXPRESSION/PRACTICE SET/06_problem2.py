sub1 = int(input("Enter the mark of subject 1: "))
sub2 = int(input("Enter the mark of subject 2: "))
sub3 = int(input("Enter the mark of subject 3: "))

# Check for average percentage.
average_percentage = (sub1 + sub2 + sub3) / 3

if(sub1 >= 33 and sub2 >= 33 and sub3 >= 33 and average_percentage >= 40):
    print("PASSED!")
else:
    print("FAILED!")