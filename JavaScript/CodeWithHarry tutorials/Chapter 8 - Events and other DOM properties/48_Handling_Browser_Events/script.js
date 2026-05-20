let x = () => {
    console.log("Hello, World! (x1)");
}

let y = () => {
    console.log("Hello, World! (x2)");
}

let details = (event) => {
    console.log(event.type, event.clientX, event.clientY);
}

btn.addEventListener("click", x);
btn.addEventListener("click", y);
btn.addEventListener("click", details);

let input = prompt("Enter a num: ");
if (input == 3) {
    btn.removeEventListener("click", y);
}