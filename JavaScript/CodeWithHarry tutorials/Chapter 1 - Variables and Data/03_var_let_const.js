var b = 12;
console.log(b);
{
    let b = 69;
    console.log(b);
}
console.log(b);
// var → Function-scoped (only accessible within the function where it's declared)
// let → Block-scoped (only accessible within the {} block where it's declared)

const author = "Ahnaf";
console.log(author);
// const → same as let (Block-scoped) but const can't be reassigned, nor redeclared.