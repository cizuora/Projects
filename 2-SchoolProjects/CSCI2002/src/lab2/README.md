How to compile & run Java files in this folder (CS2002 - lab2)

Files in this folder typically belong to package `lab2` (if the source files contain `package lab2;`).

Quick terminal commands (from the `src` root):

   cd ".../CS2002/src"
   javac lab2/Book.java lab2/Student.java
   java lab2.Book

Run using `bin` (precompiled classes):

   cd ".../CS2002"
   java -cp bin lab2.Book

Notes:
- If you see "NoClassDefFoundError: <name> (wrong name: lab2/<name>)", make sure you run from the `src` root or use `-cp bin` with the fully-qualified class name.
- In VS Code, set the run `cwd` to `${workspaceFolder}/CS2002/src` and `mainClass` to `lab2.Book` when creating launch configurations.
