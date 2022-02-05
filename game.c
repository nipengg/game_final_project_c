#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char s[5][100];
char r[5][100];
char w[5][100];

void gameWord()
{
    char keyword[10];
    int i = 0;
    FILE *fp;
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("Error Accessing File\n");
        exit(1);
    }
    while (fscanf(fp, "%s\n", keyword) != EOF)
    {
        strcpy(r[i], keyword);
        strcpy(w[i], keyword);
        ++i;
    }
    fclose(fp);
}

void swap(char *str1, char *str2)
{
    char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
    free(temp);
}

void randomize(int n)
{
    // Pakai seed beda biar ga sama terus
    srand ( time(NULL) );
    for (int i = 0; i < 16; i++)
    {
        int j = rand() % 16;
        swap(w[i], w[j]);
    }
}

void gen_random(char *t, int len)
{
    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < len; j++)
        {
            t[j] = alphabet[rand() % (sizeof(alphabet) - 1)];
        }
    }
    t[len] = 0;
}

void generate()
{
    int newLine = 1, ln = 0;
    printf("\n=============================\n");
    for (int i = 0; i < 16; i++)
    {
        char *t[5];
        gen_random(t, 5);
        if (newLine == 4)
        {
            printf("%s\n", t);

            if (ln == 3)
            {
                printf("=============================\n");

            }
            else
            {
                printf("------|-------|-------|------\n");
                newLine = 0;
            }
            ln++;
        }
        else
        {
            printf("%s | ", t);
        }
        newLine++;
        strcpy(s[i], t);
    }
    printf("Success Generate New Words!\n\n");
}

void save()
{
    FILE *fp;
    fp = fopen("data.txt", "w");
    for (int i = 0; i < 16; i++)
    {
        fprintf(fp, "%s\n", s[i]);
    }
    fclose(fp);
    printf("\nSuccess save New Words!\n\n");
}

void game()
{
    system("cls");
    char keyword[10], player[50];
    char opt, opt2;
    int newLine = 1, ln = 0;
    FILE *fp;
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("Error Accessing File\n");
        exit(1);
    }
    printf("=============================\n");
    while (fscanf(fp, "%s\n", keyword) != EOF)
    {
        if (newLine == 4)
        {
            printf("%-5s\n", keyword);

            if (ln == 3)
            {
                printf("=============================\n");

            }
            else
            {
                printf("------|-------|-------|------\n");
                newLine = 0;
            }
            ln++;
        }
        else
        {
            printf("%-5s | ", keyword);
        }
        newLine++;
    }

    printf("Apakah anda sudah siap bermain [Y/T]?");
    scanf(" %c", &opt);

    if (opt == 'Y')
    {
        system("cls");
        printf("Masukan nama pemain : ");
        scanf(" %s", player);
        int newLine = 1, ln = 0;
        printf("========================\n");
        for (int i = 1; i <= 16; i++)
        {
            if (newLine == 4)
            {
                printf("  %d\n", i);

                if (ln == 3)
                {
                    printf("========================\n");
                }
                else
                {
                    printf("----|-----|-----|------\n");
                    newLine = 0;
                }
                ln++;
            }
            else
            {
                printf("%3d | ", i);
            }
            newLine++;
        }
        printf("Game dimulai..\n");
        gameWord();
        randomize(16);
        int answer, step = 16, i = 0, playerScore = 0, botScore = 0, botCheck = 1;

        while (step > 0)
        {
            if (botCheck % 2 == 0)
            {
                srand(time(NULL));
                int botVal = 1 + rand() % 16;
                printf("Dikotak manakah tulisan %s berada?\n", w[i]);
                printf("Giliran komputer menebak kotak : %d\n", botVal);
                --botVal;
                if (strcmp(w[i], r[botVal]) == 0)
                {
                    botScore = botScore + 10;
                }
                else
                {
                    botCheck--;
                }
            }
            else
            {
                printf("Dikotak manakah tulisan %s berada?\n", w[i]);
                printf("Giliran %s menebak kotak : ", player);
                scanf("%d", &answer);
                --answer;
                if (strcmp(w[i], r[answer]) == 0)
                {
                    playerScore = playerScore + 10;
                }
                else
                {
                    botCheck++;
                }
            }
            ++i;
            --step;
            printf("\n");
        }

        if (playerScore > botScore)
        {
            printf("Pemenangnya adalah %s\n", player);
        }
        else if (playerScore == botScore)
        {
            printf("Player dan Komputer seri\n");
        }
        else
        {
            printf("Pemenangnya adalah Komputer\n");
        }
        printf("Player Score : %d\n", playerScore);
        printf("Bot Score : %d\n", botScore);

        printf("Apakah anda ingin menyimpan score[Y/N]?");
        scanf(" %c", &opt2);

        if (opt2 == 'Y')
        {
            FILE *fptr;
            fptr = fopen("score.txt", "a");

            if (playerScore > botScore)
            {
                fprintf(fptr, "%s %d\n", player, playerScore);
            }
            else if (playerScore < botScore)
            {
                fprintf(fptr, "%s %d\n", "Kompie", botScore);
            }
            else
            {
                printf("Player dan Komputer seri\n");
            }
            fclose(fptr);
            printf("\nSuccess save score!\n\n");
        }
        system("pause");
    }
    printf("Terima Kasih!\n\n");
    fclose(fp);
    system("cls");
}

void leaderboard()
{

}

int main()
{
    system("cls");
    int menu;
	do
    {
        printf("1. Generate Kata\n");
        printf("2. Simpan hasil generate kata\n");
        printf("3. Mulai Permainan\n");
		printf("4. Tampilkan nama pemenang\n");
        printf("5. Exit\n");

        printf("Enter Menu : ");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            generate();
            break;

        case 2:
            save();
            break;

        case 3:
            game();
            break;

		case 4:
            leaderboard();
            break;
        }
    } while (menu != 5);
}
