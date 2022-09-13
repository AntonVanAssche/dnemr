#!/usr/bin/env python3
import requests
import serial

sent = False

def send_notification():
    discord_webhook_url = 'https://discord.com/api/webhooks/1019241011270131762/8SLh5P3S47vEN4KOEQNiP-fawbwssHYkEXvOXPuE308UhoCTYW0I9QIA2mUyhCrqh21M'
    Message = {
        "content": "Alarm triggered!",
    }
    result = requests.post(discord_webhook_url, json=Message)

    try:
        result.raise_for_status()
    except requests.exceptions.HTTPError as err:
        print(err)
    else:
        print("Payload delivered successfully, code {}.".format(result.status_code))

ser = serial.Serial('/dev/ttyACM0', 9600)
ser.flush()

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()

        if line == 'Alarm triggered!' and sent == False:
            send_notification()
            sent = True

            if input("Press enter to reset alarm") == '':
                sent = False
        else:
            print(line)

