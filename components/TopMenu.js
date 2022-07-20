import {StyleSheet,ScrollView, Pressable,Button,TouchableOpacity, View ,Text} from 'react-native';
import * as React from 'react';
import FontAwesome5 from 'react-native-vector-icons/FontAwesome5';

export function TopMenu(){
    return (<View style={styles.topMenu}>
      <TouchableOpacity title="Logs" color={"grey"}/>
      <TouchableOpacity title="Sign Out"/>
      <Pressable
          style={({ pressed }) => [{backgroundColor: pressed? 'darkgrey': 'grey'},styles.menuButton]}>
          {() => (<Text>Logs</Text>)}
        </Pressable>
        <Pressable
          style={({ pressed }) => [{backgroundColor: pressed? 'darkgrey': 'grey'},styles.menuButton]}>
          {() => (<Text>Sign Out</Text>)}
        </Pressable>
    </View>)
  }

  const styles=StyleSheet.create({
    menuButton:{
      width:"90%",
      padding:10,
      textAlign:"center"
    },
    topMenu:{
      alignItems:"center",
    },
  })