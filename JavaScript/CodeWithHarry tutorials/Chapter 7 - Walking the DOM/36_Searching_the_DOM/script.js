let males = document.getElementsByClassName("male");
let females = document.getElementsByClassName("female");
for (let male of males) {
    male.style.color = "blue";
}
for (let female of females) {
    female.style.color = "rgb(252, 0, 155)";
}

let my_cousin = document.getElementById("cousin");
my_cousin.style.color = "rgb(95, 4, 199)";

console.log(document.getElementsByClassName("male"));
console.log(document.querySelectorAll(".male"));
console.log(document.getElementsByTagName("tr"));



// document.getElementsByClassName("class-name")            ->> this method is used to get the elements with a given "class" attribute.    
// document.getElementById("id")                            ->> this method is used to get the element with a given "id" attribute.
// document.querySelectorAll( ".class-name"  or  "#id" )    ->> returns all elements for the given CSS selector
// document.querySelector( ".class-name"  or  "#id" )       ->> returns the first element for the given CSS selector
//     Note: the upper one is the same as document.querySelectorAll()[0] but instead of searching all the elements, it's just gives the first element. because of which it's more effecient.
// document.getElementsByTagName("tag-name")                ->> returns all the elements for the given tag