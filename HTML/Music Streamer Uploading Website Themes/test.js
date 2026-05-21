const texts = [
    "Acceptance is a great virtue.",
    "Patience is a great virtue.",
    "Patience is a great virtue."
];

// console.log(texts[Math.floor(Math.random() * texts.length)]);
let first = 0;
let second = 0;
for(let i = 0; i < 1000; i++){
    let randomNum = Math.floor(Math.random() * texts.length);
    if(randomNum == 0)
        first++;
    else
        second++;
}
console.log("Acceptance is a great virtue -> " + first + " (" + (first - 333) + ")" + "\nPatience is a great virtue -> " + second + " (" + (second - 667) + ")");