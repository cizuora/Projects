How to compile & run Java files in this folder (CS2002 - lab3)

Files in this folder typically belong to package `lab3` (if the source files contain `package lab3;`).

Quick terminal commands (from the `src` root):

   cd ".../CS2002/src"
   javac lab3/AreaCalculator.java lab3/MathOperations.java
   java lab3.AreaCalculator

Run using `bin` (precompiled classes):

   cd ".../CS2002"
   java -cp bin lab3.AreaCalculator

Notes:
- If you see "NoClassDefFoundError: <name> (wrong name: lab3/<name>)", make sure you run from the `src` root or use `-cp bin` with the fully-qualified class name.
- In VS Code, set the run `cwd` to `${workspaceFolder}/CS2002/src` and `mainClass` to `lab3.AreaCalculator` when creating launch configurations.
