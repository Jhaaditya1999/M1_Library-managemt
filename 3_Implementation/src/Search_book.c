#include<library_management.h>

/**
 * @brief function to find the details about a book
 * 
 * @param id 
 * @return test_values 
 */
test_values view_a_record(int id){
    FILE *fptr;
    fptr = fopen("library_data.txt","rb");
    if(fptr==NULL){
        printf("Unable to open the file\n");
        return fail;
    }else{
        book_data *book_to_find=(book_data*)malloc(sizeof(book_data));
        while(fread(book_to_find, sizeof(book_data), 1, fptr)!='\0'){
            if(id==book_to_find->book_id){
                printf("Book ID: %d\n", book_to_find->book_id);
                printf("Title: %s\n", book_to_find->book_title);
                printf("Status: %s\n", book_to_find->status);
                printf("Issued by: %s %s\n", book_to_find->member_first_name, book_to_find->member_last_name);
                printf("ID of the member: %d\n", book_to_find->member_id);
                printf("Date of issue: %s\n", book_to_find->date_of_issue);
                printf("Due date: %s\n", book_to_find->due_date);
                fclose(fptr);
                free(book_to_find);
                return pass;
            }
        }
        fclose(fptr);
        free(book_to_find);
        printf("Specified book does not exist\n");
        return fail;
    }   
}
