var exec = require('child_process').exec;
var bodyParser = require('body-parser')
const express = require('express');
const app = express();

let info;
var child = exec('./database');

app.use(function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    next();
});

app.get('/', (req, res) => {
    execPromise(setup[4]);
    res.json(JSON.parse(info));
});

// app.use(bodyParser.json());
app.post('/', (req, res) => {
    execPromise(req.param('command') + '\n');
    console.log(info);
    if(info === "[ ]"){
        res.json([]);
    }else{
        res.json(JSON.parse(info));
    }
});

app.listen(3000, () => console.log(`Running on port ${3000}!`));

let debug = false;

child.stdout.on('data', function(data) {
    if(debug){
        console.log(data);
    }
});
async function execPromise (command, args) {
    return new Promise((resolve, reject) => {
        child.stdin.setEncoding('utf8');
        child.stdin.write(command);
        // const child = spawn(command, args)

        child.stdout.on('data', (data) => {
            info = data;
            resolve();
        });

        child.stderr.on('data', (data) => {
            resolve();
        });

        child.on('close', (code) => {
            if (code !== 0)
                this.logger.error(`Command execution failed with code: ${code}`)
            else
                this.logger.info(`Command execution completed with code: ${code}`)
            resolve();
        });
    });
}

let setup = [
    'make table products fields itemName string, itemDescription string, itemImage string, rating unsigned, price unsigned\n',
    'insert into products values "Cheesecake", "Simple cheesecake that tastes good.", "https://www.jocooks.com/wp-content/uploads/2018/11/new-york-style-cheesecake-1-2.jpg", 3, 2099\n',
    'insert into products values "Ice Cream Cake", "Cake but with ice cream.", "https://www.lifeloveandsugar.com/wp-content/uploads/2014/10/Mocha_Brownie_Ice_Cream_Cake13.jpg", 4, 2899\n',
    'insert into products values "Lasagna", "Some warm hot Italian food that is hecka good.", "https://www.thewholesomedish.com/wp-content/uploads/2018/07/Best-Lasagna-550.jpg", 3, 2599\n',
    'select * from products\n'
];

setup.forEach(e => {
    execPromise(e);
})