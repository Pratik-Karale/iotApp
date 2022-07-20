import {StyleSheet,ScrollView, Pressable,Button,TouchableOpacity, View ,Text} from 'react-native';
import * as React from 'react';
import FontAwesome5 from 'react-native-vector-icons/FontAwesome5';

export function TopNavbar({onMenuBarClick,isMenuActive}){
    return (<View style={styles.topbar}>
      {
        isMenuActive?
        <FontAwesome5 name={'times'} onPress={onMenuBarClick} solid size={30} color="white" style={styles.menuIcon} />:
        <FontAwesome5 name={'bars'} onPress={onMenuBarClick} solid size={30} color="white" style={styles.menuIcon} />
      }    
      <Text  style={styles.topBarTitle}>Automagic</Text>
      <View></View>
    </View>)
  }

const styles=StyleSheet.create({
    topbar: {
        flex:1,
        flexDirection:"row",
        maxHeight:"9%",
        justifyContent:'center',
        padding:15,
        alignItems:'center',
        backgroundColor:"black",
      },
      topBarTitle:{
        color:"#ffff",
        fontFamily:"Arial",
        color:"cyan",
        fontSize:20,
      },
      menuIcon:{
        width:30,
        position:"absolute",
        top:10,
        left:10,
      },
})