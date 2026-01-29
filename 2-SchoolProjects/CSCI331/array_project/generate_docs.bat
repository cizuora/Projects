@echo off
echo ============================================
echo  EASY ARRAY CLASS DOCUMENTATION GENERATOR
echo ============================================
echo.

echo Step 1: Installing Doxygen (if not installed)...
where doxygen >nul 2>nul
if %errorlevel% neq 0 (
    echo Doxygen not found. Please install from:
    echo https://www.doxygen.nl/download.html
    pause
    exit /b 1
)

echo Step 2: Installing GraphViz for UML diagrams...
where dot >nul 2>nul
if %errorlevel% neq 0 (
    echo GraphViz not found. UML diagrams may not work.
    echo Install from: https://graphviz.org/download/
)

echo Step 3: Installing LaTeX for PDF generation...
where pdflatex >nul 2>nul
if %errorlevel% neq 0 (
    echo LaTeX not found. PDF may not generate.
    echo Install MiKTeX: https://miktex.org/download
)

echo.
echo Step 4: Generating documentation with Doxygen...
doxygen Doxyfile
if %errorlevel% neq 0 (
    echo ERROR: Doxygen failed!
    pause
    exit /b 1
)

echo.
echo Step 5: Compiling PDF from LaTeX...
cd docs\latex
pdflatex -interaction=nonstopmode refman.tex > nul
pdflatex -interaction=nonstopmode refman.tex > nul
cd ..\..

echo.
echo ============================================
echo  SUCCESS! Documentation generated!
echo ============================================
echo.
echo Your files are ready:
echo 1. PDF: docs\latex\refman.pdf
echo 2. HTML: docs\html\index.html
echo 3. Doxyfile: Doxyfile
echo 4. Source files: array.h, array.cpp, arraydriver.cpp
echo.
echo Submit these 6 files to D2L:
echo   1. refman.pdf
echo   2. array.h
echo   3. array.cpp  
echo   4. arraydriver.cpp
echo   5. Doxyfile
echo.
pause