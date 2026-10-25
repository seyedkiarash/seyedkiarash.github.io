# Circuit Simulator in C++ (OOP course project)

Team project from the Object-Oriented Programming course (Spring 2025, Dr. Abdollah Arasteh,
Department of Electrical Engineering, Sharif University of Technology). The project was built in
three phases. This folder holds the final code that was submitted for each phase. The code has not
been changed; it is published as it was submitted.

| Folder | Contents |
| --- | --- |
| `phase1/` | Console simulator in a single C++17 file. It uses modified nodal analysis with Eigen, covers R, C, L, ideal diodes, independent DC/SIN/PULSE sources and the E, G, H and F dependent sources, runs transient and DC-sweep analyses, and saves and loads schematic files. |
| `phase2/` | Qt 6 graphical simulator with an MVC layout: a schematic editor, a waveform viewer with cursors and math traces, transient, AC and phase sweeps, sub-circuits, cereal project files and TCP networking. Third-party libraries and build folders are not included. |
| `report/oop_review.pdf` | Code review: architecture, numerical method, test results against ngspice, and the open issues of each phase. |
| `report/phase0-design.pdf` | Phase 0 design document (classes, UML, design patterns). |

## Building

**Phase 1**

```
g++ -std=c++17 -O2 -I/path/to/eigen3 phase1/OOP_Project_Farzin.cpp -o sim
mkdir circuits && ./sim
```

**Phase 2** needs Qt 6 (Widgets, Charts, Network, Svg), Eigen and cereal. Place the `Eigen/` and `cereal/`
headers in `phase2/libs/`, then run:

```
cmake -S phase2 -B build && cmake --build build
```

The network code uses `QDataStream::Qt_6_7`, so it needs Qt 6.7 or newer.

The review (`report/oop_review.pdf`) lists the known issues. Two of them matter for a first build:

- `GraphicsView` has uninitialised pointer members, so some builds crash when the first component is placed.
- In this final version, the *Simulation* menu shows sample traces instead of running the analysis engine.
