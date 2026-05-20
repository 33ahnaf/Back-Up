do {
    alert("Welcome to rock, paper, scissor game\n------------------------------------------\n1 --> Rock\n2 --> Paper\n3 --> Scissor");
    let player = Number.parseInt(prompt("1 --> Rock\n2 --> Paper\n3 --> Scissor\nEnter 1 or 2 or 3 to start the game:"));
    let max = 3, min = 1;
    let computer = Math.floor(Math.random() * (max - min + 1)) + 1;
    const myDict = { 1: "Rock", 2: "Paper", 3: "Scissor" };
    let result;
    if (player == computer) {
        result = "It's a draw!";
    } else if (player == 1 && computer == 2) {
        result = "You lose!";
    } else if (player == 1 && computer == 3) {
        result = "You won!";
    } else if (player == 2 && computer == 1) {
        result = "You won!";
    } else if (player == 2 && computer == 3) {
        result = "You lose!";
    } else if (player == 3 && computer == 1) {
        result = "You lose!";
    } else if (player == 3 && computer == 2) {
        result = "You won!";
    } else {
        alert("Something went wrong!");
        continue;
    }
    alert(`You chose: ${myDict[player]}    Computer chose: ${myDict[computer]}\n${result}`);
} while(confirm("Do you want to play one more time?"));