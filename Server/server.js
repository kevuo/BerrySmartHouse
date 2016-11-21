//Created by manzumbado 
//Last edited: September 8, 2016

var express     = require('express');
var app         = express();
var bodyParser  = require('body-parser');
var morgan		= require('morgan');
var tungus 		= require('tungus');
var mongoose	= require('mongoose');
var jwt			= require('jsonwebtoken');
var child_p     = require('child_process');
var fs 			= require('fs');
var config		= require('./config/config');         //This is to get the config file
var User 		= require('./app/models/user'); //This is to get the mongoose model
 

 //*****************
 //Config
 //*****************

 var port = process.env.PORT || 8080; 
//This is to get the request parameters
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});
app.set('myprecious', config.secret); //Secret key to encrypt password
mongoose.connect(config.database); //This is used to connect to database
mongoose.set('debug', true);
app.use(morgan('dev')); //This is lo log requests to the console
child_p.execSync('app/bin/SmartBerryWrapper -c', { encoding: 'utf8' }); //Initial pin config

//******************
//Routes
//******************

// basic Route (GET http://localhost:8080)
app.get('/', function(req, res) {
  res.send('Hi! The API is at http://localhost:' + port + '/api');
});
 
// Start the server
app.listen(port);
console.log('Starting the server on: http://localhost:' + port);

// bundle for the routes
var apiRoutes = express.Router();

// Login an user (POST http://localhost:8080/api/login)
apiRoutes.post('/login', function(req, res) {
	console.log(req.header);
	console.log(req.body);

	//Find for an user with the given credentials
	User.findOne({
		"username": req.body.username
	}, function(err,user){
		if (err) throw err;

		if(!user){
			res.json({success:false, message:'Failed to login, the user does not exist'});
		} else if(user){
			//If the user is found, check if password matches
			if(user.pass == req.body.pass){
				//If the password is right, create a token
				var token = jwt.sign(user, app.get('myprecious'), {
          		expiresIn: 1440 // expires in 24 hours
          		});
          		res.json({
          			success: true,
          			message: 'Authenticated',
          			token: token
          		});
			} else {
				res.json({success:false, message:'Failed to login, wrong password'});
			}
		}
	})
});


// This route is used as a middleware to verify a token
apiRoutes.use(function(req, res, next){

	//Get token
	var token = req.body.token || req.query.token || req.headers['x-access-token'];
	console.log(token);
	if(token){

		jwt.verify(token, app.get('myprecious'), function(err, decodedToken){
			if(err){
				return res.json({success: false, message: 'Failed to authenticate token'});
			} else {
				req.decodedToken= decodedToken;
				next();
			}
		});
	} else {
		//If no token was given return an error
		return res.status(403).send({
			success: false,
			message: 'You have to provide a token'
		});

	}
});


// get all doors state (GET http://localhost:8080)
apiRoutes.get('/doors/getAll', function(req, res) {
  var output = child_p.execSync('app/bin/SmartBerryWrapper -d', { encoding: 'utf8' });
  res.send(JSON.parse(output));
});

// get all lights state (GET http://localhost:8080)
apiRoutes.get('/lights/all', function(req, res) {
  var output = child_p.execSync('app/bin/SmartBerryWrapper -l', { encoding: 'utf8' });
  res.send(JSON.parse(output));
});

// set all lights state simultaneously (GET http://localhost:8080)
apiRoutes.post('/lights/all', function(req, res) {
  var output = child_p.execSync('app/bin/SmartBerryWrapper -a '+ req.body.value, { encoding: 'utf8' });
  res.status(200).send({
			success: true,
			message: 'Thanks'
		});
});

// set all lights state simultaneously (GET http://localhost:8080)
apiRoutes.post('/lights', function(req, res) {
  var pinNum= req.body.pin;
  var value=req.body.value;
  console.log("entering lights");
  console.log(pinNum + " "+ value);
  var output = child_p.execSync('app/bin/SmartBerryWrapper -s '+ pinNum +" "+value , { encoding: 'utf8' });
  res.status(200).send({
			success: true,
			message: 'Thanks'
		});
});
 
// get garage state (GET http://localhost:8080)
apiRoutes.get('/garage/state', function(req, res) {
  var output = child_p.execSync('app/bin/SmartBerryWrapper -g', { encoding: 'utf8' });
  res.send(JSON.parse(output));
});

apiRoutes.get('/camera', function(req,res){
	child_p.execSync('app/bin/SmartBerryWrapper -t', { encoding: 'utf8' });
	var pic = fs.readFileSync('app/data/webcamshoot.jpeg');
	var base64 = new Buffer(pic, 'binary').toString('base64');
	var output={"picture": base64};
	res.send(JSON.stringify(output));
});


// connect the api routes underut /api/*
app.use('/api', apiRoutes);

