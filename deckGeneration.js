var suits = ["h", "s", "c", "d"];
var cards = ["a","k","q","j", "t", "9", "8", "7", "6", "5", "4", "3", "2"];

exports.deckGeneration = function(){
	
	var deck = [];
	
	suits.forEach(function(current){
		cards.forEach(function(current_){
			deck.push(current + current_);
		});
	});
	
	for(var i = 0;i<52;i++){
		var index1 = Math.floor(Math.random() * deck.length);
		var index2 = Math.floor(Math.random() * deck.length);
		var value1 = deck[index1];
		var value2 = deck[index2];
		deck[index1] = value2;
		deck[index2] = value1;
	}
	return deck;
}