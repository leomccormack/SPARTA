# Raspberry Pi Versions Instructions

Note: we have only tested Raspberry Pi 4 Model B and Pi 3 Model B+, with RapianOS and Reaper (armv7l) as the host.

1. First install [Raspian](https://www.raspberrypi.org/downloads/raspbian/)  (We recommend the full install)
 
2. Install JUCE related dependencies
```
sudo apt-get update
sudo apt-get install x11proto-xinerama-dev libwebkit2gtk-4.0-dev libgtk-3-dev x11proto-xext-dev libcurl4-openssl-dev 
sudo apt install libasound2-dev
```
 
3. Install SAF related dependencies

```
sudo apt install liblapack3 liblapack-dev libopenblas-base libopenblas-dev liblapacke-dev
sudo apt-get install libhdf5-dev libnetcdf-dev libnetcdff-dev
```

4. Open and save the .jucer files and run the generated makefiles: 
```
make CONFIG=Release
``` 

## Alsa Audio Glitch RP4 FIX
https://www.element14.com/community/community/raspberry-pi/blog/2019/09/14/asla-audio-glitch-issue-pi-4-fix
First thing we will do is run open terminal ctrl + alt + t  (or from your quick launch)

type the following in bold.

sudo apt-get remove pulseaudio

now if it comes back that pulseaudio is not installed you will have to install it with:

sudo apt-get install pulseaudio

sudo reboot

after the reboot you will run the removal up top.

Test in terminal if you have sound now it might not be working quite yet we have one more line to run but you should hear something

when played through terminal.

aplay /usr/share/sounds/alsa/Noise.wav

alright a few more quick steps to complete now pulseaudio should be removed we are going to run the following

sudo apt autoremove

sudo /etc/init.d/alsa-utils reset

you can test again before reboot if you hear sound with the aplay command above.

sudo reboot

Now that the unit is rebooted we will select our analogue or HDMI as our default whichever you were using. for me it was the 3.5mm jack

Now open a web browser and go to youtube.com and play a video you should now have sound.


