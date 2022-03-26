#include"library_management.h"

/**
 * @brief function to view all the books
 * 
 * @return test_values 
 */
test_values view_all_records(){
    FILE *fptr;
    fptr = fopen("library_data.txt","rb");
    if(fptr==NULL){
        printf("Unable to open the file\n");
        return fail;
    }else{
        book_data *book_to_find=(book_data*)malloc(sizeof(book_data));
        while(fread(book_to_find, sizeof(book_data), 1, fptr)!='\0'){
            printf("Book ID: %d", book_to_find->book_id);
            printf("  Title: %s\n\n", book_to_find->book_title);
        }
        fclose(fptr);
        free(book_to_find);
        return pass;
    }   
}
