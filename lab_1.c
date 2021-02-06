#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    char lname[50];
    int assigment;
    int finalExam;
    int total; 
    int *quiz;
} students;

students *readData(FILE *in, int *noOfRecords, int *noOfQuiz)
{
    students *ptr;
    int i,j;
    
    //Get number of students, number of quizzes.
    fscanf(in, "%d %d", noOfRecords, noOfQuiz);

    ptr = (students *) malloc(sizeof(students) * (*noOfRecords));
    
    for(i=0; i< *noOfRecords; i++)
    {
        ptr[i].quiz = (int *) malloc(sizeof(int) * (*noOfQuiz));
        
        //Scan name and assignment
        fscanf(in, "%s %d", ptr[i].lname, &ptr[i].assigment);
        
        // Finds sum of quiz scores
        int quizsum = 0;
        for(j = 0; j< *noOfQuiz; j++)
        {
            fscanf(in, "%d", &ptr[i].quiz[j]);
            quizsum += ptr[i].quiz[j]; 
        }

        // read final exam 
        fscanf(in, "%d", &ptr[i].finalExam);

        //Assign total socre
        ptr[i].total = ptr[i].assigment + ptr[i].finalExam + quizsum;
    
    }
    return ptr;

}

int main()
{
    students *ptr;
    FILE *inFile, *outFile;
    int noOfRecords, noOfQuiz,i;

    inFile = fopen("input.txt", "r");
    
    // Check to make sure file was opened properly. 
    if(inFile != NULL)
    {
        printf("Reading data from input.txt ...");
        ptr = readData(inFile, &noOfRecords, &noOfQuiz);
    }
    else // If not opened, kill the program. 
    {
        printf("Please provide input file.");
        exit(-1);
    }
    
    printf("\nReading completed. showing the summary.");
    printf("\n(LastName, Total Score)");
    
    //Printing all students 
    for (i = 0; i < noOfRecords; i++)
    {
        printf("\n(%s, %d)", ptr[i].lname, ptr[i].total);
    }
    
    printf("\n\nStudents with highest total score:\n");

    //Find Highest scoring student:
    int max_score = 0;
    int max_score_index = 0;

    for (i = 0; i < noOfRecords; i++)
    {
        if (ptr[i].total > max_score)
        {
            max_score = ptr[i].total;
            max_score_index = i;
        } 
    }

    outFile = fopen("output.txt", "w");

    //Printing maximum scoring student
    fprintf(outFile, "(%s,%d)", ptr[max_score_index].lname, ptr[max_score_index].total);
    printf("(%s,%d)", ptr[max_score_index].lname, ptr[max_score_index].total);
    printf("\n");

    //Free allocated memory.
    for (i = 0; i < noOfRecords; i++)
    {
        free(ptr[i].quiz);
    }
    
    free(ptr);
    fclose(outFile);
    fclose(inFile);

    return 0;    
}