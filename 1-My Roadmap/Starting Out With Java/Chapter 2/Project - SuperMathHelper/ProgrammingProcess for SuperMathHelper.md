### **Programming Process for `SuperMathHelper.java`**

---

#### **1. Clearly define what the program is to do.**  
**Purpose:**  
A comprehensive math helper application with multiple features:  
- **Basic Calculator:** Performs arithmetic operations (`+`, `-`, `*`, `/`, `%`).  
- **Tax Calculator:** Computes tax (8%) and total price.  
- **Integer Operations:** Squares, cubes, and checks even/odd status.  
- **Unit Converter:** Converts miles ↔ kilometers.  
- **Math Quiz:** Generates random arithmetic questions.  
- **GUI Version:** Swing-based interface for all features.  

**Problem Solved:**  
Provides a centralized tool for common math-related tasks, catering to both CLI and GUI users.

---

#### **2. Visualize the program running on the computer.**  
**CLI Flow:**  
1. Displays a menu with numbered options.  
2. User selects a feature (e.g., `1` for Basic Calculator).  
3. Prompts for input (e.g., two numbers for addition).  
4. Shows results and returns to the menu.  

**GUI Flow:**  
1. Opens a dialog with buttons for each feature.  
2. Input collected via pop-up windows (e.g., `JOptionPane`).  
3. Results displayed in a message box.  

---

#### **3. Use design tools to create a model of the program.**  
**Structure:**  
- **Main Menu Loop:**  
  ```java
  while (running) {
      printMenu();
      int choice = input.nextInt();
      switch (choice) {
          case 1 -> basicCalculator();
          // ... other cases ...
      }
  }
  ```  
- **Modular Methods:** Each feature is a separate method (e.g., `taxCalculator()`).  
- **Constants:** `TAX_RATE`, `KM_PER_MILE` for maintainability.  

**Pseudocode for Math Quiz:**  
```plaintext
generate num1, num2, operator randomly
ask user: "num1 operator num2?"
check answer → display "Correct/Wrong"
```

---

#### **4. Check the model for logical errors.**  
**Potential Issues:**  
- Division by zero in `basicCalculator()`. **→ Handled with `if (num2 != 0)`.**  
- Invalid menu input (e.g., `7`). **→ Default case prints "Invalid choice!"**  
- Non-numeric input in GUI. **→ `try-catch` blocks for `NumberFormatException`.**  

**Validation:**  
- All features tested with edge cases (e.g., zero, negative numbers).  
- GUI methods handle cancel/close actions.  

---

#### **5. Enter the code and compile it.**  
**Key Implementation Details:**  
- **Scanner:** Used for CLI input.  
- **JOptionPane:** Powers GUI dialogs.  
- **Random Numbers:** `Math.random()` for quiz questions.  
- **String Formatting:** `printf()` for aligned output.  

**Compilation:**  
- No syntax errors due to proper Java conventions (e.g., braces, semicolons).  
- Imports (`java.util.Scanner`, `javax.swing.*`) included.  

---

#### **6. Correct any errors found during compilation.**  
**Fixed Issues:**  
- **Unclosed Scanner:** Added `input.close()` in `main()`.  
- **Resource Leaks:** GUI methods check for `null` input.  
- **Type Safety:** Used `Integer.parseInt()` with exception handling.  

---

#### **7. Run the program with test data for input.**  
**Test Cases:**  
| Feature          | Input                  | Expected Output                     |  
|------------------|------------------------|-------------------------------------|  
| Basic Calculator | 5, 2                   | 5 + 2 = 7, 5 / 2 = 2.50             |  
| Tax Calculator   | Price = $100           | Tax = $8.00, Total = $108.00        |  
| Math Quiz        | "3 * 5" → 15           | "Correct! 🎉"                      |  
| Unit Converter   | 10 miles → kilometers  | "16.09 km"                         |  

---

#### **8. Correct any runtime errors found while running the program.**  
**Issues Identified:**  
1. **Input Mismatch (CLI):** Entering text for `nextInt()` crashes.  
   - **Fix:** Add `try-catch` for `InputMismatchException`.  
2. **GUI Cancel Button:** Exits abruptly.  
   - **Fix:** Check for `null` in `quizGUI()`.  

---

#### **9. Validate the results of the program.**  
**Success Criteria:**  
- All features produce correct outputs for valid inputs.  
- CLI and GUI versions are consistent.  
- Handles errors gracefully (e.g., division by zero, invalid numbers).  

**Areas for Improvement:**  
- **Input Validation:** Add loops to retry invalid inputs (CLI).  
- **Enhanced GUI:** Use `JFrame` for a more polished interface.  

---
