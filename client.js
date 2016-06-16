var net = require('net');
var prompt = require('prompt');

var buffer = [];
var count = 0;
var user;

function Question(content, possibleAnswer, correctAnswer) {
	this.content = content;
	this.possibleAnswer = possibleAnswer;
	this.correctAnswer = correctAnswer;
};

var client = new net.Socket();
client.connect(6666, '127.0.0.1', function() {
	console.log('Connected');
	/*var schema = {
		properties: {
		  login: {
		    pattern: /admin|teacher|student/,
		    message: 'Wrong username',
		    required: true
		  },
		  password: {
		    hidden: true,
		    replace: '*'
		  }
		}
	};

	prompt.start();
	
	prompt.get(schema, function (err, result) {

	console.log('Command-line input received:');
	console.log('  name: ' + result.login);
	console.log('  password: ' + result.password);
	user = result.login;
	client.write(result.password);*/
});

client.on('data', function(data) {
	console.log(data.toString());
	/*if (user === "student") {
		console.log(buffer[1]);
		setTimeout(function () {
    		console.log('timeout completed');
    		client.end(); 
		}, 60000);
		console.log(buffer);
	}*/
});
