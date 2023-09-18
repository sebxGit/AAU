let btn1 = document.querySelector('#btn1');
btn1.onmouseover = sendEndpoint;

async function postData(data){
	console.log("Fetching..");
	let res = await fetch('http://localhost:3000/spying', {
		method: 'POST',
		headers: {'Content-Type': 'application/json;charset=utf-8'},
		body: data
	})

	if(res.ok) {
    let body = await res.json();
    return("server answered: " + JSON.stringify(body));
  } else {
    throw new Error("HTTP-Error: " + response.status)
  }
}

function sendEndpoint(e){
	console.log(e.currentTarget.id);
	postData(JSON.stringify(e.currentTarget.id))
	.then(console.log).catch(console.log);
}