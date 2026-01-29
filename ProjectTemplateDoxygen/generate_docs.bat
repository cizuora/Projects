@echo off
echo ============================================
echo  UNIVERSAL DOXYGEN DOCUMENTATION GENERATOR
echo ============================================
echo.

set PROJECT_NAME="My Project"
set PROJECT_DESC="C++ project documentation"

echo Project: %PROJECT_NAME%
echo Description: %PROJECT_DESC%
echo.

REM Check Doxygen
where doxygen >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] Doxygen not found!
    echo Please install from: https://www.doxygen.nl/download.html
    echo.
    pause
    exit /b 1
)

REM Check LaTeX (optional)
where pdflatex >nul 2>nul
if %errorlevel% neq 0 (
    echo [WARNING] LaTeX not found. PDF will not be generated.
    echo Install MiKTeX: https://miktex.org/download
    echo.
    set NO_PDF=1
)

REM Generate documentation
echo [1/3] Generating Doxygen documentation...
doxygen Doxyfile
if %errorlevel% neq 0 (
    echo [ERROR] Doxygen failed!
    pause
    exit /b 1
)

echo [2/3] Documentation generated in ./docs/html/

REM Generate PDF if LaTeX available
if "%NO_PDF%"=="1" (
    echo [INFO] Skipping PDF generation (LaTeX not available)
) else (
    echo [3/3] Generating PDF...
    cd docs\latex
    pdflatex -interaction=nonstopmode refman.tex > nul
    pdflatex -interaction=nonstopmode refman.tex > nul
    cd ..\..
    
    if exist docs\latex\refman.pdf (
        echo [SUCCESS] PDF generated: docs\latex\refman.pdf
    ) else (
        echo [WARNING] PDF generation failed, but HTML docs are ready
    )
)

echo.
echo ============================================
echo  DOCUMENTATION READY!
echo ============================================
echo.
echo Files generated:
echo   HTML: docs\html\index.html
if exist docs\latex\refman.pdf (
    echo   PDF:  docs\latex\refman.pdf
)
echo.
echo To view documentation:
echo   1. Open docs\html\index.html in browser
if exist docs\latex\refman.pdf (
    echo   2. Open docs\latex\refman.pdf
)
echo.
echo Press any key to open HTML documentation...
pause >nul
start docs\html\index.html