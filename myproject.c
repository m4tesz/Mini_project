#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "v1.0"

typedef char* string;

void help();
void c_template(FILE *f);
void bash_template(FILE *f);
void java_template(FILE *f);

int file_exists(const char *filename)
{
    FILE *f = fopen(filename, "r");

    if (f)
    {
        fclose(f);
        return 1;
    }

    return 0;
}

void c_template(FILE *f)
{
    fprintf(f, "#include <stdio.h>\n\n");
    fprintf(f, "void greet()\n");
    fprintf(f, "{\n");
    fprintf(f, "    printf(\"Welcome to the C template!\\n\");\n");
    fprintf(f, "}\n\n");

    fprintf(f, "int main()\n");
    fprintf(f, "{\n");
    fprintf(f, "    greet();\n");
    fprintf(f, "    return 0;\n");
    fprintf(f, "}\n");
}

void bash_template(FILE *f)
{
    fprintf(f, "#!/bin/bash\n\n");
    fprintf(f, "echo 'System information script'\n");
    fprintf(f, "echo 'Current user:' $USER\n");
    fprintf(f, "echo 'Current directory:' $(pwd)\n");
}

void java_template(FILE *f)
{
    fprintf(f, "public class Program {\n");
    fprintf(f, "\n");
    fprintf(f, "    public static void printMessage() {\n");
    fprintf(f, "        System.out.println(\"Java template started!\");\n");
    fprintf(f, "    }\n\n");

    fprintf(f, "    public static void main(String[] args) {\n");
    fprintf(f, "        printMessage();\n");
    fprintf(f, "    }\n");
    fprintf(f, "}\n");
}

void help()
{
    printf("maker %s\n\n", VERSION);

    printf("Usage:\n");
    printf("maker <template> [--stdout]\n\n");

    printf("Templates:\n");
    printf("c       -> C source [program.c]\n");
    printf("java    -> Java source [Program.java]\n");
    printf("sh      -> Bash script [program.sh]\n\n");

    printf("Options:\n");
    printf("-h --help       Show help\n");
    printf("-v              Version info\n");
}

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        help();
        return 0;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        help();
        return 0;
}