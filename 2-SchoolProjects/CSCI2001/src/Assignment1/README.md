How to compile & run Java files in this folder

This folder contains Java source files that declare a package: `package Assignment1;`.

Important: When a Java file has a package declaration, you must compile and run it from the source root (the directory that contains the top-level package folder).

Quick terminal commands (from the project workspace)

1) Compile from the `src` root (creates .class files alongside package folders):

   cd ".../CS2001/src"
   javac Assignment1/A1_Conversion.java

2) Run using the package-qualified class name (java needs the classpath set to `src`):

   cd ".../CS2001/src"
   java Assignment1.A1_Conversion

Using the existing `bin` directory with precompiled .class files

- The `bin` directory mirrors the package layout and already contains `.class` files.
- To run the existing classes without recompiling, point the Java classpath to `bin` and run the package-qualified name:

   cd ".../CS2001"
   java -cp bin Assignment1.A1_Conversion

Configuring VS Code (Java extension)

- Open the workspace root (the folder that contains `src` and `bin`).
- The Java extension normally detects `src` automatically. If it doesn't, open the Command Palette -> Java: Clean the Java language server workspace and reload.
- When running a single file from the editor, VS Code may call `java` from inside the package folder which causes the "wrong name" error. To avoid that:
  - Run from the `src` folder (see commands above) in an integrated terminal.
  - Or configure a launch configuration in `.vscode/launch.json` with `cwd` set to `${workspaceFolder}/src` and `mainClass` set to `Assignment1.A1_Conversion`.

Eclipse users

- The Eclipse project already uses `src` as source folder and `bin` as output folder. Right-click the class -> Run As -> Java Application.
- If running from command line, either compile from `src` as shown above or run using `-cp bin`.

Tips

- The "wrong name" NoClassDefFoundError occurs when you `java` from inside the package directory (e.g., `src/Assignment1`) instead of from the source root or classpath root. Always run with the classpath root on the classpath and use the full package name.
- If you don't want packages, remove the `package` line and move the file to the src root, but using packages is best practice.

If you'd like, I can create a `.vscode/launch.json` configured for this project and a short shell script `run.sh` to compile+run automatically. Which would you prefer?