var MS = require("mongoskin");
var express = require("express");
var app = express();
var bodyParser = require('body-parser');
var errorHandler = require('errorhandler');
var methodOverride = require('method-override');
var hostname = process.env.HOSTNAME || 'localhost';
var port = 1234;
var VALUEt = 0;
var VALUEh = 0;
var VALUEtime = 0;


var db = MS.db("mongodb://localhost:27017/sensorData")
app.get("/", function (req, res) {
    res.redirect("/index.html");
});

app.get("/getAverage", function (req, res) {
  var from = parseInt(req.query.from);
  var to = parseInt(req.query.to);
  db.collection("dataWeather").find({time:{$gt:from, $lt:to}}).toArray(function(err, result){
  	console.log(err);
  	console.log(result);
  	var tempSum = 0;
  	var humSum = 0;
  	for(var i=0; i< result.length; i++){
  		tempSum += result[i].t || 0;
  		humSum += result[i].t || 0;
  	}
  	var tAvg = tempSum/result.length;
  	var hAvg = humSum/result.length;
  	res.send(tAvg + " "+  hAvg);
  });
});

app.get("/getLatest", function (req, res) {
  db.collection("dataWeather").find({}).sort({time:-1}).limit(10).toArray(function(err, result){
    res.send(JSON.stringify(result));
  });
});

app.get("/getData", function (req, res) {
  var from = parseInt(req.query.from);
  var to = parseInt(req.query.to);
  db.collection("dataWeather").find({time:{$gt:from, $lt:to}}).sort({time:-1}).toArray(function(err, result){
    res.send(JSON.stringify(result));
  });
});


app.get("/getValue", function (req, res) {
  //res.writeHead(200, {'Content-Type': 'text/plain'});
  res.send(VALUEt.toString() + " " + VALUEh + " " + VALUEtime + "\r");
});

app.get("/setValue", function (req, res) {
  VALUEt = parseFloat(req.query.t);
  VALUEh = parseFloat(req.query.h);
  VALUEtime = new Date().getTime();
	var dataObj = {
		t: VALUEt,
		h: VALUEh,
		time: VALUEtime
	}
	db.collection("dataWeather").insert(dataObj, function(err,result){
		console.log("added data: " + JSON.stringify(dataObj));
	});
  res.send(VALUEtime.toString());
});


app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
