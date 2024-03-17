# Managing_Financial_Data_Project1_C

![image](https://github.com/Alle43221/Managing_Financial_Data_Project2_C/assets/79206599/f2832776-b148-46a5-a007-b8d1f0897989)


## Warning! 
There may be errors on loading the information from files. These are because of the different aproach the systems Windows and Unix have on entering the newline character (Windows inserts the invisible character CR defore newline). That's why if such problems are encountered, the files can be first open with a generic text editor like Notepad++ and saved in a different encoding, correspoding to the system that will host the files.

## Overview
A console C application to simulate the management of financial data in the form of transactions.\
Author: Moroz Alexandra-Ioana, UBB informatica romana\
[Presentation video](https://ubbcluj-my.sharepoint.com/:v:/g/personal/alexandra_moroz_stud_ubbcluj_ro/EQrHprpL2hNGkVHVDDmraggBG20VwL6dqqzolMavg9al9w?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=rp2qTE)

## Features
An  accounting project for managing financial and accounting data, performing financial calculations, generating reports, and ensuring data security.
1. **User Interface**: a command-line program
2. **Account Management**: users can create, edit, and delete financial accounts, such as savings accounts, checking accounts and credit accounts
3. **Transaction Recording**: deposits, withdrawals and transfers
4. **Balance Calculation**: automatically calculates account balances based on recorded transactions
5. **Financial Reporting**: options for generating financial reports, such as account statements, balances, transaction registers and expense reports
6. **Security and Authentication**: financial data is protected, and users must authenticate to access the accounting system
7. **Customer Data Management**: users can input and manage information about customers or entities with whom they do business (name, iban, phone number, email)
8. **Data Export and Import**: exporting financial reports in .CSV file format and across the project data is stored in .CSV format for portability
9. **Input Data Validation**: checks on user-entered data to prevent errors or incorrect data
10. **Error and Exception Handling**: system for proper error handling and handling exceptional situations that may arise during the accounting process (invalid/non-existing accounts/customers/users etc.)
11. **Audit and Logging**: an activity log to provide audit capabilities to track changes and activities related to accounts (independent for each user in a .TXT file)
12. **Documentation and Comments**: code with comments to make it easier to understand and Documentation (PDF)
    
## Menu
1. Add customer                           
2. Delete customer                        
3. Modify customer                        
4. Print all customers                    
---------------------------------------------
5. Create account                         
6. Delete account                         
7. Print all accounts                     
8. Check account balance                  
---------------------------------------------
9. Save deposit                           
10. Save withdrawal                       
11. Save transaction                      
---------------------------------------------
12. Generate account statement            
13. Generate transaction register     
14. Generate expense report             
---------------------------------------------
15. Log out                               

## Admin options:                            
16. Add client
17. Delete client
18. Reset password                           
