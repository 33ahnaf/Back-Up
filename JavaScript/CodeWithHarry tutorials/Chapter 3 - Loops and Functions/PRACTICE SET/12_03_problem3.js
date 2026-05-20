const prompt = require("prompt-sync")({ sigint: true });

let correct_num = 3;
let user_input_num = prompt("Enter a number: ");
while (user_input_num != correct_num) {
    console.log("Try again!");
    user_input_num = prompt("Enter a number: ");
}
console.log("You have entered the correct number!");