const fetch = require("node-fetch")

// 1)
// fetch('http://ikkeensite.dk/')
// 	.then(response => console.log(response))
// 	.then(data => console.log(data))
// 	.catch(err => console.log(err))

// 2)
// fetch('http://127.0.0.1:3000/html/findesej.json', {
// 	method: 'POST',
// 	headers: {
// 		'Content-Type': 'application/json'
// 	}
// 	// can append data to json if needed
// 	// body: JSON.stringify({
// 	// 	name: 'User 1'
// 	// })
// }).then(res => {
// 	return res.json()
// 	})
// 	.then(data => console.log(data))
// 	.catch(error => console.log("Error"))

// 3) wdym ???

// 4)
fetch('http://people.cs.aau.dk/~bnielsen/IWP/scores.json', {
	method: 'POST',
	headers: {
		'Content-Type': 'application/json'
	}
}).then(res => {
	return res.json()
	})
	.then(data => console.log(data))
	.catch(error => console.log("Error"))

// 5) wdym again ???