import FontAwesome5 from 'react-native-vector-icons/FontAwesome5';
import { useState } from 'react';
import { StyleSheet } from 'react-native-web';
export default function RoomBtn({button,roomName,sendButtonData}){
    console.log("YAY",button)
    return <FontAwesome5 name={button.iconName}  
        size={30} 
        color={button.state?"blue":"cyan"}
        style={styles.roomButton}
        onPress={()=>{
            // console.log(button)
            console.log(button)
        if(button.state){
            sendButtonData(roomName,button.device,0)
            return
        }
        sendButtonData(roomName,button.device,1)
    }}/>
}

const styles=StyleSheet.create({
roomButtons: {
    flex: 1,
    flexDirection: "row",
    width: "100%",
    justifyContent: "space-around"
  }})