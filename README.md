# jaccuziArduiControler
Jaccuzi management code for arduino Mega board (water circulation + heater + ozoner cycles + heure pleines/heures creuse )

Hardware :

1 arduino MEGA card

1 module RTC DS1307 ( bus I2C)

1 LCD  16 cols x 2 lines

1 2 Relay 10A /220V with freewheel and opto card

     for ozoner
     for heater circulation pump

1 4 Relay 10A/220V  with freewheel and opto card

     for heater . 4 Relays working in parrallel to drain suffisant current for heater (3kWatts)
     so almost 3.5 Amp for each relay

1 Relay 10A/220V with freewheel and opto card

     for leakPump (unable to fix a small leak in the jaccuzi heater circuit, so collecting leak and re injecting it in the jaccuzi
     
1 Water level detector

1 Small 12V/1A pump for managing the leak

1 9V/2A alimentation for arduino + RTC module

1 5V/2A alimentation for relays circuits / lcd backlight / leds / rvb leds

1 12V/2A alimentation for leak pump

1 a fistfull of resitors / colored leds  and rvb leds

1 variable resitor for lcd contrast 

The rest from the jacuzzi
   
   temperature sonde
   water circulation pump
   heater 
   ozoner
   
   .....
   
   
