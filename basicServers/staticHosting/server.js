var express = require("express");
var server = express();
var bodyParser = require('body-parser');
var hostname = process.env.HOSTNAME || 'localhost';
var port = 1234;

server.get("/", function (req, res) {
    res.redirect("index.html")
});


server.use(bodyParser());
server.use(express.static(__dirname + '/public'));

console.log("Simple static server listening at http://" + hostname + ":" + port);
server.listen(port);
