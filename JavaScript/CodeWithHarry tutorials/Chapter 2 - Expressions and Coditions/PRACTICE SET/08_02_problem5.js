const prompt = require("prompt-sync")({ sigint: true });

let age = Number.parseInt(prompt("Enter your age: "));
console.log(age >= 18 ? "You can drive." : "You can not drive.");