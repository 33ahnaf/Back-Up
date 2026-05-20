const prompt = require("prompt-sync")({ sigint: true });

let age = Number.parseInt(prompt("Enter your age: "));
if (age > 10 && age < 20) {
    console.log("Your age is between 10 and 20 years.");
}else{
    console.log("Your age isn't between 10 and 20.");
}