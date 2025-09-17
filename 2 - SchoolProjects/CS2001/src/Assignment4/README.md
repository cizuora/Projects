How to compile & run Java files in this folder (Assignment4)

Files in this folder declare the package `Assignment4` (if the source files have `package Assignment4;` at the top).

Quick terminal commands (from the `src` root):

   cd ".../CS2001/src"
   javac Assignment4/ArrayListExplorerWithOutCollections.java
   java Assignment4.ArrayListExplorerWithOutCollections

Run using `bin` (precompiled .class files):

   cd ".../CS2001"
   java -cp bin Assignment4.ArrayListExplorerWithOutCollections

Notes:
- If running produces "NoClassDefFoundError: <name> (wrong name: Assignment4/<name>)", make sure you run from the `src` root or use `-cp bin` and the fully-qualified class name.
- In VS Code, configure your run configuration `cwd` to `${workspaceFolder}/src` and `mainClass` to `Assignment4.ArrayListExplorerWithOutCollections`.
