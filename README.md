# Light-Alarm-Clock
---
An Alarm Clock that is supposed to wake up the user by gradually turning on a bright light source. In my case, I have glued warm-white LEDs to a picture frame and use a diffusion layer to smooth the light a bit. The current time gets synced via an NTPClient and gets written to a real time clock connected to the ESP32. The ESP controlls the LED strip via a transistor and a PWM signal. The time for the alarm can be set via an html server that also displays the current time, the alarm time and whether the light is on, indipendent of the alarm. That is because the alarm can be turned on via a push button and the brightness can be changed via a potentiometer. The current, and the alarm time also get shown on a mini 128x64 pixel OLED display.

---

This is the first project, where I decided to design my own enclosure and 3d print it. The enclosure fits the a prototype board with all the electric components, a 12V inuput, the button to turn on the light and the potentiometer. The enclosure can be placed on the underside of the picture frame.
