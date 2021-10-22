var http = require("http");
var mysql = require('mysql');
var express = require('express');
var app = express();
/*Allows to set up middlewares to respond to HTTP Requests.
Defines a routing table which is used to perform different actions based on HTTP Method and URL.
Allows to dynamically render HTML Pages based on passing arguments to templates.*/
var bodyParser = require('body-parser');
//This is a node.js middleware for handling 
//JSON, Raw, Text and URL encoded form data.
var urlencodedParser = bodyParser.urlencoded({ extended: true });
//---------------------------------------------//
   var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "",
  database: "WT2"
});

//-------------------------------------------//
app.get('/', function (req, res) {
var rr="<html>";
rr = rr+"<body>";
rr=rr+"<form  method='post' action='thank' >";
rr = rr+"roll number"+"<input type='number' name='one' value=' '> <br> <br>" ; 
rr = rr+"per "+"<input type='number' name='two' value=' '> <br> <br>"; 
rr = rr+"name "+"<input type='text' name='three' value=' '> <br> <br>";
rr = rr+"<input type='submit' align='center' name='t1' value='Save '>";
rr = rr+"</form>";
rr = rr+"</body>";
res.send(rr);

  
})
app.post('/thank', urlencodedParser, function (req, res){
  var reply='';
  roll = req.body.one;
  per=req.body.two;
  name=req.body.three;
  var sql =" insert into wt2(roll,per,name) values("+roll+","+per+","+"'"+name+"')";


con.connect(function(err) {
  if (err) throw err;
  console.log("Connected!");
});
con.query(sql, function (err, result) {
	if (err) throw err; 
  res.end("Record inserted");
 });


 //res.write("record inserted");
 // res.end();
 }).listen(8080);