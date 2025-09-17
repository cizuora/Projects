How to compile & run Java files in this folder (CS2002 - Assignment1)

Files in this folder typically belong to package `Assignment1` (if the source files contain `package Assignment1;`).

Quick terminal commands (from the `src` root):

   cd ".../CS2002/src"
   javac Assignment1/Car.java Assignment1/CarAutoTester.java
   java Assignment1.CarAutoTester

Run using `bin` (precompiled classes):

   cd ".../CS2002"
   java -cp bin Assignment1.CarAutoTester

Notes:
- If you see "NoClassDefFoundError: <name> (wrong name: Assignment1/<name>)", make sure you run from the `src` root or use `-cp bin` with the fully-qualified class name.
- In VS Code, set the run `cwd` to `${workspaceFolder}/CS2002/src` and `mainClass` to `Assignment1.CarAutoTester` when creating launch configurations.
