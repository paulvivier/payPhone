# payPhone - Client

This is the code that resides on the device that will be inside the payPhone hardware.
Specific hardware is unknown at this point, but likely to be one or more of the following: Raspberry Pi, Arduino Yun, Arduino Uno, Arduinio Nano.

I am also using the 'server' module present in this repository, but it is not required. It simply needs to host an XML file that is able to be accessed on the open internet (but by Twilio in particular). I could manage this by modifying my in-home router properties, but I'd prefer to simply host this externally. AWS free tier should be enough to do this at this time.

