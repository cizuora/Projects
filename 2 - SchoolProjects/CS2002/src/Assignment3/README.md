How to compile & run Java files in this folder (CS2002 - Assignment3)

Files in this folder typically belong to package `Assignment3` (if the source files contain `package Assignment3;`).

Quick terminal commands (from the `src` root):

   cd ".../CS2002/src"
   javac Assignment3/RideQueue.java Assignment3/ThemeParkTicketingSystemTester.java Assignment3/Ticket.java Assignment3/TicketStack.java
   java Assignment3.ThemeParkTicketingSystemTester

Run using `bin` (precompiled classes):

   cd ".../CS2002"
   java -cp bin Assignment3.ThemeParkTicketingSystemTester

Notes:
- If you see "NoClassDefFoundError: <name> (wrong name: Assignment3/<name>)", make sure you run from the `src` root or use `-cp bin` with the fully-qualified class name.
- In VS Code, set the run `cwd` to `${workspaceFolder}/CS2002/src` and `mainClass` to `Assignment3.ThemeParkTicketingSystemTester` when creating launch configurations.
