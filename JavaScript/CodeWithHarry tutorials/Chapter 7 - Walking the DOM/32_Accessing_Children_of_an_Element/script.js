console.log(document.body.firstChild); // returns the first child node.
console.log(document.body.lastChild); // returns the last child node.
console.log(document.body.childNodes); // returns the list of child nodes.
/*
fact:
    elem.childNodes[0] === elem.firstChild
    elem.childNodes[elem.childNodes.length - 1] === elem.lastChild
*/
console.log(document.body.hasChildNodes()); // returns true if child node is present.

// storing child nodes in an array
let arr = Array.from(document.body.childNodes);
console.log(arr);