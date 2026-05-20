function Average(num1, num2) {
    console.log("Done");
    return (num1 + num2) / 2;
}

function Say_Hello_to_(name) {
    console.log("Hello, " + name + ".");
}

const print_sum = (num1, num2) => {
    console.log(num1 + " + " + num2 + " = " + (num1 + num2));
}
// Note: the upper method of declaring/creating a function is called "arrow function" (idk why CodeWithHarry prefer this method over the older one).

console.log("Average of 19 and 3 is: ", Average(19, 3));
console.log("Average of 2 and 3 is: ", Average(2, 3));
console.log("Average of 19 and 39 is: ", Average(19, 39));
Say_Hello_to_("Afrina");
print_sum(23, 34);