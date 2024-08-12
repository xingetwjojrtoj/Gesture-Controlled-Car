#Gesture-Controlled Car
This project utilizes mediapipe library to get landmark points of hand and using simple distance calculations between the coordinates to compute different hand gestures. Communication between ESP8266 and the running python script(to identify gestures) is performed via being on the same Wi-Fi network. These hand gestures are then sent to ESP8266 which is then responsible for turning the wheels accordingly to move forward, sideways, etc. The wheels used here are mecanum wheels which are a special type of wheels which can be used to move the car into a circle or move them sideways.

##Code walkthrough
- `ip_address.ino` file can be used to find the IP address of ESP8266 on the Wi-Fi network in case we aren't aware of it.
- `transmitter.py` file figures out the hand gestures and sends them to ESP8266.
- `esp_32_receiver.ino` is the file which is uploaded onto ESP8266 which performs actions based on the gestures identified by the python script.
