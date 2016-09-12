# payFONA

This project involves converting a Protell 7000 payphone and turning it into a functioning "Home Phone". 

# "Why?" 
The short answer is because I bought one on the cheap and thought that some day I'd like to see it working again. In the 7 years that I've owned this phone (and simply had it as a converesation piece in my home), I've debated many different ways to make it functional again. I first thought about getting a VOIP kit and trying that. I wasn't crazy about spending $100 on a piece of proprietary hardware that would lock me into a service of their choosing. The second route I thought about was using something like Google Voice or Twilio and making it a "wifi" phone. I tried this for a few months, even got a funny Twilio prank call app running on AWS, but it seemed that Twilio is best to make conference-like phone calls. It was important for me to be able to recreate the entire functionality of a payphone. So I finally went with my last idea that seemed the easiest but the most costly: Make it a cell phone. 

# What I Used
I used an Arduino and a FONA shield produced by AdaFruit. I can't say enough about the support system from both of these groups. This is probably the most complex electronic thing I've ever built on my own and the hardest code I've written in a while. I never had to ask anyone personally for help, but the entire internet was available for looking up questions and answers. 

The other advantage to using an Arduino (and maybe a reason I needed at least an Arduino in the first place) is that I could take some of the other switches and levers on the phone and make them also functional. The reciever becomes a switch to trigger a function and I'll be able to trigger a servo to ring a real bell (it's gotta have that bell!). There's a volume button on the phone that I can also wire up to do something (like maybe adjust the volume, amazing) and at some point I'd like to be able to trigger a behavior when you put coins in it. There's a functioning coin mech. I'm hoping the mechanics are basic enough that I can hack it to trigger a response to any type of coin put into it. 

# History
Sept 11, 2016 - What it does so far
1) Turn the reciever on to accept an incoming call 
2) Turn the reciever off to hang up on a call that is in progress
3) Turn on the reciever to make a call, then use the keypad to dial a 10 digit number. 

# To do
- All electronics are still on prototype breadboards. I'm going to have to transfer the wiring to a stationary board and document circuitry. They'll have to be wired in a way that allows me to switch the payphone's handset with the prototyping handset. 
- Smarter phone number detection. I'd like to put a few speed dial numbers in, maybe have them triggered by starting with a * or #. Yes, 911 works. I pay for it so it better. 


# Reference
The following sites were used as reference to work on most of the details
- [Adafruit FONA 800 Shield](https://learn.adafruit.com/adafruit-fona-800-shield)
- [Single Analog input for matrix keyboard ](http://www.instructables.com/id/Arduino-3-wire-Matrix-Keypad/step2/Wiring-up-the-resistors/)
- [More ideas about using a single input for a matrix keyboard](http://forum.arduino.cc/index.php?topic=8558.0)
- [Keypad inspiration that something was possible](http://playground.arduino.cc/Code/Keypad)
