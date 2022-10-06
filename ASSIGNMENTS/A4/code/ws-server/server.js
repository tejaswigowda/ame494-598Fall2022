const express = require("express");
const app = express();
const WebSocket = require('ws')
var cors = require('cors');

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

app.use(cors())

app.get("/getLatest.csv", function(req,res){
    var csv = "Time, X, Y, Z \n";
    csv += new Date().toJSON() + "," + lts.x + "," + lts.y + "," + lts.z + "\n";
    res.setHeader("Access-Control-Allow-Origin", "*");
    res.setHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    res.setHeader('content-type', 'text/csv');
	res.end(csv);
});


app.listen(8080);
