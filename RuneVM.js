var server = require("./server");

exports.executeSingle = function(rune, state){
		var action = require(rune.action);
		action.execute(rune, state);
		server.sendMessage(rune, state.sockets[rune.playerGuid], state.sockets[rune.playerGuid]);
};