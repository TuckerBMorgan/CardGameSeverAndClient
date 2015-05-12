var server = require('./server');

exports.executeSingle = function(rune, state){
		var action = require("./" + rune.type);
		action.execute(rune, state);
		server.sendMessage(rune, state.sockets[rune.playerGuid], state.sockets[rune.playerGuid]);
};