const prompt = require("prompt-sync")({ sigint: true });

let my_string = prompt("Enter some texts: ");
console.log(my_string.toLowerCase());