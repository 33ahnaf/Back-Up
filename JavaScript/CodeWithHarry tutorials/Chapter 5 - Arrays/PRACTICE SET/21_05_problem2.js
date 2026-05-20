const prompt = require('prompt-sync') ({ sigint: true });

let nums = [];
let user_input = Number.parseInt(prompt("Enter a num: "));
while (true) {
    if (user_input != 0) {
        nums.push(Number.parseInt(user_input));
        user_input = Number.parseInt(prompt("Enter a num: "));
    }else {
        break;
    }
}
console.log(nums);