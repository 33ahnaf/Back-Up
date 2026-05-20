const prompt = require("prompt-sync")({ sigint: true });

let num = Number.parseInt(prompt("Enter 0 for Kilometer or 1 for Mile or 2 for Nautical Mile: "));
switch (num) {
    case 0:
        console.log("Kilometer");
        break;
    case 1:
        console.log("Mile");
        break;
    case 2:
        console.log("Nautical Mile");
        break;
    default:
        console.log("Invalid option!");
}