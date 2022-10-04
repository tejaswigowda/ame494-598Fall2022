const express = require("express");
const app = express();
const WebSocket = require('ws')


const wss = new WebSocket.Server({ port: 3000})
var count = 0;
wss.on('connection', ws => {
  ws.on('message', message => {
	console.log(count, message, new Date());count++;
	var x = `${message}`;
  })
})
