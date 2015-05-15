var deckControl = require("./deckControl");
var cardValues = require("./cardValues");
exports.execute = function(args, state){
	var playerGuid = args.guid;
	var playerHand = state.playerHands[playerGuid];
	var card = args.card;
	var value = card[1];
	state.handValue[playerGuid] += cardValues.value[value];
	playerHand.push(args.card);
	
	if(state.handValue[playerGuid] > 21){
		state.playerState[playerGuid].state = "busted";
	}
};