How to compile & run Java files in this folder (CS2002 - lab1)

Files in this folder typically belong to package `lab1` (if the source files contain `package lab1;`).

Quick terminal commands (from the `src` root):

   cd ".../CS2002/src"
   javac lab1/DiceDemo.java lab1/Die.java
   java lab1.DiceDemo

Run using `bin` (precompiled classes):

   cd ".../CS2002"
   java -cp bin lab1.DiceDemo

Notes:
- If you see "NoClassDefFoundError: <name> (wrong name: lab1/<name>)", make sure you run from the `src` root or use `-cp bin` with the fully-qualified class name.
- In VS Code, set the run `cwd` to `${workspaceFolder}/CS2002/src` and `mainClass` to `lab1.DiceDemo` when creating launch configurations.
