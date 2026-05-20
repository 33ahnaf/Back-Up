alert("Hey there, your script works.");

let username = prompt("Username: ", "Meghna"); // in case you are wondering why the second argument is there, the second one is a default argument.

alert("Username: " + username);

let result = confirm("Do you want to write it to the page?");
if (result) {
    document.write(`${username}!`);
}else{
    document.write("Permission denied!");
}

alert(typeof result);
// Note: confirm() statement pops up box that have 2 options, "OK" and "Cancel"   If OK is pressed then confirm() function returns true and vice versa.
//       we can also store the returned value in a variable like this -> let x = confirm("Do you want to continue?");