#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hash = md5(plaintext,strlen(plaintext));  // hash plaintext, store in hash

    // Open the hash file
    FILE *hashed = fopen(hashFilename, "r");
     if (hashed==NULL) {
        free(hash);
        return NULL;
    }

    // Loop through the hash file, one line at a time.
     char line[1000];
    while(fgets(line, sizeof(line), hashed) != NULL){
        char *newline=strchr(line, '\n');//Sets a pointer for where the newline haracter is
        if (newline) *newline = '\0';
        if(strcmp(line, hash)==0){
            fclose(hashed);
            return(hash);
        }
    }
    fclose(hashed);
    free(hash);
    return NULL;




    // Attempt to match the hash from the file to the
    // hash of the plaintext.

    // If there is a match, you'll return the hash.
    // If not, return NULL.

    // Before returning, do any needed cleanup:
    //   Close files?
    //   Free memory?

    // Modify this line so it returns the hash
    // that was found, or NULL if not found.
    //return "0123456789abcdef0123456789abcdef";
}



int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.
    //char *found = tryWord("hello", "hashes00.txt");
    //printf("%s %s\n", found, "hello");


    // Open the dictionary file for reading.
    FILE *dict=fopen(argv[2],"r");//opens dictionary file
    

    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    int hashesCracked=0;
    while(!feof(dict)){
        char word[1000];//makes a string to holf the word
        fgets(word,1000,dict);//takes in the word
        char *newline=strchr(word,'\n');//Sets a pointer for where the newline haracter is
        if (newline!=NULL) {
            *newline='\0';//sets it to null
        }
        if(tryWord(word,argv[1])){
            hashesCracked++;
            char *found = tryWord(word,argv[1]);
            printf("%s %s\n",found,word);
        }
    }

    // If we got a match, display the hash and the word. For example:
    //   5d41402abc4b2a76b9719d911017c592 hello
    
    // Close the dictionary file.
    fclose(dict);
    // Display the number of hashes that were cracked.
    printf("%d hashes cracked",hashesCracked);
    // Free up any malloc'd memory?
    //free(found);
}

