How to compile & run Java files in this folder (CS2002 - lab4)

Files in this folder typically belong to package `lab4` (if the source files contain `package lab4;`).

Quick terminal commands (from the `src` root):

   cd ".../CS2002/src"
   javac lab4/ArrayIntro.java
   java lab4.ArrayIntro

Run using `bin` (precompiled classes):

   cd ".../CS2002"
   java -cp bin lab4.ArrayIntro

Notes:
- If you see "NoClassDefFoundError: <name> (wrong name: lab4/<name>)", make sure you run from the `src` root or use `-cp bin` with the fully-qualified class name.
- In VS Code, set the run `cwd` to `${workspaceFolder}/CS2002/src` and `mainClass` to `lab4.ArrayIntro` when creating launch configurations.
