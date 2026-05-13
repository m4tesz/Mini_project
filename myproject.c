#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "v1.0"

typedef char* string;

int file_exists(const char *filename)   //ezaltal nem irodik felul a fajl, ha mar letezik
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

    fprintf(f, "int main()\n");
    fprintf(f, "{\n");
    fprintf(f, "    printf(\"[C] Hello World\\n\");\n");
    fprintf(f, "    return 0;\n");
    fprintf(f, "}\n");
}

void bash_template(FILE *f)
{
    fprintf(f, "#!/bin/bash\n\n");
    fprintf(f, "echo \"[BASH] Hello World\"\n");
}

void java_template(FILE *f)
{
    fprintf(f, "public class Program {\n\n");
    fprintf(f, "    public static void main(String[] args) {\n");
    fprintf(f, "        System.out.println(\"[JAVA] Hello World\");\n");
    fprintf(f, "    }\n");
    fprintf(f, "}\n");
}

void help()
{
    printf("myproject %s\n\n", VERSION);

    printf("Options:\n\n");

    printf("myproject <template> [--stdout]\n\n");

    printf("Templates:\n");
    printf("c       -> C source [program.c]\n");
    printf("java    -> Java source [program.java]\n");
    printf("sh      -> Bash source [program.sh]\n\n");

    printf("Options:\n");
    printf("-h --help       Show help\n");
    printf("-v              Show version\n");
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

    if (strcmp(argv[1], "-v") == 0)
    {
        printf("myproject %s\n", VERSION);
        return 0;
    }

    string language = argv[1];
    FILE *output = NULL;
    int is_stdout = (argc > 2 && strcmp(argv[2], "--stdout") == 0);
    char *filename = NULL;

    if (strcmp(language, "c") == 0)
        filename = "program.c";
    else if (strcmp(language, "java") == 0)
        filename = "Program.java";
    else if (strcmp(language, "sh") == 0)
        filename = "program.sh";
    else
    {
        printf("Unknown template: %s\n", language);
        return 1;
    }

    if (is_stdout)
    {
        output = stdout;
    }
    else
    {
        if (file_exists(filename))
        {
            printf("File already exists: %s\n", filename);
            return 1;
        }

        output = fopen(filename, "w");

        if (!output)
        {
            printf("Error opening file!\n");
            return 1;
        }
    }

    if(strcmp(language, "c") == 0)
        c_template(output);
    else if (strcmp(language, "java") == 0)
        java_template(output);
    else if (strcmp(language, "sh") == 0)
        bash_template(output);

    if (!is_stdout)
    {
        fclose(output);
        printf("Created: %s\n", filename);
    }

    return 0;
}
