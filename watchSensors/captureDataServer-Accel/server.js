var express = require("express");
var app = express();
var bodyParser = require('body-parser');
var errorHandler = require('errorhandler');
var methodOverride = require('method-override');
var MS = require("mongoskin");
var hostname = process.env.HOSTNAME || 'localhost';
var port = 8080;

var accX, accY, accZ;

var db = MS.db("mongodb://127.0.0.1:27017/sensorData");

app.get("/", function (req, res) {
    res.redirect("index.html")
});

app.get("/sendData", function (req, res) {
    accX = req.query.x
    accY = req.query.y
    accZ = req.query.z
    req.query.time = new Date().getTime();
    console.log(req.query);
    

   db.collection("data").insertOne(req.query, function(result, err){
       console.log(result, err);
    res.send("1");
   });
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
