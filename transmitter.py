import cv2 as cv
import mediapipe as mp
import datetime
import socket
import time
import math

# Configure your ESP32 server details
SERVER_IP = '192.168.74.232' #192.168.14.234
SERVER_PORT = 80  # Replace with the port number your ESP32 is listening on

# Initialize MediaPipe Hands and OpenCV
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(min_detection_confidence=0.8)
mp_draw = mp.solutions.drawing_utils
cap = cv.VideoCapture(0)

# Gesture command mapping
commands = {
    'STOP': 's',
    'FORWARD': 'f',
    'BACKWARD': 'b',
    'MSR': 'a',
    'MSL': 'c',
    'RL': 'd',
    'RR': 'e',
    'MRF': 'g',
    'MRB': 'h',
    'MLF': 'i',
    'MLB': 'j'
}

def send_command(command, s):
    try:
        command = bytearray(command,'utf-8')
        s.send(command)
    except Exception as e:
        print(f"Error: {e}")

def recognize_gesture(landmarks):
    thumb_tip = [landmarks[4][0], landmarks[4][1]]
    index_tip = [landmarks[8][0], landmarks[8][1]]
    middle_tip = [landmarks[12][0], landmarks[12][1]]
    ring_tip = [landmarks[16][0], landmarks[16][1]]
    pinky_tip = [landmarks[20][0], landmarks[20][1]]
    palm_base = [landmarks[0][0], landmarks[0][1]]

    thumb_base = [landmarks[2][0], landmarks[2][1]]
    index_base = [landmarks[5][0], landmarks[5][1]]
    middle_base = [landmarks[9][0], landmarks[9][1]]
    ring_base = [landmarks[13][0], landmarks[13][1]]
    pinky_base = [landmarks[17][0], landmarks[17][1]]

    base = [thumb_base, index_base, middle_base, ring_base, pinky_base]
    tips = [thumb_tip, index_tip, middle_tip, ring_tip, pinky_tip]

    list = []

    for i in range(5):
        if i==0:
            if math.dist(thumb_tip, pinky_base) > math.dist(pinky_base, thumb_base):
                list.append(1)
            else:
                list.append(0)
        else:
            if math.dist(tips[i], palm_base) > math.dist(base[i], palm_base):
                list.append(1)
            else:
                list.append(0)

        # Define gesture logic
    if list == [0,0,0,0,0]:
        return 'STOP'
    elif list == [1,1,1,1,1]:
        return 'FORWARD'
    elif list == [0,1,0,0,0]:
        return 'BACKWARD'
    elif list == [0,1,1,0,0]:
        return 'MSR'
    elif list == [0,1,1,1,0]:
        return 'MSL'
    elif list == [0,1,1,1,1]:
        return 'RL'
    elif list == [0,1,0,0,1]:
        return 'RR'
    elif list == [1,1,0,0,0]:
        return 'MRF'
    elif list == [1,1,1,0,0]:
        return 'MRB'
    elif list == [1,1,1,1,0]:
        return 'MLF'
    elif list == [1,1,0,0,1]:
        return 'MLB'
    return 'STOP'

def main():
    # Create and connect the socket
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((SERVER_IP, SERVER_PORT))
            print("Connected to server")
            time.sleep(2)  # Give some time for the connection to stabilize
            prev_gesture = ''
            prev = 0.0
            while True:
                now = datetime.datetime.now()
                ret, frame = cap.read()
                if not ret:
                    print("Failed to read frame")
                    break
                
                img_rgb = cv.cvtColor(frame, cv.COLOR_BGR2RGB)
                results = hands.process(img_rgb)
                img_bgr = cv.cvtColor(img_rgb, cv.COLOR_RGB2BGR)
                
                if results.multi_hand_landmarks:
                    for hand_landmarks in results.multi_hand_landmarks:
                        mp_draw.draw_landmarks(img_bgr, hand_landmarks, mp_hands.HAND_CONNECTIONS)
                        
                        # Extract landmark positions
                        landmarks = []
                        for id, lm in enumerate(hand_landmarks.landmark):
                            h, w, c = img_bgr.shape
                            cx, cy = int(lm.x * w), int(lm.y * h)
                            landmarks.append((cx, cy))
                        
                        # Recognize gesture
                        if now.second % 1 == 0 and prev != now.second:
                            gesture = recognize_gesture(landmarks)
                            if gesture != prev_gesture:
                                cv.putText(img_bgr, gesture, (90, 360), cv.FONT_HERSHEY_PLAIN, 3, (0, 255, 0), 5)
                                send_command(commands[gesture], s)
                                print(f"Gesture recognized: {gesture}")
                            prev_gesture = gesture
                prev = now.second
                
                cv.imshow("Gesture Recognition", img_bgr)
                if cv.waitKey(1) & 0xFF == ord('q'):
                    break

    except Exception as e:
        print(f"Connection Error: {e}")
    finally:
        cap.release()
        cv.destroyAllWindows()
        s.close()

if __name__ == "__main__":
    main()
