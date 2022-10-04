const express = require("express");
const app = express();
const WebSocket = require('ws')
var lts = {};

const wss = new WebSocket.Server({ port: 3000})
var count = 0;
wss.on('connection', ws => {
  ws.on('message', message => {
	  lts = message;
	console.log(count, message, new Date());count++;
	var x = `${message}`;
  })
})

app.get("getLatest", function(req,res){
	res.end(JSON.stringify(lts);
});


app.listen(8080);