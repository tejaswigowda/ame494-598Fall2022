const express = require("express");
const app = express();
const WebSocket = require('ws')




const wss = new WebSocket.Server({ port: 3000})

wss.on('connection', ws => {
  ws.on('message', message => {
	var x = `${message}`;
	  console.log(x, new Date());
  })
})
