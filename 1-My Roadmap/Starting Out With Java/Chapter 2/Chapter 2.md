### **Chapter 2: Java Fundamentals - A Comprehensive Guide**

This chapter introduces you to the core building blocks of Java programming, covering how programs are structured, how they interact with the user, and how data is handled.

#### **1. The Parts of a Java Program**

A Java program is built around **classes**.
*   A Java source code file (which you write) contains one or more Java classes.
*   If there's more than one class in a file, **only one of them can be declared `public`**.
*   The `public` class's name **must match the filename** of your source code file. For example, if your public class is named `Simple`, your file must be `Simple.java`.
*   Each Java class is further divided into parts.

Let's look at a simple example program structure (like `Simple.java`):

```java
// This is a simple Java program.
public class Simple       // This is the class header for the class Simple
{                         // This curly brace marks the beginning of the class body
    public static void main(String [] args) // This is the method header for the main method
    {                     // This curly brace marks the beginning of the main method's body
        System.out.println("Programming is great fun!"); // This is a Java Statement
    }                     // This curly brace marks the end of the main method's body
}                         // This curly brace marks the end of the class body
```

**Understanding the Components:**

*   **Comments**: Lines starting with `//` are **comments**. They are ignored by the compiler and are used by programmers to explain the code.
*   **Class Header**: `public class Simple` is the **class header**. It tells the compiler that `Simple` is a Java class and that other classes can use it (`public`).
*   **Curly Braces `{}`**: These are crucial for defining **scope**.
    *   When associated with a class header, they define the **scope of the class** (the code that belongs to that class).
    *   When associated with a method, they define the **scope of the method** (the actions performed by that method).
    *   For every opening brace, there **must be a corresponding closing brace**.
*   **The `main` Method**: `public static void main(String [] args)` is the **method header for the `main` method**.
    *   This is the **starting point of any Java application**.
    *   The `java` command will always run this method first.
    *   Every Java application must have a `main` method, and its header must be exactly as shown (except the `args` variable name can be changed).
*   **Java Statements**: `System.out.println("Programming is great fun!");` is a **Java statement**.
    *   Statements are instructions that are executed when the program runs.
    *   **All Java statements must end with a semicolon (`;`)**.
    *   **Comments, class headers, method headers, and curly braces are *not* considered Java statements** and therefore do not need semicolons.

**Compiling and Running a Java Program:**

After writing your Java source code (e.g., `Simple.java`), you need to compile it and then run it.
*   **To Compile**: Open a command prompt or terminal and type `javac Simple.java`.
    *   Notice that the `.java` file extension is required.
    *   If successful, this will create a file named `Simple.class` (this contains the compiled bytecode).
*   **To Run**: Type `java Simple`.
    *   Notice that **no file extension is needed here**; the `java` command assumes the extension is `.class`.

#### **2. Console Output**

Many Java programs you write will display information in a **console window**, which is also known as the **standard output device**. The **standard input device** is typically the keyboard.

Java sends information to the standard output device using classes from the **standard Java library**, which is commonly referred to as the **Java Applications Programming Interface (API)**.

*   **The `System.out.println` and `System.out.print` Methods**:
    *   The `System.out.println("Programming is great fun!");` line uses the `System` class from the standard Java library.
    *   The `System` class contains methods and objects for system-level tasks.
    *   The `out` object, a member of the `System` class, contains the `print` and `println` methods. These methods send characters to the output device.
    *   `System.out.println` (pronounced "System dot out dot println") takes a value inside its parentheses and prints it. **Crucially, it then places a newline character at the end of the output**, moving the cursor to the next line for subsequent printing.
        ```java
        System.out.println("This is being printed out");
        System.out.println("on two separate lines."); 
        // Output:
        // This is being printed out
        // on two separate lines.
        ```
    *   `System.out.print` works similarly but **does not put a newline character** at the end of the output. This means subsequent output will appear on the *same line*.
        ```java
        System.out.print("These lines will be"); 
        System.out.print("printed on");         
        System.out.println("the same line.");   
        // Output:
        // These lines will beprinted onthe same line.
        ```
        (Note: The odd spacing in the example above is because no spaces were included at the end of the first two strings to separate the words).

*   **Java Escape Sequences**:
    *   These are special character combinations within a string that allow you to print characters that would otherwise be unprintable or to control formatting.
    *   Even though they are made of two characters, the compiler treats them as a **single character**.
    *   Common escape sequences:
        *   `\n`: **newline** (moves cursor to the next line).
        *   `\t`: **tab** (moves cursor to the next tab stop).
        *   `\b`: backspace (moves cursor left one position).
        *   `\r`: carriage return (moves cursor to the beginning of the *current* line).
        *   `\\`: backslash (prints a backslash character).
        *   `\'`: single quote (prints a single quotation mark).
        *   `\"`: double quote (prints a double quotation mark).
        ```java
        System.out.print("These are our top sellers:\n"); 
        System.out.print("\tComputer games\n\tCoffee\n");
        System.out.println("\tAspirin");                  
        // Output:
        // These are our top seller:
        //     Computer games
        //     Coffee
        //     Asprin
        ```

#### **3. Variables and Literals**

To store and manipulate data in your programs, you use **variables** and **literals**.
*   A **variable** is a **named storage location in the computer's memory**. Programmers decide how many and what type of variables a program needs.
*   A **literal** is a **value that is written directly into the code** of a program.
    *   Examples: `"Hello"` (string literal), `5` (integer literal), `23.5F` (float literal), `true` (boolean literal), `'a'` (char literal).

**The `+` Operator:**
The `+` operator in Java has two main uses:
1.  **Addition operator**: For mathematical addition.
2.  **Concatenation operator**: If **either side** of the `+` operator is a **string**, the result will be a **string**. This is useful for combining text with variable values.
    ```java
    System.out.println("Hello " + "World");       // Concatenates two strings
    System.out.println("The value is: " + 5);     // Concatenates a string and a number
    ```

**String Concatenation for Long Literals:**
*   A single string literal value **cannot span multiple lines** in Java source code. This will cause a syntax error.
*   To fix this, you can use the **string concatenation operator (`+`)** to join parts of the string across multiple lines.
    ```java
    System.out.println("These lines are " +   
                       "are now ok and will not " +
                       "cause the error as before.");
    ```
*   The `+` operator can also join different data types.
*   **Important**: If you need to perform an **addition operation** within a string concatenation, that addition must be placed **inside parentheses** to ensure it's evaluated first.
    ```java
    // Incorrect: "First = " + 5 * 6 + ", " + "\n\tSecond = " + 6 + 4 + "," ...
    // This would concatenate 6 and 4 as strings if not in parentheses.
    System.out.println("The following will be printed " +
                       "in a tabbed format: " +
                       "\n\tFirst = " + (5 * 6) + ", " + // Parentheses ensure 5*6 is calculated first
                       "\n\tSecond = " + (6 + 4) + "," + // Parentheses ensure 6+4 is calculated first
                       "\n\tThird = " + 16.7 + ".");
    ```

#### **4. Identifiers**

**Identifiers** are names that programmers define for classes, variables, and methods.
*   **Rules for Identifiers**:
    *   They can only contain: **letters (a-z, A-Z), digits (0-9), underscores (`_`), or the dollar sign (`$`)**.
    *   The **first character may NOT be a digit**.
    *   **Java is case-sensitive**: `itemsOrdered` is different from `itemsordered`.
    *   Identifiers **cannot include spaces**.
    *   Identifiers **may not be any of the Java reserved keywords** (words like `public`, `class`, `int`, `void`, `true`, `false`, etc., which have special meaning in Java).

**Variable Naming Conventions (Style Guide):**
*   **Variable names should be descriptive** to make your code more readable and maintainable (e.g., `salesTaxRate` is better than `tr`). This helps make programs "self-documenting".
*   **Convention for variables**: Begin with a **lower case letter and then switch to title case** (camelCase) thereafter (e.g., `int caTaxRate`).
*   **Convention for classes**: Class names should be **all title case** (PascalCase) (e.g., `public class BigLittle`).
*   Generally, variable and class names tend to be nouns or noun phrases.

#### **5. Primitive Data Types**

Java has **8 primitive data types**, which are built into the language and are not derived from classes. These types directly hold values.

*   **Numeric Data Types**:
    *   **Integer Data Types** (for whole numbers without decimal points):
        *   `byte`: 1 byte, range -128 to +127.
        *   `short`: 2 bytes, range -32,768 to +32,767.
        *   `int`: **4 bytes**, range -2,147,483,648 to +2,147,483,647. This is the most commonly used integer type.
        *   `long`: 8 bytes, range -9,223,372,036,854,775,808 to +9,223,372,036,854,775,807.
        *   **Integer Division**: When you divide two integers, the result will be an integer, and **any decimal remainder will be truncated (removed)**. For example, `1 / 2` in Java results in `0`, not `0.5`.
    *   **Floating-Point Data Types** (for numbers with fractional values):
        *   `float`: **4 bytes**, also called **single precision** (about 7 digits of accuracy).
        *   `double`: **8 bytes**, also called **double precision** (about 15 digits of accuracy). This is the default type for floating-point literals.
        *   **Floating-Point Literals**:
            *   Numbers like `29.75`, `1.76`, `31.51` are by default `double` types.
            *   Because Java is a **strongly-typed language**, a `double` value is not directly compatible with a `float` variable due to size and precision differences.
            *   To assign a floating-point literal to a `float` variable, you must **append the letter `F` or `f`** to the literal (e.g., `23.5F`).
            *   Literals **cannot contain embedded currency symbols or commas** (e.g., `$1,257.00` is an error, `1257.00` is correct).
            *   They can be represented in **scientific (E) notation** (e.g., `47281.97` can be `4.728197E4`).

*   **The `boolean` Data Type**:
    *   Can only have two possible values: **`true` or `false`**.
    *   A `boolean` variable's value can only be copied into another `boolean` variable.

*   **The `char` Data Type**:
    *   Provides access to **single characters**.
    *   `char` literals are enclosed in **single quote marks** (e.g., `'a'`, `'Z'`, `'\n'`, `'1'`).
    *   **Do not confuse `char` literals with `String` literals**, which are enclosed in double quotes (`" "`).
    *   **Unicode**: Internally, characters are stored as numbers. Java uses **Unicode characters**, which can represent 65,536 (2^16) individual characters, with each taking up **2 bytes in memory**. The first 256 Unicode characters are compatible with the ASCII character set.

#### **6. Variable Declarations, Assignment, and Initialization**

Before you can use a variable, you must declare it.
*   **Variable Declaration**: `DataType VariableName;`.
    *   Examples: `byte inches;`, `int speed;`, `double distance;`.

*   **Variable Assignment**: To store a value in a variable, you use an **assignment statement**.
    *   The **assignment operator is the equal sign (`=`)**.
    *   The operand on the left side of `=` **must be a variable name**.
    *   The operand on the right side must be a literal or an expression that evaluates to a type **compatible** with the variable's declared type.
    *   Example: `value = 5;`.

*   **Variable Initialization**:
    *   Variables can be **declared and initialized on the same line**.
        ```java
        int month = 2, days = 28;
        ```
    *   **Local variables** (those declared inside a method like `main`) **do not receive a default value**.
    *   **Local variables must be initialized (given a value) before they are used**, otherwise, a **compiler error** will be generated.
    *   Variables can only hold **one value at a time**; assigning a new value overwrites the old one.

#### **7. Arithmetic Operators**

Java provides five arithmetic operators:
*   `+`: **Addition** (e.g., `total = cost + tax;`).
*   `-`: **Subtraction** (e.g., `cost = total - tax;`).
*   `*`: **Multiplication** (e.g., `tax = cost * rate;`).
*   `/`: **Division** (e.g., `salePrice = original / 2;`). Remember integer division truncates.
*   `%`: **Modulus** (returns the remainder of a division) (e.g., `remainder = value % 5;`).

*   These are **binary operators** because they operate on two operands (a left and a right operand).
*   It is an **error to try to divide any number by zero**.

**Operator Precedence**:
When an expression contains multiple operators, Java follows a set order of operations:
1.  **Unary negation** (`-` for negative numbers).
2.  **Multiplication (`*`), Division (`/`), Modulus (`%`)** (Higher priority, evaluated left-to-right).
3.  **Addition (`+`), Subtraction (`-`)** (Lower priority, evaluated left-to-right).

**Grouping with Parentheses `()`**:
*   You can use parentheses to **override the default operator precedence**.
*   Operations inside the **innermost parentheses are processed first**.
*   If two sets of parentheses are at the same level, they are processed from **left to right**.
    *   Example: `x = ((4 * 5) / (5 - 2)) - 25;` will result in `-19`.

**Combined Assignment Operators**:
These operators combine an arithmetic operation with assignment, providing a shorthand.
*   `+=`: `x += 5;` is equivalent to `x = x + 5;`.
*   `-=`: `y -= 2;` is equivalent to `y = y - 2;`.
*   `*=`: `z *= 10;` is equivalent to `z = z * 10;`.
*   `/=`: `a /= b;` is equivalent to `a = a / b;`.
*   `%=`: `c %= 3;` is equivalent to `c = c % 3;`.

#### **8. Creating Named Constants with `final`**

**Constants** are identifiers that can hold only a **single, unchanging value** throughout the program's execution.
*   They are declared using the keyword **`final`**.
*   **Benefits of using constants**:
    *   They make programs **easier to read and maintain** by replacing "magic numbers" (literal values) with descriptive names.
    *   They provide a **singular point for changing values** when needed, avoiding scattered literal changes.
*   Constants **must be initialized before they are used**; otherwise, a compiler error will occur.
*   Once initialized, their value **cannot be changed programmatically**.
*   **Convention for constants**: They are typically **all uppercase**, with words separated by the **underscore character** (e.g., `final int CAL_SALES_TAX = 0.725;`).

#### **9. The `String` Class**

Java **does not have a primitive data type that directly holds a series of characters**. Instead, it uses the **`String` class** from the Java standard library for this purpose.

*   **Primitive vs. Reference Variables**:
    *   **Primitive variables** (like `int`, `double`, `boolean`, `char`) actually **contain the value** they are assigned.
    *   **Objects**, including `String` objects, are **not stored directly in variables**. Instead, variables that hold objects are called **reference variables**. They contain the **memory address** of where the actual object is located. So, a `String` variable `cityName` references (points to) the object containing the characters `"Charleston"`.
*   **Creating `String` Objects**:
    *   You can assign a `String` literal directly to a `String` variable (e.g., `String value = "Hello";`). **Strings are the only objects that can be created this way**.
    *   For all other objects (and optionally for `String` objects), you use the `new` keyword (e.g., `String value = new String("Hello");`).
*   **`String` Methods**:
    *   Since `String` is a class, `String` objects have **methods** (functions that perform actions).
    *   An example is the `length()` method, which returns the number of characters in a string (e.g., `stringSize = value.length();`).
    *   **`String` objects are immutable**, meaning **they cannot be changed** once created. Many `String` methods that seem to modify a string actually create a *new* `String` object with the desired changes.

#### **10. Scope**

**Scope** refers to the **part of a program that has access to a variable's contents**.
*   Variables declared inside a method (like the `main` method) are called **local variables**.
*   A local variable's scope begins at its **declaration** and ends at the **end of the method** in which it was declared. You cannot use a variable outside its scope.

#### **11. Commenting Code**

Java offers three styles for comments, which are ignored by the compiler:
*   **Single-line comment (`//`)**: Everything after `//` on that line is a comment.
*   **Block comment (`/* ... */`)**: Everything between `/*` and the first `*/` is a comment. These **cannot be nested** (you can't put a block comment inside another block comment).
*   **Javadoc comment (`/** ... */`)**: A special type of block comment that starts with `/**`. These are used by the `javadoc` utility program to **generate HTML documentation** for your code. Like regular block comments, they **cannot be nested**.

#### **12. Programming Style**

While Java has strict syntax, it largely **ignores whitespace characters** (spaces, tabs, newlines, carriage returns, form feeds). However, good programming style is essential for **readability and maintainability**.
*   **Indentation**: Programs should use **proper indentation**. Each block of code (defined by curly braces) should be indented a few spaces (2-4 spaces are sufficient) from its surrounding block.
    *   **Avoid tab characters** because their size can vary between different text editors and devices. Most modern programming text editors can be configured to replace tabs with spaces.

#### **13. Using the `Scanner` Class for Input**

To read input from the keyboard, you use the **`Scanner` class**.
*   It's defined in the `java.util` package, so you need to include the following statement at the top of your program (before the class header) to make it available:
    `import java.util.Scanner;`.
*   To create a `Scanner` object, you link it to the standard input device (`System.in`):
    `Scanner keyboard = new Scanner(System.in);`.
*   Once created, you can use methods of the `Scanner` object (like `nextInt()`, `nextDouble()`, `nextLine()`, etc. - often detailed in a table in the textbook) to read different types of input.

#### **14. Dialog Boxes (`JOptionPane` Class)**

**Dialog boxes** are small graphical windows that can display messages or request input from the user. Java's **`JOptionPane` class** is used for this purpose.
*   The `JOptionPane` class is not automatically available, so you must include the following `import` statement at the top of your program:
    `import javax.swing.JOptionPane;`.

*   **Message Dialogs**: Used to display a message to the user.
    *   You use the `JOptionPane.showMessageDialog` method.
    *   Example: `JOptionPane.showMessageDialog(null, "Hello World");`. (The `null` argument is for more advanced uses explained later).

*   **Input Dialogs**: Used to prompt the user for input.
    *   They display a text field, an "Ok" button, and a "Cancel" button.
    *   If the user presses "Ok", the dialog returns the user's input as a `String`.
    *   If the user presses "Cancel", the dialog returns `null`.
    *   Example: `String name = JOptionPane.showInputDialog("Enter your name.");`.

*   **The `System.exit` Method**:
    *   When you use `JOptionPane`, Java creates a "thread" (a process running in the computer).
    *   A program using `JOptionPane` **does not automatically stop executing** when the `main` method ends. You need to explicitly stop the thread.
    *   To ensure the program terminates, you must call `System.exit(0);`.
    *   The integer argument (e.g., `0`) is an **exit code** passed back to the operating system. **A value of `0` traditionally indicates that the program ended successfully**.

*   **Converting a `String` to a Number (Parse Methods)**:
    *   The `JOptionPane.showInputDialog` method **always returns the user's input as a `String`**, even if they type numbers.
    *   To use this input as a numeric type (like `int` or `double`), you need to **convert the `String` to a number**.
    *   Each **numeric wrapper class** (e.g., `Integer` for `int`, `Double` for `double`, `Byte` for `byte`, `Short` for `short`, `Long` for `long`, `Float` for `float`) has a **parse method** for this conversion.
    *   These methods are named starting with "parse" (e.g., `Integer.parseInt`, `Double.parseDouble`).
    *   Examples:
        ```java
        // Reading an integer:
        int number;
        String str;
        str = JOptionPane.showInputDialog("Enter a number.");
        number = Integer.parseInt(str); // Converts the string to an int

        // Reading a double:
        double price;
        String strPrice; // Changed variable name to avoid conflict, not in source
        strPrice = JOptionPane.showInputDialog("Enter the retail price.");
        price = Double.parseDouble(strPrice); // Converts the string to a double
        ```

