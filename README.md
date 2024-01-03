# Introduction to C Programming
- Developed a non-GUI leave management system in C with key features for Superior, Admin, and Staff users.
- Applied local time in and relevant validation in the system.
- Gained experience with C pointer, which improved understanding of data structures and memory.
- Design a more clear and tidy display in the system.
- Enhanced programming skills and system architecture knowledge.

---

# Role

## Admin
1. add new staff’s information (including his leave details) to the system
2. update the leave balance (annual leave, compassionate leave, emergency leave, maternity leave, medical leave, etc.) of staff for every new year or when it is necessary
3. search for any staff’s leave information using staff ID or name
4. generate monthly report (text file) for the leave statistics of each department or school

## Staff
1. Apply leave
2. Cancel leave (approved or pending status, cannot cancel if the on-leave date has passed)
3. Check the leave status
4. Check the summary of leave information

## Leave Approver
1. Approve or reject leave application(s)
2. Can search a date and view the number of staff who applied leave on the specified date (this could provide more information on the approval of leave)

---

# Additional Feature

1. StaffID Generator
   - Auto Generate a new unique StaffID (Primary Key) when add a new staff
2. Check Date Overlap
   - Check the valid date to apply leave
3. Day Calculation
   - Auto Calculate the Day Number based on the start day and end day 
4. LeaveID Generator
   - Auto Generate a new unique StaffID (Primary Key) when add a new staff
5. Check Current Time
   - A feature used to check the current time
   - If the leave date already passed, then not display it
