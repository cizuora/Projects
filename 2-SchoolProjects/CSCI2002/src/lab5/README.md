How to compile & run Java files in this folder (CS2002 - lab5)

Files in this folder typically belong to package `lab5` (if the source files contain `package lab5;`).

Quick terminal commands (from the `src` root):

   cd ".../CS2002/src"
   javac lab5/ArrayListIntro.java
   java lab5.ArrayListIntro

Run using `bin` (precompiled classes):

   cd ".../CS2002"
   java -cp bin lab5.ArrayListIntro

Notes:
- If you see "NoClassDefFoundError: <name> (wrong name: lab5/<name>)", make sure you run from the `src` root or use `-cp bin` with the fully-qualified class name.
- In VS Code, set the run `cwd` to `${workspaceFolder}/CS2002/src` and `mainClass` to `lab5.ArrayListIntro` when creating launch configurations.
