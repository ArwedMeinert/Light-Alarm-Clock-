# Light-Alarm-Clock
---
An Alarm Clock that is supposed to wake up the user by gradually turning on a bright light source. In my case, I have glued warm-white LEDs to a picture frame and use a diffusion layer to smooth the light a bit. The current time gets synced via an NTPClient and gets written to a real time clock connected to the ESP32. The ESP controlls the LED strip via a transistor and a PWM signal. The time for the alarm can be set via an html server that also displays the current time, the alarm time and whether the light is on, indipendent of the alarm. That is because the light can be turned on via a push button and the brightness can be changed via a potentiometer. The current, and the alarm time also get shown on a mini 128x64 pixel OLED display. If no alarm is set, it displays "Alarm" instead of the set alarm time.

---

This is the first project, where I decided to design my own enclosure and 3d print it. The enclosure was supposed to fit the a prototype board with all the electric components, a 12V inuput, the button to turn on the light and the potentiometer. The enclosure can be placed on the underside of the picture frame. Sadly, as can be seen in the pictures below, I massively underestimated the height of the pcb (I did not order a pcb, but used a prototyping pcb with THM components and had to hand solder them). Therefore the lid wouldn't close. I had to use spacers to fit everything in the enclosure. 

---

<img src="https://github.com/ArwedMeinert/Light-Alarm-Clock-/blob/main/Day-Light-Alarm-Clock/IMG_20230315_211313_312.jpg" alt= "Picture frame with the control box" width="50%" height="50%" >

I plan to replace the picture in the pictureframe (statistics of one of the everestings i've done) with a proper diffusion layer. I might need to increse the distance between the LED's and the diffusion layer for a proper effect.

---

<img src="https://github.com/ArwedMeinert/Light-Alarm-Clock-/blob/main/Day-Light-Alarm-Clock/IMG_20230315_211342_956.jpg" alt= "Picture frame with the control box" width="50%" height="50%" >

The OLED display shows the current time and, that no alarm is currently set. The light can be turned on manually using the button and dimmed with the potentiometer below the button.

---

<img src="https://github.com/ArwedMeinert/Light-Alarm-Clock-/blob/main/Day-Light-Alarm-Clock/IMG_20230315_211313_312.jpg" alt= "Picture frame with the control box" width="50%" height="50%" >

The LEDs don't get diffused properly because of the small distance betwenn the LED's and the "diffusion layer" (a piece of paper).-

---

<img src="https://github.com/ArwedMeinert/Light-Alarm-Clock-/blob/main/Day-Light-Alarm-Clock/IMG_20230315_212840_559.jpg" alt= "Picture frame with the control box" width="50%" height="50%" >

The alarm time gets displayed below the current time on the OLED display.
