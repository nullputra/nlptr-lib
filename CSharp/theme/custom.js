/*
Ref: https://o296.com/e/mdbook_as_blog.html
*/
const y = document.querySelector(".sidebar .active").offsetTop - 50;
document.querySelector(".sidebar-scrollbox").scroll(0, y);
