// Load the twilio module
var twilio = require('twilio');
 
// Create a new REST API client to make authenticated requests against the
// twilio back end
var client = new twilio.RestClient('ACeb7d56d94d52573b1a6e9bd3408e2b89', '5fb2483c2914ab745a87677e3742da53');
 
// Pass in parameters to the REST API using an object literal notation. The
// REST client will handle authentication and response serialzation for you.
client.sms.messages.create({
    to:'+18043878834',
    from:'+18042922701',
    body:'ahoy hoy! Testing Twilio and node.js'
}, function(error, message) {
    // The HTTP request to Twilio will run asynchronously. This callback
    // function will be called when a response is received from Twilio
    // The "error" variable will contain error information, if any.
    // If the request was successful, this value will be "falsy"
    if (!error) {
        // The second argument to the callback will contain the information
        // sent back by Twilio for the request. In this case, it is the
        // information about the text messsage you just sent:
        console.log('Success! The SID for this SMS message is:');
        console.log(message.sid);
 
        console.log('Message sent on:');
        console.log(message.dateCreated);
    } else {
        console.log('Oops! There was an error.');
    }
});
