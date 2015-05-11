var blackJack = require("./blackJack");

var net = require('net');
var deckGen = require("./deckGeneration");
var state = {
	"players":[],
	"deck":{}
};
var server = net.createServer(function(socket){
	socket.on('data', function(data){
		console.log(JSON.parse(data));
		blackJack.processMove(JSON.parse(data), socket);
	});
});

exports.sendMessage = function(message, socket){
	socket.write(message + "\n\n");	
};

server.listen(1337, '127.0.0.1');