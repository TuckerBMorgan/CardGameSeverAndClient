var rune  = require("./RuneVM");
var deckControl = require("./deckControl");

exports.newPlayer = function(playerGuid, socket, state){
	state.playerHands[playerGuid] = [];
	state.sockets[playerGuid] = socket;
	state.playerState[playerGuid] = "inPlay";
	state.playerGuids[socket] = playerGuid;
	rune.executeSingle({"runeType":"addCardToHand","card":deckControl.dealcard(state.deck, true),  "guid":playerGuid}, state);
	rune.executeSingle({"runeType":"addCardToHand","card":deckControl.dealcard(state.deck, false), "guid":playerGuid}, state);
};