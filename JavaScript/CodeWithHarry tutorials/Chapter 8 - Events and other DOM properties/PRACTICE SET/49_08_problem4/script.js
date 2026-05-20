setInterval(async function() {
    let url = "https://jsonplaceholder.typicode.com/todos/1";
    console.log(await fetch(url));
}, 3000)