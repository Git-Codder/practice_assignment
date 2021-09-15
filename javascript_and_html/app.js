var bodyParser = require('body-parser'),
    express = require('express'),
    request = require('request'),
    path  = require('path'),
    app = express();
    
    app.use(express.static("public"));
    app.set('view engine', 'ejs'); 

    app.use('/', express.static(path.join(__dirname, '/')))

    
    app.get("/", async(req,res) => {
        try {
            res.render("customerBug.ejs");
        } catch (err) {
            console.log(err.message);
        }
    });

// server listening 
app.listen(process.env.PORT || 5000,process.env.IP,function(){
    console.log("App is listening Now....!");
});