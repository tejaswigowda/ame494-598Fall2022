const express = require("express");
const app = express();
const WebSocket = require('ws')

var MS = require("mongoskin");
var db = MS.db("mongodb://localhost:27017/sensorData")



const wss = new WebSocket.Server({ port: 3000})

wss.on('connection', ws => {
  ws.on('message', message => {
	var x = `${message}`;
	  console.log(x)
	  try{
		    db.collection("dataWS").insert(JSON.parse(x), function(err, result){
		    });
	  }
	  catch(e){}
  })
})
