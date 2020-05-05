# jaccuziArduiControler
Because my Gecko SPA controler card out of service for the heater part of my SPA, and need more than 500$ for replacement, 
i decided to start this spa management project with arduino Mega board (an arduino Uno with a 74HC595 is suffisant but require more cabling)  
(for managing failed features of the Gecko card : hot water circulation cycles + heater management + ozoner cycles + full hours/off peaks hours for heater + a leak management).

The rest of jacuzzi features (blower + water jets ) are not covered into this project, because still working with the Gecko card, and the Gecko panel of the jaccuzzi.

Hardware for the project:

1 arduino MEGA card

1 arduino mega prototype shield

1 RTC DS1307 module ( bus I2C) 
    (used for getting datetime +
    storing temperature consign into the small amount of persistant ram of the DS1307)

1 LCD  16 cols x 2 lines module

1 2xRelay 10A /220V with freewheel and opto module

     1 10A runned under 220V AC for ozoner
     1 10A runned under 220V AC for heater circulation pump

1 4xRelay 10A/220V  with freewheel and opto module

     4 10A runned under 220V AC for electrical heater . 
     4 Relays working in parallel to drain suffisant current for heater 
        without exceeding 10A relay max capacity (3kWatts for heater)
     so almost 3.5 Amp for each relay

1 1xRelay 10A/220V with freewheel and opto module

     1 10A runned under 12V DC for leakPump 
     (unable to fix a small leak in the jaccuzi heater circuit because of pvc pipes totally confined 
     into a big amount of polyurethane foam (almost impossible the access the leak without causing more damages), 
     so collecting the leak and re injecting it in the jaccuzi  when high level detected in the collector below the leak.)
     
1 Water level detector

1 Small 12V/1A pump for managing the leak

1 9V/2A alimentation for arduino + RTC module

1 5V/2A alimentation for relays circuits / lcd backlight / leds / rvb leds

1 12V/2A alimentation for leak pump

1 a fistfull of resitors / colored leds  and rvb leds

1 variable resitor for lcd contrast

1 IR receptor led

1 21 touchs small IR emmettor to manage consigned temp, forcing heater, and walking into the differents menus 

(please note that everything included (except power suplies and small pump) into the arduino mega starter kit for less than 40$ )

The rest from the jacuzzi
   
   temperature probe
   water circulation pump
   heater 
   ozoner
   
   .....
   
   
   
   To come soon :
   The UML diagram of differents classes designed for this project.
   
   
   Minds for future revisions :
   * Add a flow meter into the hot water circulation circuit to shudown the heater in case of pump failure and protect the heater form  overheat.
   (actually, the temperature sensor used is not taking temperature in the jaccuzzi, but is in contact with alluminium pipe of 
   the heater, in order to prevent overheat in case of flow stop in the circuit. 
   Nevertheless, totaly representative of the temperature into the jaccuzi with 1°C  precision).
   
   * Add ethernet/wifi connectivity for remote monitoring / management of the jaccuzi. 
   
   * Add a ph probe for water quality analysis and reporting.
