// sample example
// let promise1 = new Promise((resolve, reject) => {
//     setTimeout(() => {
//         console.log("This promise resolved after 2 seconds (Promise 1)");
//         resolve(3);
//     }, 2000);
// });

// promise1.then((value) => {
//     console.log(value);
//     return new Promise((resolve, reject) => {
//         console.log("This is promise 2");
//         resolve(3+19);
//     });
// }).then((value) => {
//     console.log(value)
//     console.log("We are done!");
// });



// loadscript using promise
function loadScript(src){
    return new Promise((resolve, reject) => {
        let script = document.createElement("script");
        script.src = src;
        script.onload = () => {
            resolve("Script has been loaded successfully.");
        }
        script.onerror = () => {
            reject(0);
        }
        document.body.appendChild(script);
    });
};

let promise1 = loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap.bundle.min.js");
promise1.then((value) => {
    console.log(value);
    return loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap.bundle.min.js");
}).then((value) => {
    console.log(value);
    return loadScript("https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/js/bootstrap.bundle.min.js");
}).then((value) => {
    console.log(value);
}).catch((error) => {
    console.log("We've got some error before GTA VI !!!");
});