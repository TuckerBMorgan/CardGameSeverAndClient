var deckControl = require("./deckControl");
var deckGeneration = require("./deckGeneration");
var server = require("./server");
var newPlayer = require("./newPlayer");

var state = {
	"deck":[],//deck[n] is a card that is still undealt, dealt cards go to playerHands
	"playerHands":{},//playerHands[playerGuid] is the current hand of a person, 0n is the card that the others can't see
	"players":[],//players[n] in a guid of a player, placed in connection order
	"sockets":{},//socket has 
	"playerGuids":{},//playerGuids[Socket] will return the guid of the player that is part of that server
	"playerState":{}, //playerState[playerGuid] is the current state of the player, inPlay, folded, or busted
	"handValue":{} //HandValue[playerGuid] is the current value of the players Hand, is calculated on card deal
};
exports.newPlayer = function(playerGuid, socket, state){
	state.players.guid(playerGuid);
};
exports.processMove = function(message, socket){
	  switch(message.type){
		  
		  case "newPlayer":
		  GenerateBlankSlate();
		  newPlayer.newPlayer(message.playerGuid, socket, state);
		  break;
		  
		  case "newConnection":
		  var newConnectionRune= {
			  "runeType":"newConnection"
		  };
		  server.sendMessage(JSON.stringify(newConnectionRune), socket);
		  break;
		  
		  case "moveSelection":
		  var move = require("./" + message.move);
		  move.attempt(message, state.playerGuids[socket], state);
		  break;
	  }
};
function GenerateBlankSlate(){
	state.deck = deckGeneration.deckGeneration();
	state.playerHands = {};
	state.players = [];
	state.sockets = {};
	state.playerGuids = {};
}