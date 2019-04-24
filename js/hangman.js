// Make sure that the document is ready, per https://learn.jquery.com/using-jquery-core/document-ready/
// You can use $( window ).on( "load", function() { ... }) if you want all elements, including images to have been loaded before javascript is ready
$(document).ready(function() {
	console.log("Document is ready!")

	// Wait til the p elements have loaded and then add a p element to existing p elements
    $(window).on("load", function() {

    	// Create a p element with pure javascript
    	var p = document.createElement('p');

    	// Make the inner text what I want using jquery and give it a class
    	$(p).text("This was added by jquery!").addClass('javascript-added');

    	// Use jquery to select all p elements and append my new element
    	$('p').append(p);

    	getFile();
    })
});

function getFile() {
	$.get('./data/sample.txt', function(txt) {
    	$('.javascript-added').append('<p>' + txt + '</p>')
	}, 'text');
}