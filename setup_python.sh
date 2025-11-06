#!/bin/bash

# Python Setup Script for BBBCube
# Works across different Linux distributions (Fedora, Ubuntu, etc.)

set -e

echo "=== BBBCube Python Environment Setup ==="
echo ""

# Check if Python 3 is installed
if ! command -v python3 &> /dev/null; then
    echo "Error: Python 3 is not installed!"
    echo "Please install Python 3 first:"
    echo "  Fedora: sudo dnf install python3"
    echo "  Ubuntu: sudo apt install python3"
    exit 1
fi

# Check Python version
PYTHON_VERSION=$(python3 --version | cut -d' ' -f2 | cut -d'.' -f1,2)
echo "Found Python $PYTHON_VERSION"

# Check if pip is available
if ! python3 -m pip --version &> /dev/null; then
    echo "Error: pip is not installed!"
    echo "Please install pip first:"
    echo "  Fedora: sudo dnf install python3-pip"
    echo "  Ubuntu: sudo apt install python3-pip"
    exit 1
fi

# Create virtual environment if it doesn't exist
if [ ! -d ".venv" ]; then
    echo ""
    echo "Creating virtual environment..."
    python3 -m venv .venv
    echo "Virtual environment created in .venv/"
else
    echo ""
    echo "Virtual environment already exists in .venv/"
fi

# Activate virtual environment
echo ""
echo "Activating virtual environment..."
source .venv/bin/activate

# Upgrade pip
echo ""
echo "Upgrading pip..."
pip install --upgrade pip

# Install requirements
echo ""
echo "Installing Python packages from requirements.txt..."
pip install -r requirements.txt

echo ""
echo "=== Setup Complete! ==="
echo ""
echo "To use the Python tools, activate the virtual environment:"
echo "  source .venv/bin/activate"
echo ""
echo "Then run the GUIs:"
echo "  python gui/cube_control.py"
echo "  python gui/cube_data_viewer.py"
echo ""
echo "To deactivate the virtual environment later:"
echo "  deactivate"
