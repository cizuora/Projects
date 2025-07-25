### **Programming Process for `BankingAssistant.java`**

---

#### **1. Clearly define what the program is to do.**  
**Purpose:**  
A banking assistant program that provides:  
- **Account Management:** Supports Savings, Checking, and Student accounts.  
- **Balance Evaluation:** Classifies balances as OVERDRAWN, LOW, MEDIUM, or HIGH.  
- **Loan Eligibility:** Determines if a user qualifies for a loan based on balance and account type.  
- **Transaction Processing:** Simulates random transactions (-$100 to +$100).  
- **Multi-Mode Interface:** Offers both console and GUI versions.  

**Problem Solved:**  
Helps users understand their account status, fees, and loan eligibility in an intuitive way.

---

#### **2. Visualize the program running on the computer.**  
**Console Flow:**  
1. User selects account type (Savings/Checking/Student).  
2. Enters current balance.  
3. Program evaluates balance status, calculates interest/fees, and simulates a transaction.  
4. Displays a receipt with all details.  

**GUI Flow:**  
1. Pop-up dialog for account selection.  
2. Input field for balance.  
3. Results shown in a formatted message box.  

---

#### **3. Use design tools to create a model of the program.**  
**Structure:**  
- **Main Menu:**  
  ```java
  if (mode == 1) consoleVersion();
  else if (mode == 2) guiVersion();
  ```  
- **Account Logic:**  
  ```java
  switch(accountType) {
      case 1: // Savings
      case 2: // Checking
      case 3: // Student
  }
  ```  
- **Loan Eligibility:**  
  ```java
  boolean loanEligible = (balance >= LOAN_THRESHOLD) && 
                        (accountType != 3) && 
                        (!balanceStatus.equals("OVERDRAWN"));
  ```  

**Pseudocode for Transaction:**  
```plaintext
transaction = random(-100, 100)
newBalance = balance + transaction
if (newBalance < 0) → "ALERT: Overdrawn!"
```

---

#### **4. Check the model for logical errors.**  
**Potential Issues:**  
- **Negative Balances:** Handled with `OVERDRAWN` status.  
- **Student Accounts:** Ineligible for loans (correctly excluded).  
- **Random Transactions:** Range (-100 to +100) ensures realistic values.  

**Validation:**  
- All account types tested with edge cases (e.g., $0, -$50, $10,000).  
- Loan eligibility logic verified.  

---

#### **5. Enter the code and compile it.**  
**Key Implementation Details:**  
- **Constants:** `SAVINGS_RATE`, `CHECKING_FEE` for easy maintenance.  
- **Random Class:** Generates realistic transactions.  
- **String Formatting:** `printf` and `StringBuilder` for clean output.  
- **GUI Components:** `JOptionPane` for dialogs.  

**Compilation:**  
- No syntax errors due to proper Java conventions.  
- Imports (`java.util.*`, `javax.swing.*`) included.  

---

#### **6. Correct any errors found during compilation.**  
**Fixed Issues:**  
- **Input Handling:** Added `input.nextLine()` to consume newlines.  
- **GUI Null Checks:** Verified input cancellation doesn’t crash.  
- **Number Parsing:** Used `try-catch` for `Double.parseDouble()`.  

---

#### **7. Run the program with test data for input.**  
**Test Cases:**  
| Feature          | Input (Account/Balance) | Expected Output                     |  
|------------------|-------------------------|-------------------------------------|  
| Savings          | $1500                   | HIGH status, 3% interest            |  
| Checking         | -$20                    | OVERDRAWN, $10 fee, no loan         |  
| Student          | $6000                   | HIGH status, 4.5% interest, no loan |  
| Random Transaction| Balance = $200 → +$75   | "Bonus: Large deposit!"             |  

---

#### **8. Correct any runtime errors found while running the program.**  
**Issues Identified:**  
1. **Invalid Balance Input (GUI):** Non-numeric input crashes.  
   - **Fix:** Added `try-catch` for `NumberFormatException`.  
2. **Transaction Logic:** Negative balances trigger alerts correctly.  
   - **Verified:** Edge cases handled as expected.  

---

#### **9. Validate the results of the program.**  
**Success Criteria:**  
- Correct account-specific logic (e.g., fees for Checking, bonus interest for Student).  
- Loan eligibility matches business rules.  
- GUI and console outputs are consistent.  

**Areas for Improvement:**  
- **Enhanced GUI:** Add input validation loops.  
- **More Features:** Deposit/withdrawal history, PIN authentication.  

--- 

**Key Strengths:**  
✔ Clean separation of console/GUI logic  
✔ Realistic transaction simulation  
✔ Comprehensive receipt formatting  
✔ Defensive programming (input validation)  

**Example Output (Console):**  
```
=== BANKING RECEIPT ===  
Account Type: Savings  
Current Balance: $1,500.00  
Balance Status: HIGH  
Interest Rate: 3.0%  

Transaction Amount: +$75.00  
New Balance: $1,575.00  

Loan Eligible: YES  
Bonus: Large deposit received!  
```