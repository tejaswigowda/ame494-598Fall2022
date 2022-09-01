var express = require("express");
var app = express();
var bodyParser = require('body-parser');
var errorHandler = require('errorhandler');
var methodOverride = require('method-override');
var MS = require("mongoskin");
var hostname = process.env.HOSTNAME || 'localhost';
var port = 1234;

var t, h;

var db = MS.db("mongodb://13.56.213.25:27017/sensorData");

app.get("/", function (req, res) {
    res.redirect("index.html")
});

app.get("/sendData", function (req, res) {
  t = req.query.t;
  h = req.query.h;
    req.query.time = new Date().getTime();

    db.collection("data").insert(req.query, function(result, err){
      res.send("1");
    });
});


app.get("/getData", function (req, res) {
  var ret = {}

    ret.t = t; 
    ret.h = h; 
    
    res.send(JSON.stringify(ret));
});

app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
