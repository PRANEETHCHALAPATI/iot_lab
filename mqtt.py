import paho.mqtt.client as mqtt

broker_address="192.168.173.114" // ip of the mobile device we noted from ifconfig command
client=mqtt.Client("PiClient")
client.connect(broker_address)

def on_message(client,userdata,message):
    print("Message received"+message.payload.decode("utf-8"))
    client.publish("ESP32/Acknowledgement","Message received from from ESP32, sent from Pi")

client.on_message=on_message
client.subscribe("ESP32/Temperaturedataread")
client.loop_start()
while True:
    pass