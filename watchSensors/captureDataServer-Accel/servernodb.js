var express = require("express");
var app = express();
var bodyParser = require('body-parser');
var errorHandler = require('errorhandler');
var methodOverride = require('method-override');
var hostname = process.env.HOSTNAME || 'localhost';
var port = 8080;

var accX, accY, accZ;


app.get("/", function (req, res) {
    res.redirect("index.html")
});

app.get("/sendData", function (req, res) {
    accX = req.query.x
    accY = req.query.y
    accZ = req.query.z
    req.query.time = new Date().getTime();
    res.end("OK");
    console.log(req.query, new Date());
});


app.get("/getData", function (req, res) {
  var ret = {}

    ret.x = accX; 
    ret.y = accY; 
    ret.z = accZ; 
    
    res.send(JSON.stringify(ret));
});

app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
