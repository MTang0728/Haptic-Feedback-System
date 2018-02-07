# Haptic-Feedback-System

The Haptic Feedback System aims to help upper arm amputees regain tactile sensations through haptic (vibrotactile) feedbacks.

The system currently is composed of an Arduino uno, a FSR (Force Sensitive Resistor) sensor, a DRV2605 haptic motor driver by Adafruit, and a vibrational disc motor.

Principle of Operations:

The system uses a closed loop, where the first half of the loop is capture force applied to/by finger and transmit it to the user through means of vibrations. The second half of the loop is achieved physiologically through patient's perception of the feedback cues and training.

For the first half of the loop:
- A FSR is to be attached to the finger tip of the prosthetic arm to measure forces of up to 20 lbs.
- The vibrating motor is to be attached to the rib cage area of the patient, each assigned based on the dermatonal region
* A total number of 5 pairs of sensor and motors are to be used. For the purpose of testing, only one pair has been built so far.

For the second half of the loop:



UPDATE
The FSR was desensitized due to execessive loads during testing. A potentiometer was used temporarily to simulate a changing load.
