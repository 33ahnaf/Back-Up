const changeBG = (color) => {
    document.body.style.backgroundColor = color;
}

let b = document.body;
console.log("First child of b is:", b.firstChild);
console.log("Second child of b is:", b.firstChild.nextSibling);
console.log("First element child of b is:", b.firstElementChild);
console.log("Second element child of b is:", b.firstElementChild.nextElementSibling);

changeBG(prompt("Background color:"));

console.log(b.childNodes); // child nodes
console.log(b.children); // child element nodes