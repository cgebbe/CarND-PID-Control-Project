# About

<img src="output_Kp_Kd.gif" width="600">

### Problem

Keep the car on the track by setting a suitable steering angle (yaw). As input you receive the cross track error (CTE), i.e. the deviation from center lane.

### Solution approach

Use a PID Controller, see https://en.wikipedia.org/wiki/PID_controller. Determine the parameters Kp, Kd, Ki in two ways:

1. Manually, through **systematic** experiments
2. Automatically, through optimization (Udacity denotes this as twiddle algorithm)

### Result

Both of my solutions passed the test successfully, see my [detailed report](report.md).

# FAQ

See detailed instructions in original [original README.org](README_org.md)

### How to install

- Get term2-simulator from https://github.com/udacity/self-driving-car-sim/releases
- Install required websocket library via `install-ubuntu.sh`
- Build project, e.g. via cmake + make

### How to run

- Run `build/pid`
- Start term2-simulator
  - Select "Project 4: PID Controller"
  - Start simulation