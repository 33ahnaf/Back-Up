/*

    DOM -> Document Object Model
   ------------------------------
 DOM represents the page content as HTML
 document.body    -> page body as JS object
 document.body.style.backgroundColor = "hotpink"    -> changes page background color to hotpink

*/
let color = prompt("Background color:");
document.body.style.backgroundColor = color;



/*

    BOM -> Browser Object Model
   -----------------------------
 The browser object model (BOM) represents additional objects provided by the browser (host enviroment) for
 working with everything except the document.

 The functions alert, confirm and prompt are also part of the BOM.

 location.href = https://codewithharry.com    -> redirects to another URL

*/
let web_link = prompt("URL:");
location.href = `https://${web_link}`;