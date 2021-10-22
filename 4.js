var url = require('url');
var http = require('http');
var dt = require('./mymodule');

http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/html'});
  
   
  res.write( "\n the addition is  "+ dt.add(8,9) + '<br/>' );
  

  res.write("\n the subtraction is "+ dt.sub(10,2) + '<br/>');
  

  res.write("\n the multiplication is "+ dt.mul(10,10) + '<br/>');

  res.write("\n the division is "+ dt.div(100,10));
  
  res.end();
}).listen(8081);
   