let id_1 = document.getElementById("id1");
console.log(id_1);
console.log(id_1.matches(".random_thing"));
console.log(id_1.matches(".box"));
console.log(id_1.matches("#id2"));
console.log(id_1.matches("#id_1"));

console.log(sp1.closest("#sp1"));
console.log(sp1.closest(".box"));

console.log(id_1.contains(sp1));
console.log(id_1.contains(id_1));
console.log(sp1.contains(id_1));