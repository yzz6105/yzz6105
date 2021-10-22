var express = require('express');
var app = express();
var mysql = require("mysql");
var http = require('http');
var port = 3000; 

    // config for your database
     var con = mysql.createConnection({
         host: "localhost",
         user: "root",
         password: "",
         database: "wt21"
       }); 
	   
	// connect to your database
		con.connect(function(err) {
		if (err) throw err;
		console.log('Connected')
	
	});
		
	   
app.get('/', function (req, res) {
     
    con.query('select * from wt1', function (err, result) {
	if (err) throw err;
	res.send(result)
	console.log(result)

			
	});
});
	
//});

app.listen(port, () => console.log('Details are:'));
		