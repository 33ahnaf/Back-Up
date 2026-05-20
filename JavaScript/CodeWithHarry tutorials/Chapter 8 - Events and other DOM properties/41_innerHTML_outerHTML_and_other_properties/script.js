console.log(document.getElementsByTagName("span")[0]); // console.log() shows the element DOM tree.
console.dir(document.getElementsByTagName("span")[0]); // console.dir() shows the element as an object with it's properties.


// tagName vs nodeName ->> tagName only shows elements, nodeName shows all nodes(like #text, comment)
console.log(document.body.firstChild.nodeName);
console.log(document.body.firstElementChild.tagName);

document.getElementsByTagName("span")[0].outerHTML = "<div><h1>Hello, World!</h1></div>";

console.log(document.body.textContent);

document.getElementsByTagName("div")[1].hidden = false;