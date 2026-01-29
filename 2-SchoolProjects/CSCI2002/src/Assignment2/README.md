How to compile & run Java files in this folder (CS2002 - Assignment2)

Files in this folder typically belong to package `Assignment2` (if the source files contain `package Assignment2;`).

Quick terminal commands (from the `src` root):

   cd ".../CS2002/src"
   javac Assignment2/ArrayBag.java Assignment2/ArrayBagTester.java Assignment2/BagInterface.java
   java Assignment2.ArrayBagTester

Run using `bin` (precompiled classes):

   cd ".../CS2002"
   java -cp bin Assignment2.ArrayBagTester

Notes:
- If you see "NoClassDefFoundError: <name> (wrong name: Assignment2/<name>)", make sure you run from the `src` root or use `-cp bin` with the fully-qualified class name.
- In VS Code, set the run `cwd` to `${workspaceFolder}/CS2002/src` and `mainClass` to `Assignment2.ArrayBagTester` when creating launch configurations.
