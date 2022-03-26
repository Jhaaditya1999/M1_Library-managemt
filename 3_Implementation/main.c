/**
 * @file main.c
 * @author Rahul (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include"library_management.h"

/**
 * @brief main function of the project
 * 
 * @return int 
 */
int main()
{
    int ch, success, ID, new_member_id;
    char new_status[10], new_date_of_issue[10], new_due_date[10], new_member_first_name[10],new_member_last_name[10], new_title[20];
    printf("1. Add books\n2. View books\n3. Search books\n4. Update book records\n5. Delete books\n");
    printf("Enter the choice\n");
    scanf("%d",&ch);
    if(ch == 1)
    {
        printf("Enter the book id\n");
        scanf("%d",&ID);
        fflush(stdin);
        printf("Enter name of the book\n");
        gets(new_title);
        success = enter_new_record(ID, new_title);
    }
    else if(ch == 2)
    {
        success = view_all_records();
    }
    else if(ch == 3)
    {
        printf("Enter the book id to search\n");
        scanf("%d",&ID);
        success = view_a_record(ID);
    }
    else if(ch == 4)
    {
        printf("Enter the book id to update\n");
        scanf("%d",&ID);
        success = view_a_record(ID);
        if(success == 1){
            printf("Enter new status\n");
            scanf("%s", new_status);
            printf("Enter new date of issue\n");
            scanf("%s", new_date_of_issue);
            printf("Enter new due date\n");
            scanf("%s", new_due_date);
            printf("Enter first name of member\n");
            scanf("%s", new_member_first_name);
            printf("Enter last name of member\n");
            scanf("%s", new_member_last_name);
            printf("Enter member ID\n");
            scanf("%d", &new_member_id);
            success=update_record(ID, new_status, new_date_of_issue, new_due_date, new_member_first_name,new_member_last_name, new_member_id);
        }
    }
    else if (ch==5)
    {
        printf("Enter book id to delete\n");
        scanf("%d",&ID);
        success=delete_record(ID);
    }
    else
    {
        printf("Wrong I/p\n");
    }
    if(success == pass)
    {
        printf("successful\n");
    }
    else if(success == fail)
    {
        printf("unseccessful\n");
    }
    else
    {
        printf("Error\n");
    }
    return 0;
}
