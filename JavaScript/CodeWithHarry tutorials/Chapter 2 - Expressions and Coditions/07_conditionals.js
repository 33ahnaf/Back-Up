const prompt = require("prompt-sync")({ sigint: true });
const alert = require("alert-node");

let age = Number.parseInt(prompt("Enter your age: "));
if (age <= 0) {
    alert("Invalid age!");
}else if (age < 10) {
    console.log("Don't even think of driving as you are a kid.");
}else if (age < 18) {
    console.log("You can drive after 18.");
}else{
    console.log("You can drive now as you are an adult.");
}