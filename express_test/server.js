const express = require('express')
const app = express()
const server = require('http').createServer(app);
const WebSocket = require('ws');
const cors=require("cors")

app.use(cors({origin:"*"}))
const wss = new WebSocket.Server({ server:server });

wss.on('connection', function connection(ws) {
  console.log('A new client Connected!');
  ws.send('Welcome New Client!');
  ws.send("hello")
  ws.on('message', function incoming(message) {
      console.log('received: %s', message);
      ws.send(message)
    //   wss.clients.forEach(function each(client) {
    //     //   if (client !== ws && client.readyState === WebSocket.OPEN) {
    //           client.send(message);
    //         // }
    //     });
        
    });
});
app.get("/",(rq,rs)=>{
    console.log("main")
    rs.send("ok")
})
// app.get("/fgfg",(rq,rs)=>rs.json({msg:1212}))
app.get('/house/devices', (req, res) => res.status(200).json([{ device: "power", iconName: "bolt" ,state:0}]))
app.get('/hall/devices', (req, res) => res.json([
    {device: "fan", iconName: "fan", state:0},
    { device: "light", iconName: "lightbulb"  ,state:0},
    { device: "door", iconName: "door-open" ,state:0}
]))
server.listen(3000, () => console.log(`Lisening on port :3000`))