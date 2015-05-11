exports.dealcard = function(deck, hidden){
	var index = Math.floor(Math.random() * deck.length);
	var card = deck[index];
	deck.splice(index, 0);
	return card + "," + hidden;
};