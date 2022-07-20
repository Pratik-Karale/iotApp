import {StyleSheet,ScrollView, Pressable,Button,TouchableOpacity, View ,Text} from 'react-native';
import * as React from 'react';
import RoomBtn from './RoomBtn';
function makeTitleCased(str){
    return str[0].toUpperCase()+str.slice(1)
}

export function Room({name,buttonsData,sendButtonData}){
    // console.log(roomObj)
    React.useEffect(()=>console.log("!@!@@!@!K!@K!@KK@@K!"),[buttonsData])
    return(<View style={styles.room}>
                <Text>{makeTitleCased(name)}</Text>
                <View style={styles.roomButtons}>
                {buttonsData.map(button=>
                    <RoomBtn button={button} roomName={name} sendButtonData={sendButtonData}/>
                )}
                </View>
            </View>)
}
const styles=StyleSheet.create({
    room:{
        width:"100%",
        border:"1px solid cyan",
        borderRadius:10,
        padding:10,
        marginTop:15
    },
})