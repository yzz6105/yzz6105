var http = require('http');
var express = require('express');
var app = express();
var bodyParser = require('body-parser');
var urlencodedParser = bodyParser.urlencoded({ extended: true });

app.get('/se', function (req, res) {
var rr="<html>";
rr = rr+"<body>";
rr= rr+"<form method='post' action='add' >";
rr = rr+"first number"+"<input type='text' name='one' value=' '>";
rr = rr+"second number"+"<input type='text' name='two' value=' '>";
rr = rr+"<input type='submit' name='t1' value='Add '>";
rr = rr+"</form>"
rr = rr+"</body>";
res.send(rr);
})

app.post('/add', urlencodedParser, function (req, res){
  var a = req.body.one;
  var b= req.body.two;
  
  a = parseInt(a);
  b= parseInt(b);
  
 var c = a+b; 
  
  res.send("sum is of "+a+" and "+b+" "+"is "+c);
 }).listen(9000);
 
 
 
 