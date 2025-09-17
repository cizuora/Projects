How to compile & run Java files in this folder (Assignment3)

Files in this folder declare the package `Assignment3` (if the source files have `package Assignment3;` at the top).

Quick terminal commands (from the `src` root):

   cd ".../CS2001/src"
   javac Assignment3/ArrayExplorer.java
   java Assignment3.ArrayExplorer

Run using `bin` (precompiled .class files):

   cd ".../CS2001"
   java -cp bin Assignment3.ArrayExplorer

Notes:
- If running produces "NoClassDefFoundError: <name> (wrong name: Assignment3/<name>)", make sure you run from the `src` root or use `-cp bin` and the fully-qualified class name.
- In VS Code, configure your run configuration `cwd` to `${workspaceFolder}/src` and `mainClass` to `Assignment3.ArrayExplorer`.
