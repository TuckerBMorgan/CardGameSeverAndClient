var deckControl = require("./deckControl");

exports.execute = function(args, state){
	var playerGuid = args.guid;
	var playerHand = state.playerHands[playerGuid];
	playerHand.push(args.card);
};