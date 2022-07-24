    var unicodeToChar = function(text) {
        return text.replace(/\\u[\dA-F]{4}/gi, function(match) {
                return String.fromCharCode(parseInt(match.replace(/\\u/g, ''), 16));
            });
        }
        document.querySelectorAll(".room-btn").forEach(roomBtn=>{
          roomBtn.innerText=String.fromCodePoint(parseInt(roomBtn.innerText, 16))
            roomBtn.addEventListener("click",()=>{
                if(roomBtn.getAttribute("data-active")=="0"){
                    roomBtn.setAttribute("data-active","1")
                }else{
                    roomBtn.setAttribute("data-active","0")
                }
                if(roomBtn.getAttribute("data-btn")=="door"){
                  if(roomBtn.getAttribute("data-active")=="1"){
                    setTimeout(()=>{
                        roomBtn.setAttribute("data-active","0")
                        fetch(`/${roomBtn.parentNode.getAttribute("data-room")}/${roomBtn.getAttribute("data-btn")}/stop`)
                    },10000)
                  }
                }
                fetch(`/${roomBtn.parentNode.getAttribute("data-room")}/${roomBtn.getAttribute("data-btn")}/${+roomBtn.getAttribute("data-active")?"start":"stop"}`)
            })
        })
      function say(msg){
      console.log(msg)
      var utterance = new SpeechSynthesisUtterance();  
      utterance.text = msg;
      window.speechSynthesis.speak(utterance);
    }
    let pump=document.querySelector(`[data-btn="pump"]`)
    if (annyang) {
      // Let's define a command.
      const commands = {
        'water the plants': () => {
          say("watering plants!")
          pump.getAttribute("data-active")=="0"?pump.click():null
        },
        'stop watering the plants': () => {
          say("stopping to water plants!")
          pump.getAttribute("data-active")=="1"?pump.click():null
        },
        "turn room :roomNumber :device :state": (roomNumber,device, state) => {
          say("turning room " + roomNumber + " "+device+" " + state)
          let button;
          if(roomNumber=="one" || roomNumber=="won"){
            button=document.querySelector(`[data-room="room1"] [data-btn="${device}"]`)
          }else{
            button=document.querySelector(`[data-room="room2"] [data-btn="${device}"]`)
          }
            // return if the needed state is already there
            if((button.getAttribute("data-active")=="1"&& state=="on")||
               (button.getAttribute("data-active")=="0"&& state.slice(0,3)=="of")){
              return;
            }
            button.click()
        },
        "open main door":()=>{
          say("opening main door")
          let button=document.querySelector(`[data-btn="door"]`)
          if(button.getAttribute("data-active")==1)return;
          button.click()
        },
        "close main door":()=>{
          say("closing main door")
          if(button.getAttribute("data-active")==0)return;
          button.click()
        }
        
      };

      // Add our commands to annyang
      annyang.addCommands(commands);
    }
      annyang.start({paused:true})
      document.querySelector("#mic-btn").addEventListener("click",(e)=>{
        e.target.setAttribute("data-active",e.target.getAttribute("data-active")=="0"?1:0)
        if(e.target.getAttribute("data-active")=="0"){
          annyang.abort()
        }else{annyang.start()
        }
      })
      
