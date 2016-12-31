#Facial Recognition Home Security System

Alec Ng, (David Henderson)[https://github.com/orgs/EECE-381/people/D-H], (Daniel Sallaway)[https://github.com/dansall], (Anna Gudimova)[https://github.com/Anna-Gudimova]

Overview
---

(Demo 1)[https://www.youtube.com/watch?v=Ze3dJgEQsDE] and (Demo 2)[https://www.youtube.com/watch?v=S9FLD0_HgnQ]

This project mimics a home security system that has a two step authentication process. Each user is represented by a unique 4 digit PIN code, which is first entered in a matrix keypad. Then, the user takes a picture through a webcam attached to an Altera DE-2 FPGA, which then is sent to a Raspberry Pi for face recognition logic. If the picture matches the person the ID entered represents, a servo is activated to represent unlocking of a lock.

Features
---

- Ability to create new users to add to the list of recognized users, as well as to train a new face to be recognized
- Facial recognition of known subjects, and ability to reject unknown subjects
- Two step authentication (keypad, face recognition) for added security and robustness
- Scheduler that logs all unauthorized attempts (i.e. incorrect keypad PIN, mismatching face)
- Real time SMS messaging to let master user know of an unauthorized attempt
- Bi directional communication between the DE2 and Pi
- User interface via the DE2, plus integration of several peripherals

Contents
---

/DE2
- Qsys file and Quartus project, plus relevant VHDL file to replicate hardware system that includes peripherals such as a webcam, matrix keypad, GPIO pins for bi directional communication with the Pi, switches, LCD screen and push buttons
- Nios II Eclipse C files that serve as the DE2 main program functions 

/Python
- Scripts to generate a new user, get raw images from the DE2 camera, preprocess all images and use OpenCV API to create a trained model
- Scheduler files to send SMS and texts
- Communication files with custom python bindings to receive and send information to the DE2, and reconstruction of a picture from the DE2


Technical Components
---

Languages:
- Python 
- VHDL
- C

Libraries:
- OpenCV ((installation guide)[https://alecng94.github.io/tech/Installing-OpenCV-Linux-Dist/])
- Twilio

Other:
- Quartus
- PostgreSQL

Hardware Components:
- Raspberry Pi 2 Model B
- Altera DE-2 FPGA Circuit Board
- Servo motor
- Webcam
- Matrix Keypad
