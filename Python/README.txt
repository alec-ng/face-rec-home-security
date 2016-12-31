Contents
---

- main.py: main routine run on the Pi
- trainedFisherModel.xml: trained model that learned three faces
- haacascade_frontalface_default.xml: OpenCV trained model for detecting faces
- DE2_success_failure.py: main setup and utility file enabling communication between DE2 and Pi

- /communication: programs and python bindings for the Pi to communicate with the DE2
- /logging: all PDF generation and Twilio alert scripts
- /training-utilities: scripts to facilitate the training phase of the face reocgnizer

Execution
---

- Connect Pi to DE2 via breadboard and GPIO
- Load Quartus project and NiosII project
- run main.py and scheduler.py
- Follow instructions on DE2.
