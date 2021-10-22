const express = require('express')
var mysql = require('mysql')
const bodyParser = require('body-parser');
const app = express()
const port = 3000
//const urlencodedParser = bodyParser.urlencoded({ extended: false });

app.use(express.static('index.html'))

//app.set('view engine', 'ejs');  // to display the web page content

app.use(bodyParser.urlencoded({extended: false}))
 
var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "",
  database: "wt2"
});

con.connect(function(err) {
  if (err) throw err;
  console.log("Connected!");
})

app.get('/', function(req, res){
	res.sendFile('index.html', {root:__dirname})
});



app.post('/submit',function (req,res){
		//console.log(req.body)
		//var reply='';
		roll = req.body.roll;
		per=req.body.per;
		name=req.body.name;
		
		var sql =" insert into wt2(roll,per,name) values("+roll+","+per+","+"'"+name+"')";
		
		con.query(sql, function (err, result) {
			if (err) throw err; 
			
			//res.write('Saved');
			
			//res.render('index', {title: 'Data saved',
			//message: 'Data saved successfully.'})
		});
		
	res.end('Saved');	
})

app.listen(port,() => console.log('you got it'));
