let element = document.body.firstElementChild;

console.log(element.getAttribute("id")); // method to get the value of an attribute
console.log(element.getAttribute("class")); // method to get the value of an attribute

console.log(element.hasAttribute("id")); // method to check for existence of an attribute
console.log(element.hasAttribute("class")); // method to check for existence of an attribute
console.log(element.hasAttribute("style")); // method to check for existence of an attribute

// element.setAttribute("hidden", "true"); // method to set the value of an attribute

element.removeAttribute("class"); // method to remove an attribute from the element

console.log(element.attributes); // method to get the collection of all attribute of an element

console.log(element.dataset);
console.log(element.dataset.game);
console.log(element.dataset.player);