let first_div = document.body.firstElementChild;
let button = first_div.firstElementChild;
first_div.onmouseenter = () => {
    console.log("mouse pointer has entered the div section");
}
first_div.onclick = () => {
    console.log("clicked in div section");
}
button.onclick = () => {
    let a = 3;
    console.log(a);
}

// Note: index.html's scripts shal be ignored.
//       (adding a handler using JavaScript overwrites the existing one)