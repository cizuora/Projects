How to compile & run Java files in this folder (CS2002 - lab6)

Files in this folder typically belong to package `lab6` (if the source files contain `package lab6;`).

Quick terminal commands (from the `src` root):

   cd ".../CS2002/src"
   javac lab6/Book.java lab6/BookEqualsTest.java
   java lab6.BookEqualsTest

Run using `bin` (precompiled classes):

   cd ".../CS2002"
   java -cp bin lab6.BookEqualsTest

Notes:
- If you see "NoClassDefFoundError: <name> (wrong name: lab6/<name>)", make sure you run from the `src` root or use `-cp bin` with the fully-qualified class name.
- In VS Code, set the run `cwd` to `${workspaceFolder}/CS2002/src` and `mainClass` to `lab6.BookEqualsTest` when creating launch configurations.
