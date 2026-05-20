const prompt = require("prompt-sync")({ sigint: true });

let num = Number.parseInt(prompt("Enter a num: "));
if (num%2 == 0 && num%3 == 0) {
    console.log("The number is divisable by 2 and 3.");
}else{
    console.log("The number is not divisable by 2 and 3.");
}