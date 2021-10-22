var mysql = require('mysql');

var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "",
  database: "first"
});

con.connect(function(err) {
  if (err) throw err;
  console.log("Connected!");
  var sql = "UPDATE student SET per = '45' where name=''";
  con.query(sql, function (err, result) {
    if (err) throw err;
    console.log("Record Updated ");
  });
});