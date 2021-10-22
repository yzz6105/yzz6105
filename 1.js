var http = require('http');      //loads node.js modules

http.createServer(function (req, res)  		// Send the HTTP header 
											// HTTP Status: 200 : OK (for output, 400 for errors)
											// Content Type: text/plain
		{

   res.writeHead(200, {'Content-Type': 'text/html'});

   res.write("<h1> good morning</h1>");
   res.end();
   //res.end("Hello") The content to be displayed can also be directly written in the end statement

}).listen(8080);