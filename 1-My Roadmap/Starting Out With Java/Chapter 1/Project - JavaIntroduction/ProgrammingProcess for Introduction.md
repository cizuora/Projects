### **My Programming Process** for the `Introduction.java` Program

1. **Clearly define what the program is to do.**  
   - The program collects personal information (name, age, dream job, favorite food, hobbies) from the user and displays it in a formatted introduction.  
   - It allows multiple introductions to be created in a single session.  
   - The goal is to practice Java input/output, loops, and basic logic (like age-based messages).

2. **Visualize the program running on the computer.**  
   - The program starts with a welcome message in a bordered box.  
   - The user is prompted to enter their details one by one.  
   - Hobbies are collected in a loop until the user types "done."  
   - The introduction is displayed in a structured format with conditional text (e.g., "Young and energetic!" for ages under 18).  
   - The user can choose to create another introduction or exit.

3. **Use design tools to create a model of the program.**  
   - **Pseudocode Example:**  
     ```
     Display welcome box  
     Loop while running:  
         Ask for name, age, job, food  
         Loop to collect hobbies until "done"  
         Display introduction with formatted output  
         Ask if user wants to continue  
     Display goodbye message  
     ```  
   - **Structure:**  
     - Main loop for multiple introductions.  
     - Helper method (`printBox`) for bordered text.  
     - `ArrayList` for dynamic hobby storage.  

4. **Check the model for logical errors.**  
   - Does the loop properly handle multiple introductions? **Yes.**  
   - Does the age condition (`age < 18`) work as intended? **Yes.**  
   - Does the hobby collection stop at "done"? **Yes.**  
   - Is the buffer cleared after `nextInt()`? **Yes (via `scanner.nextLine()`).**  

5. **Enter the code and compile it.**  
   - The Java code was written with proper syntax (e.g., `Scanner` for input, `ArrayList` for hobbies).  
   - The `printBox` method modularizes border formatting.  

6. **Correct any errors found during compilation.**  
   - Potential errors might include:  
     - Missing imports (`java.util.Scanner`, `java.util.ArrayList`).  
     - Unclosed `Scanner` (fixed with `scanner.close()`).  
     - Type mismatches (e.g., `nextInt()` vs. `nextLine()`).  

7. **Run the program with test data for input.**  
   - **Test Case 1:**  
     - Input: Name = "Alice", Age = 17, Job = "Doctor", Food = "Pizza", Hobbies = "Reading, Swimming".  
     - Expected Output: Introduction with "Young and energetic!"  
   - **Test Case 2:**  
     - Input: Name = "Bob", Age = 30, Job = "Engineer", Food = "Sushi", Hobbies = "Gaming, Hiking".  
     - Expected Output: Introduction with "Wise and experienced!"  

8. **Correct any runtime errors found while running the program.**  
   - Issue: If the user enters non-integer input for age, the program crashes.  
     - **Fix:** Add input validation (e.g., `try-catch` for `nextInt()`).  
   - Issue: Hobbies loop might not handle empty input gracefully.  
     - **Fix:** Add a check for empty strings before adding to the list.  

9. **Validate the results of the program.**  
   - The output matches expectations for all test cases.  
   - The program handles multiple introductions and exits cleanly.  
   - Edge cases (e.g., no hobbies, invalid age input) could be improved but are functional.  
