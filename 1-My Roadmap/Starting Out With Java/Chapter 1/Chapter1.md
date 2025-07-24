### **Introduction to Computers and Java**

This chapter serves as an introduction to how computers work, why programming is essential, and specifically, what Java is all about.

**Java History**
Java's journey began in **1991** when Sun Microsystems (now owned by Oracle) initiated the **Green Team**. The initial focus was on a handheld controller for entertainment systems, which led to a clear **need for a programming language that could run on various devices**. This necessity gave birth to Java, which was originally named **Oak**.

A significant moment for Java came in **1995** when a Java-enabled web browser called **HotJava** was demonstrated at the Sun World conference. Soon after, Java was incorporated into Netscape. A key characteristic of Java that emerged from its development purpose is its **"cross platform"** capability, meaning it can run on diverse computer operating systems.

**Java Applications and Applets**
Java programs generally come in two types:
*   **Applications**: These are **stand-alone programs** that can run independently without the need for a web browser. They operate with a more **relaxed security model** because the user explicitly runs the program locally.
*   **Applets**: These are smaller applications that **require a Java-enabled web browser to run**. They come with an **enhanced security model** as they run automatically when a user visits a web page.

### **Why Program?**

Computers are incredibly versatile tools because they can be **programmed** to perform a vast array of functions. Computer programmers are the individuals who implement these programs. Common examples of what computers can be programmed to do include spreadsheets, databases, word processing, and games.

When designing a computer program, several aspects must be carefully considered:
*   The **logical flow of instructions**.
*   The **mathematical procedures** involved.
*   The **layout of the programming statements**.
*   The **appearance of the screens**.
*   How information is presented to the user, ensuring the **program’s “user friendliness”**.
*   The creation of **manuals, help systems, and other forms of written documentation**.

It's crucial that programs are **analytically correct**. Programs rarely work perfectly on the first attempt, requiring programmers to continually **analyze, experiment, correct, and redesign**. Programming languages are governed by **strict rules, known as syntax**, which must be meticulously followed.

### **Computer Systems: Hardware and Software**

A computer system is composed of two main parts: hardware and software.

#### **Computer Systems: Hardware**
**Hardware** refers to the **physical pieces** that make up the computer. The major hardware components include:
*   **The Central Processing Unit (CPU)**.
*   **Main Memory**.
*   **Secondary Storage Devices**.
*   **Input and Output Devices**.

1.  **Central Processing Unit (CPU)**
    The CPU is often considered the "brain" of the computer. It contains an **Arithmetic Logic Unit (ALU)** for mathematical and logical operations, and a **Control Unit** that coordinates all the computer's activities. The CPU processes program information by performing a continuous **fetch, decode, execute cycle**:
    *   **Fetch**: The CPU’s control unit retrieves the next instruction from main memory.
    *   **Decode**: The instruction, encoded as a number, is translated by the control unit into an electronic signal.
    *   **Execute**: This signal is then sent to the appropriate computer component (like the ALU or a disk drive), causing it to perform the specified operation.

2.  **Main Memory (RAM)**
    Main memory is commonly known as **Random-Access Memory (RAM)**. It temporarily holds **currently running programs and the data** these programs use.
    *   RAM is organized into units called **bytes**, where each byte consists of eight **bits**.
    *   A bit is the most basic unit of information in a computer, representing either an **"on" (1) or "off" (0)** state. Patterns of these bits form characters or numbers.
    *   Each byte in memory has a unique identifying number called an **address**.
    *   A section of two or four bytes is often referred to as a **word**.
    *   **RAM is volatile**, meaning that its contents are erased when the computer is turned off.

3.  **Secondary Storage Devices**
    Unlike RAM, secondary storage devices are **non-volatile**, meaning they are capable of **storing information for longer periods** of time, even when the computer is turned off. Common examples include disk drives, external drives, CD drives, solid state drives, USB drives, and DVD drives.

4.  **Input Devices**
    **Input** is any data that the computer collects from the outside world. This data comes from **input devices**, such as a keyboard, mouse, scanner, or digital camera.

5.  **Output Devices**
    **Output** is any data the computer sends to the outside world. This data is displayed or presented via **output devices**, such as monitors and printers. Some devices, like disk drives, can perform both input and output functions and are therefore called **I/O devices**.

#### **Computer Systems: Software**
**Software** refers to the **programs that run on a computer**. Software is broadly classified into two categories:
*   **Operating Systems**.
*   **Application Software**.

1.  **Operating Systems (OS)**
    An operating system is a **set of programs that manages the computer’s hardware devices and controls their processes**. Most modern operating systems are **multitasking**, meaning they can run multiple programs simultaneously. This is achieved through a technique called **time sharing**, where the OS efficiently divides hardware resources and the CPU's attention among all executing programs. Examples include Unix, Linux, Mac OS, and Windows.

2.  **Application Software**
    **Application software** consists of programs designed to make the computer **useful to the user**. They provide specialized environments for users to perform specific tasks. Common examples include spreadsheets, word processors, accounting software, tax software, and games.

### **Programming Languages**

A **program** is a set of instructions a computer follows to perform a task. A **programming language** is a specialized language used to write these computer programs. Collectively, these instructions form an **algorithm**.

An **algorithm** is a **set of well-defined steps** to complete a task, and these steps are typically performed **sequentially**. For a computer to understand an algorithm, it must be written in **machine language**.
*   **Machine language** is a binary numbering system (base 2) that uses only two digits: **0 and 1**.
*   Each CPU has its **own unique machine language**. In the past, programmers wrote directly in machine language, which was very difficult.

To simplify programming, **higher-level programming languages** were developed.
*   The first step was **assembler**, which made programming easier but was still **processor-dependent**.
*   Eventually, **high-level programming languages** emerged that were **not processor-dependent**, offering much greater ease of use and flexibility. Examples include Java, C++, Python, C#, and Ruby.

**Common Language Elements**
Despite their differences, virtually all programming languages share some common concepts:
*   **Key words**: These are words that have a special meaning in the language and cannot be used for other purposes. In Java, keywords are lowercase, and Java is a **case-sensitive** language (meaning `Public` is different from `public`).
*   **Operators**: Symbols that perform operations on data (e.g., `+` for addition).
*   **Punctuation**: Symbols used to mark the beginning or end of statements or to separate items (e.g., semi-colons). In Java, **semi-colons are used to end statements**, but not all lines in a Java program necessarily end a statement.
*   **Programmer-defined identifiers**: Names created by the programmer for variables, functions, etc..
*   **Strict syntactic rules**: The specific grammar and structure that must be followed when writing code.

**Lines vs. Statements**
It's important to understand the difference between lines of code and statements. A **statement is a complete Java instruction** that tells the computer to perform an action. A single statement can sometimes be written across multiple lines of code.

### **What Is a Program Made Of? (Variables)**

In a Java program, data is stored in the computer's memory. To work with this data, programmers use **variables**.
*   **Variables are symbolic names that represent a location in memory** where data is stored. In Java, variables are sometimes also called **fields**.
*   Programmers create variables and assign them a **programmer-defined identifier** (their name).
*   For example, `int hours = 40;` creates a variable named `hours` (an integer type) and stores the value `40` in the memory location it represents.
*   While the programmer declares the variable, the **Java Virtual Machine (JVM)** ultimately decides the exact physical location in memory where the value will be placed.

### **The Compiler and the Java Virtual Machine (JVM)**

The process of creating and running a Java program involves several steps and specialized tools:

1.  **Source Code**: A programmer writes Java programming statements, known as **source code**, using a text editor. These files are saved with a **`.java` file extension** (e.g., `HelloWorld.java`).
2.  **Compiler**: A **compiler** is a program that translates the human-readable source code into an executable form that the computer can understand.
    *   During compilation, the compiler checks for **syntax errors**, which are mistakes made by the programmer that violate the programming language's rules. If errors are found, the programmer must correct them.
    *   Unlike most compilers that translate directly into machine code, the **Java compiler** (known as `javac`) translates a Java source file into **byte code instructions**.
    *   **Byte code instructions** are the machine language of the **Java Virtual Machine (JVM)**. Crucially, they **cannot be executed directly by the computer's CPU**.
    *   Byte code files are saved with a **`.class` file extension**.
3.  **Java Virtual Machine (JVM)**: The JVM is a program that **emulates a microprocessor**. It reads and executes the byte code instructions. Because the JVM interprets and executes instructions as they are read, the JVM is often called an **interpreter**, and Java is frequently referred to as an **interpreted language**.

This process can be visualized as:
**Text editor** (`.java` source code) → **Java compiler** (`javac`) → **Byte code** (`.class` file) → **Java Virtual Machine (JVM)** → **Program Execution**.

**Portability**
One of Java's most significant advantages is its **portability**.
*   **Portability** means that a program can be written on one type of computer and then **run on a wide variety of other computers with little to no modification**.
*   Java achieves this by having its byte code run on the JVM, rather than directly on a specific CPU.
*   JVMs are available for many different platforms, including Unix, Windows, Mac, and Linux.
*   This means that Java programmers do not have to recompile their programs for each different platform, unlike with many other programming languages.

**Java Versions and Compiling**
The software used to write Java programs is called the **Java Development Kit (JDK)**. There are different editions of the JDK, such as:
*   **Java SE (Standard Edition)**.
*   **Java EE (Enterprise Edition)**.
*   **Java ME (Micro Edition)**.
The JDK is available for download from `http://java.oracle.com`.

To compile a Java program using the command line, you use the `javac` command, followed by the filename including the `.java` extension. For example, to compile `Payroll.java`, you would type `javac Payroll.java`.

### **The Programming Process**

Developing a program is a systematic process, typically involving these steps:
1.  **Clearly define what the program is to do.** What problem will it solve?
2.  **Visualize the program running on the computer.** How will it interact with the user?
3.  **Use design tools to create a model of the program.** This might involve diagrams or pseudocode.
4.  **Check the model for logical errors.** Does the proposed solution make sense?
5.  **Enter the code and compile it.** Translate your design into a programming language.
6.  **Correct any errors found during compilation.** This step often involves repeating steps 5 and 6 until the code compiles successfully.
7.  **Run the program with test data for input.** See how the program behaves with actual data.
8.  **Correct any runtime errors found while running the program.** These are errors that only appear when the program is executing. This step may require repeating steps 5 through 8.
9.  **Validate the results of the program.** Ensure the program produces the correct output for various inputs.

### **Software Engineering**

**Software engineering** encompasses the entire process of crafting computer software. Software engineers are involved in numerous tasks for complex software projects, including:
*   **Designing** the software.
*   **Writing** the code.
*   **Testing** for functionality and errors.
*   **Debugging** (finding and fixing errors).
*   **Documenting** the code and its usage.
*   **Modifying** and **maintaining** the software over time.

They develop various artifacts like program specifications, diagrams of screen output, diagrams representing program components and data flow, pseudocode, and examples of expected input and desired output. They also utilize specialized software for testing. Given the large and complex nature of most commercial software, it is usually developed by a **team of programmers**, not just an individual. Program requirements are thoroughly analyzed and divided into subtasks for individual teams or members.

### **Object-Oriented Programming (OOP)**

Chapter 1 introduces two major programming paradigms: procedural programming and object-oriented programming.

**Procedural Programming**
*   This is an older approach to programming.
*   It focuses on **procedures** (also called functions or subroutines), which are sets of programming language statements that perform a specific task.
*   In procedural programming, **procedures typically operate on data items that are separate from the procedures themselves**. Data items are commonly passed from one procedure to another, and data tends to be **global** to the entire program.
*   A major challenge with procedural programming is that if data formats change, all the procedures that operate on that data must also change, which can be complex.

**Object-Oriented Programming (OOP)**
*   OOP is a more modern approach that is **centered on creating objects** rather than just procedures.
*   An **object** is a **melding of data and the procedures that manipulate that data**.
    *   The **data** within an object is known as its **attributes**.
    *   The **procedures** within an object are known as its **methods** (also referred to as behaviors).
*   A core concept in OOP is **encapsulation**, which is the practice of combining data (attributes) and behavior (methods) into a single unit (the object).
*   Another key concept is **data hiding**, which means an object can hide its data from other objects in the program.
*   Ideally, **only an object's own methods should be able to directly manipulate its attributes**. Other objects are allowed to interact with an object's attributes only **indirectly, through the object’s methods**. This indirect access is known as a **programming interface**. This approach enhances program organization, reusability, and maintainability.

---

**Analogy:**
Think of programming a computer like training a highly intelligent, but very literal, puppy.

*   The **CPU** is the puppy's brain, which understands simple commands one at a time.
*   **Main memory (RAM)** is like the puppy's short-term memory or a whiteboard where it quickly scribbles down notes for the tasks it's currently doing, but everything gets erased when it takes a nap (turns off).
*   **Secondary storage** is like the puppy's long-term memory or a sturdy notebook where it keeps important things permanently, even when it's sleeping.
*   **Input devices** are how you give commands to the puppy, like hand signals or voice commands. **Output devices** are how the puppy shows you it's done something, like wagging its tail or bringing a toy.
*   A **program** is like a complex trick you want the puppy to do, broken down into a precise sequence of simple commands.
*   A **programming language** is the specific set of words and gestures you use to communicate these commands to the puppy.
*   **Machine language** is like the puppy's innate, most basic understanding – barks and whimpers – which is hard for you to speak directly. **High-level languages** are like translating those into human words that the puppy *learns* to associate with actions.
*   The **compiler** is your translator, turning your human words (source code) into the puppy's specialized language (byte code).
*   The **Java Virtual Machine (JVM)** is like a special trainer or "dog whisperer" that understands all the different breeds of puppies (different operating systems) and interprets your translated commands (byte code) so any puppy can understand them, making your trick **portable**.
*   **Variables** are like specific spots where the puppy holds a particular toy or object you've given it, each spot having a unique name.
*   **Object-Oriented Programming (OOP)** is like teaching the puppy to group its toys (data/attributes) with the tricks it knows to do with those specific toys (methods). So, instead of just "fetch," you teach it "fetch the *ball*," and the "ball" knows how to be fetched and bounced, keeping its related actions together. This way, you don't accidentally tell it to "bounce" a stick if it doesn't know how to do that with a stick.