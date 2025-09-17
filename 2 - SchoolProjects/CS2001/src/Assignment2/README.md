How to compile & run Java files in this folder (Assignment2)

Files in this folder declare the package `Assignment2` (if the source files have `package Assignment2;` at the top).

Quick terminal commands (from the `src` root):

   cd ".../CS2001/src"
   javac Assignment2/Car.java Assignment2/CarAutoTester.java
   java Assignment2.CarAutoTester

Run using `bin` (precompiled .class files):

   cd ".../CS2001"
   java -cp bin Assignment2.CarAutoTester

Notes:
- If running produces "NoClassDefFoundError: <name> (wrong name: Assignment2/<name>)", make sure you run from the `src` root or use `-cp bin` and the fully-qualified class name.
- In VS Code, configure your run configuration `cwd` to `${workspaceFolder}/src` and `mainClass` to `Assignment2.CarAutoTester`.
