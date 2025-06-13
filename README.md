NPC2 is a robotics team from Caracas, Venezuela nationally representing Colegio Jefferson in the World Robotics Olimpiad. We have a car named Crazy Diamond that has one motor, one servomotor, one PixyCam2, two ultrasonic sensors, one Arduino R4, one voltage regulator, one H bridge, one 7.6 v battery, and an ackerman sterring wheel.
Team Picture:![picture of the team](https://github.com/user-attachments/assets/0116211c-a6b6-41da-97f7-951bd6472900)
From left to right: Juan Ignacio González Cardesin,Andrea Jaimes Bselis,Leonardo Carrasquero Recchuiti.
We are competing in the future engineers category of the W.R.O.
The future engineers category consist in 3 mayor challenges:
The first challenge consist that the car has to do 3 complete laps in the track for then stop in the same place the car started.
The second challenge consist that the car will has to do laps but in these case there are some obstacles that depending on the color, the car will have to go left or right.
The last challenge consist that the car will started in a parking slot and it has to do the second challenge again, but in this case  the car will have to stop in the parking slot in parallel.

For this the first thing we do, was to organize different things for example the materials, the chasis we will use, and in what microcontroller we will program.
After a long period of discussion we have already the different materials we will use that are:
1. The microcontroller that we used is the Arduino R4 WIFI. The Arduino UNO R4 WIFI is an upgraded version of the Arduino UNO, featuring Wi-Fi and Bluetooth connectivity (in this case, due to the competition the Wi-Fi and Bluetooth connectivity is disable). It’s built around the Renesas RA4M1 microcontroller, which is a 32-bit ARM Cortex-M4 running at 48 MHz, offering significantly more power than the previous 8-bit ATmega328P in the UNO R3. Also this Arduino just needs 5V to start working and in short words, this will be the brain of the car. The Arduino R4 Wi-Fi has 14 digital pins and 6 analogs, so this make it perfect for us to works. Besides is very easy to code in it as it use a subdivision of C++ called Arduino C++.


Arduino R4:![descarga](https://github.com/user-attachments/assets/77c6d0bc-d8ed-4c2c-aaf1-d589cc2190f4)


2. The electronic device we will use to detect colors will be the pixy cam 2 that is a compact, self-contained vision sensor designed to learn objects by their colors. It processes images and quickly outputs data such as the object's signature.
   
Pixy cam: ![Pixy-2 1-Smart-Vision-Sensor-Object-Tracking-Camera](https://github.com/user-attachments/assets/66575a41-1351-47f3-9a1f-872ceead4ada)


3. To help us know where, when, and to mantain position. We will use ultrasonic sensors that uses sonar to measure the distance between itself and an object. It can measure between 2cm to 400 cm, and it operates 40 kHz. To complete the challenges, we used 2 ultrasonic sensors that are in the sides of the car, and are program in way that they will be like a second confirmation of when the car has to cross.

    Photo of ultrasonic sensor: ![Ultrasonic-Sensor (1)](https://github.com/user-attachments/assets/d6b3bff4-a4e4-48a0-98d6-80e1829464db)

   
4. To power all this we use the Zeee battery Shorty of 2200 mAh, of 2 Lithium polymer ,from Zeee. This battery weight 98 g. It does 7,4V, and its dimmensions are 73mm*34mm*18mm.

   Battery: ![71juzktL4dL _AC_UF894,1000_QL80_](https://github.com/user-attachments/assets/ed4bb08f-dce2-4e19-8e15-5ce876a3e188)

5. To power the motor, and regulates their speed and voltage, we use an H-Bridge, especially the L298N that is a dual H-bridge motor driver module designed to control the speed and direction of DC and stepper motors. It operates within a voltage range of 5V to 35V. We connect the H-Bridge to the Arduino, using the L298N as an intermediary between the Arduino R4 and the motors like the servomotor.

   L298N: ![dual-h-bridge-motor-driver-l298n-44325-750x750](https://github.com/user-attachments/assets/50f5d1bb-c85c-4b46-b90e-ffeaee35d658)

6. To regulate the voltage and electricity, we use a voltage regulator that is connected directly to the battery and also powers the DC motor.

   Photo of the voltage regulator:
   ![modulo-voltaje-ajustable-con-voltimetro-generico-lm2596-step-down-led-digital-2035-2612-1](https://github.com/user-attachments/assets/ea85fa16-83b9-4891-b576-245e0ad8913d)}

7. For last but not least we have the Servo motor and the DC motor, that are very important because this electronical attachments will help us that the car can move and change dirrections. In the case of the Servo motor, this one is connected to an Ackerman Steering Wheel that is a physical steering mechanism designed based on Ackermann geometry with the idea that during a turn the inner wheel should turn sharper than the outer wheel so both wheels follow smooth path. If you are wondering, the Ackerman geometry is a system that ensures a smooth turn by making the inner wheel turn more than the outer one. Meanwhile, the DC motor is part of a mechanism of differents gears where it makes possible the movement of two different wheels with just one motor. This mechanism was created using 3D printers.

   Ackerman steering wheel and Servo photo:
   ![61U4BQ34BkL _AC_SX522_](https://github.com/user-attachments/assets/a5e1931c-8a38-4a1e-971f-afa697b164bb)

   Mechanism of the DC motor:
   ![Screenshot 2025-06-12 222236](https://github.com/user-attachments/assets/89c35461-acf2-4244-ba4f-b824a8509724)



   


















 

