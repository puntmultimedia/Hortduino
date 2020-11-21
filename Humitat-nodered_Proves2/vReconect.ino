// ---SI SE CONECTA ------SUSCRIBCIÓN DEL ESP <---------AL BROQUER -ENCENDIDO DEL LED EN ESP POR ORDEN DEL BROQUER------------

// Change the function below if you want to subscribe to more topics with your ESP8266 
void reconnect() {                // This functions reconnects your ESP8266 to your MQTT broker (Instalado a través RASPBERRY PI)
  while (!client.connected()) {     // Loop until we're reconnected
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
  
   //-----CAMBIAR DE NOMBRE (ESP8266Office)PARA MULTIPLES CONEXIONES parece que solo es necesario cambiarlo aquí que es la función
    if (client.connect("ESP8266Moisture")) {  
      Serial.println("connected");  
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("room/lamp"); // Suscribción de ESP a Broquer --- CUIDADO
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
