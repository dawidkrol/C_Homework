#include <stdio.h>

int verification(char* toCheck, char to_find)
{
    int output = 1;
    while (*toCheck != '\0')
    {
        if(*toCheck == '{' || *toCheck == '[' || *toCheck == '(')
        {
            char tf;
            if(*toCheck == '{')
                tf = '}';
            if(*toCheck == '[')
                tf = ']';
            if(*toCheck == '(')
                tf = ')';

            output = verification(toCheck + 1, tf);

            if(output)
                *toCheck = '_';
            else
                return 0;
        }
        else if(*toCheck == '}' || *toCheck == ']' || *toCheck == ')')
        {
            if(to_find == *toCheck)
            {
                *toCheck = '_';
                return 1;
            } else
                return 0;
        }
        toCheck++;
    }
    if(to_find != '\0')
        output = 0;

    return output;
}


int main() {
    char input[] = "(a) + {}({[a]*[a] + b})\0";
    int result = verification(input,'\0');
    if(result)
    {
        printf("Verified\n");
    } else
    {
        printf("Error\n");
    }
    return 0;
}
