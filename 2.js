var url = require('url');
var http = require('http');

http.createServer(function (req, res) {

  res.writeHead(200, {'Content-Type': 'text/html'});
  a= 3
  b= 4
  var c = a+b;  
  
  res.write("the answer is " +c);
  res.end();
}).listen(8080);


