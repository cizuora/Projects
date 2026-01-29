#!/bin/bash
# ============================================
# UNIVERSAL DOXYGEN DOCUMENTATION GENERATOR
# ============================================

PROJECT_NAME="My Project"
PROJECT_DESC="C++ project documentation"

echo "============================================"
echo " UNIVERSAL DOXYGEN DOCUMENTATION GENERATOR"
echo "============================================"
echo
echo "Project: $PROJECT_NAME"
echo "Description: $PROJECT_DESC"
echo

# Check Doxygen
if ! command -v doxygen &> /dev/null; then
    echo "[ERROR] Doxygen not found!"
    echo "Please install:"
    echo "  macOS: brew install doxygen"
    echo "  Ubuntu: sudo apt-get install doxygen"
    echo "  Fedora: sudo dnf install doxygen"
    echo
    exit 1
fi

# Check LaTeX (optional)
if ! command -v pdflatex &> /dev/null; then
    echo "[WARNING] LaTeX not found. PDF will not be generated."
    echo "Install:"
    echo "  macOS: brew install --cask mactex"
    echo "  Ubuntu: sudo apt-get install texlive-full"
    echo
    NO_PDF=1
fi

# Generate documentation
echo "[1/3] Generating Doxygen documentation..."
doxygen Doxyfile
if [ $? -ne 0 ]; then
    echo "[ERROR] Doxygen failed!"
    exit 1
fi

echo "[2/3] Documentation generated in ./docs/html/"

# Generate PDF if LaTeX available
if [ -z "$NO_PDF" ]; then
    echo "[3/3] Generating PDF..."
    cd docs/latex
    pdflatex -interaction=nonstopmode refman.tex > /dev/null
    pdflatex -interaction=nonstopmode refman.tex > /dev/null
    cd ../..
    
    if [ -f "docs/latex/refman.pdf" ]; then
        echo "[SUCCESS] PDF generated: docs/latex/refman.pdf"
    else
        echo "[WARNING] PDF generation failed, but HTML docs are ready"
    fi
else
    echo "[INFO] Skipping PDF generation (LaTeX not available)"
fi

echo
echo "============================================"
echo " DOCUMENTATION READY!"
echo "============================================"
echo
echo "Files generated:"
echo "  HTML: docs/html/index.html"
if [ -f "docs/latex/refman.pdf" ]; then
    echo "  PDF:  docs/latex/refman.pdf"
fi
echo
echo "To view documentation:"
echo "  1. Open docs/html/index.html in browser"
if [ -f "docs/latex/refman.pdf" ]; then
    echo "  2. Open docs/latex/refman.pdf"
fi
echo
read -p "Press Enter to open HTML documentation..."
open docs/html/index.html 2>/dev/null || xdg-open docs/html/index.html 2>/dev/null || echo "Open docs/html/index.html manually"