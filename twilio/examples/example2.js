// Download the Node helper library from twilio.com/docs/node/install
// These vars are your accountSid and authToken from twilio.com/user/account
var accountSid = process.env.TWILIO_ACCOUNT_SID;
var authToken = process.env.TWILIO_AUTH_TOKEN;
var client = require('twilio')(accountSid, authToken);


console.log("Account ID" + accountSid);
 
client.calls.create({
    url: "http://demo.twilio.com/docs/voice.xml",
    to: "+18043878834",
    from: "+18042922701"
}, function(err, call) {
//    process.stdout.write(call.sid);
});
