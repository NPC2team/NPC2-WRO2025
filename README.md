![NPC2](https://github.com/user-attachments/assets/f0175fc0-a37f-4198-93c1-9c4c6ef82ea9)
![GitHub commit activity](https://img.shields.io/github/commit-activity/t/NPC2team/NPC2-WRO2025) ![GitHub commit activity](https://img.shields.io/github/commit-activity/w/NPC2team/NPC2-WRO2025) ![GitHub last commit](https://img.shields.io/github/last-commit/NPC2team/NPC2-WRO2025) ![Static Badge](https://img.shields.io/badge/WRO-2025-green?style=flat)

## Table of Contents

- [Our Team](#our-team)
- [Materials](#materials)
- [Car's Construction](#cars-construction)
- [Challenge Problem Solving](#challenge-problem-solving)
- [Electrical Design](#electrical-design)
- [Ackermann Steering Mechanism](#ackeman-steering-mechanism)


## Our Team

NPC2 is a robotics team from Caracas, Venezuela nationally representing Colegio Jefferson in the World Robotics Olimpiad.  
We have a car named Crazy Diamond and we will be explaning every single detail about him in this repository.
Team Picture:![picture of the team](https://github.com/user-attachments/assets/0116211c-a6b6-41da-97f7-951bd6472900)
From left to right: Juan Ignacio González Cardesin,Andrea Jaimes Bselis,Leonardo Carrasquero Recchuiti.
We are competing in the future engineers category of the W.R.O.
The future engineers category consists in 3 mayor challenges:

The first challenge states that the car has to do 3 complete laps in the track and upon finishing stop in the same place it started.

In the second challenge, the car has to do the same three laps while evading obstacles, these oblatacles will vary from color being red or green and depending on the color the bcar while have to evade them via the right (red) or left (green)  .

During the last challenge the car will start in a parking spot and it has to do the second challenge again, but in this case  the car will have to park in the parking spot , this parking must be parelel parking.

## Materials

For this competition we had to organize and coordinate with each other in order to narrow down the materials we will use. 
We ended up diciding on the following materiales: one motor, one servomotor, one PixyCam2, three ultrasonic sensors, one Arduino R4, one voltage regulator, one H bridge, one 11.1 v battery, and an ackerman steering mecanisim that came with the chasis. 
Below you will see what each material will be used for and why we chose them.

1. The microcontroller that we used is the Arduino R4 WIFI. The Arduino UNO R4 WIFI is an upgraded version of the Arduino UNO, featuring Wi-Fi and Bluetooth connectivity (in this case, due to the competition's rules the Wi-Fi and Bluetooth connectivity is disabled). It’s built around the Renesas RA4M1 microcontroller, which is a 32-bit ARM Cortex-M4 running at 48 MHz, offering significantly more power than the previous 8-bit ATmega328P in the UNO R3. Also this Arduino just needs 5V to start working and in short words, this will be the brain of the car. The Arduino R4 Wi-Fi has 14 digital pins and 6 analogs, so this makes it perfect for us to work. Besides, it's very easy to code in it as it uses a subdivision of C++ called Arduino C++.


Arduino R4:![descarga](https://github.com/user-attachments/assets/77c6d0bc-d8ed-4c2c-aaf1-d589cc2190f4)


2. The electronic device we will use to detect colors will be the pixy cam 2 that is a compact, self-contained vision sensor designed to learn objects by their colors. It processes images and quickly outputs data such as the object's signature.
   
Pixy cam: ![Pixy-2 1-Smart-Vision-Sensor-Object-Tracking-Camera](https://github.com/user-attachments/assets/66575a41-1351-47f3-9a1f-872ceead4ada)

[Why Pixy?](https://github.com/NPC2team/NPC2-WRO2025/blob/master/Materials/why%20was%20pixy%20chosen.pdf)



3. To help us know where, when, and how to mantain position, we will use ultrasonic sensors that use sonar to measure the distance between themselves and an object. The sensors can measure between 2cm to 400 cm, and they operate at 40 kHz. To complete the challenges, we used 3 ultrasonic sensors. Two of them being in the sides of the car, and one in the front. They are programmed in way so that they will confirm when the car has to cross.

    3D model of ultrasonic sensor: ![Ultrasonic-Sensor (1)](https://github.com/user-attachments/assets/d6b3bff4-a4e4-48a0-98d6-80e1829464db)

   
4. To power all this we used the Zeee battery Shorty that has 2200 mAh, 3 Lithium polymer. This battery weighs 137 g. It has 11.1V, and its dimmensions are 75mm*34mm*26.5mm.

   Battery: ![71m+EHRrMrL](https://github.com/user-attachments/assets/fa1c7f04-95cc-4ecc-a46f-69529cfb2c18)
   

6. To power the motor, and regulate the speed and voltage, we use an H-Bridge, specifically the L298N which is a dual H-bridge motor driver module designed to control the speed and direction of the DC and stepper motors. It operates within a voltage range of 5V to 35V. We connected the H-Bridge to the Arduino using the L298N as an intermediary between the Arduino R4 and the motors.

   L298N: ![dual-h-bridge-motor-driver-l298n-44325-750x750](https://github.com/user-attachments/assets/50f5d1bb-c85c-4b46-b90e-ffeaee35d658)

7. To regulate the voltage and electricity, we used a voltage regulator that is connected directly to the battery and also powers the DC motor.

   Photo of the voltage regulator:
   ![modulo-voltaje-ajustable-con-voltimetro-generico-lm2596-step-down-led-digital-2035-2612-1](https://github.com/user-attachments/assets/ea85fa16-83b9-4891-b576-245e0ad8913d)

8. last but not least we have the Servo motor and the DC motor, that are very important because these electronic attachments will help the car move and change dirrections. In the Servo motor's case, it is connected to an Ackerman Steering Wheel that is a physical steering mechanism designed based on Ackermann geometry with the idea that during a turn the inner wheel should turn sharper than the outer wheel so both wheels follow a smooth path. If you are wondering, the Ackerman geometry is a system that ensures a smooth turn by making the inner wheel turn more than the outer one. Meanwhile, the DC motor is part of a mechanism of different gears where it makes the movement of two different wheels possible with just one motor. This mechanism was created using a 3D printer.

   Ackerman steering wheel and Servo photo:
   ![61U4BQ34BkL _AC_SX522_](https://github.com/user-attachments/assets/a5e1931c-8a38-4a1e-971f-afa697b164bb)

   Mechanism of the DC motor:
   ![Screenshot 2025-06-12 222236](https://github.com/user-attachments/assets/89c35461-acf2-4244-ba4f-b824a8509724)


Knowing this, you may wonder what is the chasis that we are going to use, after all is a very important part of the vehicle because without it, Crazy Diamond wouldn´t exist in the first place.
Well the chasis that we used is a metal chasis that already had the ackerman steering wheel, this chasis can be bought from Amazon. The dimensions of the original chasis are of 337*191*131mm.
[Chasis link](https://www.amazon.com/-/es/inteligente-codificado-estructura-anticolisi%C3%B3n-triangular/dp/B0CWTZC5FQ/ref=sr_1_7?crid=3D9Y448EALARV&dib=eyJ2IjoiMSJ9.bCJjQ8c7nkW4Nwuakx-PQ0JSlsAtqFOYd4IfrV90OSppyMg7DebPeTKPTXEKDJlfPcESpcsJSoPtTjKUi3ovc-TNKSxQ_JUGRNZ3x5tnm776BvoPmyBzOIg2gmtpw0X2vn1QENXU6xpZ87O_cs2MhxIkoNzD6WcaPQV7HH_46VwBi9P1fDxEZxWsTRry3HO04tfUn8vBew1MA0w_9aZ2eg.bfHSBu8WWMGvrkC-OKG4-P4m9GnF3JpKHgq5pyXknh0&dib_tag=se&keywords=ackerman+steering+kit&qid=1749764977&sprefix=ackerman+st%2Caps%2C124&sr=8-7) 


Photo of the chasis: ![61YIGLu0T0L _AC_SL1500_](https://github.com/user-attachments/assets/3b866ae3-cc4d-49d3-b05d-4d8c8e8187c9)

## Car's Construccion

After that we started disarming, destroying, and putting a lot of things in the car. Adapting the car, evolving it into a wonderful construction, putting the pieces together, and starting to test and view possible ideas for the challenges.

Example of how the proccess should look in Powerpoint: ![Screenshot 2025-06-12 224532](https://github.com/user-attachments/assets/95bb5eab-1ceb-4f80-9074-d34f4e8d0cf4)

The first thing we did to the original chassis was to cut the sides that were near the back wheels and we also cut the chassis in half. We did this so we have less length and avoid the problem of being near the maximum length.

We cut the sides of the chassis so we could add a mechanism that makes it possible for our two back wheels to use only one motor.

Photo of the parts that were about to be cut off:
![hola](https://github.com/user-attachments/assets/2bcc6786-80e5-4b6b-9bda-23d1080794a0)

Photo after the proccess of the car´s adaptation:
![Car after adaptation](https://github.com/user-attachments/assets/67911118-9095-4905-9a5a-4999bb856103)


After putting everything where it must go, the car ended up like this:

![Back of the vehicle](https://github.com/user-attachments/assets/d84f18ec-d28c-4e1a-b476-ad0eacad9e0f)}



![Front of the vehicle](https://github.com/user-attachments/assets/4aa69e8d-950e-4e0f-b923-1388caeebf31)



![Up view of the vehicle](https://github.com/user-attachments/assets/3d93f163-7ada-4756-86f7-f130d9bfa369)


![Side 2 of the vehicle](https://github.com/user-attachments/assets/1cd57ae4-c6ca-4bbb-a0d7-5659cdb06ed6)



![Vehicle side1](https://github.com/user-attachments/assets/6e4e4bbf-1efd-4bb6-a8ce-6042c837e99a)

## Challenge Problem Solving

When we finished building the car, we were able to see possible solutions for the challenges.

For the first challenge, we initially planned to do it only with the Pixy camera. The camera signals would be orange and blue, and depending on the color, Crazy Diamond (our car) would spin clockwise or counterclockwise. At the same time, upon detecting the color, a variable will count the number of turns made.
However, we realized it was better to use the ultrasonic sensors for the first challenge, as they allow you to program a code that detects an opening and rotates toward it.
To reinforce the ultrasound idea, we realized it was easier to correct it every time it rotated. This was difficult with the Pixy camera. We also tried to use the VL53L0x or TOF sensor , but we ultimately decided against it because of non consistent measurements when the car was in movement.  We made a document that compared the ultrasonic sensors and the TOF.

[TOFvsULTRASONIC](https://github.com/NPC2team/NPC2-WRO2025/blob/master/Materials/Ultrasonic%20vs%20tof.pdf)

![8e7409_c0e539c39a5e4f6d9af293265917e344~mv2](https://github.com/user-attachments/assets/227bbb83-842f-42a5-80a2-90cf01292889)

With this we managed to complete the challenge, which can be seen through the link on YouTube.

[First Challenge](https://youtube.com/shorts/cBEeWWgM5bk)



In the second challenge, we combined the Pixy camera with the ultrasonic sensor. The Pixy camera's function would be to detect the red and green blocks. This would allow the car to move toward the blocks and then turn in the direction determined by the block's color.

The ultrasound would have the same function as in Challenge 1: to look for an opening for the car to turn.

Problems in both challenges:

In the first challenge, the main problem was the light illuminating the track, which caused the Pixy camera to misdetect colors or even ignore them, confusing the Arduino.

We managed to solve this problem by using only ultrasound and disabling the Pixy camera for this challenge.

![Pixy-2 1-Smart-Vision-Sensor-Object-Tracking-Camera](https://github.com/user-attachments/assets/c38f0298-1c55-4a4a-8b60-57655285e606)

The second problem was the car's weight, as the battery we were using weighed approximately 500 grams. We solved this by replacing it with a lighter one, that weighs 137 grams.

![716CISc+2RL _AC_SX466_](https://github.com/user-attachments/assets/ae512b6e-a400-4746-97d7-0c506d0fb135)

[Why Zeee battery 2200 mAh?](https://github.com/NPC2team/NPC2-WRO2025/blob/master/Energy%20explanation/DETAILED%20POWER%20CONSUMPTION%20ANALYSIS.pdf)

## Electrical Design

The electrical diagrams for the car are shown below.
![Final electric diagram with 3 ultrasonic sensors](https://github.com/user-attachments/assets/a63ccc0c-6770-41c2-a5b6-ffa303ebe780)


The circuit starts with a 12V battery that feeds all of the parts. For safety, a main power switch (SW1) turns on or off the whole circuit. The LM2596 step-down regulator is used to convert the 12V supply to a stable 5V output given that some parts need a lower voltage level. These controlled 5 volts are essential so we can power sensitive devices including sensors, the servo motor, and the pixy cam without risking overvoltage damage.

Acting as the main controller of the project is the Arduino UNO R4 WiFi. Directly from the 12V source, the Arduino is driven via its DC connector so ensuring it has enough power even if several accessories are running. Three HC-SR04 ultrasonic sensors are used for distance measurement; one sensor has trigger and echo pins wired to digital pins D2 and D4; another has pins D3 and D5. Moreover, a start button wired to digital pin D10 offers a dependable approach to safely start the action by means of a built-in 10k pull-up resistor.

Concurrent with these sensor links, the circuit drives a motor through an L298N motor driver module. The Arduino controls the enable input and the motor direction inputs (IN3 and IN4) using digital pins D6, D7, and D8. This design is vital for any mobile robotic system because it lets the motor travel in different speeds and directions. This motor controls simplicity and strength making it perfect for applications needing variable movement.

Another important element is the Pixy Cam (CMUcam5), which offers visual processing ability. Through an SPI connection, the Pixy Cam contacts with the Arduino; the MOSI, MISO, and SCK signals are linked to digital pins D11, D12, and D13 respectively, with a dedicated Slave Select (SS) line on pin A0. Real-time picture processing is made possible by this fast communication channel, hence allowing the system to carry out operations such object tracking or visual navigation. Moreover, an SG90 (often) is included to communicate with the mechanical parts, receiving control signals on a PWM pin and working at 5V from the regulator.

The precise pin assignments for sensors, motor drivers, and the camera together with the deliberate distribution of energy from the strong 12V supply to the precisely controlled 5V emphasize the thoughtful integration and equilibrium needed in such an arrangement. Effective mechanical motion control is provided by this design along with sensor data fusing to help with object tracking, obstacle detection, and several user-controllable capabilities.

![images](https://github.com/user-attachments/assets/ee1032ac-dd8a-4fbe-8475-3255ff89e473)

For more details you can check the document: [Diagram Explanation](https://github.com/NPC2team/NPC2-WRO2025/blob/master/Energy%20explanation/DETAILED%20DESCRIPTION%20OF%20ELECTRICAL%20DIAGRAM.pdf)



## ACKEMAN STEERING MECHANISM

An Ackerman steering mechanism is designed to guarantee that a vehicle's front wheels turn at the appropriate angles during a turn, the Ackermann steering mechanism is a cunning mechanical device that enables smooth and effective cornering that helps to avoid tire slippage.
Ackermann steering geometry is a smart configuration of linkages in vehicles designed to guarantee that during a turn the interior and outer front wheels trace separate circular paths. This is because the inner wheel should spin more quickly than the outer wheel to avoid tire scrubbing or slipping, as we said before.

![Figure-1](https://github.com/user-attachments/assets/183b187d-b60b-417c-9dff-150b1c3031a8)
This works because the inner front wheel has to move a closer radius than the outer front wheel as the car turns. In view of the fact, if both wheels were rotated at the same angle, tire wear would occur as the tires scraped against the road, which also reduces control. The Ackermann mechanism solves this issue by arranging the steering angles of each wheel in a way that employs trapezoids to form links. 

We use the Ackerman steering wheel because it reduces tire wear, it improves the handling, and it help the car take directions combined with the servo motor.
   


















 

