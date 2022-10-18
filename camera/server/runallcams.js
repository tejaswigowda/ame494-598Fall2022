var shell = require('shelljs');

var command = 'forever stopall';
shell.exec(command);

var cameras = require('./public/cameras.json');
console.log(cameras);


var keys = Object.keys(cameras);

for (var i = 0; i < keys.length; i++) {
  var command = 'forever start server.js ' + cameras[keys[i]].port;
  shell.exec(command);
}
