console.log(document.body.childNodes);
console.log(document.body.firstChild);
console.log(document.body.firstChild.nextSibling);
console.log(document.body.lastChild);
console.log(document.body.lastChild.previousSibling);
console.log("\n\n");
let a = document.body.firstChild.nextSibling.firstChild;
console.log(a.parentNode);
console.log(a.parentElement);
// Note: Difference between elem.parentNode and elem.parentElement
//       elem.parentNode returns the parent node. (node means anything like text, h1, div, comment etc.)
//       elem.parentElement return the parent element, if the parent node is not an element then it returns null.