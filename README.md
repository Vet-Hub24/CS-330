# CS-330 Computational Graphics and Visualization

## 3D OpenGL Scene

This repository contains my final project for **CS-330: Computational Graphics and Visualization** at Southern New Hampshire University. The project was built from the OpenGL starter framework provided for the course. My work focused on constructing and customizing the 3D scene, positioning objects, applying textures and materials, configuring lighting, and working with the interactive camera and projection controls.

## Project Overview

The application renders an interactive 3D desktop-style scene in C++ using OpenGL. The scene is assembled from reusable primitive meshes such as planes, boxes, cylinders, spheres, and cones. These shapes are transformed and combined to create objects in the environment, including a work surface, monitor-style objects, books, a mouse, pencils, and other scene elements.

The project also uses multiple textures and light sources to give the scene more depth and visual variation. Scene rendering is organized through `SceneManager`, while `ViewManager` handles the camera and projection setup.

## What I Worked With

- C++ and OpenGL
- Object translation, rotation, and scaling
- Texture loading and UV scaling
- Materials and multiple light sources
- Perspective and orthographic projection
- Interactive camera movement
- Reusable 3D primitive meshes
- Visual Studio project organization and debugging

## Controls

- **W / A / S / D** — move the camera forward, left, backward, and right
- **Q / E** — move the camera vertically
- **Mouse movement** — change the viewing direction
- **Mouse wheel** — adjust the camera zoom
- **O** — switch to orthographic projection
- **P** — switch to perspective projection
- **Esc** — close the application

## Repository Structure

The primary final-project code is under:

`7-1_FinalProjectMilestones/`

Important source files include:

- `Source/MainCode.cpp` — application setup and render loop
- `Source/SceneManager.cpp` — scene preparation, textures, lighting, transformations, and object rendering
- `Source/ViewManager.cpp` — camera movement and projection controls

## What I Learned

This course gave me foundational experience with how a 3D scene is built from code. I learned how transformations determine the size, position, and orientation of objects, how textures and lighting affect the appearance of a scene, and how a camera and projection matrix control what the user sees.

I also gained more practice troubleshooting a larger C++ project and making changes incrementally rather than trying to build the entire scene at once. I still consider my graphics-programming experience foundational, but this project gave me practical exposure to the structure of an interactive OpenGL application.

## Academic Note

This is an academic portfolio project. SNHU supplied the course framework and supporting graphics utilities. The repository is presented to document the concepts I practiced and the scene work I completed during the course.