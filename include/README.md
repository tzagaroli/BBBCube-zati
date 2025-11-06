# include/

This folder contains project-wide header files used throughout the application.

These headers define internal structures, utility classes, configuration constants, and interfaces. 
They are **not meant to be generic**, unlike true libraries in the `lib/` folder.

## Guidelines

- Keep headers modular and focused on specific features.
- Avoid placing implementation code here unless necessary (e.g., inline functions or templates).
- Always include guards or `#pragma once`.