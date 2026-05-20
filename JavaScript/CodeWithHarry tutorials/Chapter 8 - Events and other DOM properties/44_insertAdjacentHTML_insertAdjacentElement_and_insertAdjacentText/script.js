let first_div = document.getElementById("first");

first_div.insertAdjacentHTML("beforebegin", "<h1>beforebegin</h1>"); // inserts before begin of node
first_div.insertAdjacentHTML("afterbegin", "<h1>afterbegin</h1>"); // inserts after begin of node
first_div.insertAdjacentHTML("beforeend", "<h1>beforeend</h1>"); // inserts before end of node
first_div.insertAdjacentHTML("afterend", "<h1>afterend</h1>"); // inserts after end of node

first_div.remove();