import * as React from 'react';
import { StyleSheet, ScrollView, Pressable, Button, TouchableOpacity, View, Text } from 'react-native';
import { TopMenu } from './components/TopMenu';
import { TopNavbar } from './components/TopNavbar';
import { useState } from 'react';
import { Room } from './components/Room';

const App = () => {
  const [isMenuActive, setIsMenuActive] = useState(false)
  const [hallBtnsData,setHallBtnsData]=useState([])
  const [houseBtnsData,setHouseBtnsData]=useState([])
  const [username,setUsername]=useState("Username")
  let [ws] = useState(new WebSocket('ws://localhost:3000/'))

  const getHallBtnsData=()=>{return hallBtnsData;}
  const getHouseBtnsData=()=>{return houseBtnsData;}
  // React.useEffect(()=>{console.log(hallBtnsData);console.log("hall btns changed")},[hallBtnsData])
  // const [sendButtonData,setSendButtonData]=React.useState()
  const wsMessageHandler=(e)=>{
    let reader = new FileReader();
    reader.onload = function() {
      const {room,device,state}=JSON.parse(reader.result)
      if(room=="hall")updateBtnsData(setHallBtnsData,{room,device,state});
      if(room=="house")updateBtnsData(setHouseBtnsData,{room,device,state});
    }
    try{
      reader.readAsText(e.data);
    }catch(f){
      console.log(e.data)
    }
  }
  React.useEffect(()=>{console.log(hallBtnsData)},[hallBtnsData])
  React.useEffect(()=>{
    fetch("http://localhost:3000/hall/devices")
      .then(res=>res.json()).then(data=>setHallBtnsData(data))
    fetch("http://localhost:3000/house/devices")
      .then(res=>res.json()).then(data=>setHouseBtnsData(data))
   
    
    ws.onopen=()=> {
      console.log('A client Connected!');
    };
    ws.onmessage=(e)=>{wsMessageHandler(e)}
  },[])
  // setInterval(()=>console.log(hallBtnsData),1000)
  
  function updateBtnsData(setFunc,updateObj){
    setFunc(prevObj=>{
      // console.log("!#(*(!@#*(!*(@*(#*(",prevObj)
      // console.log("!#(*(!@#*(!*(@*(#*(",updateObj)
      for(const [index,btnObj] of Object.entries(prevObj)){
        if(btnObj["device"]==updateObj["device"]){
          prevObj[index]["state"]=updateObj["state"]
        }
    }
    return [...prevObj]
  })
    
    // console.log(22222,originalObj)
    // setFunc(originalObj)
  }
  function sendButtonData(room,device,state){
    // if(room=="hall"){
    //   updateBtnsData()
    // }
    // console.log(344334,hallBtnsData)
    ws.send(JSON.stringify({room,device,state}))
  }
  
  return (
    <View style={styles.app}>
      <TopNavbar onMenuBarClick={() => setIsMenuActive(!isMenuActive)} isMenuActive={isMenuActive} />
      {isMenuActive && <TopMenu />}
      <ScrollView>
        <Text style={styles.greeting}>Hello {username}!</Text>
        <View style={styles.rooms}>

          <Room name="house" buttonsData={houseBtnsData}  sendButtonData={sendButtonData}/>
          <Room name="hall" buttonsData={hallBtnsData}  sendButtonData={sendButtonData}/>

        </View>
      </ScrollView>
    </View>
  )
}

const styles = StyleSheet.create({
  app: {
    width: "100%",
    height: "100%",
  },
  greeting:{
    padding:20,
    fontWeight:500,
    fontSize:30
  },
  rooms: {
    width: "100%",
    padding:20,
  },
});
export default App
