var connect = require('connect');
var serveStatic = require('serve-static');

// __dirname is the name of the directory the file is run
connect().use(serveStatic(__dirname)).listen(8080);

