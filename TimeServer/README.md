To connect to the NTP Server, you first must be connected to WiFi. (Follow the README.md in WiFi folder). To connect to a specific time server and change the timezone, go into ntp_server.h and change the defined NTPSERVER.

After this, in the main function, initialize the sntp by calling the following function:
```
initialize_sntp(); // Initialize the Time Server
```

Once the Microcontroller is connected to WiFi, you can simply call the following function:
```
update_time();
```

In order to retrieve the current time.
