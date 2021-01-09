const http = require('http');
const express = require('express');
const socketio = require('socket.io')

const app = express();
const server = http.createServer(app);
const io = socketio(server);

// SOCKET IO 
io.on('connection', ( socket ) => {
    
    // everything bellow executes for specific client when a new client connects 
    console.log('new connection')

    //executes when the client emits on the "message" event
    socket.on('message',(message)=>{
        console.log('_____________________________________')
        console.log("ESP-Data ->")
        console.log(message);
        console.log('_____________________________________')
    })

    //executes every 500ms    
    setInterval(()=>{
        socket.emit('vsm',"hello esp");//emits for the clients on the "vsm event"
        count++ 
    },500)
    
    //executes when the client disconnects
    socket.on('disconnect',()=>{
        console.log('____________DISCONNECTED_________________________')
    })

})

server.listen(process.env.PORT || 5000, () => console.log(`Server has started.`));