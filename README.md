# ⚽ Arduino Football GOAL Celebration System

> **One button. One goal. A complete celebration experience.**

## Project Overview

This project is an interactive Arduino-based **Football GOAL Celebration System** developed as a practical application of the electrical engineering concepts I learned during **Week 2 of my Full Stack Robotics Engineering Internship at Smart Methods**.

Inspired by the excitement surrounding World Cup matches, I designed a system that transforms a single push-button input into a coordinated celebration involving motion, light, sound, and visual feedback.

When the push button is pressed, the system:

- Activates a DC motor
- Displays `GOAL!!!` on a 16×2 LCD
- Plays a celebration sound using a piezo buzzer
- Runs green, white, and rainbow animations on a 12-LED NeoPixel Ring
- Returns automatically to the ready state after the celebration sequence

The project combines electrical engineering fundamentals, embedded programming, motor control, circuit protection, power distribution, and creative interaction design in one integrated Arduino simulation.

---

## Demo

[▶ Watch the GOAL Celebration Demo](Goal-Cheer.mp4)


---

## Circuit Overview

<img width="1536" height="632" alt="circuit-overview png" src="https://github.com/user-attachments/assets/9d1b2948-e2cd-49b4-9ac8-9a31c581e7ca" />

---

## Project Idea

The idea was to recreate the excitement of scoring a football goal using a compact embedded system.

Instead of controlling only one output, the Arduino coordinates multiple components simultaneously:

1. The user presses the push button.
2. The LCD changes from the ready message to `GOAL!!!`.
3. The DC motor starts rotating.
4. The piezo buzzer plays a short celebration tone.
5. The NeoPixel Ring displays green, white, and rainbow effects.
6. The system stops the celebration and returns to its initial state.

This demonstrates how one digital input can trigger several synchronized hardware outputs.

---

## Technologies and Tools

- Arduino Uno R3
- C++ / Arduino
- Tinkercad Circuits Simulation
- LiquidCrystal Library
- Adafruit NeoPixel Library

---

## Hardware Components

- 1 × Arduino Uno R3
- 2 × Full-size breadboards
- 1 × Push button
- 1 × DC motor
- 1 × NPN transistor
- 1 × Flyback diode
- 1 × Base resistor for the transistor
- 1 × 16×2 LCD
- 1 × 10 kΩ potentiometer
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

## Push Button Connections

The push button uses the Arduino internal pull-up resistor.

| Connection | Destination |
|---|---|
| Button signal terminal | Arduino D8 |
| Opposite button terminal | GND |

The code uses:

```cpp
pinMode(buttonPin, INPUT_PULLUP);
```

Therefore:

- Released button = `HIGH`
- Pressed button = `LOW`

---

## LCD Connections

| LCD Pin | Connection |
|---|---|
| GND | Ground rail |
| VCC | 5V |
| VO | Middle terminal of the 10 kΩ potentiometer |
| RS | Arduino D12 |
| RW | GND |
| E | Arduino D11 |
| DB0–DB3 | Not connected |
| DB4 | Arduino D5 |
| DB5 | Arduino D4 |
| DB6 | Arduino D3 |
| DB7 | Arduino D2 |
| LED Anode | 5V through a current-limiting resistor |
| LED Cathode | GND |

### Potentiometer Connections

| Potentiometer Terminal | Connection |
|---|---|
| Outer terminal 1 | GND |
| Middle terminal | LCD VO |
| Outer terminal 2 | 5V |

The potentiometer controls LCD contrast.

If the screen is powered but the text is not visible, rotate the potentiometer gradually until the characters appear clearly.

---

## DC Motor Driver Circuit

The DC motor is not driven directly by an Arduino digital pin because it requires more current than the pin can safely provide.

An NPN transistor is used as an electronic switch.

### Motor Driver Connections

| Component | Connection |
|---|---|
| Arduino D9 | Base resistor |
| Base resistor | NPN Base |
| NPN Collector | DC motor terminal 1 |
| NPN Emitter | GND |
| DC motor terminal 2 | 5V |

---

## Flyback Diode Protection

A flyback diode is connected across the DC motor terminals.

Its purpose is to protect the Arduino and transistor from reverse voltage generated when the motor stops.

The diode must be installed with the correct polarity:

- Cathode, marked side → motor terminal connected to 5V
- Anode → motor terminal connected to the transistor collector

---

## NeoPixel Ring Connections

| NeoPixel Ring Pin | Connection |
|---|---|
| PWR | 5V |
| GND | GND |
| IN | Arduino D10 |
| OUT | Not connected |

The Arduino signal must connect to `IN`, not `OUT`.

The NeoPixel Ring contains 12 LEDs, so the code must use:

```cpp
const int pixelCount = 12;
```

---

## Piezo Buzzer Connections

| Piezo Terminal | Connection |
|---|---|
| Positive | Arduino D7 |
| Negative | GND |

The buzzer plays a short celebration sequence when the goal event is triggered.

---

## Power Distribution Between the Breadboards

The project uses two breadboards connected to the same Arduino power source.

### Correct Power Path

```text
Arduino 5V
   ↓
Breadboard 1 positive rail
   ↓
Breadboard 2 positive rail
```

```text
Arduino GND
   ↓
Breadboard 1 negative rail
   ↓
Breadboard 2 negative rail
```

The correct rule is always:

```text
Positive → Positive
Ground   → Ground
```

Both breadboards must share a common ground with the Arduino.

---

## Connecting Upper and Lower Power Rails

A major troubleshooting point in this project was discovering that the upper and lower power rails of the breadboard are not automatically connected.

If power enters the upper rails while components use the lower rails, jumper wires must be added:

```text
Upper positive rail → Lower positive rail
Upper negative rail → Lower negative rail
```

Without these jumpers, the lower rails receive no power even though the wiring may appear correct visually.

---

## System Behavior

### Initial State

The LCD displays:

```text
Ready...
Press Button
```

The following components remain off:

- DC motor
- NeoPixel Ring
- Piezo buzzer

### Goal Celebration State

When the button is pressed, the LCD displays:

```text
GOAL!!!
Celebration!
```

At the same time:

- The DC motor starts rotating
- The piezo buzzer plays a goal celebration tone
- The NeoPixel Ring displays a moving green effect
- The ring changes to green, white, and rainbow animations
- The system returns to the ready state after the sequence finishes

---
## Source Code

The complete Arduino code is available here:

[`goal_celebration.ino`](goal_celebration.ino)

---

## Important Engineering Lessons

### 1. Breadboard Power Rails Are Not Always Connected

The upper and lower power rails are separate unless jumper wires connect them.

A component may appear connected to a power rail while receiving no voltage.

### 2. Multiple Breadboards Must Share a Common Ground

All connected components must share the same Arduino ground.

A missing common ground can prevent signals and components from operating correctly.

### 3. A Breadboard Does Not Normally Reduce Voltage

A correctly connected breadboard does not significantly reduce the Arduino 5V supply.

If a component works when connected directly to Arduino but not through the breadboard, the likely causes are:

- An isolated power rail
- A missing jumper
- A wire connected to the wrong row
- An incomplete ground connection

### 4. Breadboard Rows Must Be Understood Correctly

In the main breadboard area, each numbered group contains two electrically separate sections.

For example:

```text
a15, b15, c15, d15, e15
```

are connected together.

And:

```text
f15, g15, h15, i15, j15
```

are connected together.

The two groups are separated by the center gap.

### 5. The Push Button Does Not Control Breadboard Power

The push button is only a digital input.

Pressing it does not transfer power from one breadboard to another.

### 6. LCD Contrast Must Be Adjusted

The LCD may be powered and correctly programmed while still appearing blank.

The 10 kΩ potentiometer adjusts the voltage supplied to `VO`, controlling text contrast.

### 7. LCD Backlight Requires Current Limiting

The LCD LED Anode should be connected through a current-limiting resistor.

Connecting it directly to 5V may cause an overcurrent warning or component failure in the simulation.

### 8. Arduino Pins Should Not Be Shared Accidentally

Each component should use its own assigned pin unless the circuit is intentionally designed for shared communication.

The push button was moved to D8 because D2 was required by LCD DB7.

### 9. A DC Motor Should Not Be Driven Directly by Arduino

The motor requires a transistor driver because an Arduino output pin cannot safely supply the required current.

The base resistor protects the Arduino output, while the flyback diode protects the circuit from reverse voltage.

### 10. NeoPixel Data Must Connect to IN

The Arduino data signal must enter the NeoPixel Ring through `IN`.

The `OUT` terminal is only used when connecting another NeoPixel device in a chain.

### 11. Simulation Software May Need Restarting

During testing, the NeoPixel Ring temporarily stopped responding even though its wiring and code were correct.

Stopping and restarting the simulation restored its operation.

Troubleshooting should therefore include:

- Reviewing the connections
- Checking the code
- Restarting the simulation
- Refreshing Tinkercad when necessary

Sometimes the circuit is innocent and the simulation simply chooses chaos.

---

## Wire Color Organization

A consistent wire color convention makes the circuit easier to understand, debug, and document.

| Function | Suggested Color |
|---|---|
| 5V / VCC | Red |
| GND | Black |
| LCD Data | Blue |
| LCD Control | Purple |
| Push Button Signal | Yellow |
| DC Motor Control | Orange |
| NeoPixel Data | Green |
| Piezo Buzzer Signal | Brown |
| Potentiometer Signal | Light Blue |

The exact colors may vary, but consistency should be maintained throughout the circuit.

---

## Skills Demonstrated

- Electrical circuit prototyping
- Arduino programming
- Embedded systems integration
- Digital input processing
- Multi-output control
- LCD interfacing
- Motor control with an NPN transistor
- Flyback diode protection
- NeoPixel LED animation
- Piezo buzzer control
- Breadboard power distribution
- Circuit troubleshooting
- Wire organization and documentation
- Creative interactive system design

---

## Project Structure

```text
Arduino-Football-Goal-Celebration-System/
│
├── README.md
├── goal_celebration.ino
├── circuit-overview.png
└── Goal-Cheer.mp4
```

---

## Future Improvements

- Add a goal counter to the LCD
- Add two buttons for different teams
- Create multiple celebration modes
- Replace the push button with a motion or distance sensor
- Add a football detection mechanism
- Build a miniature football field enclosure
- Use an external power supply in the physical prototype
- Add Bluetooth or IoT control
- Add team colors to the NeoPixel animations

---

## Acknowledgment

This project was developed as a practical application of the electrical engineering concepts covered during **Week 2 of my Full Stack Robotics Engineering Internship at Smart Methods**.

It reflects my interest in combining electrical engineering, robotics, embedded programming, and creative interaction design to transform technical concepts into engaging real-world experiences.

---

## Author

**Wejdan AlHarby**

Artificial Intelligence, Software, and Robotics Enthusiast
