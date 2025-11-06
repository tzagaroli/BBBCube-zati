# src/

This is the main application code directory.

It must include the `main.cpp` file, which serves as the program's entry point. Additional source files with the application logic should also be placed here.

## Guidelines

- Start with a minimal `main.cpp`, calling into well-separated modules/functions.
- Use this directory to define high-level application logic and workflows.
- **All functionality implemented in this folder should be declared in headers inside the `include/` directory.**
  This improves modularity, separates interface from implementation, and allows reuse across the project.
- For reusable or modular functionality, prefer placing code in `lib/`.