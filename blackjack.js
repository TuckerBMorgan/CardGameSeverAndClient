var deckControl = require("./deckControl");
var deckGeneration = require("./deckGeneration");
var server = require("./server");
var newPlayer = require("./newPlayer");

var state = {
	"deck":[],//deck[n] is a card that is still undealt, dealt cards go to playerHands
	"playerHands":{},//playerHands[playerGuid] is the current hand of a person, 0n is the card that the others can't see
	"players":[],//players[n] in a guid of a player, placed in connection order
	"sockets":{},//socket has 
	"playerGuids":{}//playerGuids[Socket] will return the guid of the player that is part of that server 
};
exports.newPlayer = function(playerGuid, socket, state){
	state.players.guid(playerGuid);
};
exports.processMove = function(message, socket, state){
	  switch(message.type){
		  
		  case "newPlayer":
		  GenerateBlankSlate();
		  newPlayer.newPlayer(message.playerGuid, socket, state);
		  break;
		  
		  case "newConnection":
		  server.sendMessage(JSON.stringify(constuctMessage("connected", null)), socket);
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
	state.player = [];
	state.sockets = {};
	state.playerGuids = {};
}

function constuctMessage(type, payLoad){
	var message = {
		"type": type,
		"payLoad":payLoad
	} 
	console.log(JSON.stringify(message));
	return message;
}