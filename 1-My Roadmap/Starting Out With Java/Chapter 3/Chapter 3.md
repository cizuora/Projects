### Chapter 3: Decision Structures – Guiding Your Program's Choices

Chapter 3 of your textbook focuses on **Decision Structures**. In programming, decision structures allow your program to make choices and execute different parts of code based on certain conditions, much like you make decisions in your daily life. This chapter covers various ways to implement these choices, including:
*   The `if` Statement
*   The `if-else` Statement
*   Nested `if` statements
*   The `if-else-if` Statement
*   Logical Operators
*   Comparing `String` Objects
*   More about Variable Declaration and Scope
*   The Conditional Operator
*   The `switch` Statement
*   Displaying Formatted Output with `System.out.printf` and `String.format`

Let's break down each of these topics:

### 1. The `if` Statement: Making a Single Choice

The `if` statement is the most fundamental decision structure. Its purpose is to **decide whether a specific section of code should run or not**.

*   It uses a **boolean expression** to make this decision. A boolean expression is any variable or calculation that evaluates to either `true` or `false`.
*   If the boolean expression inside the `if` statement is `true`, the code immediately following the `if` statement executes. If it's `false`, that code is skipped.

**Basic Syntax:**
```java
if (boolean expression is true)
  execute next statement;
```


**Visualizing `if` Statements with Flowcharts:**
Think of a flowchart as a visual representation of your program's path.
*   For a simple `if` statement, it's like asking a question: "Is it cold outside?".
    *   If "Yes" (the condition is `true`), you "Wear a coat.".
    *   If "No" (the condition is `false`), you simply move on without wearing a coat.

**Relational Operators: How We Form Boolean Expressions**
In most cases, the boolean expressions used by `if` statements involve **relational operators**. These operators compare two values and determine if a relationship exists between them, resulting in a `true` or `false` outcome.

Here's a list of common relational operators:
*   `>`: **is greater than** (e.g., `x > y` checks "Is x greater than y?")
*   `<`: **is less than** (e.g., `x < y` checks "Is x less than y?")
*   `>=`: **is greater than or equal to** (e.g., `x >= y` checks "Is x greater than or equal to y?")
*   `<=`: **is less than or equal to** (e.g., `x <= y` checks "Is x less than or equal to y.")
*   `==`: **is equal to** (e.g., `x == y` checks "Is x equal to y?")
*   `!=`: **is not equal to** (e.g., `x != y` checks "Is x not equal to y?")

**Examples of `if` statements with Boolean Expressions:**
```java
if (x > y) // Is x greater than y?
  System.out.println("X is greater than Y");

if (x == y) // Is x equal to y?
  System.out.println("X is equal to Y");

if (x != y) // Is x not equal to y?
{
  System.out.println("X is not equal to Y");
  x = y; // You can have multiple statements
  System.out.println("However, now it is.");
}
```

**Programming Style and `if` Statements:**
While an `if` statement can span multiple lines, it's still considered one logical statement.
```java
if (average > 95)
  grade = 'A';
// This is functionally equivalent to:
if (average > 95) grade = 'A';
```


**Rules of Thumb for Good Style:**
*   The statement that is conditionally executed (the one that runs if the `if` condition is true) **should be on the line immediately after the `if` condition**.
*   This conditionally executed statement **should be indented one level** from the `if` condition. This makes your code much easier to read and understand.
*   **Crucially, if an `if` statement does not use curly braces `{}` (which we'll discuss next), it is ended by the very first semicolon (`;`) encountered after the `if` condition**.

**Block `if` Statements: Executing Multiple Statements Conditionally**
What if you want to execute more than one statement when an `if` condition is true? You can **group these statements into a "block" by enclosing them within curly braces `{}`**.

```java
if (coldOutside) // If it's cold outside...
{ // ...start a block of statements
  wearCoat();
  wearHat();
  wearGloves();
} // The closing curly brace ends the if statement.
```


**Important Note:** When curly braces are NOT used, **only the very next statement after the `if` condition will be executed conditionally**.
```java
if (expression)
  statement1; // Only this statement is conditionally executed.
statement2; // This statement will ALWAYS execute, regardless of 'expression'.
statement3; // This statement will ALSO always execute.
```


**Flags: Monitoring Conditions with Boolean Variables**
A **flag** is a special kind of boolean variable that acts like a switch to monitor a condition in your program.
*   When a condition becomes `true`, you set the flag variable to `true`.
*   Later in your program, you can test the flag to see if that condition still holds or has changed.

**Example:**
```java
if (average > 95)
  highScore = true; // Set the flag if the condition is met.

// Later in the program...
if (highScore) // Test the flag.
  System.out.println("That's a high score!");
```

**Comparing Characters:**
Characters can also be compared using relational operators.
*   Characters are stored in computer memory using the **Unicode character format**.
*   Unicode characters are represented as **sixteen (16) bit numbers**.
*   Because characters have a specific **ordinal order** within the Unicode set, you can compare them. For example, 'A' comes before 'Z', so `'A' < 'Z'` would evaluate to `true`.

**Example:**
```java
char c = 'A';
if (c < 'Z')
  System.out.println("A is less than Z"); // This will print, as 'A' has a lower Unicode value than 'Z'.
```


### 2. The `if-else` Statement: Making a Two-Way Choice

The `if-else` statement expands on the `if` statement by providing an alternative path of execution when the `if` condition is `false`. It allows you to say, "If this condition is true, do A; otherwise (else), do B."

**Syntax:**
```java
if (expression)
  statementOrBlockIfTrue; // Executes if 'expression' is true.
else
  statementOrBlockIfFalse; // Executes if 'expression' is false.
```

**`if-else` Flowchart:**
```
            +-----------------+
            | Is it cold      |
            | outside?        |
            +-----------------+
                  | Yes      | No
                  v          v
          +---------------+   +---------------+
          | Wear a coat.  |   | Wear shorts.  |
          +---------------+   +---------------+
                  |          |
                  +----------+
                       |
                       v
                 (Continue program)
```


### 3. Nested `if` Statements: Choices Within Choices

A **nested `if` statement** occurs when an `if` statement (either single or a block) is placed **inside another `if` statement**.

*   The key concept here is that the **nested `if` statement will only execute if the outer `if` statement's condition evaluates to `true`**.

**Nested `if` Statement Flowchart:**
Imagine it's cold outside, and you also want to check if it's snowing:
```
            +-----------------+
            | Is it cold      |
            | outside?        |
            +-----------------+
                  | Yes      | No
                  v          v
          +-----------------+   +---------------+
          | Is it snowing?  |   | Wear shorts.  |
          +-----------------+   +---------------+
                  | Yes      | No
                  v          v
          +---------------+   +---------------+
          | Wear a parka. |   | Wear a jacket.|
          +---------------+   +---------------+
                  |          |
                  +----------+
                       |
                       v
                 (Continue program)
```


**Example Code Structure for Nested `if`:**
```java
if (coldOutside) // Outer if: executes only if coldOutside is true
{
  if (snowing) // Nested if: executes only if coldOutside is true AND snowing is true
  {
    wearParka();
  }
  else // This 'else' belongs to the nested 'if (snowing)'
  {
    wearJacket();
  }
}
else // This 'else' belongs to the outer 'if (coldOutside)'
{
  wearShorts();
}
```


**`if-else` Matching and Readability:**
While curly braces aren't always required for a single conditionally executed statement, **using curly braces can significantly improve program readability**, especially with nested `if-else` structures. **Proper indentation is also crucial** as it makes it much easier to see which `else` statement corresponds to which `if` statement.

*   Java matches an `else` clause to the **immediately preceding unmatched `if` statement**. Clear indentation helps you visually confirm this matching.

### 4. The `if-else-if` Statement: Handling Multiple Exclusive Choices

Nested `if` statements can sometimes become very complex and difficult to read. The `if-else-if` statement provides a **simpler way to write certain types of nested decision logic** when you have a series of mutually exclusive conditions (meaning only one of them can be true).

**General Format:**
```java
if (expression_1) // First condition to check
{
  // Statements executed if expression_1 is true
  // The rest of the structure is ignored.
}
else if (expression_2) // If expression_1 was false, check expression_2
{
  // Statements executed if expression_2 is true
  // The rest of the structure is ignored.
}
// You can insert as many else if clauses as needed.
else // If none of the above expressions are true
{
  // Statements executed if all preceding expressions are false.
}
```


**How it Works:** The program checks the `if` condition first. If it's true, its block executes, and the rest of the `if-else-if` structure is skipped. If the first `if` is false, it moves to the `else if` condition. This continues down the chain. If none of the `if` or `else if` conditions are met, the final `else` block (if present) is executed.

### 5. Logical Operators: Combining and Modifying Conditions

Java provides **logical operators** to combine boolean expressions or reverse their truth. These are incredibly useful when you need to check multiple conditions simultaneously.

There are two **binary logical operators** (meaning they take two operands):
*   `&&` (Logical AND)
*   `||` (Logical OR)

And one **unary logical operator** (meaning it takes one operand):
*   `!` (Logical NOT)

| Operator | Meaning      | Effect                                                                                                                                                                                                                                                         |
| :------- | :----------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `&&`     | **AND**      | Connects two boolean expressions. **Both expressions must be true for the overall combined expression to be true.** If even one is false, the whole expression is false.                                                                                  |
| `||`     | **OR**       | Connects two boolean expressions. **One or both expressions must be true for the overall combined expression to be true.** It is only false if *both* expressions are false.                                                                             |
| `!`      | **NOT**      | Reverses the truth of a boolean expression. If applied to `true`, it returns `false`. If applied to `false`, it returns `true`.                                                                                                                      |



**The `&&` Operator (Logical AND):**
*   Takes two boolean expressions as operands.
*   The combined expression is `true` **if and only if both operands are `true`**.

| Expression 1 | Expression 2 | Expression1 `&&` Expression2 |
| :----------- | :----------- | :--------------------------- |
| `true`       | `false`      | `false`                      |
| `false`      | `true`       | `false`                      |
| `false`      | `false`      | `false`                      |
| `true`       | `true`       | `true`                       |



**The `||` Operator (Logical OR):**
*   Takes two boolean expressions as operands.
*   The combined expression is `false` **if and only if both operands are `false`**. Otherwise, it's `true`.

| Expression 1 | Expression 2 | Expression1 `||` Expression2 |
| :----------- | :----------- | :--------------------------- |
| `true`       | `false`      | `true`                       |
| `false`      | `true`       | `true`                       |
| `false`      | `false`      | `false`                      |
| `true`       | `true`       | `true`                       |



**The `!` Operator (Logical NOT):**
*   Performs a logical NOT operation.
*   If an expression is `true`, `!expression` will be `false`.
*   If an expression is `false`, `!expression` will be `true`.

**Example:**
```java
if (!(temperature > 100)) // This reads: "If it's NOT true that temperature is greater than 100"
  System.out.println("Below the maximum temperature.");
```
If `temperature` is 90 (so `temperature > 100` is `false`), then `!(false)` becomes `true`, and the `println` statement runs.

| Expression 1 | `!`Expression1 |
| :----------- | :------------- |
| `true`       | `false`        |
| `false`      | `true`         |



**Short-Circuiting:**
Logical `AND` (`&&`) and logical `OR` (`||`) operations in Java are "short-circuit" operations, which means they optimize their evaluation.
*   **Logical `AND` (`&&`) will evaluate to `false` as soon as it encounters an operand that is `false`**. It doesn't need to check the second operand because the result will already be `false`.
*   **Logical `OR` (`||`) will evaluate to `true` as soon as it encounters an operand that is `true`**. It doesn't need to check the second operand because the result will already be `true`.

**Order of Precedence:**
When you have multiple operators in an expression, Java follows a specific **order of precedence** to determine which operations are performed first.
*   The `!` operator has higher precedence than `&&` and `||`.
*   `&&` and `||` have lower precedence than relational operators (`<`, `>`, `<=`, `>=`).
*   You can always use **parentheses `()` to force the precedence to be changed** and ensure operations are performed in the order you intend.

Here's a simplified order of precedence for relevant operators (lower number means higher precedence):

| Order of Precedence | Operators                               | Description                                                                 |
| :------------------ | :-------------------------------------- | :-------------------------------------------------------------------------- |
| 1                   | `! `                                    | Unary negation, logical NOT                                                 |
| 2                   | `*` `/` `%`                             | Multiplication, Division, Modulus (remainder)                               |
| 3                   | `+` `-`                                 | Addition, Subtraction                                                       |
| 4                   | `<` `>` `<=` `>=`                       | Less-than, Greater-than, Less-than or equal to, Greater-than or equal to |
| 5                   | `==` `!=`                               | Is equal to, Is not equal to                                                |
| 6                   | `&&`                                    | Logical AND                                                                 |
| 7                   | `||`                                    | Logical OR                                                                  |
| 8                   | `=` `+=` `-=` `*=` `/=` `%=`            | Assignment and combined assignment operators                              |



### 6. Comparing `String` Objects: Beyond Relational Operators

This is a common point of confusion for beginners! **In most cases, you cannot use the relational operators (like `==`) to compare two `String` objects to see if their contents are the same**.

*   This is because `String` variables in Java are **reference variables**. Instead of holding the actual text, they hold the **memory address** where the `String` object (the actual text) is stored.
*   When you use `==` with `String` objects, it checks if the **reference variables point to the exact same object in memory**, not whether the characters inside the strings are identical. If they point to different objects, even if those objects contain the identical sequence of characters, `==` will return `false`.

To compare the *contents* of two `String` objects, you must use **methods provided by the `String` class**, such as `equals()` or `compareTo()`.

**Ignoring Case in String Comparisons:**
The `equals()` and `compareTo()` methods are **case-sensitive**. This means "Hello" is considered different from "hello".
*   To compare two `String` objects while ignoring their case, use the methods:
    *   `equalsIgnoreCase()`
    *   `compareToIgnoreCase()`

### 7. Variable Scope: Where Your Variables Are Visible

**Scope** refers to the region of a program where a variable is accessible or "visible".
*   In Java, a **local variable** (a variable declared inside a method or block of code) **does not have to be declared at the very beginning of the method**.
*   The **scope of a local variable begins at the exact point where it is declared** and **terminates at the end of the method or block of code where it was declared**.
*   When a program reaches a section of code where a variable has scope, that variable is said to have **"come into scope,"** meaning it becomes visible and usable by the program.

### 8. The Conditional Operator: A Concise `if-else`

The **conditional operator** is a unique operator in Java because it is a **ternary operator**, meaning it takes **three operands**.
*   You can use it as a compact way to write a simple `if-else` statement, often for assigning a value based on a condition.

**Format:**
`BooleanExpression ? Value1 : Value2`

**How it works:**
*   First, the `BooleanExpression` is evaluated.
*   If `BooleanExpression` is `true`, the value of the entire conditional expression is `Value1`.
*   If `BooleanExpression` is `false`, the value of the entire conditional expression is `Value2`.

**Example:**
```java
z = x > y ? 10 : 5; // If x is greater than y, z becomes 10; otherwise, z becomes 5.
```
This single line is functionally equivalent to the following `if-else` statement:
```java
if (x > y)
  z = 10;
else
  z = 5;
```

It is very commonly used to supply a value to a variable.

### 9. The `switch` Statement: Multi-Way Branching

While `if-else` statements allow for true/false branches or sequential checks, the `switch` statement is designed for **making decisions based on an ordinal value**. It's excellent when you have a variable that could have several distinct integer or character values, and you want to execute different code for each specific value.

*   The `switch` statement can evaluate an **integer type** (`byte`, `short`, `int`, `long`) or **character type** (`char`) variable.
*   As of Java 7, the `SwitchExpression` can also be a **`String`**.

**General Format:**
```java
switch (SwitchExpression) // The variable whose value will be evaluated
{
  case CaseExpression1: // If SwitchExpression matches CaseExpression1
    // place one or more statements here
    break; // Exit the switch statement
  case CaseExpression2: // If SwitchExpression matches CaseExpression2
    // place one or more statements here
    break;
  // ... (case statements may be repeated as many times as necessary)
  default: // Optional: if no CaseExpression matches the SwitchExpression
    // place one or more statements here
}
```


**How it Works:**
1.  The `switch` statement evaluates the `SwitchExpression`.
2.  The program then looks for a `case` statement whose `CaseExpression` matches the value of the `SwitchExpression`.
3.  If a match is found, program execution "jumps" to that `case` statement, and the statements following it are executed.
4.  Each `CaseExpression` must be unique.

**The `break` Statement:**
*   The `break` statement is crucial inside a `case`. When a `break` statement is encountered, it **ends the `case` statement** and causes program execution to exit the entire `switch` structure.
*   **The `break` statement is optional**. If a `case` does not contain a `break` statement, execution will **continue into the next `case` statement** (this is called "fall-through"). While sometimes intentional, it's a common source of bugs if forgotten.

**The `default` Section:**
*   The `default` section is also optional.
*   It will be executed if **none of the `CaseExpression` values match the `SwitchExpression`**. It acts like an `else` block for the `switch` statement.

### 10. Displaying Formatted Output: `System.out.printf` and `String.format`

Sometimes, you need more control over how your program's output looks, especially when dealing with numbers or aligning text. Java provides powerful methods for this.

**The `System.out.printf` Method:**
*   This method allows you to perform **formatted console output**. This means you can specify how values (like integers, floating-point numbers, or strings) should be displayed, including their width, precision, and alignment.
*   **General Format:** `System.out.printf(FormatString, ArgList);`
    *   `FormatString`: A `String` that contains regular text and/or special **formatting specifiers**.
    *   `ArgList`: An optional list of additional arguments (variables or values) that will be formatted according to the specifiers in the `FormatString`.

**Examples of `printf` and Format Specifiers:**
*   **Simple text:**
    ```java
    System.out.printf("Hello World\n"); // Prints "Hello World" followed by a new line.
    ```
   
*   **`%d` for decimal integers:**
    ```java
    int hours = 40;
    System.out.printf("I worked %d hours.\n", hours); // %d indicates an integer will be printed.
    // Output: I worked 40 hours.
    ```
   
    You can use multiple `%d` specifiers for multiple integer variables:
    ```java
    int dogs = 2, cats = 4;
    System.out.printf("We have %d dogs and %d cats.\n", dogs, cats);
    // Output: We have 2 dogs and 4 cats.
    ```
   
*   **`%f` for floating-point values:**
    ```java
    double grossPay = 874.12;
    System.out.printf("Your pay is %f.\n", grossPay); // %f indicates a floating-point value.
    // Output: Your pay is 874.120000. (Default precision is 6 decimal places)
    ```
   
*   **`%.nf` for specific decimal precision (e.g., `%.2f` for two decimal places):**
    ```java
    double grossPay = 874.12;
    System.out.printf("Your pay is %.2f.\n", grossPay); // %.2f rounds to two decimal places.
    // Output: Your pay is 874.12.
    ```
   
*   **`%,.nf` for comma separators and specific decimal precision:**
    ```java
    double grossPay = 5874.127;
    System.out.printf("Your pay is %,.2f.\n", grossPay); // %,.2f adds commas and rounds.
    // Output: Your pay is 5,874.13. (Note the rounding of .127 to .13)
    ```
   
*   **`%s` for strings:**
    ```java
    String name = "Ringo";
    System.out.printf("Your name is %s.\n", name); // %s indicates a string.
    // Output: Your name is Ringo.
    ```
   
*   **Specifying a field width (e.g., `%6d`):** This allocates a certain number of spaces for the output. The value will be right-aligned by default within that field.
    ```java
    int number = 9;
    System.out.printf("The value is %6d\n", number); // %6d allocates 6 spaces for the integer.
    // Output: The value is      9 (5 spaces before 9)
    ```
   
*   **Combining field width and precision (e.g., `%6.2f`):**
    ```java
    double number = 9.76891;
    System.out.printf("The value is %6.2f\n", number); // 6 spaces total, 2 decimal places.
    // Output: The value is   9.77 (2 spaces before 9.77, total 6 characters including '.')
    ```
   

**The `String.format` Method:**
*   This method works **exactly like `System.out.printf`** in terms of how you specify formatting.
*   However, `String.format` **does not display the formatted string on the screen**.
*   Instead, it **returns a reference to the newly formatted string**. This means you can store the formatted string in a variable and then use it later in your program (e.g., to display it, save it to a file, etc.).

**General Format:** `String.format(FormatString, ArgumentList);`

**Example:**
```java
double amount = 123.45;
String formattedAmount = String.format("The amount is $%,.2f", amount); // Formats the string.
// formattedAmount now holds the string "The amount is $123.45"
System.out.println(formattedAmount); // You can then print the variable.
```

***

**Analogy for Decision Structures:**
Think of decision structures in programming like a **road with intersections and traffic lights**.
*   An **`if` statement** is like a single traffic light: if it's green, you go straight; otherwise, you wait (or simply don't go this specific direction).
*   An **`if-else` statement** is like a fork in the road with a sign: "If the path is clear, go left; otherwise, go right." You'll always take one path or the other.
*   **Nested `if` statements** are like driving through a series of traffic lights. You only get to the second light if the first one is green.
*   An **`if-else-if` chain** is like a series of alternative routes you can take to your destination, checking each one in order until you find one that's open, or defaulting to a specific route if all others are blocked.
*   A **`switch` statement** is like a roundabout with multiple exits labeled for different destinations. You enter the roundabout (the `switch` expression) and take the specific exit (a `case`) that matches where you want to go. If your destination isn't explicitly labeled, you might take a general "default" exit.