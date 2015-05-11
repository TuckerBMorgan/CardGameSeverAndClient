var deckControl = require("./deckControl");
var rune = require("./RuneVM");

exports.attempt = function(message,playerGuid,state) {
	var player = state.players[playerGuid];
	if(player.state  == "inPlay"){
		rune.executeSingle({"type":"addCardToHand","card":deckControl.dealcard(state.deck, false),"playerGuid":playerGuid},state);
	}
};