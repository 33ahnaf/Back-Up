first.className = "yellow text-dark red";
first.classList.remove("yellow");

// Note:
//  elem.className ->> if we assign something to elem.className, it replaces the whole string of classes
//  elem.classList ->> returns or help us to mainpulate tasks related to class (bottom one's)
//  elem.classList.add/remove("class-name") ->> adds/removes a class
//  elem.classList.toggle("class-name") ->> adds the class if it doesn't exists, removes it otherwise
//  elem.classList.contains("class-name") ->> checks for the given class, returns true/false