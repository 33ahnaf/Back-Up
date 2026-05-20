console.log("Hello");

// setTimeout(function(){
//     console.log("Hello (x2)");
// }, 5000);
// setTimeout(function(){
//     console.log("Hello (x3)");
// }, 3000);

// setTimeout(function(){
//     console.log("Hello (x2)");
//     setTimeout(function(){
//         console.log("Hello (x3)");
//     }, 5000);
// }, 2000);


const sum = (a, b) => {
    console.log(a + b);
};

let a = setTimeout(sum, 5000, 1, 2); // ->> syntax ->> setTimeout(func, delay, arg1, arg2 ...)
confirm("Do you want to processed?") ? void(0) : clearTimeout(a);

let b = setInterval(function(){
    console.log("I like that person who asked me who do I like.");
}, 1000);
confirm("Do you want to processed?") ? void(0) : clearInterval(b);