var deckControl = require("./deckControl");

exports.execute = function(args, state){
	var playerGuid = args.guid;
	var playerHand = state.playersHand[playerGuid];
	playerHand.push(args.card);
};