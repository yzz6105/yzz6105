const express=require("express");
const app=express();
const mysql=require("mysql");
const bodyParser=require("body-parser");
app.use(bodyParser.urlencoded({extended:false}));
const port = 3000;

connector=mysql.createConnection({
    host:"localhost",
    user:"root",
    password:"",
    database:"nodejsdb"
})

connector.connect(function(err){
    if (err) throw err;
    console.log("Connected to db");
})

app.use(express.static('./login/login.html'));
app.use(express.static('./register/register.html'));
app.set('view engine','ejs');

app.get('/',function(req,res){
    res.sendFile('register.html',{root:__dirname+'/register'})
})

app.post('/register',function(req,res){
    ufname=req.body.fname;
    uusername=req.body.username;
    upassword=req.body.password;
    uemail=req.body.email;
    uphone=req.body.phone;
    sql='INSERT INTO users(fname, username, password, email,phone)VALUES ("'+ufname+'", "'+uusername+'","'+upassword+'","'+uemail+'",'+uphone+');'
    connector.query(sql,function(err,result){
        if(err) throw err;
        console.log(err);
        res.sendFile('login.html',{root:__dirname+'/login'})

    })
})

app.post('/home',function(req,res){
    vusername=req.body.username;
    vpassword=req.body.password;
    sql='select * from users where username="'+vusername+'" and password="'+vpassword+'"' 
    connector.query(sql,function(err,result){
        if(err) throw err;
        if(Object.keys(result).length>0 && result[0].username==vusername && result[0].password==vpassword){
            res.sendFile('home.html',{root:__dirname+'/home'})
        }
        else{
            res.send("<h1>User Not Found!</h1>")
        }

    })
})

app.post('/update',function(req,res){
    res.sendFile('update.html',{root:__dirname+'/update'})
})

app.post('/login',function(req,res){
    res.sendFile('login.html',{root:__dirname+'/login'})
})


app.post('/deleting',function(req,res){
    res.sendFile('delete.html',{root:__dirname+'/delete'})
})

app.post('/updatevalue',function(req,res){
    upfname=req.body.fname;
    upusername=req.body.username;
    uppassword=req.body.password;
    upemail=req.body.email;
    upphone=req.body.phone;
    if(upfname!=""){
        sql='update users set fname ="'+upfname+'" where username="'+upusername+'";'
        connector.query(sql,function(err,res){
            if(err) throw err;
        })
    }
    if(upusername!=""){
        sql='update users set username ="'+upusername+'" where username="'+upusername+'";'
        connector.query(sql,function(err,res){
            if(err) throw err;
        })
    }
    if(uppassword!=""){
        sql='update users set password ="'+uppassword+'" where username="'+upusername+'";'
        connector.query(sql,function(err,res){
            if(err) throw err;
        })
    }
    if(upemail!=""){
        sql='update users set email ="'+upemail+'" where username="'+upusername+'";'
        connector.query(sql,function(err,res){
            if(err) throw err;
        })
    }
    if(upphone!=0){
        sql='update users set phone ="'+upphone+'" where username="'+upusername+'";'
        connector.query(sql,function(err,res){
            if(err) throw err;
        })
    }
    res.send("<h1>Updated sucesfully</h1>")

})

app.post('/searching',function(req,res){
    res.sendFile('search.html',{root:__dirname+'/search'})
})

app.post('/searchuser',function(req,res){
    user=req.body.username;
    sql='select * from users where username="'+user+'";'
    connector.query(sql,function(err,resu){
        if(err) throw err;
        userdetail=resu;
        res.render("search.ejs",{userdetail:resu})
        console.log(userdetail)
    })
})

app.post('/deleteuser',function(req,res){
    user=req.body.username;
    sql='delete from users where username="'+user+'";'
    connector.query(sql,function(err,resu){
        if(err) throw err;
        res.send('<h1>User Deleted sucessfully!');
    })

})

app.post('/display',function(req,res){
    sql='select * from users';
    connector.query(sql,function(err,result){
        users=result;
        res.render("users.ejs",{users:result});
    })
})

app.listen(port,()=>{
    console.log("your app is running at http://localhost:3000/")
})

