// Download the Node helper library from twilio.com/docs/node/install
// These vars are your accountSid and authToken from twilio.com/user/account

// You'll have to set these manually if you can't put in environment variables. 
 var accountSid = process.env.TWILIO_ACCOUNT_SID;
 var authToken = process.env.TWILIO_AUTH_TOKEN;
 var client = require('twilio')(accountSid, authToken);
//var client = require('twilio');

console.log("Account ID" + accountSid);
 
client.call.create({
    url: "http://demo.twilio.com/docs/voice.xml",
    to: "+18043878834",
    from: "+18042922701"
}, function(err, call) {
//    process.stdout.write(call.sid);
});

