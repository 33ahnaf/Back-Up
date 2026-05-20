const prompt = require('prompt-sync') ({ sigint: true });

console.log("Welcome to the number guessing game");
console.log("-----------------------------------");
let min = 1, max = 100;
let random_num = Math.floor(Math.random() * (max - min + 1)) + min;
let user_input_num = Number.parseInt(prompt("Enter a number to start the game: "));
let number_of_guesses = 0;

while (true) {
    if (user_input_num > random_num) {
        console.log(`The number is smaller than ${user_input_num}`);
        user_input_num = Number.parseInt(prompt("Try again: "));
        number_of_guesses++;
    }else if (user_input_num < random_num) {
        console.log(`The number is greater than ${user_input_num}`);
        user_input_num = Number.parseInt(prompt("Try again: "));
        number_of_guesses++;
    }else if (user_input_num == random_num) {
        number_of_guesses++;
        break;
    }
}

console.log("\nYou have guessed the number correctly!");
console.log("--------------------------------------");
console.log(`Try's count: ${number_of_guesses}`);
console.log(`Score: ${101 - number_of_guesses}`);