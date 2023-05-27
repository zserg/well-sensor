# well-sensor
/lib/systemd/system/well-sensor.service

```
[Unit]
Description=Well sensor
After=multi-user.target
[Service]
Type=idle
ExecStart=/home/pi/well-sensor/venv/bin/python3 /home/pi/well-sensor/well-sensor.py
Restart=on-failure
[Install]
WantedBy=multi-user.target
```

GET http://192.168.0.38:5000/status

GET http://192.168.0.38:5000/status?led=0

GET http://192.168.0.38:5000/status?led=1

