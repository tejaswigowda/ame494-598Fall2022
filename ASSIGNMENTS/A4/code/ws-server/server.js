const express = require("express");
const app = express();
const WebSocket = require('ws')
var lts = {};

const wss = new WebSocket.Server({ port: 3000})
var count = 0;
wss.on('connection', ws => {
  ws.on('message', message => {
	try{  
      lts = JSON.parse(message);
    }
    catch(e){
      console.log(e);
    }
	console.log(count, message, new Date());count++;
	var x = `${message}`;
  })
})

app.get("/getLatest", function(req,res){
    var csv = "Time, X, Y, Z \n";
    csv += new Date().toString() + "," + lts.x + "," + lts.y + "," + lts.z + "\n";
	res.end(csv);
});


app.listen(8080);
