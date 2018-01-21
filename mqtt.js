 var WebSocket_MQTT_Broker_URL = "MQTTBROKER";
 var MQTT_Client_ID = "randomID";
 var MQTT_Client = "";
 var message = "";

 function mqtt_Connect_with_Broker(){
   // MQTT Client object
   // Your custom settings
   MQTT_Client = new Paho.MQTT.Client(WebSocket_MQTT_Broker_URL,"PORT", MQTT_Client_ID+new Date().getTime());

   // callback handlers
   MQTT_Client.onConnectionLost = onConnectionLost;
   MQTT_Client.onMessageArrived = onMessageArrived;

   MQTT_Client.connect({onSuccess:onConnect,
                         useSSL: true,
                         userName:"customUserName",
                         password:"customPassword",
                        });
   }

 function mqtt_Subscribe_to_Topic(topic){
   MQTT_Client.subscribe(topic);
 }

 //Publish message
 function publishMessage(poruka){
   message = new Paho.MQTT.Message(poruka);
   message.qos = 0;
   message.destinationName = "Test/3";
   MQTT_Client.send(message);
 }

function onConnect() {
toastr.success("You are connected with the MQTT broker!");

//Subscribe to topics for notifications
mqtt_Subscribe_to_Topic('Test/1');
mqtt_Subscribe_to_Topic('Test/2');
}

function onConnectionLost(responseObject) {
   if (responseObject.errorCode !== 0) {
      toastr.error("Connection lost!")
   }
 }

function onMessageArrived(message) {

 switch(message.payloadString){
    case "ON":
    toastr.success("WiFi module is connected to MQTT broker!");  
    break;
    
    case "OFF":
    toastr.success("WiFi module lost its connection to MQTT broker!");  

    case "LEDON":
    toastr.success("LED IS ON!");  

    case "LEDOFF":
    toastr.success("LED IS OFF!");  
 }

}
 
$(document).ready( function() {
toastr.options = {
           "closeButton": false,
           "debug": false,
           "newestOnTop": false,
           "progressBar": false,
           "positionClass": "toast-top-right",
           "preventDuplicates": true,
           "onclick": null,
           "showDuration": "0",
           "hideDuration": "2000",
           "timeOut": "1500",
           "extendedTimeOut": "",
           "showEasing": "swing",
           "hideEasing": "linear",
           "showMethod": "slideDown",
           "hideMethod": "slideUp",
     
}
mqtt_Connect_with_Broker();
});

