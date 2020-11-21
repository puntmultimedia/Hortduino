// Esta función se ejecuta cuando algún dispositivo publica un mensaje sobre un tema al que está suscrito su ESP8266
// Cambie la función a continuación para agregar lógica a su programa, cuando un dispositivo publica un mensaje a un tema que
// tu ESP8266 está suscrito, puedes hacer algo. EL ESP ESTÁ SUSCRITO (Recibe del Broquer) AL String messageTemp, si recibe "on" enciende led 

void callback(String topic, byte* message, unsigned int length) { // Función con parámetros tema, mensaje corto, longitud del mensaje
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;           //VARIABLE QUE RECOGE INFORMACION DEL BROKER
  
  for (int i = 0; i < length; i++) { // Suma los caracteres del mensaje
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println("---------");
  Serial.println(topic);

  // Feel free to add more if statements to control more GPIOs with MQTT

  // Si se recibe un mensaje en el tema room / lamp, verifica si el mensaje está encendido o apagado (on o off). Enciende la lámpara GPIO de acuerdo con el mensaje
  if(topic=="room/lamp"){
      Serial.print("Changing Room lamp to ");
      if(messageTemp == "on"){
        digitalWrite(lamp, HIGH);
        Serial.print("On");
      }
      else if(messageTemp == "off"){
        digitalWrite(lamp, LOW);
        Serial.print("Off");
      }
  }
  Serial.println();
}                 
