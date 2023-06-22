import http from 'http'
import url from 'url'
import fs from 'fs'
import { ESRCH } from 'node:constants'
const port = 3000

const rootFileSystem=process.cwd();

function sendFileRes(filename, res){
	fs.readFile(filename, (err, data) => {
		if (err){
			console.log(err);
			res.statusCode=404;
			res.setHeader('Context-Type', 'text/txt');
			res.write('Error: '+ String(err));
		}
		else{
			res.statusCode=200;
			res.setHeader('Context-Type', guessMimeType(filename));
			res.write(data);
		}
		res.end();
	})
}


function guessMimeType(fileName){
  const fileExtension=fileName.split('.').pop().toLowerCase();
  console.log(fileExtension);
  const ext2Mime ={ //Aught to check with IANA spec
    "txt": "text/txt",
    "html": "text/html",
    "ico": "image/ico", // CHECK x-icon vs image/vnd.microsoft.icon
    "js": "text/javascript",
    "json": "application/json", 
    "css": 'text/css',
    "png": 'image/png',
    "jpg": 'image/jpeg',
    "wav": 'audio/wav',
    "mp3": 'audio/mpeg',
    "svg": 'image/svg+xml',
    "pdf": 'application/pdf',
    "doc": 'application/msword',
    "docx": 'application/msword'
   };
    //incomplete
  return (ext2Mime[fileExtension]||"text/plain");
}

const server = http.createServer((req, res) => {
	console.log("Got: " + req.method + " " + req.url);
	if(req.method=="GET"){
		switch(req.url){
			case "/": sendFileRes("spysite.html", res); break;
			case "/client.js": sendFileRes("./client.js", res); break;
			default: sendFileRes(req.url, res);
		}
	}
	if(req.method=="POST" && req.url=="/spying"){
		res.statusCode = 200;
		res.setHeader('Content-Type', 'application/json');
		
		let body = "";
		req.on("data", chunk => {body += chunk});
		showData(body);
		res.end();
	}
});

function showData(res){
	console.log(res);
}


server.listen(port, (err) => {
	(err) ? console.log("something went wrong", err) 
				: console.log(`Server running at port ${port}`);
})