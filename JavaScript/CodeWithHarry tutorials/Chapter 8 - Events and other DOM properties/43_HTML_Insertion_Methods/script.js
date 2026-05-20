let first_div = document.getElementsByTagName("div")[0];


// first_div.innerHTML = first_div.innerHTML + "<h1>Hello, World!</h1>";


let additional_content = document.createElement("h1");
additional_content.innerHTML = "Hello, World!";


// first_div.appendChild(additional_content); // node.appendChild() -> appends at the end of node.

// first_div.append(additional_content); // node.append() -> appends at the end of node.

// first_div.prepend(additional_content); // node.prepend() -> inserts at the beginning of node.

// first_div.before(additional_content); // node.before() -> inserts before node.

// first_div.after(additional_content); // node.after() -> inserts after node.

// first_div.replaceWith(additional_content); // node.replaceWith() -> replaces node with the given node.