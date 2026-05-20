let user_age = 0;
do {
    user_age = Number.parseInt(prompt("Enter your age:"));
    alert(`You ${user_age >= 18 ? "" : "do not "}have the permission to drive a car.`);
} while ((confirm("Do you want to run the program again?")));