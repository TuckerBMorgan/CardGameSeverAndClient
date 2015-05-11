var rune  = require("./RuneVM");
var deckControl = require("./deckControl");

exports.newPlayer = function(playerGuid, socket, state){
	state.hand[playerGuid] = [];
	state.sockets[playerGuid] = socket;
	state.playerGuids[socket] = playerGuid;
	rune.executeSingle({"type":"addCardToHand","card":deckControl.dealcard(state.deck, true),"playerGuid":playerGuid},state);
	rune.executeSingle({"type":"addCardToHand","card":deckControl.dealcard(state.deck, false), "playerGuid":playerGuid}, state);
};