
https://github.com/user-attachments/assets/a66ba806-56a4-495b-b914-512ccf068cfa
# Omni Engine

> A modular c++ physics/Game engine build froms scratch with a strong focus on physics, rendering and engine architecture

![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![OpenGL](https://img.shields.io/badge/OpenGL-4.6-green)
![GLFW](https://img.shields.io/badge/GLFW-Windowing-orange)
![CMake](https://img.shields.io/badge/CMake-Build-red)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

---
## Overview
Omni Engine is a personal long-term game engine project developed entiery from scratch in modern c++.
The primary goal is not to create a game engine clone, but to deepen my understand of architecture behind commersial engines.


<video src="https://github.com/user-attachments/assets/33d4dee0-8339-41ad-96b3-4f6ec4a157cf" autoplay loop muted playsinline width="100%"></video>
Simulated Rod Constraint, A const acceleration is being applied to the rightmost and left most particle and The engine is simulating behaviour of all the particles connected with Rods.

<video src="https://github.com/user-attachments/assets/2c43c11a-de18-4cb2-8d97-7db537cc821a" autoplay loop muted playsinline width="100%"></video>
Automated collision Detection with wireframe spheres, There is a opposite diagnoal force being applied to both Partiles causing the repeaded collisions. 
The Elasticity of the collisino is being determined by the restitution which is set to 0.5.

Current development focuses on:
- Physics engine
- Debug Visualization
- Experiment Framework
- Mathematics Library

Future Gols include:
- Rigid body Dynamics
- Collision Dectection
- Spacial Partitioning
- ECS
- Asset Management
- Vulkan Renderer
- Audio

Current Implementations
## Mathematics
  - Custom Vector3 implementation
  - Scalar math utilities
  - Normalization
  - Dot product
  - Magnitude
  - Distance operations

## Particle Physics
  - Particle Intergration
  - Gravity
  - Drag
  - Springs
  - Anchored Springs
  - Bungee
  - Buoyancy
  - Contact Generation
  - Contact Resolution
  - Force Registry

## Rendering
  - OpenGL Renderer
  - GLFW Window System
  - Immediate Mode Debug Rendering
  - Point Rendering
  - Line Rendering
  - Debug Visualization Utilites

## Debug Tools
  Built in visualization for
  - Particle positions
  - Velocitiy vector
  - Contact normals
  - Constraints visualization

# Building
---

Clone the repository

```bash
git clone https://github.com/yourusername/Omni_Engine.git
```

Configure

```bash
cmake -S . -B build
```

Build

```bash
cmake --build build
```

Run

```bash
./build/OmniPhysicsLab
```

---

# Current Status
Active Development 
New systems are added incremently with an emphasis on correctness, readability

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
