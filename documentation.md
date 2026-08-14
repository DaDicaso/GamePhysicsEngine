# Omni Engine — Documentation

> A modular C++ physics/game engine built from scratch, with a strong focus on physics, rendering, and engine architecture.

This document is a technical reference for the Omni Engine codebase. For a quick project summary, see the [README](README.md).

---

## Table of Contents

- [Overview](#overview)
- [Project Layout](#project-layout)
- [Build & Run](#build--run)
- [Core Modules](#core-modules)
  - [Math (`engine/math`)](#math)
  - [Core (`engine/core`)](#core)
  - [Physics (`engine/physics`)](#physics)
  - [Rendering (`engine/renderer`)](#rendering)
  - [Debug (`engine/debug`)](#debug)
- [Experiment Framework (`lab`)](#experiment-framework)
- [Application Entry (`app`)](#application-entry)
- [Demos (`demos`)](#demos)
- [Third-Party Dependencies](#third-party-dependencies)
- [Adding a New Experiment](#adding-a-new-experiment)
- [Current Status & Roadmap](#current-status--roadmap)
- [License](#license)

---

## Overview

Omni Engine is a personal, long-term game engine project developed entirely from scratch in modern C++ (C++17). The primary goal is not to clone an existing engine, but to deepen understanding of the architecture behind commercial engines.

The engine currently centers on:

- Particle physics (forces, integration, contacts)
- OpenGL rendering with immediate-mode debug visualization
- An experiment framework for rapidly testing new subsystems
- A custom mathematics library (starting with `Vector3`)

All code lives in the `omni` namespace.

---

## Project Layout

```
Omni_Engine/
├── CMakeLists.txt              # Top-level CMake build script
├── README.md                   # Quick-start project summary
├── documentation.md            # This file
├── LICENSE                     # MIT license
├── app/                        # Application entry point
│   └── main.cpp                # Creates PhysicsLab and runs the main loop
├── engine/                     # Core engine source
│   ├── core/                   # Window, time, precision utilities
│   ├── math/                   # Mathematics library (Vector3)
│   ├── physics/                # Particle physics systems
│   │   ├── particle/           # Single particle dynamics
│   │   ├── force/              # Force generators + registry
│   │   └── contact/            # Contacts, links, resolver
│   ├── renderer/               # OpenGL rendering
│   └── debug/                  # Immediate-mode debug drawing
├── lab/                        # Experiment framework
│   ├── experiment.h            # Experiment interface
│   ├── experiment_manager.h    # Swaps and drives experiments
│   ├── physics_lab.h           # Top-level application host
│   └── experiments/            # Concrete experiments
├── demos/                      # Standalone demo programs
│   └── particle_sandbox/       # Legacy particle sandbox demo
├── tests/                      # Test directory
├── external/                   # Vendored dependencies (GLFW, GLAD)
└── third_party/                # Additional third-party code
```

---

## Build & Run

### Prerequisites

- CMake 3.16+
- A C++17 compiler (GCC, Clang, or MSVC)
- OpenGL 4.6-capable driver
- Linux: X11/Wayland development libraries (GLFW requirement)

### Steps

```bash
# 1. Clone the repository
git clone https://github.com/DaDicaso/Omni_Engine.git
cd Omni_Engine

# 2. Configure
cmake -S . -B build

# 3. Build
cmake --build build

# 4. Run the physics lab
./build/OmniPhysicsLab
```

The build produces a single executable, `OmniPhysicsLab`, which hosts the physics lab and its currently selected experiment.

---

## Core Modules

### Math

Location: `engine/math/`

| File | Purpose |
| --- | --- |
| `vector3.h` | 3D vector with operators, magnitude, normalization, and dot product |

`Vector3` uses the engine-wide `real` type (see Core) and stores `x`, `y`, `z` plus a padding component for SIMD alignment headroom. Key operations:

- `magnitude()` / `squareMagnitude()`
- `normalize()` / `invert()`
- Arithmetic operators (`+`, `-`, `*`, `/`) and compound assignments
- `clear()` resets the vector to zero

### Core

Location: `engine/core/`

| File | Purpose |
| --- | --- |
| `precision.h` | `real` typedef (currently `float`) and scalar math helpers |
| `core.h` | Central core header |
| `time.h` | Frame timing: delta time and elapsed time |
| `window.h` | GLFW window abstraction |

`precision.h` defines `omni::real` and float-based math wrappers (`real_sqrt`, `real_sin`, etc.). Switching to double precision later is a one-line change, making the engine precision-agnostic.

`Time` tracks per-frame `delta time` and total `elapsed time`, updated once per frame by `PhysicsLab`.

`Window` wraps GLFW lifecycle: creation, event polling, buffer swapping, and close detection.

### Physics

Location: `engine/physics/`

#### Particle (`particle/`)

`Particle` is the fundamental simulation unit. It stores position, velocity, acceleration, accumulated force, damping, and inverse mass.

Key API:

- `integrate(duration)` — Euler integration of velocity and position
- `addForce(force)` / `clearAccumulator()` — force accumulation per frame
- `setMass()` / `setInverseMass()` — mass setters; inverse mass is used directly in integration
- `hasFiniteMass()` — `true` when the particle has a non-zero inverse mass

#### Forces (`force/`)

| File | Purpose |
| --- | --- |
| `ParticleForceGenerator.h` | Abstract interface: `updateForce(particle, duration)` |
| `ParticleForceRegistry.h` | Registry pairing particles with force generators |
| `ParticleGravity.h` | Constant gravitational acceleration |
| `ParticleDrag.h` | Velocity-dependent drag (linear + quadratic terms) |
| `ParticleSpring.h` | Spring between two particles |
| `ParticleAnchoredSpring.h` | Spring anchored to a fixed world point |
| `ParticleBungee.h` | Bungee (rope) constraint between two particles |
| `ParticleBuoyancy.h` | Buoyancy force from fluid immersion |

`ParticleForceRegistry` holds `(particle, generator)` pairs. `updateForces(duration)` iterates every registration and applies each generator's force before integration.

#### Contacts (`contact/`)

| File | Purpose |
| --- | --- |
| `ParticleContact.h` | A contact between two particles |
| `ParticleContactResolver.h` | Iterative contact resolution |
| `ParticleLink.h` | Base class for links between particles |
| `ParticleCable.h` | Cable constraint (max length) |

`ParticleContact` stores the two particles, restitution, contact normal, and penetration depth. Resolution is split into:

- `resolveVelocity(duration)` — applies impulse based on separating velocity and restitution
- `resolvePenetration(duration)` — positional correction based on inverse mass

`ParticleContactResolver` iterates over the contact array several times (configurable), resolving the contact with the largest separating velocity each pass.

#### World (`particle_world.h`)

`ParticleWorld` aggregates particles, force generators, and contact generators into a single simulation container:

- `startFrame()` clears force accumulators
- `runPhysics(duration)` integrates particles and resolves contacts
- Holds a `ParticleForceRegistry`, `ParticleContactResolver`, and contact storage

### Rendering

Location: `engine/renderer/`

`Renderer` is the OpenGL renderer abstraction. It owns a `DebugDraw` instance and provides:

- `beginFrame()` / `endFrame()` — frame lifecycle
- `setClearColor(r, g, b, a)`
- `drawPoint(position, color, size)`
- `drawLine(start, end, color, width)`

### Debug

Location: `engine/debug/`

| File | Purpose |
| --- | --- |
| `DebugDraw.h` | Immediate-mode debug draw API (points, lines) |
| `Color.h` | `Color` type (RGBA) |
| `Colors.h` | Named color presets |

`DebugDraw` is used by experiments to visualize:

- Particle positions
- Velocity vectors
- Contact normals
- Constraint geometry

---

## Experiment Framework

Location: `lab/`

The lab is a small framework for writing and swapping isolated physics demos.

### Experiment Interface

`lab/experiment.h` defines the pure-virtual interface every experiment implements:

```cpp
class Experiment {
public:
  virtual ~Experiment() = default;

  virtual void initialize() = 0;   // Set up particles, forces, state
  virtual void update(float dt) = 0; // Advance the simulation
  virtual void render(Renderer& renderer) = 0; // Draw the experiment
  virtual void shutdown() = 0;     // Clean up
};
```

### ExperimentManager

`lab/experiment_manager.h` owns the current `Experiment` via `std::unique_ptr` and forwards the frame lifecycle:

- `setExperiment(experiment)` — shuts down the old experiment, installs and initializes the new one
- `initialize()` / `update(dt)` / `render(renderer)` / `shutdown()`

To change which experiment runs by default, edit the constructor in `lab/experiment_manager.cpp`:

```cpp
ExperimentManager::ExperimentManager(){
  setExperiment(std::make_unique<ContactResolutionExperiment>());
}
```

### PhysicsLab

`lab/physics_lab.h` is the application host. It owns a `Window`, `Renderer`, `ExperimentManager`, and `Time`, and runs the main loop in `run()`.

### Built-in Experiments

Location: `lab/experiments/`

| Directory | Description |
| --- | --- |
| `Gravity/` | Particle under gravity + drag, projected as a point |
| `Spring/` | Two particles connected by a spring |
| `ContactResolution/` | Contact generation and resolution between particles |
| `empty/` | Minimal template experiment for new work |

---

## Application Entry

Location: `app/main.cpp`

The executable entry point is minimal:

```cpp
#include "lab/physics_lab.h"

int main(){
  omni::PhysicsLab app;
  app.run();
  return 0;
}
```

---

## Demos

Location: `demos/`

`particle_sandbox/` is a standalone (legacy) demo using raw GLFW + OpenGL immediate mode. It is not wired into the main `OmniPhysicsLab` target and is kept for reference/experimentation.

---

## Third-Party Dependencies

| Dependency | Location | Purpose |
| --- | --- | --- |
| GLFW | `external/glfw/` | Windowing and input |
| GLAD | `external/glad/` | OpenGL function loading |
| GL (system) | — | OpenGL library, linked via CMake |

All dependencies are vendored or system-provided; no network access is needed to build.

---

## Adding a New Experiment

1. Create a folder under `lab/experiments/`, e.g. `lab/experiments/MyExperiment/`.
2. Implement `MyExperiment.h` / `.cpp` deriving from `omni::Experiment` and overriding all four lifecycle methods.
3. Register the sources in `CMakeLists.txt` under `LAB_SOURCES`.
4. Set it as the active experiment in `lab/experiment_manager.cpp`:

```cpp
setExperiment(std::make_unique<MyExperiment>());
```

5. Rebuild and run `./build/OmniPhysicsLab`.

---

## Current Status & Roadmap

Active development. New systems are added incrementally with an emphasis on correctness and readability.

### Implemented

- Custom `Vector3` math (normalization, dot product, magnitude, distance)
- Particle integration and dynamics
- Force generators: gravity, drag, springs, anchored springs, bungee, buoyancy
- Force registry
- Contact generation and iterative resolution
- OpenGL renderer with GLFW windowing
- Immediate-mode debug drawing (points, lines)
- Experiment framework and physics lab host

### Planned

- Rigid body dynamics
- Collision detection
- Spatial partitioning
- ECS
- Asset management
- Vulkan renderer
- Audio

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
