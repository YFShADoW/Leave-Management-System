// System admin
// Username:admin
// Password:1234

// called the C library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "function_struct.h"

//main function
int main(){
    // Clear the terminal.
    system("cls");
    // Called main_interface.
    main_interface();
    return 0;
}

//==========================================================================================================================================

void main_interface(){
    // Declaration
    int option;
    //Display welcome message
    printf("\n____________________ Welcome to APU leave management system !!!____________________\n\n\n");
    //Display selection
    printf("1. School of Computing, Technology and Game Development\n"
           "2. School of Engineering\n"
           "3. School of Business, Management, Marketing and Tourism\n"
           "4. School of Accounting, Banking, Finance & Actuarial\n"
           "5. School of Media, International Relations & Psychology\n"
           "6. School of Design, Advertising & Animation\n"
           "7. Exit\n");
    // Get input repeatly if the user enter invalid number
    do{
        int check;
        //Ask the user option
        printf("\nPlease select which school are you depand on : ");
        check = scanf("%d",&option);
        //validation for not number input
        if (check !=1 ){
            printf("Invalid input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        // In this assignment, I only done the "School of Computing"
        if (option==1||option==2||option==3||option==4||option==5||option==6){
            // Clear the terminal.
            system("cls");
            printf("____________________ Welcome to School of Computing !!!____________________\n\n");
            login_interface();
        }
        // If the user enter the 'exit' option, exit the program
        else if (option == 7){
            // Clear the terminal.
            system("cls");
            printf("\n____________________ Thank You !!!____________________\n");
            exit(0);
        }
        else{
            printf("Please Enter Correct Number\n");
            continue;
        }
    }
    while (!(option>=1 && option<=7));
}

void login_interface(){
    // Declaration
    struct Staff Login;
    struct Staff checker;
    char staffID[100],staffName[100],dept[100];

    FILE *fp;
    int check = 0;

    //Clear the 'stdin' space
    fflush(stdin);

    // Get user input
    printf("\nPlease Enter Your Username and Password\n");
    printf("Username : ");
    fgets(Login.username,100,stdin);
    // Let the last character of string be a NULL
    Login.username[strlen(Login.username)-1]='\0';

    // Get user input
    printf("Password : ");
    fgets(Login.password,100,stdin);
    // Let the last character of string be a NULL
    Login.password[strlen(Login.password)-1]='\0';

    // In this system, only one admin with the username and password.
    if (strcmp(Login.username,"admin")==0 && strcmp(Login.password,"1234")==0){
        check=-1;
        
    }

    else{
        // Open file
        fp=fopen("staff.txt","r");
        // Check file exist
        if (fp == NULL){
            printf("Error opening file\n");
            exit(0);
        }

        // Check the username and password
        while(fscanf(fp, "%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^\n]\n",
        checker.ID,checker.name,checker.dept,checker.role,checker.username,checker.password)!= EOF){
            if ((strcmp(Login.username,checker.username) == 0) && (strcmp(Login.password,checker.password) == 0)){
                // If the role is Staff, copy the staff id ,name ,department and save them.
                // make 'check'=1 --> staff_interace
                if (strcmp(checker.role,"Staff")==0){
                    check=1;
                    strcpy(staffID,checker.ID);
                    strcpy(staffName,checker.name);
                    strcpy(dept,checker.dept);
                    break;
                }
                // If the role is Superior, copy the staff id ,name ,department and save them.
                // make 'check'=2 -->Leave_Approver_interface
                else if(strcmp(checker.role,"Superior")==0){
                    strcpy(staffID,checker.ID);
                    strcpy(staffName,checker.name);
                    strcpy(dept,checker.dept);
                    check=2;
                    break;
                }
            }
        }
        // Close file
        fclose(fp);
    }

    // Call the user interface
    if (check==1){
        // Clear the terminal.
        system("cls");
        // Display Login Status Message.
        printf("\n____________________ Login Successful !!____________________\n\n");
        staff_interface(staffID,staffName,dept);
    }
    else if (check==2){
        // Clear the terminal.
        system("cls");
        // Display Login Status Message.
        printf("\n____________________ Login Successful !!____________________\n");
        LeaveApprover_interface(staffID,staffName,dept);
    }   
    else if(check==-1){
        // Clear the terminal.
        system("cls");
        // Display Login Status Message.
        printf("\n____________________ Login Successful !!____________________\n");
        admin_interface();
    }
    else{
        // Clear the terminal.
        system("cls");
        // Display Login Status Message.
        printf("\n____________________ Login Failed !!____________________\n");
        main_interface();
    }
}

//=================================================================================================================================
void admin_interface(){
    int option;
    // Display Welcome Message.
    printf("\n____________________ Welcome ADMIN !! ____________________\n");
    // Display Selection
    printf("1. Add New Staff Information.\n"
           "2. Update Leave Balance.\n"
           "3. Search Staff Leave Information.\n"
           "4. Generate monthly report.\n"
           "5. Exit.\n");
    printf("Enter the number from 1 to 5 : ");
    // Get input repeatly if the user enter invalid number
    do{
        int check;
        // Get input and Validation
        check = scanf("%d",&option);
        //validation for not number input
        if (check !=1 ){
            printf("Invalid input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        // According the selection from user, assigned to the different case.
        switch (option){
            case 1:
            // Clear the terminal.
            system("cls");
            add_new_staff();
            break;

            case 2:
            // Clear the terminal.
            system("cls");
            update_leave_balance();
            break;

            case 3:
            // Clear the terminal.
            system("cls");
            search_staff_leave_info();
            break;

            case 4:
            // Clear the terminal.
            system("cls");
            generate_report();
            break;

            // If the user enter the 'exit' option, exit the program
            case 5:
            // Clear the terminal.
            system("cls");
            main_interface();
            break;

            // if above case not relevent, run default
            default:
            printf("\nPlease enter the correct Number\n");
            continue;
        }
    }
    while (!(option==1||option==2||option==3||option==4||option==5||option==6));
}

void add_new_staff(){
    // Declaration
    char str[100],line[200];
    int check,option;
    FILE *staff_file;
    struct Staff Add_Staff,Checker;
    struct Leave Add_Leave;

    // Display function name
    printf("\n____________________ Add New Staff Information !!!____________________\n");
    printf("\nPlease Enter the Staff Information\n");

    //Clear the 'stdin' space
    fflush(stdin);
    printf("\n==========================================================================================\n");
    // Display Selection
    printf("\nPlease Select the Department.\n");
    printf("1.Technical\n");
    printf("2.Management\n");
    printf("3.Academic\n");
    printf("4.Administration\n");
    printf("5.Exit\n");
    // Get input repeatly if the user enter invalid number
    do{
        printf("Your Choice : ");
        int check = scanf("%d",&option);
        //validation for not number input
        if (check !=1 ){
            printf("Invalid input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        // According the selection from user, assigned to the different case.
        switch (option){
            case 1:
            strcpy(Add_Staff.dept,"Technical");
            break;

            case 2:
            strcpy(Add_Staff.dept,"Management");
            break;

            case 3:
            strcpy(Add_Staff.dept,"Academic");
            break;

            case 4:
            strcpy(Add_Staff.dept,"Administration");
            break;

            // If the user enter the 'exit' option, exit the program
            case 5:
            // Clear the terminal.
            system("cls");
            admin_interface();
            exit(0);

            // if above case not relevent,run default
            default:
            printf("Please enter the correct number!\n");
            continue;

        }
    }while(!(option==1 || option==2 ||option==3 ||option==4));

    // Display selection
    printf("\nPlease Select the Role.\n");
    printf("1.Superior\n");
    printf("2.Staff\n");
    // Get input repeatly if the user enter invalid number
    do{
        printf("Your Choice : ");
        int check = scanf("%d",&option);
        //validation for not number input
        if (check !=1 ){
            printf("Invalid input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        // According the selection from user, assigned to the different case.
        switch (option){
            case 1:
            strcpy(Add_Staff.role,"Superior");
            break;

            case 2:
            strcpy(Add_Staff.role,"Staff");
            break;

            // if above case not relevent, run default
            default:
            printf("Please enter the correct number!\n");
            continue;

        }
    }while(!(option==1 || option==2));


    printf("\n==========================================================================================\n");
    // Use the StaffID_generator to create a new StaffID
    // Use sprintf to convert the 'S' and new PK no to a string.
    sprintf(Add_Staff.ID,"S%03d",StaffID_generator());
    printf("StaffID             : %s\n",Add_Staff.ID);

    //Clear the 'stdin' space
    fflush(stdin);
    printf("Name                : ");
    // Get user input
    fgets(str,100,stdin);
    str[strlen(str)-1]='\0';
    strcpy(Add_Staff.name,str);

    printf("Department          : %s\n",Add_Staff.dept);
    printf("Role                : %s\n",Add_Staff.role);
    
    while (1){
        int flag=0;
        printf("Username            : ");
        // Get user input
        fgets(str,100,stdin);
        str[strlen(str)-1]='\0';
        strcpy(Add_Staff.username,str);

        // Open file
        staff_file=fopen("staff.txt","r");
        if (staff_file == NULL){
            printf("Error opening file\n");
            exit(0);
        }
        // Loop through each line of the input file
        while (fgets(line,sizeof(line),staff_file)){
            sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^\n]",
            Checker.ID,Checker.name,Checker.dept,Checker.role,Checker.username,Checker.password);
            // if the username is existing in the file, display the message.
            if (strcmp(Checker.username,Add_Staff.username)==0){
                printf("\n__________ This username has been used.__________ \n");
                flag=1;
                break;
            }
        }
        if (flag){
            continue;
        }
        else{
            break;
        }
    }

    printf("Password            : ");
    // Get user input
    fgets(str,100,stdin);
    str[strlen(str)-1]='\0';
    strcpy(Add_Staff.password,str);


    printf("\n==========================================================================================\n");

    while (1){
        int count;
        printf("Annual Leave        : ");
        count=scanf("%d",&Add_Leave.Annual_leave);
        if (count!=1){
            printf("Invalid Input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        else{
            break;
        }
    }
    while (1){
        int count;
        printf("Medical Leave       : ");
        count=scanf("%d",&Add_Leave.Medical_leave);
        if (count!=1){
            printf("Invalid Input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        else{
            break;
        }
    }

    while(1){
        int count;
        printf("Emergency Leave     : ");
        count=scanf("%d",&Add_Leave.Emergency_leave);
        if (count!=1){
            printf("Invalid Input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        else{
            break;
        }
    }

    while(1){
        int count;
        printf("Compassionate Leave : ");
        count=scanf("%d",&Add_Leave.Compassionate_leave);
        if (count!=1){
            printf("Invalid Input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        else{
            break;
        }
    }
    
    while (1){
        int count;
        printf("Personal Leave      : ");
        count=scanf("%d",&Add_Leave.Personal_leave);
        if (count!=1){
            printf("Invalid Input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        else{
            break;
        }
    }

    printf("\n==========================================================================================\n");
    printf("\nPlease Check Again the information.\n");
    printf("Is All the Information is correct?\n1.Yes\n2.No\n");
    // Get input repeatly if the user enter invalid number
    do{
        printf("Please Enter Your Choice : ");
        check = scanf("%d",&option);
        //validation for not number input
        if (check !=1 ){
            printf("Invalid input\n");
            scanf("%*s");
            continue;
        }
        if (option == 1){
            // Open file
            FILE *fptr1,*fptr2;
            fptr1 = fopen("staff.txt","a");
            fptr2 = fopen("leave.txt","a");
            if (fptr1 == NULL ||fptr2 == NULL){
                printf("Error opening file\n");
                exit;
            }
            // Write File
            fprintf(fptr1,"%s||%s||%s||%s||%s||%s\n",
            Add_Staff.ID,Add_Staff.name,Add_Staff.dept,Add_Staff.role,Add_Staff.username,Add_Staff.password);
            fprintf(fptr2,"%s||%s||%s||%d||%d||%d||%d||%d\n",
            Add_Staff.ID,Add_Staff.name,Add_Staff.dept,Add_Leave.Annual_leave, Add_Leave.Medical_leave, Add_Leave.Emergency_leave, 
            Add_Leave.Compassionate_leave, Add_Leave.Personal_leave);
            // Close File
            fclose(fptr1);
            fclose(fptr2);

            // Display Status message.
            printf("\n__________ Information is Successfully Recorded.__________\n");
            admin_interface();
        }
        else if(option == 2){
            // Display Status message.
            printf("\n__________ Please Enter the Information Again !__________\n");
            admin_interface();
        }
        else{
            // Display Status message.
            printf("\n__________ Please give the correct option!__________\n");
        }
    } while (!(option==1||option==2));

}

int StaffID_generator(){
    // declaration
    char line[200];
    char last_PK[20],new_PK[20];
    int count=0;

    // Open file
    FILE *file = fopen("staff.txt", "r");
    if (file==NULL){
        printf("Error file\n");
        exit(0);
    }
    // Let the file pointer run until the last line.
    while(fgets(line,sizeof(line),file)!=NULL){
    }
    // Get the lastest PK in the line(string)
    strncpy(last_PK,&line[1],3);
    // Add a NULL at the end of string.
    last_PK[3]='\0';
    //Close file
    fclose(file);
    // Convert the last_PK(string) into integar and save into count
    sscanf(last_PK,"%03d",&count);
    // "last_PK" + 1 to be the new PK.
    count+=1;
    return count; //return the new PK number.
}

void update_leave_balance(){
    // Declaration
    FILE *fptr1,*fptr2;
    struct Staff staff,Check;
    struct Leave leave,Update;
    char line[200],str[100],new_line[200];
    int option,flag=0;
    char dept[100],staffID[100],staffname[100];

    printf("\n____________________ Update Leave Balance !!!____________________\n");
    printf("Please select a department.\n");
    printf("1.Techincal\n");
    printf("2.Management\n");
    printf("3.Academic\n");
    printf("4.Administration\n");
    printf("5.Exit\n");
    // Get input repeatly if the user enter invalid number
    do{
        printf("Your Choice : ");
        int check = scanf("%d",&option);
        //validation for not number input
        if (check !=1 ){
            printf("Invalid input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        // According the selection from user, assigned to the different case.
        switch (option){
            case 1:
            strcpy(dept,"Technical");
            break;

            case 2:
            strcpy(dept,"Management");
            break;

            case 3:
            strcpy(dept,"Academic");
            break;

            case 4:
            strcpy(dept,"Administration");
            break;

            // If the user enter the 'exit' option, exit the program
            case 5:
            // Clear the terminal.
            system("cls");
            admin_interface();
            exit(0);

            // if above case not relevent, run default
            default:
            printf("Please enter the correct number!\n");
            continue;

        }
    }while(!(option==1 || option==2 ||option==3 ||option==4));
    printf("\n==========================================================================================\n");
    // Open file
    fptr1=fopen("leave.txt","r");
    
    // Display the attributes of the table
    printf("\n_Staff ID_|_____________Name_____________|____Annual  Leave____|____Medical Leave____|___Emergency Leave___|_Compassionate Leave_|___Personal  Leave___\n");
    if (fptr1==NULL){
        printf("File Not Found.\n");
        exit(0);
    }
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr1)!=NULL){
        sscanf(line,"%[^||]||%[^||]||%[^||]||%d||%d||%d||%d||%d",staff.ID,staff.name,staff.dept,
        &leave.Annual_leave,&leave.Medical_leave,&leave.Emergency_leave,&leave.Compassionate_leave,&leave.Personal_leave);
        // If the staff department == department seleted
        if (strcmp(staff.dept,dept)==0){
            // Display the leave detail.
            printf("%-10s|%-30s|%-21d|%-21d|%-21d|%-21d|%-21d\n",
            staff.ID,staff.name,leave.Annual_leave,leave.Medical_leave,leave.Emergency_leave,leave.Compassionate_leave,leave.Personal_leave);
        }
    }
    // Close file
    fclose(fptr1);
    printf("\n==========================================================================================\n");
    printf("Please enter the StaffID to select.\n");
    printf("Enter \"exit\" to quit.\n");
    while(1){
        //Clear the 'stdin' space
        fflush(stdin);
        // declaration
        char PK[20];
        int check,PK_Num;

        printf("Staff ID : ");
        // Get user input
        fgets(str,100,stdin);
        str[strlen(str)-1]='\0';
        // copy the input into Check.ID
        strcpy(Check.ID,str);
        strncpy(PK,&Check.ID[1],4);

        // If 'exit' is inputed , exit this process.
        if (strcmp(Check.ID,"exit")==0){
            admin_interface();
            exit(0);
        }
        // Valiadtion of the Input "Staff ID" Format :S001
        if (Check.ID[0]!='S'){
            printf("Wrong Prefix Format!\n");
            continue;
        }
        else if (check = sscanf(PK,"%03d",&PK_Num)!=1){
            printf("Wrong Number Format!\n");
            continue;
        }
        else if (strlen(Check.ID)!=4){
            printf("Wrong Format!\n");
            continue;
        }
        else{
            break;
        }
    }
    printf("\n==========================================================================================\n");
    // Open file
    fptr1=fopen("leave.txt","r");
    
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr1)!=NULL){
        sscanf(line,"%[^||]||%[^||]||%[^||]||%d||%d||%d||%d||%d",staff.ID,staff.name,staff.dept,
        &leave.Annual_leave,&leave.Medical_leave,&leave.Emergency_leave,&leave.Compassionate_leave,&leave.Personal_leave);
        // Check if the staffID and department from the file line by line.
        // If true , set flag =1 and break the loops
        if (strcmp(staff.ID,Check.ID)==0 && strcmp(staff.dept,dept)==0){
            flag=1;
            break;
        }
    }
    // if staffid not found , the flag = 0 ,run this.
    if (flag==0){
        printf("\nStaff Not Exist!\n");
        admin_interface();
        exit(0);
    }
    // Close file
    fclose(fptr1);
    printf("Staff ID    : %s\n",staff.ID);
    printf("Staff Name  : %s\n",staff.name);
    printf("Department  : %s\n",staff.dept);
    printf("\n======Please enter the new leave balance======\n");

    // Get the admin input , to change each leave balance.
    // Each input will be valided to ensure the input must be a number.
    while (1){
        int count;
        printf("Annual Leave        : ");
        count=scanf("%d",&Update.Annual_leave);
        if (count!=1){
            printf("Invalid Input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        else{
            break;
        }
    }
    while (1){
        int count;
        printf("Medical Leave       : ");
        count=scanf("%d",&Update.Medical_leave);
        if (count!=1){
            printf("Invalid Input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        else{
            break;
        }
    }

    while(1){
        int count;
        printf("Emergency Leave     : ");
        count=scanf("%d",&Update.Emergency_leave);
        if (count!=1){
            printf("Invalid Input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        else{
            break;
        }
    }

    while(1){
        int count;
        printf("Compassionate Leave : ");
        count=scanf("%d",&Update.Compassionate_leave);
        if (count!=1){
            printf("Invalid Input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        else{
            break;
        }
    }
    
    while (1){
        int count;
        printf("Personal Leave      : ");
        count=scanf("%d",&Update.Personal_leave);
        if (count!=1){
            printf("Invalid Input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        else{
            break;
        }
    }
    printf("\n==========================================================================================\n");
    // Display the attributes of the table
    printf("\n_Staff ID_|_____________Name_____________|____Annual  Leave____|____Medical Leave____|___Emergency Leave___|_Compassionate Leave_|___Personal  Leave___\n");
    printf("%-10s|%-30s|%-21d|%-21d|%-21d|%-21d|%-21d\n",
    staff.ID,staff.name,Update.Annual_leave,Update.Medical_leave,Update.Emergency_leave,Update.Compassionate_leave,Update.Personal_leave);
    printf("\nPlease Check Again the information.\n");
    printf("Is All the Information is correct?\n1.Yes\n2.No\n");
    // Get input repeatly if the user enter invalid number
    do{
        printf("Please Enter Your Choice : ");
        int check = scanf("%d",&option);
        //validation for not number input
        if (check !=1 ){
            printf("Invalid input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        // According the selection from user, assigned to the different case.
        switch (option){
            case 1:
            // Replace the new data into new line, and creates as a new string.
            sprintf(new_line,"%s||%s||%s||%d||%d||%d||%d||%d\n",staff.ID,staff.name,staff.dept,
            Update.Annual_leave,Update.Medical_leave,Update.Emergency_leave,Update.Compassionate_leave,Update.Personal_leave);
            
            // Open file
            fptr1 = fopen("leave.txt","r");
            fptr2 = fopen("temp.txt","w");
            if (fptr1 == NULL || fptr2 == NULL){
                printf("Unable to open the file.\n");
                exit(0);
            }
            // Loop through each line of the input file
            while (fgets(line, 200, fptr1) != NULL) {
            // Check if the line contains the data to be replace
                if (strstr(line,Check.ID) != NULL) { // substr in str !=NULL
                    // Write the newline to the temporary file 
                    fputs(new_line, fptr2);
                }
                else{
                    // Write the other line into the temporary file.
                    fputs(line,fptr2);
                }
            }
            // Close file
            fclose(fptr1);
            fclose(fptr2);

            remove("leave.txt");
            rename("temp.txt","leave.txt");
            printf("\n___________Updated Successful !__________\n");
            // Back to admin interface.
            admin_interface();
            break;
            
            case 2:
            printf("\nThank you ! Please updated again !\n");
            // back to admin interface
            admin_interface();
            exit(0);
            break;

            // if above case not relevent, run default
            default:
            printf("\n Please enter the correct option ! \n");
            continue;
        }
    }while(!(option==1||option==2));
    
}

void search_staff_leave_info(){
    // Clear the stdin
    fflush(stdin);
    // Declaration
    char str[100];
    int flag=0;
    struct Staff checker;
    struct Leave leave;
    FILE *fptr1,*fptr2;

    // Open file
    fptr1=fopen("staff.txt","r");
    fptr2=fopen("leave.txt","r");
    if (fptr1==NULL){
        printf("File does not exists");
        exit(0);
    }
    if (fptr2==NULL){
        printf("File does not exists");
        exit(0);
    }

    // Display
    printf("\n____________________ Search Staff Information ____________________\n");
    printf("\nPlease enter the Name or the ID that you want to search\n");
    printf("Enter \"exit\" to quit.\n");
    printf("Your Answer: ");
    fgets(str,100,stdin);
    str[strlen(str)-1]='\0';

    // If 'exit' is inputed , exit this process.
    if (strcmp(str,"exit")==0){
        admin_interface();
        exit(0);
    }
    // read the file line by line until the end of file.
    while(fscanf(fptr1, "%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^\n]\n",
        checker.ID,checker.name,checker.dept,checker.role,checker.username,checker.password)!=EOF){
        // Display staff info if name or ID matches user input
        if (strcmp(checker.ID,str)==0 || strcmp(checker.name,str)==0){
            printf("\n");
            printf("==========Staff Info===========\n");
            printf("ID         : %s\n",checker.ID);
            printf("Name       : %s\n",checker.name);
            printf("Department : %s\n",checker.dept);
            printf("Role       : %s\n",checker.role);
            printf("Username   : %s\n",checker.username);
            printf("Password   : %s\n",checker.password);
            flag=1;
        }
    }
    // Close file
    fclose(fptr1);
    // read the file line by line until the end of file.
    while(fscanf(fptr2, "%[^||]||%[^||]||%[^||]||%d||%d||%d||%d||%d\n",checker.ID,checker.name,checker.dept,
        &leave.Annual_leave,&leave.Medical_leave,&leave.Emergency_leave,&leave.Compassionate_leave,&leave.Personal_leave)!=EOF){
        // print leave info if name or ID matches user input
        if (strcmp(checker.ID,str)==0 || strcmp(checker.name,str)==0){
            printf("\n");
            printf("==========Leave Info===========\n");
            printf("Annual Leave        : %d\n",leave.Annual_leave);
            printf("Medical Leave       : %d\n",leave.Medical_leave);
            printf("Emergency Leave     : %d\n",leave.Emergency_leave);
            printf("Compassionate Leave : %d\n",leave.Compassionate_leave);
            printf("Personal Leave      : %d\n",leave.Personal_leave);
            flag=1;
            break;
        }
    }
    // Close file
    fclose(fptr2);
    // Display message about staff was found or not
    if (flag){
        printf("\n____________________ Search Successful!!____________________\n");
        printf("\n==========================================================================================\n");
        // back to admin interface
        admin_interface();
    }
    else{
        printf("\n____________________ Staff Not Found!!____________________\n");
        printf("==========================================================================================\n");
        // back to admin interface.
        admin_interface();
    }
}

void generate_report(){
    // Declaration
    FILE *write_file, *read_file,*staff_file;
    struct Leave_Detail Leave;
    struct Staff Staff;
    int option,selected_num;
    int start_day, start_month,start_year;
    int end_day,end_month,end_year;
    int rejected_count=0,pending_count=0,approved_count=0;
    char dept[100],selected_month[20],line[100];

    // Declare the name of each month in an array.
    char month_name[12][4]={"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
    printf("\n____________________ Generate Monthly Report ____________________\n");
    printf("Please select a department.\n");
    printf("1.Techincal\n");
    printf("2.Management\n");
    printf("3.Academic\n");
    printf("4.Administration\n");
    printf("5.Exit\n");
    // Get input repeatly if the user enter invalid number
    do{
        printf("Your Choice : ");
        int check = scanf("%d",&option);
        //validation for not number input
        if (check !=1 ){
            printf("Invalid input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        // According the selection from user, assigned to the different case.
        switch (option){
            case 1:
            strcpy(dept,"Technical");
            break;

            case 2:
            strcpy(dept,"Management");
            break;

            case 3:
            strcpy(dept,"Academic");
            break;

            case 4:
            strcpy(dept,"Administration");
            break;

            // If the user enter the 'exit' option, exit the program
            case 5:
            // Clear the terminal
            system("cls");
            admin_interface();
            exit(0);

            // if above case not relevent, run default
            default:
            printf("Please enter the correct number!\n");
            continue;

        }
    }while(!(option==1 || option==2 ||option==3 ||option==4));
    
    printf("\nPlease enter the month(num)\n");
    // Get input repeatly if the user enter invalid number
    do{
        printf("Enter Month   : ");
        int check = scanf("%d",&option);
        //validation for not number input
        if (check !=1 ){
            printf("Invalid input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        if (option>=1 && option <=12){
            strcpy(selected_month,month_name[option-1]);
            selected_num=option;
            printf("Selected Month: %s\n",selected_month);
        }
        else{
            printf("\nEnter the Correct Number (1~12).\n");
        }
    }while(!(option>=1 && option <=12));

    // Open file
    write_file=fopen("Monthly_Report.txt","w");
    fprintf(write_file,"____________________ Monthly Report ____________________\n");
    fprintf(write_file,"\nDepartment     : %s\n",dept);
    fprintf(write_file,"Selected Month : %s\n",selected_month);
    fprintf(write_file,"\n==========================================================================================\n");

    fprintf(write_file,"\n======== Pending List ========\n");
    // Display the attributes of the table
    fprintf(write_file,"\n_Leave ID_|_Staff ID_|_____________Name_____________|_____Leave Type_____|___Start Date___|____End Date____|_Day Number_|_______Status_______\n");
    
    // Open file
    read_file=fopen("Apply_Leave.txt","r");
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),read_file)!=NULL){
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",Leave.LeaveID,Staff.ID,Staff.name,Staff.dept,
        Leave.LeaveType,Leave.Start_Date,Leave.End_Date,&Leave.Day_Number,Leave.LeaveStatus);
        sscanf(Leave.Start_Date, "%d-%d-%d", &start_day, &start_month, &start_year);
        sscanf(Leave.End_Date, "%d-%d-%d", &end_day, &end_month, &end_year);
        if (strcmp(dept,Staff.dept)==0){
            if (start_month == selected_num && strcmp(Leave.LeaveStatus,"Pending")==0){
                fprintf(write_file,"%-10s|%-10s|%-30s|%-20s|%-16s|%-16s|%-12d|%s\n",Leave.LeaveID,Staff.ID,Staff.name,
                Leave.LeaveType,Leave.Start_Date,Leave.End_Date,Leave.Day_Number,Leave.LeaveStatus);
                pending_count++;
            }
        }
    }
    // Close file
    fclose(read_file);

    fprintf(write_file,"\n======== Approved List ========\n");
    // Display the attributes of the table
    fprintf(write_file,"\n_Leave ID_|_Staff ID_|_____________Name_____________|_____Leave Type_____|___Start Date___|____End Date____|_Day Number_|_______Status_______\n");
    // Open file
    read_file=fopen("Apply_Leave.txt","r");
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),read_file)!=NULL){
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",Leave.LeaveID,Staff.ID,Staff.name,Staff.dept,
        Leave.LeaveType,Leave.Start_Date,Leave.End_Date,&Leave.Day_Number,Leave.LeaveStatus);
        sscanf(Leave.Start_Date, "%d-%d-%d", &start_day, &start_month, &start_year);
        sscanf(Leave.End_Date, "%d-%d-%d", &end_day, &end_month, &end_year);
        if (strcmp(dept,Staff.dept)==0){
            if (start_month == selected_num && strcmp(Leave.LeaveStatus,"Approved")==0){
                fprintf(write_file,"%-10s|%-10s|%-30s|%-20s|%-16s|%-16s|%-12d|%s\n",Leave.LeaveID,Staff.ID,Staff.name,
                Leave.LeaveType,Leave.Start_Date,Leave.End_Date,Leave.Day_Number,Leave.LeaveStatus);
                approved_count++;
            }
        }
    }
    // Close file
    fclose(read_file);


    fprintf(write_file,"\n======== Rejected List ========\n");
    // Display the attributes of the table
    fprintf(write_file,"\n_Leave ID_|_Staff ID_|_____________Name_____________|_____Leave Type_____|___Start Date___|____End Date____|_Day Number_|_______Status_______\n");
    
    // Open file
    read_file=fopen("Apply_Leave.txt","r");
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),read_file)!=NULL){
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",Leave.LeaveID,Staff.ID,Staff.name,Staff.dept,
        Leave.LeaveType,Leave.Start_Date,Leave.End_Date,&Leave.Day_Number,Leave.LeaveStatus);
        sscanf(Leave.Start_Date, "%d-%d-%d", &start_day, &start_month, &start_year);
        if (strcmp(dept,Staff.dept)==0){
            if (start_month == selected_num && strcmp(Leave.LeaveStatus,"Rejected")==0){
                fprintf(write_file,"%-10s|%-10s|%-30s|%-20s|%-16s|%-16s|%-12d|%s\n",Leave.LeaveID,Staff.ID,Staff.name,
                Leave.LeaveType,Leave.Start_Date,Leave.End_Date,Leave.Day_Number,Leave.LeaveStatus);
                rejected_count++;
            }
        }
    }
    // Close file
    fclose(read_file);
    
    fprintf(write_file,"\n==========================================================================================\n");
    fprintf(write_file,"In This month, the total number of the leave pending : %d\n",pending_count);
    fprintf(write_file,"In This month, the total number of the leave approved : %d\n",approved_count);
    fprintf(write_file,"In This month, the total number of the leave rejected : %d\n",rejected_count);
    fprintf(write_file,"\n==========================================================================================\n");
    
    // Open file
    staff_file=fopen("staff.txt","r");
    char staff_line[100];
    // Loop through each line of the input file
    while(fgets(staff_line,sizeof(line),staff_file)!=NULL){
        int count=0;
        sscanf(staff_line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^\n]",Staff.ID,Staff.name,Staff.dept,Staff.role,Staff.username,Staff.password);

        if (strcmp(dept,Staff.dept)==0 && strcmp(Staff.role,"Staff")==0){
            fprintf(write_file,"\n------------------------------------------------------------------------------------------\n");
            fprintf(write_file,"Staff ID: %s\n",Staff.ID);
            fprintf(write_file,"Staff Name: %s\n",Staff.name);
            fprintf(write_file,"Staff dept: %s\n",Staff.dept);
            // Display the attributes of the table
            fprintf(write_file,"\n_Leave ID_|_Staff ID_|_____________Name_____________|_____Leave Type_____|___Start Date___|____End Date____|_Day Number_|_______Status_______\n");
            
            // Open file
            read_file=fopen("Apply_Leave.txt","r");
            // Loop through each line of the input file
            while(fgets(line,sizeof(line),read_file)!=NULL){
                char id[20],name[100],staffdept[100];
                sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",Leave.LeaveID,id,name,staffdept,
                Leave.LeaveType,Leave.Start_Date,Leave.End_Date,&Leave.Day_Number,Leave.LeaveStatus);
                sscanf(Leave.Start_Date, "%d-%d-%d", &start_day, &start_month, &start_year);
                if(strcmp(id,Staff.ID)==0 && strcmp(name,Staff.name)==0 && start_month == selected_num){
                    count++;
                    fprintf(write_file,"%-10s|%-10s|%-30s|%-20s|%-16s|%-16s|%-12d|%s\n",Leave.LeaveID,id,name,
                    Leave.LeaveType,Leave.Start_Date,Leave.End_Date,Leave.Day_Number,Leave.LeaveStatus);
                }
            }
            // Close file
            fclose(read_file);
            fprintf(write_file,"\n\nNumber of times that %s applied for leave: %d\n",Staff.name,count);
        }
    }
    // Close file
    fclose(staff_file);

    fprintf(write_file,"\n==========================================================================================\n");
    // Close file
    fclose(write_file);

    // Display process status
    printf("\n____________________ Monthly Report Successfully Generated ____________________\n");
    admin_interface();
}


//=================================================================================================================================
void staff_interface(char *staffID,char *staffName, char *dept){
    // declare
    int option;

    // Display
    printf("\n\tHello, Staff %s , Hope you have a nice day !!\n",staffName);
    printf("\n");
    printf("1. Apply Leave\n"
           "2. Cancel Leave\n"
           "3. Check Leave Status\n"
           "4. Check the summary of leave information\n"
           "5. Check Your information\n"
           "6. Exit\n");
    printf("Please enter your choice from 1 to 6 : ");
    // Get input repeatly if the user enter invalid number
    do{
        int check;

        // Get input and Validation
        check = scanf("%d",&option);
        //validation for not number input
        if (check !=1 ){
            printf("Invalid input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        // According the selection from user, assigned to the different case.
        switch (option){
            case 1:
            // Clear the terminal.
            system("cls");
            Apply_leave(staffID,staffName,dept);
            break;

            case 2:
            // Clear the terminal.
            system("cls");
            Cancel_leave(staffID,staffName,dept);
            break;

            case 3:
            // Clear the terminal.
            system("cls");
            Check_Leave_Status(staffID,staffName,dept);
            break;

            case 4:
            // Clear the terminal.
            system("cls");
            Summary_of_Leave_Information(staffID,staffName,dept);
            break;

            case 5:
            // Clear the terminal.
            system("cls");
            Check_User_Information(staffID, staffName, dept);
            break;

            // If the user enter the 'exit' option, exit the program
            case 6:
            // Clear the terminal.
            system("cls");
            main_interface();
            break;

            // if above case not relevent, run default
            default:
            printf("\nPlease enter the correct Number\n");
            continue;
        }
    }
    while (!(option==1||option==2||option==3||option==4||option==5||option==6));
}

void Apply_leave(char *staffID, char *staffName, char *dept){
    // Declaration
    FILE *fptr1,*fptr2;
    int option,choice;
    int function_check;
    int flag=0;

    char line[200], str[100];
    // Declare the 5 types of leave
    char TypeLeave[][20]={"Annual Leave","Medical Leave","Emergency Leave","Compassionate Leave","Personal Leave"};
    int Quantity_Leave[5];
    struct Leave_Detail Leave;
    struct Staff Apply;
    struct Staff Staff;

    // Open file
    fptr1=fopen("leave.txt","r");
    if (fptr1==NULL){
        printf("File Not Found.\n");
        exit(0);
    }
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr1)!=NULL){
        // Read the data from each line
        sscanf(line,"%[^||]||%[^||]||%[^||]||%d||%d||%d||%d||%d",Apply.ID,Apply.name,Apply.dept,
        &Quantity_Leave[0],&Quantity_Leave[1],&Quantity_Leave[2],&Quantity_Leave[3],&Quantity_Leave[4]);
        // if the staff ID is same as the user 's, break the loops
        if(strcmp(Apply.ID,staffID)==0 && strcmp(Apply.name,staffName)==0){
            break;
        }    
    }
    // Close file
    fclose(fptr1);

    // Display the staff 's leave balance information.
    printf("\n____________________ Leave Application ____________________\n\n");
    printf("Staff ID   : %s\n", staffID);
    printf("Name       : %s\n", staffName);
    printf("Department : %s\n", dept);
    printf("__________________________\n");
    printf("|Types of Leave     | Day|\n");
    printf("__________________________\n");
    printf("Annual Leave        | %3d|\n",Quantity_Leave[0]);
    printf("Medical Leave       | %3d|\n",Quantity_Leave[1]);
    printf("Emergency Leave     | %3d|\n",Quantity_Leave[2]);
    printf("Compassionate Leave | %3d|\n",Quantity_Leave[3]);
    printf("Personal Leave      | %3d|\n",Quantity_Leave[4]);
    printf("__________________________\n");
    printf("\n==========================================================================================\n");
    printf("Please select which leave that you want to apply.\n");
    printf("1. Annual Leave.\n"
           "2. Medical Leave.\n"
           "3. Emergency Leave.\n"
           "4. Compassionate Leave.\n"
           "5. Peronal Leave.\n"
           "6. Exit.\n");
    printf("\n==========================================================================================\n");
    // Loops for getting the correct input to let user choose the leave type.
    while(1){
        printf("Please select from 1 to 6: ");
        int check=scanf("%d",&option);
        if (check != 1){
            printf("\nInvalid Input!!!\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        if (option==1){
            // Save the Leave.LeaveType from the array.
            strcpy(Leave.LeaveType,TypeLeave[option-1]);
            printf("Leave Type              : %s\n",Leave.LeaveType);
            break;   
        }
        else if (option==1){
            // Save the Leave.LeaveType from the array.
            strcpy(Leave.LeaveType,TypeLeave[option-1]);
            printf("Leave Type              : %s\n",Leave.LeaveType);
            break;   
        }
        else if (option==2){
            // Save the Leave.LeaveType from the array.
            strcpy(Leave.LeaveType,TypeLeave[option-1]);
            printf("Leave Type              : %s\n",Leave.LeaveType);
            break;   
        }
        else if (option==3){
            // Save the Leave.LeaveType from the array.
            strcpy(Leave.LeaveType,TypeLeave[option-1]);
            printf("Leave Type              : %s\n",Leave.LeaveType);
            break;   
        }
        else if (option==4){
            // Save the Leave.LeaveType from the array.
            strcpy(Leave.LeaveType,TypeLeave[option-1]);
            printf("Leave Type              : %s\n",Leave.LeaveType);
            break;   
        }
        else if (option==5){
            // Save the Leave.LeaveType from the array.
            strcpy(Leave.LeaveType,TypeLeave[option-1]);
            printf("Leave Type              : %s\n",Leave.LeaveType);
            break;   
        }
        // If the user enter the 'exit' option, exit the program
        else if (option == 6){
            function_check=-1;
            break;
        }
        else{
            printf("\nWrong choice!!!\n");
            continue;
        }
    }
    if (function_check==-1){
        // Clear the terminal.
        system("cls");
        staff_interface(staffID,staffName,dept);
        exit(0);
    }
    printf("==========================================================================================\n");
    
    // Loop for getting the correct Date input from user.
    while(1){
        //Clear the 'stdin' space
        fflush(stdin);
        int start_year, start_month, start_day;
        int end_year, end_month, end_day;
        printf("Start Date (DD-MM-YYYY) : ");
        fgets(str,100,stdin);
        str[strlen(str)-1]='\0';
        strcpy(Leave.Start_Date,str);
        
        printf("End   Date (DD-MM-YYYY) : ");
        fgets(str,100,stdin);
        str[strlen(str)-1]='\0';
        strcpy(Leave.End_Date,str);

        // Read the date and divide it into day, month, year
        sscanf(Leave.Start_Date, "%d-%d-%d", &start_day, &start_month, &start_year);
        sscanf(Leave.End_Date, "%d-%d-%d", &end_day, &end_month, &end_year);

        // declare the day number of each number.
        int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if ((start_year % 4 == 0 && start_year % 100 != 0) || start_year % 400 == 0) {
            days_in_month[1] = 29;
        }

        // Validate the date with the range of true date
        if(start_day<1 || start_day>31 || end_day<1 || end_day>31 || start_month<1 || start_month>12 || end_month<1 || end_month>12){
            printf("\nInvalid Date!! Please Enter the Correct Date!!\n");
            flag=1;
        }
        // Validate the daynumber in each month
        else if (start_day>days_in_month[start_month-1] || end_day>days_in_month[end_month-1]){
            printf("\nInvalid Date!! The Date does not exist!!\n");
            flag=1;
        }
        // Compared the validity between startdate and enddate
        else{
            if (start_year > end_year ||
                (start_year == end_year && start_month > end_month) ||
                (start_year == end_year && start_month == end_month && start_day > end_day)) {
                printf("\nInvalid Date!! End Date is earlier than Start Date !!\n");
                flag=1;
            }
            else{
                flag=0;
            }
        }
        if (flag==1){
            continue;
        }
        // Check the Start date with additional function (Check_Current_Time)
        int check1=Check_Current_Time(Leave.Start_Date);
        // check1==1 , means the input date already passed.
        if (check1==1){
            printf("\nCannot apply leave for the passing date.\n");
            continue;
        }
        // Check the startdate and enddate with additional function (Check_Date_Overlap) 
        int check2=Check_Date_Overlap(Leave.Start_Date,Leave.End_Date,staffID,staffName,dept);
        
        // check2 == 1 ,means either startdate or enddate is overlap to other date 
        if (check2==1){
            continue;
        }
        else{
            break;
        }
    }
    

    printf("==========================================================================================\n");
    // Use the additional function to calculate the day number between startdate and enddate (included enddate).
    int DayNumber=day_calculation(Leave.Start_Date,Leave.End_Date);
    Leave.Day_Number=DayNumber;
    // Use the LeaveID_generator to create a new LeaveID
    // Use sprintf to convert the 'L' and new PK no to a string.
    sprintf(Leave.LeaveID,"L%04d",LeaveID_generator());
    printf("Leave ID       : %s\n",Leave.LeaveID);
    printf("Leave Type     : %s\n",Leave.LeaveType);
    printf("Start Date     : %s\n",Leave.Start_Date);
    printf("End   Date     : %s\n",Leave.End_Date);
    printf("Numbers of Day : %d\n",DayNumber);
    printf("Status         : ");
    // Check the daynumber to apply is enough leave or not
    if (DayNumber<=Quantity_Leave[option-1]){
        printf("Avaliable\n");
        printf("\n==========================================================================================\n");
        printf("\nPlease Check Again the information.\n");
        printf("Is All the Information is correct?\n1.Yes\n2.No\n");
        // Get input repeatly if the user enter invalid number
        do{
            printf("Please Enter Your Choice : ");
            int check = scanf("%d",&choice);
            //validation for not number input
            if (check !=1 ){
                printf("Invalid input\n");
                // Clear input buffer
                scanf("%*s");
            }
            // According the selection from user, assigned to the different case.
            switch (choice){
                case 1:
                // Open file
                fptr2=fopen("Apply_Leave.txt","a");
                // Write the appiled leave detail into file. 
                fprintf(fptr2,"%s||%s||%s||%s||%s||%s||%s||%d||Pending\n",
                Leave.LeaveID,staffID,staffName,dept,Leave.LeaveType,Leave.Start_Date,Leave.End_Date,Leave.Day_Number);
                // Close file
                fclose(fptr2);
                printf("\n__________ Information is Successfully Recorded.__________\n");
                staff_interface(staffID,staffName,dept);
                
                case 2:
                staff_interface(staffID,staffName,dept);
                exit(0);

                // if above case not relevant, run default
                default:
                printf("\nPlease Enter the Correct Number!!\n");
                continue;
            }
        }while (!(choice==1 || choice ==2));
    }
    // if the leave number is not enough to apply , run this.
    else{
        printf("Not Enough\n");
        printf("==========================================================================================\n");
        printf("\n__________ Sorry ! Not Enough Leave! Please Apply Again !__________\n\n");
        staff_interface(staffID,staffName,dept);
    }
}

int Check_Date_Overlap(char *Start_Date,char *End_Date,char *staffID,char *staffName, char *dept){
    // Declaration
    FILE *fptr;
    char line[200];
    int flag=0;

    // Declare the date format
    int start_year, start_month, start_day;
    int end_year, end_month, end_day;
    int check_year, check_month, check_day;

    // Validation of the Start Date
    sscanf(Start_Date, "%d-%d-%d", &check_day, &check_month, &check_year);

    // Open file
    fptr=fopen("Apply_Leave.txt","r");
    if (fptr==NULL){
        printf("File Not Found.\n");
        exit(0);
    }
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr)!=NULL){
        // Declaration
        struct Leave_Detail check_leave;
        struct Staff check_staff;
        // read the data and save it in each variable line by line
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",check_leave.LeaveID,check_staff.ID,check_staff.name,check_staff.dept,
        check_leave.LeaveType,check_leave.Start_Date,check_leave.End_Date,&check_leave.Day_Number,check_leave.LeaveStatus);
        
        // Read the Pending Leave only, make sure only check the person who appiled leave.
        if (strcmp(staffID,check_staff.ID)==0 && strcmp(staffName,check_staff.name)==0 && strcmp(dept,check_staff.dept)==0 && strcmp(check_leave.LeaveStatus,"Pending")==0){
            // read the date and save it with day, month, year
            sscanf(check_leave.Start_Date, "%d-%d-%d", &start_day, &start_month, &start_year);
            sscanf(check_leave.End_Date, "%d-%d-%d", &end_day, &end_month, &end_year);
            // Check is the check date in between the start date and end date?
            if ((check_year > start_year || (check_year == start_year && check_month > start_month) || (check_year == start_year && check_month == start_month && check_day >= start_day))
            && (check_year < end_year || (check_year == end_year && check_month < end_month) || (check_year == end_year && check_month == end_month && check_day <= end_day))) {
                printf("\n__________Start Date Overlap__________\n");
                // Set the flag 
                flag=1;
                break;
            }
        }   
    }
    // Close file
    fclose(fptr);

    //Validation of the End Date
    sscanf(End_Date, "%d-%d-%d", &check_day, &check_month, &check_year);
    
    // Open file
    fptr=fopen("Apply_Leave.txt","r");
    if (fptr==NULL){
        printf("File Not Found.\n");
        exit(0);
    }
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr)!=NULL){
        // Declaration
        struct Leave_Detail check_leave;
        struct Staff check_staff;
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",check_leave.LeaveID,check_staff.ID,check_staff.name,check_staff.dept,
        check_leave.LeaveType,check_leave.Start_Date,check_leave.End_Date,&check_leave.Day_Number,check_leave.LeaveStatus);
        // read the date and save it with day, month, year
        if (strcmp(staffID,check_staff.ID)==0 && strcmp(staffName,check_staff.name)==0 && strcmp(dept,check_staff.dept)==0 && strcmp(check_leave.LeaveStatus,"Pending")==0){
            sscanf(check_leave.Start_Date, "%d-%d-%d", &start_day, &start_month, &start_year);
            sscanf(check_leave.End_Date, "%d-%d-%d", &end_day, &end_month, &end_year);
            // Check is the check date in between the start date and end date?
            if ((check_year > start_year || (check_year == start_year && check_month > start_month) || (check_year == start_year && check_month == start_month && check_day >= start_day))
            && (check_year < end_year || (check_year == end_year && check_month < end_month) || (check_year == end_year && check_month == end_month && check_day <= end_day))) {
                printf("\n__________End date Overlap__________\n");
                flag=1;
                break;
            }
        } 
    }
    // Close file
    fclose(fptr);

    // flag == 1 ,means the check date is overlap, flag == 0,means not overlap
    return flag;
}

int day_calculation(char* start_date, char* end_date) {
    int start_year, start_month, start_day;
    int end_year, end_month, end_day;
    int day_number;
    // Parse the start date string and end date
    sscanf(start_date, "%d-%d-%d", &start_day, &start_month, &start_year);
    sscanf(end_date, "%d-%d-%d", &end_day, &end_month, &end_year);
    // declare the day number of each number.
    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Check for leap years
    if ((start_year % 4 == 0 && start_year % 100 != 0) || start_year % 400 == 0) {
        days_in_month[1] = 29;
    }
    // Calculate the number of days between the start and end dates
    if (start_year == end_year && start_month == end_month) {
        day_number = end_day - start_day +1;
    } else {
        // Calculate the number of days between the start day and the end of the start month
        day_number = days_in_month[start_month-1] - start_day +1;
        // Calculate the number of days between the start and end months
        for (int month = start_month + 1; month < end_month; month++) {
            int days= days_in_month[month - 1];

            day_number += days;
        }
        // Calculate the number of days between the start of the end month and the end date
        day_number += end_day;
    }
    // return the number of days between the start and end dates
    return day_number;
}

int LeaveID_generator(){
    char line[200];
    char last_PK[20],new_PK[20];
    int count=0;

    // Open file
    FILE *file = fopen("Apply_Leave.txt", "r");
    if (file==NULL){
        printf("Error file\n");
        exit(0);
    }   
    // Let the file pointer run until the last line.
    while(fgets(line,sizeof(line),file)!=NULL){
    }
    strncpy(last_PK,&line[1],4);
    last_PK[4]='\0';
    // Close file
    fclose(file);
    sscanf(last_PK,"%04d",&count);
    count+=1;
    return count;
}

int Check_Current_Time(char *Start_Date){
    // Declaration
    char current_date[100];
    time_t current = time(0); // get current time
    struct tm *t = localtime(&current); // convert to local time
    int current_year=t->tm_year+1900;
    int current_month=t->tm_mon+1;
    int current_day=t->tm_mday;

    int year,month,day;
    sscanf(Start_Date,"%d-%d-%d",&day,&month,&year);
    if ((year<current_year)||(year == current_year && month < current_month) || (year == current_year && month == current_month && day < current_day)){
        return 1;
    }
    return 0;
}

void Cancel_leave(char *staffID,char *staffName, char *dept){
    // Declaration
    FILE *fptr1;
    char line[200],str[100];
    int flag=0;
    struct Leave_Detail Leave;
    struct Leave_Detail Cancel;
    struct Staff Staff;

    // Open file
    fptr1 = fopen("Apply_Leave.txt","r");
    if (fptr1 == NULL){
        printf("Unable to open the file.\n");
        exit(0);
    }
    printf("\n____________________ Leave Cancellation ____________________\n\n");
    printf("1.The approved leave cannot be canceled !!\n");
    printf("2.The overdue date will not be displayed and cannot be canceled.\n\n");
    printf("StaffID        : %s\n",staffID);
    printf("Name           : %s\n",staffName);
    printf("Department     : %s\n",dept);
    // Display the attributes of the table
    printf("\n_Leave ID_|_Staff ID_|_____________Name_____________|_____Leave Type_____|___Start Date___|____End Date____|_Day Number_|_______Status_______\n");
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr1)!=NULL){
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",Leave.LeaveID,Staff.ID,Staff.name,Staff.dept,
        Leave.LeaveType,Leave.Start_Date,Leave.End_Date,&Leave.Day_Number,Leave.LeaveStatus);
        if (strcmp(staffID,Staff.ID)==0 && strcmp(staffName,Staff.name)==0 && strcmp(Leave.LeaveStatus,"Pending")==0 && !(Check_Current_Time(Leave.Start_Date))){
                printf("%-10s|%-10s|%-30s|%-20s|%-16s|%-16s|%-12d|%s\n",Leave.LeaveID,Staff.ID,Staff.name,Leave.LeaveType,Leave.Start_Date,Leave.End_Date,Leave.Day_Number,Leave.LeaveStatus);
                flag++;
        }
    }
    if (flag ==0){
        printf("\n__________You are not apply any leave!___________\n");
        staff_interface(staffID,staffName,dept);
        exit(0);
    }
    printf("\n==========================================================================================\n");
    printf("Please enter the LeaveID to select.\n");
    printf("Enter \"exit\" to quit.\n");

    while(1){
        //Clear the 'stdin' space
        fflush(stdin);
        char PK[20];
        int check,PK_Num;
        printf("LeaveID : ");
        fgets(str,100,stdin);
        str[strlen(str)-1]='\0';
        strcpy(Cancel.LeaveID,str);
        strncpy(PK,&Cancel.LeaveID[1],5);

        // If 'exit' is inputed , exit this process.
        if (strcmp(Cancel.LeaveID,"exit")==0){
            staff_interface(staffID,staffName,dept);
            exit(0);
        }
        // Valiadtion of the Input "Leave ID" Format :L0001
        if (Cancel.LeaveID[0]!='L'){
            printf("Wrong Prefix Format!\n");
            continue;
        }
        else if (check = sscanf(PK,"%04d",&PK_Num)!=1){
            printf("Wrong Number Format!\n");
            continue;
        }
        else if (strlen(Cancel.LeaveID)!=5){
            printf("Wrong Format!\n");
            continue;
        }
        else{
            break;
        }
    }
    printf("\n==========================================================================================\n");
    fseek(fptr1,0L,SEEK_SET);
    int count=0;
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr1)!=NULL){
        // Read the line and divide into each different data.
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",Leave.LeaveID,Staff.ID,Staff.name,Staff.dept,
        Leave.LeaveType,Leave.Start_Date,Leave.End_Date,&Leave.Day_Number,Leave.LeaveStatus);
        // if the Leave ID correct , display its detail.
        if (strcmp(Cancel.LeaveID,Leave.LeaveID)==0 && strcmp(staffID,Staff.ID)==0 && strcmp(staffName,Staff.name)==0 && 
            strcmp(Leave.LeaveStatus,"Pending")==0 && !(Check_Current_Time(Leave.Start_Date))){
            printf("Leave ID       : %s\n",Leave.LeaveID);
            printf("Leave Type     : %s\n",Leave.LeaveType);
            printf("Start Date     : %s\n",Leave.Start_Date);
            printf("End   Date     : %s\n",Leave.End_Date);
            printf("Numbers of Day : %d\n",Leave.Day_Number);
            printf("Status         : %s\n",Leave.LeaveStatus);
            printf("==========================================================================================\n");
            count++;
            break;
        }
    }
    // Close file
    fclose(fptr1);
    if (count==0){
        printf("Leave Not Found !\n");
        printf("==========================================================================================\n");
        staff_interface(staffID,staffName,dept);
    }
    // Check is the Status is Pending or not
    if (strcmp(Leave.LeaveStatus,"Pending")==0){
        int choice;
        printf("\nPlease Check Again the information.\n");
        printf("Confirm Delete?\n1.Yes\n2.No\n");
        // Get input repeatly if the user enter invalid number
        do{
            printf("Your Choice : ");
            int check = scanf("%d",&choice);
            //validation for not number input
            if (check !=1 ){
                printf("Invalid input\n");
                // Clear input buffer
                scanf("%*s");
            }
            // According the selection from user, assigned to the different case.
            switch (choice){
                case 1:
                // declaration
                FILE *input_file,*temp_file;
                char delete_leave[100];
                char line[200];

                // Copy the leaveID which want to delete
                strcpy(delete_leave,Cancel.LeaveID);
                
                // Open file
                input_file = fopen("Apply_Leave.txt","r");
                temp_file = fopen("temp.txt","w");
                if (input_file == NULL || temp_file == NULL){
                    printf("Unable to open the file.\n");
                    exit(0);
                }
                // Loop through each line of the input file
                while (fgets(line, 200, input_file) != NULL) {
                // Check if the line contains the data to be deleted
                    if (strstr(line, delete_leave) == NULL) {
                        // Write the line to the temporary file if it does not contain the data to be deleted
                        fputs(line, temp_file);
                    }
                }
                // Close file
                fclose(input_file);
                fclose(temp_file);

                remove("Apply_Leave.txt");
                rename("temp.txt","Apply_Leave.txt");
                printf("Leave canceled successfully.\n");
                printf("\n==========================================================================================\n\n");

                case 2:
                printf("\n==========================================================================================\n");
                staff_interface(staffID,staffName,dept);
                exit(0);

                // if above case not relevent, run default
                default:
                printf("\nPlease Enter the Correct Number!!\n");
                continue;
            }
        }while (!(choice==1 || choice ==2));
        printf("==========================================================================================\n");
    }
    // If there are not any Pending Leave Found , Display not found.
    else{
        printf("Leave Not Found.\n");
        printf("==========================================================================================\n");
    }  
}

void Check_Leave_Status(char *staffID,char *staffname,char *dept){
    // Declaration
    char line[200];
    int count=0;
    FILE *fptr;
    struct Leave_Detail Leave;
    struct Staff Staff;
    
    // Open file
    fptr=fopen("Apply_Leave.txt","r");
    if (fptr==NULL){
        printf("File does not exists");
        exit(0);
    }
    printf("\n____________________ Check Leave Status  ____________________\n");
    printf("\n==========================================================================================\n");
    
    // Display the attributes of the table
    printf("\n_Leave ID_|_Staff ID_|_____________Name_____________|_____Leave Type_____|___Start Date___|____End Date____|_Day Number_|_______Status_______\n");

    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr)!=NULL){
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^||]\n",Leave.LeaveID,Staff.ID,Staff.name,Staff.dept,
        Leave.LeaveType,Leave.Start_Date,Leave.End_Date,&Leave.Day_Number,Leave.LeaveStatus);

        if (strcmp(staffID,Staff.ID)==0 && strcmp(staffname,Staff.name)==0 && !(Check_Current_Time(Leave.Start_Date))){
                printf("%-10s|%-10s|%-30s|%-20s|%-16s|%-16s|%-12d|%s",
                Leave.LeaveID,Staff.ID,Staff.name,Leave.LeaveType,Leave.Start_Date,Leave.End_Date,Leave.Day_Number,Leave.LeaveStatus);
                count++;
            }
    }
    // Close file
    fclose(fptr);
    if (count ==0){
        printf("\n__________You are not apply any leave!___________\n\n");
    }
    printf("\n==========================================================================================\n");
    printf("\n\n");
    staff_interface(staffID,staffname,dept);
}

void Summary_of_Leave_Information(char *staffID,char *staffName,char *dept){
    // Declaration
    FILE *fptr1,*fptr2;
    char line[200];
    struct Leave Leave;
    struct Leave_Detail ApplyLeave;
    struct Staff Staff;
    int Quantity_Leave[5];
    int count1=0,count2=0,count3=0;

    // Open file
    fptr1=fopen("leave.txt","r");
    if (fptr1==NULL){
        printf("File Not Found.\n");
        exit(0);
    }
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr1)!=NULL){
        sscanf(line,"%[^||]||%[^||]||%[^||]||%d||%d||%d||%d||%d",Staff.ID,Staff.name,Staff.dept,
        &Quantity_Leave[0],&Quantity_Leave[1],&Quantity_Leave[2],&Quantity_Leave[3],&Quantity_Leave[4]);
        if(strcmp(Staff.ID,staffID)==0 && strcmp(Staff.name,staffName)==0){
            break;
        }    
    }
    // Close file
    fclose(fptr1);

    printf("\n____________________ Summary of leave information ____________________\n\n");
    printf("Staff ID   : %s\n", staffID);
    printf("Name       : %s\n", staffName);
    printf("Department : %s\n", dept);

    printf("\n======== Leave Balance ========\n");
    printf("__________________________\n");
    printf("|Types of Leave     | Day|\n");
    printf("__________________________\n");
    printf("Annual Leave        | %3d|\n",Quantity_Leave[0]);
    printf("Medical Leave       | %3d|\n",Quantity_Leave[1]);
    printf("Emergency Leave     | %3d|\n",Quantity_Leave[2]);
    printf("Compassionate Leave | %3d|\n",Quantity_Leave[3]);
    printf("Personal Leave      | %3d|\n",Quantity_Leave[4]);
    printf("__________________________\n");
    printf("\n==========================================================================================\n");
    
    // Open file
    fptr2=fopen("Apply_Leave.txt","r");
    if (fptr2==NULL){
        printf("File does not exists");
        exit(0);
    }

    printf("\n======== Pending List ========\n");
    // Display the attributes of the table
    printf("\n_Leave ID_|_Staff ID_|_____________Name_____________|_____Leave Type_____|___Start Date___|____End Date____|_Day Number_|_______Status_______\n");
    
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr2)!=NULL){
        // Read the data
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",ApplyLeave.LeaveID,Staff.ID,Staff.name,Staff.dept,
        ApplyLeave.LeaveType,ApplyLeave.Start_Date,ApplyLeave.End_Date,&ApplyLeave.Day_Number,ApplyLeave.LeaveStatus);
        // If the status is "Pending", Print
        if (strcmp(staffID,Staff.ID)==0 && strcmp(staffName,Staff.name)==0 && strcmp(ApplyLeave.LeaveStatus,"Pending")==0){
            count1+=ApplyLeave.Day_Number;
            printf("%-10s|%-10s|%-30s|%-20s|%-16s|%-16s|%-12d|%s\n",ApplyLeave.LeaveID,Staff.ID,Staff.name,
                    ApplyLeave.LeaveType,ApplyLeave.Start_Date,ApplyLeave.End_Date,ApplyLeave.Day_Number,ApplyLeave.LeaveStatus);
        }
    }
    // Close file
    fclose(fptr2);
    
    printf("\n==========================================================================================\n");
    // Open file
    fptr2=fopen("Apply_Leave.txt","r");
    if (fptr2==NULL){
        printf("File does not exists");
        exit(0);
    }
    printf("\n======== Approved List ========");
    // Display the attributes of the table
    printf("\n_Leave ID_|_Staff ID_|_____________Name_____________|_____Leave Type_____|___Start Date___|____End Date____|_Day Number_|_______Status_______\n");

    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr2)!=NULL){
        // Read the data
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",ApplyLeave.LeaveID,Staff.ID,Staff.name,Staff.dept,
        ApplyLeave.LeaveType,ApplyLeave.Start_Date,ApplyLeave.End_Date,&ApplyLeave.Day_Number,ApplyLeave.LeaveStatus);
        // If the status is "Approved", Print
        if (strcmp(staffID,Staff.ID)==0 && strcmp(staffName,Staff.name)==0 && strcmp(ApplyLeave.LeaveStatus,"Approved")==0){
            count2+=ApplyLeave.Day_Number;
            printf("%-10s|%-10s|%-30s|%-20s|%-16s|%-16s|%-12d|%s\n",ApplyLeave.LeaveID,Staff.ID,Staff.name,ApplyLeave.LeaveType,
                    ApplyLeave.Start_Date,ApplyLeave.End_Date,ApplyLeave.Day_Number,ApplyLeave.LeaveStatus);
        }
    }
    // Close file
    fclose(fptr2);

    printf("\n==========================================================================================\n");
    // Open file
    fptr2=fopen("Apply_Leave.txt","r");
    if (fptr2==NULL){
        printf("File does not exists");
        exit(0);
    }
    printf("\n======== Rejected List ========");
    // Display the attributes of the table
    printf("\n_Leave ID_|_Staff ID_|_____________Name_____________|_____Leave Type_____|___Start Date___|____End Date____|_Day Number_|_______Status_______\n");
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr2)!=NULL){
        // Read the data
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",ApplyLeave.LeaveID,Staff.ID,Staff.name,Staff.dept,
        ApplyLeave.LeaveType,ApplyLeave.Start_Date,ApplyLeave.End_Date,&ApplyLeave.Day_Number,ApplyLeave.LeaveStatus);
        // If the status is "Rejected", Print
        if (strcmp(staffID,Staff.ID)==0 && strcmp(staffName,Staff.name)==0 && strcmp(ApplyLeave.LeaveStatus,"Rejected")==0){
            count3+=ApplyLeave.Day_Number;
            printf("%-10s|%-10s|%-30s|%-20s|%-16s|%-16s|%-12d|%s\n",ApplyLeave.LeaveID,Staff.ID,Staff.name,ApplyLeave.LeaveType,
            ApplyLeave.Start_Date,ApplyLeave.End_Date,ApplyLeave.Day_Number,ApplyLeave.LeaveStatus);
        }
    }
    // Close file
    fclose(fptr2);

    printf("\n==========================================================================================\n");
    printf("The total number of leave can apply : %d\n",Quantity_Leave[0]+Quantity_Leave[1]+Quantity_Leave[2]+Quantity_Leave[3]+Quantity_Leave[4]-count1);
    printf("The total number of leave pending   : %d\n",count1);
    printf("The total number of leave approved  : %d\n",count2);
    printf("The total number of leave rejected  : %d\n",count3);
    printf("\n==========================================================================================\n");
    printf("\n\n");
    staff_interface(staffID,staffName,dept);
}


void Check_User_Information(char *staffID,char *staffName, char *dept){
    // Declaration
    struct Staff staff;
    FILE *fptr;
    // Open file
    fptr=fopen("staff.txt","r");
    if (fptr==NULL){
        printf("File does not exists");
        exit(0);
    }
    // Display
    printf("\n____________________ Check Personal Information ____________________\n");
    while(fscanf(fptr, "%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^\n]\n",staff.ID,staff.name,staff.dept,staff.role,staff.username,staff.password)!=EOF){
        if (strcmp(staff.ID,staffID)==0 && strcmp(staff.name,staffName)==0){
            break;
        }
    }
    // Close file
    fclose(fptr);
    printf("ID         : %s\n",staff.ID);
    printf("Name       : %s\n",staff.name);
    printf("Department : %s\n",staff.dept);
    printf("Role       : %s\n",staff.role);
    printf("Username   : %s\n",staff.username);
    printf("Password   : %s\n",staff.password);
    printf("\n\n");
    printf("\n==========================================================================================\n");
    staff_interface(staffID,staffName,dept);
}

// ============================================================================================================================

void LeaveApprover_interface(char *staffID,char *staffName,char *dept){
    // declare
    int option;

    // Display the selection
    printf("\n");
    printf("\tHello, Superior %s , Hope you have a nice day !!\n\n",staffName);
    printf("1. Approve and Reject Leave Applications.\n"
           "2. Search the date of leave status.\n"
           "3. Exit.\n");
    do {
        printf("Please enter your choice from 1 to 3 : ");
        int check=scanf("%d",&option);
        //validation for not number input
        if (check !=1 ){
            printf("Invalid input\n");
            // Clear input buffer
            scanf("%*s");
            continue;
        }
        // According the selection from user, assigned to the different case.
        switch (option){
            case 1:
            // Clear the terminal.
            system("cls");
            Approve_Leave(staffID,staffName,dept);
            break;

            case 2:
            // Clear the terminal.
            system("cls");
            Search_Date_Leave(staffID,staffName,dept);
            break;

            // If the user enter the 'exit' option, exit the program
            case 3:
            // Clear the terminal.
            system("cls");
            main_interface();
            break;

            // if above case not relevant, run default
            default:
            printf("\nPlease Enter the Correct Choice!!\n");
            continue;

        }

    }while (!(option>=1 && option <=3));
}

void Approve_Leave(char *staffID,char *staffName, char * dept){
    // Declaration
    FILE *fptr1,*fptr2;
    char line[200],str[100],status[100],STAFFID[20],TYPE[100],new_line[200];
    int DAY_NUM;
    struct Leave_Detail Detail,Check;
    struct Leave Quantity;
    struct Staff Staff;

    // Open file
    fptr1=fopen("Apply_Leave.txt","r");
    if (fptr1==NULL){
        printf("File does not exists");
        exit(0);
    }
    printf("\n____________________ Approve Leave  ____________________\n");
    printf("\n==========================================================================================\n");
    // Display the attributes of the table
    printf("\n_Leave ID_|_Staff ID_|_____________Name_____________|_____Leave Type_____|___Start Date___|____End Date____|_Day Number_|_______Status_______\n");

    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr1)!=NULL){
        // read data from the line
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",Detail.LeaveID,Staff.ID,Staff.name,Staff.dept,
        Detail.LeaveType,Detail.Start_Date,Detail.End_Date,&Detail.Day_Number,Detail.LeaveStatus);
        // Print the leave detail, if the leave status is pending and it have no passed the current time.
        if (strcmp(Staff.dept,dept)==0 && strcmp(Detail.LeaveStatus,"Pending")==0 && !(Check_Current_Time(Detail.Start_Date))){
            printf("%-10s|%-10s|%-30s|%-20s|%-16s|%-16s|%-12d|%s\n",Detail.LeaveID,Staff.ID,Staff.name,Detail.LeaveType,
            Detail.Start_Date,Detail.End_Date,Detail.Day_Number,Detail.LeaveStatus);
        }
    }
    printf("\n==========================================================================================\n");
    printf("Please enter the LeaveID to select.\n");
    printf("Enter \"exit\" to quit\n");
    while(1){
        //Clear the 'stdin' space
        fflush(stdin);
        char PK[20];
        int check,PK_Num;
        printf("LeaveID : ");
        fgets(str,100,stdin);
        // Set a NULL at the last of string.
        str[strlen(str)-1]='\0';
        strcpy(Check.LeaveID,str);
        strncpy(PK,&Check.LeaveID[1],5);

        // If 'exit' is inputed , exit this process.
        if (strcmp(Check.LeaveID,"exit")==0){
            // Clear the terminal.
            system("cls");
            LeaveApprover_interface(staffID,staffName,dept);
        }
        // Valiadtion of the Input "Leave ID" Format :L0001
        if (Check.LeaveID[0]!='L'){
            printf("Wrong Prefix Format!\n");
            continue;
        }
        else if (check = sscanf(PK,"%04d",&PK_Num)!=1){
            printf("Wrong Number Format!\n");
            continue;
        }
        else if (strlen(Check.LeaveID)!=5){
            printf("Wrong Format!\n");
            continue;
        }
        else{
            break;
        }
    }
    printf("\n==========================================================================================\n");
    // Set the file pointer to the beginning of the file
    fseek(fptr1,0L,SEEK_SET);
    int count=0;
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr1)!=NULL){
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^\n]",Detail.LeaveID,Staff.ID,Staff.name,Staff.dept,
        Detail.LeaveType,Detail.Start_Date,Detail.End_Date,&Detail.Day_Number,Detail.LeaveStatus);
        // Print it , if the leave ID is match and the status is "pending" and the leave has not passed the current time.
        if (strcmp(Check.LeaveID,Detail.LeaveID)==0 && strcmp(Detail.LeaveStatus,"Pending")==0 && !(Check_Current_Time(Detail.Start_Date))){
            printf("Leave ID       : %s\n",Detail.LeaveID);
            printf("Leave Type     : %s\n",Detail.LeaveType);
            printf("Start Date     : %s\n",Detail.Start_Date);
            printf("End   Date     : %s\n",Detail.End_Date);
            printf("Numbers of Day : %d\n",Detail.Day_Number);
            printf("Status         : %s\n",Detail.LeaveStatus);
            printf("==========================================================================================\n");
            // copy the staffid,Leavetype into a new independent string
            strcpy(STAFFID,Staff.ID);
            strcpy(TYPE,Detail.LeaveType);
            DAY_NUM=Detail.Day_Number;
            count++;
            break;
        }
    }
    // Close file
    fclose(fptr1);
    if (count==0){
        printf("Leave Not Exist !\n");
        printf("==========================================================================================\n");
        LeaveApprover_interface(staffID,staffName,dept);
    }
    else{
        int choice;
        //Display selection to let the superior change the status of leave
        printf("\nPlease select the action.\n");
        printf("1.Approved\n2.Reject\n3.Pending\n");
        // Get input repeatly if the user enter invalid number
        do{
            printf("Your Choice : ");
            int check = scanf("%d",&choice);
            //validation for not number input
            if (check !=1 ){
                printf("Invalid input\n");
                // Clear input buffer
                scanf("%*s");
            }
            // According the selection from user, assigned to the different case.
            switch (choice){
                case 1:
                strcpy(status,"Approved");
                // Rewrite the Leave Status
                // Replace the old status ,and convert it to a new line(string)
                sprintf(new_line,"%s||%s||%s||%s||%s||%s||%s||%d||%s\n",Detail.LeaveID,Staff.ID,Staff.name,Staff.dept,
                        Detail.LeaveType,Detail.Start_Date,Detail.End_Date,Detail.Day_Number,status);
        
                // Open file
                fptr1 = fopen("Apply_Leave.txt","r");
                fptr2 = fopen("temp.txt","w");
                // Check file exist
                if (fptr1 == NULL || fptr2 == NULL){
                    printf("Unable to open the file.\n");
                    exit(0);
                }
                // Loop through each line of the input file
                while (fgets(line, 200, fptr1) != NULL) {
                // Check if the line contains the data to be deleted
                    if (strstr(line,Check.LeaveID) != NULL) {
                        // Replace the line with the new_line into the temporary file.
                        fputs(new_line, fptr2);
                    }
                    else{
                        // continue writing the line from the old file to temporary file
                        fputs(line,fptr2);
                    }
                }
                // Close file
                fclose(fptr1);
                fclose(fptr2);

                remove("Apply_Leave.txt");
                rename("temp.txt","Apply_Leave.txt");
                
                // Rewrite Leave Balance
                // Open file
                fptr1 = fopen("leave.txt","r");
                fptr2 = fopen("temp.txt","w");
                if (fptr1 == NULL || fptr2 == NULL){
                    printf("Unable to open the file.\n");
                    exit(0);
                }
                // Loop through each line of the input file
                while(fgets(line,sizeof(line),fptr1)!=NULL){
                    //Read
                    sscanf(line,"%[^||]||%[^||]||%[^||]||%d||%d||%d||%d||%d\n",Staff.ID,Staff.name,Staff.dept,
                    &Quantity.Annual_leave,&Quantity.Medical_leave,&Quantity.Emergency_leave,&Quantity.Compassionate_leave,&Quantity.Personal_leave);
                    //Calculate the remaining leave number
                    if (strcmp(STAFFID,Staff.ID)==0){
                        if(strcmp(TYPE,"Annual Leave")==0){
                            Quantity.Annual_leave-=DAY_NUM;
                        }
                        else if(strcmp(TYPE,"Medical Leave")==0){
                            Quantity.Medical_leave-=DAY_NUM;
                        }
                        else if(strcmp(TYPE,"Emergency Leave")==0){
                            Quantity.Emergency_leave-=DAY_NUM;
                        }
                        else if(strcmp(TYPE,"Compassionate Leave")==0){
                            Quantity.Compassionate_leave-=DAY_NUM;
                        }
                        else if(strcmp(TYPE,"Personal Leave")==0){
                            Quantity.Personal_leave-=DAY_NUM;
                        }
                        // Replace the new data with the new_line
                        sprintf(new_line,"%s||%s||%s||%d||%d||%d||%d||%d\n",Staff.ID,Staff.name,Staff.dept,
                        Quantity.Annual_leave,Quantity.Medical_leave,Quantity.Emergency_leave,Quantity.Compassionate_leave,Quantity.Personal_leave);
                        fputs(new_line, fptr2);
                    }
                    else{
                        fputs(line, fptr2);
                    }
                }
                // Close file
                fclose(fptr1);
                fclose(fptr2);

                remove("leave.txt");
                rename("temp.txt","leave.txt");
                break;

                case 2:
                // As same as above , but here is change the status to "Rejected",and will not reduce any leave number
                strcpy(status,"Rejected");
                sprintf(new_line,"%s||%s||%s||%s||%s||%s||%s||%d||%s\n",Detail.LeaveID,Staff.ID,Staff.name,Staff.dept,
                        Detail.LeaveType,Detail.Start_Date,Detail.End_Date,Detail.Day_Number,status);
        
                // Open file
                fptr1 = fopen("Apply_Leave.txt","r");
                fptr2 = fopen("temp.txt","w");
                if (fptr1 == NULL || fptr2 == NULL){
                    printf("Unable to open the file.\n");
                    exit(0);
                }
                // Loop through each line of the input file
                while (fgets(line, 200, fptr1) != NULL) {
                // Check if the line contains the data to be deleted
                    if (strstr(line,Check.LeaveID) != NULL) {
                        // Write the line to the temporary file if it does not contain the data to be deleted
                        fputs(new_line, fptr2);
                    }
                    else{
                        fputs(line,fptr2);
                    }
                }
                // Close file
                fclose(fptr1);
                fclose(fptr2);

                remove("Apply_Leave.txt");
                rename("temp.txt","Apply_Leave.txt");
                // Rewrite Leave Balance
                break;

                case 3:
                // As same as above , but here is change the status to "Approved", and will not reduce any leave number
                strcpy(status,"Pending");
                sprintf(new_line,"%s||%s||%s||%s||%s||%s||%s||%d||%s\n",Detail.LeaveID,Staff.ID,Staff.name,Staff.dept,
                        Detail.LeaveType,Detail.Start_Date,Detail.End_Date,Detail.Day_Number,status);
        
                // Open file
                fptr1 = fopen("Apply_Leave.txt","r");
                fptr2 = fopen("temp.txt","w");
                if (fptr1 == NULL || fptr2 == NULL){
                    printf("Unable to open the file.\n");
                    exit(0);
                }
                // Loop through each line of the input file
                while (fgets(line, 200, fptr1) != NULL) {
                // Check if the line contains the data to be deleted
                    if (strstr(line,Check.LeaveID) != NULL) {
                        // Write the line to the temporary file if it does not contain the data to be deleted
                        fputs(new_line, fptr2);
                    }
                    else{
                        fputs(line,fptr2);
                    }
                }
                // Close file
                fclose(fptr1);
                fclose(fptr2);

                remove("Apply_Leave.txt");
                rename("temp.txt","Apply_Leave.txt");
                break;

                // if above case not relevent, run default
                default:
                printf("\nPlease Enter the Correct Number!!\n");
                continue;
            }
        }while (!(choice==1 || choice ==2 ||choice ==3));
        printf("==========================================================================================\n");
        printf("\n__________ Done! Thank You! __________\n\n");
        LeaveApprover_interface(staffID,staffName,dept);
    }
}

void Search_Date_Leave(char *staffID, char *staffName, char *dept){
    //Clear the 'stdin' space
    fflush(stdin);
    // Declaration
    char Search_Date[100],line[100];
    int search_year, search_month, search_day;
    // declare the day number of each number.
    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    FILE *fptr;
    struct Leave_Detail Leave;
    struct Staff Staff;
    // Open file
    fptr=fopen("Apply_Leave.txt","r");
    if (fptr==NULL){
        printf("File does not exists");
        exit(0);
    }
    printf("\n____________________ Search Date of Leave  ____________________\n");
    printf("\n==========================================================================================\n");
    printf("\nPlease enter the Date that you want to search\n");
    printf("\nEnter \"exit\" to quit.\n");
    // Loops for getting the date until the superior input the correct date
    while(1){
        printf("Search Date (DD-MM-YYYY): ");
        fgets(Search_Date,100,stdin);
        Search_Date[strlen(Search_Date)-1]='\0';

        // If 'exit' is inputed , exit this process.
        if (strcmp(Search_Date,"exit")==0){
            // Clear the terminal.
            system("cls");
            LeaveApprover_interface(staffID,staffName,dept);
        }

        // Save the Search Date into day, month , year
        sscanf(Search_Date, "%d-%d-%d", &search_day, &search_month, &search_year);

        // Validate the date with the true format
        if(search_day<1 || search_day>31 || search_month<1 || search_month>12||search_year!=2023){
            printf("\nInvalid Date!! Please Enter the Correct Date!!\n");
            continue;
        }
        // Validate the day number in FEB depending on the year
        if ((search_year % 4 == 0 && search_year % 100 != 0) || search_year % 400 == 0) {
            days_in_month[1] = 29;
        }
        // Validate the day number in each month 
        if (search_day>days_in_month[search_month-1]){
            printf("\nInvalid Date!! The Date does not exist!!\n");
            continue;
        }
        break;
    }
    printf("\n==========================================================================================\n");
    int count=0;
    int start_year, start_month, start_day;
    int end_year, end_month, end_day;
    // Display the attributes of the table
    printf("\n_Leave ID_|_Staff ID_|_____________Name_____________|_____Leave Type_____|___Start Date___|____End Date____|_Day Number_|_______Status_______\n");
    // Loop through each line of the input file
    while(fgets(line,sizeof(line),fptr)!=NULL){
        // Read data
        sscanf(line,"%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%d||%[^||]\n",Leave.LeaveID,Staff.ID,Staff.name,Staff.dept,
        Leave.LeaveType,Leave.Start_Date,Leave.End_Date,&Leave.Day_Number,Leave.LeaveStatus);
        // Save the date into day, month, year
        sscanf(Leave.Start_Date, "%d-%d-%d", &start_day, &start_month, &start_year);
        sscanf(Leave.End_Date, "%d-%d-%d", &end_day, &end_month, &end_year);
        // Check the department
        if (strcmp(dept,Staff.dept)==0){
            // If the Search Date is in between the Start Date and End Date, Print the Leave detail.
            if ((search_year > start_year || (search_year == start_year && search_month > start_month) || (search_year == start_year && search_month == start_month && search_day >= start_day))
            && (search_year < end_year || (search_year == end_year && search_month < end_month) || (search_year == end_year && search_month == end_month && search_day <= end_day))) {
                printf("%-10s|%-10s|%-30s|%-20s|%-16s|%-16s|%-12d|%s",Leave.LeaveID,Staff.ID,Staff.name,Leave.LeaveType,
                Leave.Start_Date,Leave.End_Date,Leave.Day_Number,Leave.LeaveStatus);
                count++;
            }
        }
    }
    // Close file
    fclose(fptr);
    printf("\n==========================================================================================\n");
    printf("Total Number of the staff Applied Leave: %d\n\n",count);
    LeaveApprover_interface(staffID,staffName,dept);
}

//=============================================================================================================================
