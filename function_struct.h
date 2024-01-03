#ifndef FUCNTION_H
#define FUCNTION_H

void main_interface(); //Done
void login_interface(); //Done

void admin_interface(); //Done
void add_new_staff(); //Done
int  StaffID_generator();//Done
void update_leave_balance();//Done
void search_staff_leave_info(); //Done
void generate_report();//Done

void staff_interface(char *staffID, char *staffName,char *dept);  // Done
void Apply_leave(char *staffID,char *staffName,char *dept); // Done
int Check_Current_Time (char *Start_Date);//Done
int  day_calculation(char *start_date, char *end_date);//Done
int  Check_Date_Overlap(char *start_date, char *end_date,char *staffID, char *staffName, char *dept);//Done
int  LeaveID_generator(); //Done
void Cancel_leave(char *staffID,char *staffName,char *dept);//Done
void Check_Leave_Status(char *staffID,char *staffName,char *dept); // Done
void Summary_of_Leave_Information(char *staffID,char *staffName, char *dept); //Done
void Check_User_Information(char *staffID,char *staffName, char *dept); // Done

void LeaveApprover_interface(char *staffID,char *staffName,char *dept); //Done
void Approve_Leave(char *staffID,char *staffName,char *dept);//Done
void Search_Date_Leave(char *staffID,char *staffName,char *dept); //Done

struct Leave{
    int Annual_leave;
    int Medical_leave;
    int Emergency_leave;
    int Compassionate_leave;
    int Personal_leave;
};

struct Staff{
    char ID[100];
    char name[100];
    char dept[100];
    char role[100];
    char username[100];
    char password[100];
};

struct Leave_Detail{
    char LeaveID[20];
    char LeaveType[20];
    char Start_Date[100];
    char End_Date[100];
    int  Day_Number;
    char LeaveStatus[100];
};



#endif