// const prompt = require("prompt-sync") ({ sigint: true });



// Syncronous programming
// Syncronous actions are the actions that initiate and finish one-by-one.

// let my_name = prompt("What is your name?: ");
// let age = prompt("What is your age?: ");
// let fav_color = prompt("What is your favourite color?: ");
// console.log(`${my_name} is ${age} years old and has ${fav_color} as favourite color.`);



// Asyncronous programming
// Asyncronous actions are the actions that we initiate now and they finish later. eg. ->> setTimeout()

// console.log("Program has been started.");
// setTimeout(function() {
//     console.log("This blcok of code has been run after 3000 ms");
// }, 3000);
// console.log("Program is in line 14");



// Callbacks
function loadScript(src, callback) {
    let script = document.createElement("script");
    script.src = src;
    script.onload = function() {
        callback(null, src);
    }
    script.onerror = function() {
        callback(new Error("Script got some error!"));
    }
    document.body.appendChild(script);
}

const load_alert = (error, src) => {
    if (error) {
        console.log(error);
        return;
    }
    console.log("Loaded SRC: " + src);
}

loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap.bundle.min.js", load_alert);