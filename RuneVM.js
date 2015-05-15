var server = require('./server');

exports.executeSingle = function(rune, state){
		var action = require("./" + rune.runeType);
		action.execute(rune, state);
		server.sendMessage(JSON.stringify(rune), state.sockets[rune.guid]);
};