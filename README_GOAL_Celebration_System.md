# ⚽ GOAL Celebration System — Arduino Interactive Match Experience

> **When engineering meets the excitement of football, even a simple goal can become a complete interactive experience.**

## Project Overview

This project is an interactive Arduino-based **GOAL Celebration System** developed as a practical application of the electrical engineering concepts I learned during **Week 2 of my Full Stack Robotics Engineering Internship at Smart Methods**.

Inspired by the atmosphere surrounding the World Cup matches, I designed a system that transforms a single button press into a full goal celebration involving motion, light, sound, and visual feedback.

When the push button is pressed, the system:

- Activates a DC motor
- Displays a goal message on a 16×2 LCD
- Plays a celebration sound using a piezo buzzer
- Runs animated lighting effects on a 12-LED NeoPixel Ring
- Returns automatically to the ready state after the celebration sequence

This project combines basic electrical engineering, embedded systems, user interaction, motor control, power distribution, and Arduino programming in one integrated simulation.

---

## Project Idea

The concept was to recreate the excitement of scoring a goal using a compact embedded system.

Instead of controlling only one output, the Arduino coordinates multiple components at the same time:

1. The user presses the push button.
2. The LCD changes from the ready message to `GOAL!!!`.
3. The DC motor starts rotating.
4. The piezo buzzer plays a short celebration tone.
5. The NeoPixel Ring displays green, white, and rainbow animations.
6. The system stops the celebration and returns to the ready screen.

The project demonstrates how several hardware outputs can respond together to one digital input.

---

## Simulation Output

Add a GIF, screen recording, or screenshot of the running Tinkercad simulation here.

```text
assets/goal-celebration-demo.gif
```

---

## Technologies and Tools

- **Arduino Uno R3**
- **C++ / Arduino**
- **Tinkercad Circuits Simulation**
- **LiquidCrystal Library**
- **Adafruit NeoPixel Library**

---

## Hardware Components

- 1 × Arduino Uno R3
- 2 × Full-size breadboards
- 1 × 16×2 LCD
- 1 × 10 kΩ potentiometer
- 1 × Push button
- 1 × DC motor
- 1 × NPN transistor
- 1 × Flyback diode
- 1 × Base resistor for the transistor
- 1 × Piezo buzzer
- 1 × 12-LED NeoPixel Ring
- 1 × Current-limiting resistor for the LCD backlight
- Jumper wires

---

## Arduino Pin Mapping

| Component | Arduino Pin |
|---|---:|
| LCD RS | D12 |
| LCD Enable | D11 |
| NeoPixel Ring IN | D10 |
| DC Motor Control | D9 |
| Push Button | D8 |
| Piezo Buzzer | D7 |
| LCD DB4 | D5 |
| LCD DB5 | D4 |
| LCD DB6 | D3 |
| LCD DB7 | D2 |

---

## LCD Connections

| LCD Pin | Connection |
|---|---|
| GND | Ground rail |
| VCC | 5V |
| VO | Middle pin of the 10 kΩ potentiometer |
| RS | Arduino D12 |
| RW | Ground |
| E | Arduino D11 |
| DB0–DB3 | Not connected |
| DB4 | Arduino D5 |
| DB5 | Arduino D4 |
| DB6 | Arduino D3 |
| DB7 | Arduino D2 |
| LED Anode | 5V through a current-limiting resistor |
| LED Cathode | Ground |

The two outer potentiometer pins are connected to 5V and GND, while the middle pin controls LCD contrast through VO.

---

## DC Motor Driver Circuit

The DC motor is not powered directly from an Arduino digital output.

The control circuit uses:

- **NPN transistor** as an electronic switch
- **Base resistor** to limit the current from Arduino D9
- **Flyback diode** across the motor terminals to protect the circuit from reverse voltage generated when the motor stops

### Motor Connections

- Motor terminal 1 → NPN collector
- Motor terminal 2 → 5V
- NPN base → Arduino D9 through a resistor
- NPN emitter → GND
- Flyback diode → connected across both motor terminals with correct polarity

---

## NeoPixel Ring Connections

| NeoPixel Pin | Connection |
|---|---|
| PWR | 5V |
| GND | Ground |
| IN | Arduino D10 |
| OUT | Not connected |

The number of pixels in the code must match the physical ring:

```cpp
const int pixelCount = 12;
```

---

## Power Distribution Between Breadboards

Both breadboards share the same Arduino power source.

The correct connection is:

```text
Arduino 5V
   ↓
Breadboard 1 positive rail
   ↓
Breadboard 2 positive rail

Arduino GND
   ↓
Breadboard 1 negative rail
   ↓
Breadboard 2 negative rail
```

Positive must always connect to positive, and ground must always connect to ground.

---

## System Behavior

### Ready State

The LCD displays:

```text
Ready...
Press Button
```

### Goal Celebration

When the button is pressed:

```text
GOAL!!!
Celebration!
```

At the same time:

- The DC motor rotates
- The buzzer plays a goal tone
- The NeoPixel Ring runs green and rainbow animations
- The system returns to its initial state after the celebration

---

## Key Engineering Lessons

### 1. Breadboard Power Rails Are Not Always Internally Connected

One of the most important lessons from this project was that the upper and lower power rails of a breadboard are separate unless they are connected with jumper wires.

A component may appear correctly connected to a positive or negative rail while receiving no power because that rail is isolated.

### 2. Multiple Breadboards Must Share Power and Ground Correctly

When transferring power between two breadboards:

- Positive connects to positive
- Negative connects to negative
- Both boards must share a common ground with the Arduino

A missing common ground can prevent signals and components from working correctly.

### 3. A Breadboard Does Not Reduce the Voltage

A properly connected breadboard does not significantly reduce the 5V supply. If a component works when connected directly to Arduino but not through the breadboard, the problem is usually:

- An isolated power rail
- A missing jumper
- A wire in the wrong row
- A missing common ground

### 4. Breadboard Rows Must Be Understood Before Wiring

The internal middle sections are connected in groups of five holes.

For example:

```text
a15–e15 are connected together
f15–j15 are connected together
```

The center gap separates both groups.

### 5. LCD Contrast Is Controlled by the Potentiometer

The LCD may be powered and initialized correctly but still appear blank if the potentiometer is not adjusted.

Rotating the 10 kΩ potentiometer changes the voltage at VO and controls text contrast.

### 6. LCD Backlight Requires Current Limiting

The LCD LED Anode should be connected through a current-limiting resistor.

Connecting the backlight directly to 5V may cause an overcurrent warning or component failure in the simulation.

### 7. Arduino Pins Cannot Be Shared Accidentally

Each component must have its own assigned pin unless the circuit and communication protocol are intentionally designed for sharing.

The original button pin was moved to D8 because D2 was required by LCD DB7.

### 8. Motors Should Not Be Driven Directly by Arduino Pins

A motor can draw more current than an Arduino digital pin can safely provide.

The transistor driver and flyback diode protect the Arduino while allowing the motor to operate safely.

### 9. NeoPixel Data Must Enter Through IN

The Arduino data wire must connect to the NeoPixel `IN` pin, not `OUT`.

The `OUT` pin is only used to connect another NeoPixel device in a chain.

### 10. Simulation Software May Need Restarting

When a correctly connected NeoPixel Ring suddenly stops responding, stopping and restarting the simulation or refreshing Tinkercad may reset the component.

Not every failure is a wiring failure. Sometimes the software simply decides to become part of the engineering challenge.

---

## Wire Color Organization

A consistent color convention makes the circuit easier to understand and troubleshoot.

| Function | Suggested Color |
|---|---|
| 5V / VCC | Red |
| GND | Black |
| LCD Data | Blue |
| LCD Control | Purple |
| Push Button Signal | Yellow |
| Motor Control | Orange |
| NeoPixel Data | Green |
| Buzzer Signal | Brown |
| Potentiometer Signal | Light Blue or Green |

The most important rule is consistency throughout the project.

---

## Skills Demonstrated

- Arduino programming
- Embedded systems integration
- Digital input processing
- LCD interfacing
- Motor control using an NPN transistor
- Flyback diode protection
- NeoPixel LED animation
- Piezo buzzer control
- Breadboard power distribution
- Circuit troubleshooting
- Wire organization and documentation

---

## Project Structure

```text
goal-celebration-system/
│
├── README.md
├── goal_celebration.ino
├── assets/
│   ├── circuit-overview.png
│   └── goal-celebration-demo.gif
└── circuit/
    └── tinkercad-link.txt
```

---

## Future Improvements

- Add a goal counter on the LCD
- Add two team-selection buttons
- Create different celebration modes
- Add a distance or motion sensor instead of a push button
- Use an external power supply for the motor and NeoPixel Ring in a physical prototype
- Build a miniature football field enclosure
- Add wireless control through Bluetooth or IoT

---

## Acknowledgment

This project was developed as a practical application of the electrical engineering concepts covered during **Week 2 of my Full Stack Robotics Engineering Internship at Smart Methods**.

It reflects my interest in combining robotics, embedded systems, software, and creative interaction design to transform technical concepts into engaging experiences.

---

## Author

**Wejdan AlHarby**

Artificial Intelligence, Software, and Robotics Enthusiast
