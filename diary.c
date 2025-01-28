#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct // Structure for the diary entry
{
  char date[100];
  char time[100];
  char entry[2000];
} diary_entry;

void welcome(); // Welcome user to the diary
void menu();    // Menu for the diary

int main()
{
  welcome();         // Display welcome message
  char command[100]; // Command entered by the user
  menu();            // Display the menu
  while (1)
  {
    fputs("Menu> ", stdout);
    fgets(command, 100, stdin); // Get the command from the user
    if (strncmp(command, " ", 1) == 0 || strncmp(command, "\n", 1) == 0)
    {
      continue;
    }
    if (strncmp(command, "1", 1) == 0)
    {
      puts("Adding entry to diary");
      fputs("Please type in your entry: ", stdout);
      char entry[2000]; // Diary entry
      fgets(entry, 2000, stdin);
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      char date[100];
      sprintf(date, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
      char time[100];
      sprintf(time, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
      diary_entry new_entry;
      strcpy(new_entry.entry, entry);
      strcpy(new_entry.date, date);
      strcpy(new_entry.time, time);
      FILE *file = fopen("diary", "a");
      fwrite(&new_entry, sizeof(diary_entry), 1, file);
      fclose(file);
      continue;
    }
    if (strncmp(command, "2", 1) == 0)
    {
      while (1)
      {
        FILE *file = fopen("diary", "r");
        if (file == NULL)
        {
          puts("No entries found in the diary!");
          break;
        }
        puts("Type 1 to view today's entries");
        puts("Type 2 to view all entries");
        puts("Type 3 to go back to the menu");
        fputs("View> ", stdout);
        char view_command[100]; // Command to view the diary entries
        fgets(view_command, 100, stdin);
        if (strncmp(view_command, " ", 1) == 0 || strncmp(view_command, "\n", 1) == 0)
        {
          continue;
        }
        if (strncmp(view_command, "3", 1) == 0)
        {
          break;
        }
        if (strncmp(view_command, "1", 1) == 0)
        {
          diary_entry entry;
          while (fread(&entry, sizeof(diary_entry), 1, file))
          {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            char date[100];
            sprintf(date, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
            if (strncmp(entry.date, date, 10) == 0)
            {
              printf("Date: %s\n", entry.date);
              printf("Time: %s\n", entry.time);
              printf("Entry: %s\n", entry.entry);
            }
          }
          fclose(file);
          continue;
        }
        if (strncmp(view_command, "2", 1) == 0)
        {
          FILE *file = fopen("diary", "r");
          diary_entry entry;
          while (fread(&entry, sizeof(diary_entry), 1, file))
          {
            printf("Date: %s\n", entry.date);
            printf("Time: %s\n", entry.time);
            printf("Entry: %s\n", entry.entry);
          }
          fclose(file);
          continue;
        }
      }
      continue;
    }
    if (strncmp(command, "3", 1) == 0)
    {
      puts("Removing entry from diary");
      fputs("Please enter the date of the entry you want to remove (YYYY-MM-DD): ", stdout);
      char date[100];
      fgets(date, 100, stdin);
      FILE *show = fopen("diary", "r");
      diary_entry entry;
      int count = 1;
      while (fread(&entry, sizeof(diary_entry), 1, show))
      {
        if (strncmp(entry.date, date, 10) == 0)
        {
          printf("Entry %d\n", count);
          printf("Date: %s\n", entry.date);
          printf("Time: %s\n", entry.time);
          printf("Entry: %s\n", entry.entry);
          count++;
        }
      }
      fclose(show);
      fputs("Please enter the entry number you want to remove (0 to exit): ", stdout);
      int entry_number;
      scanf("%d", &entry_number);
      getchar(); // Consume the newline character
      if (entry_number == 0 || entry_number < 0 || entry_number >= count)
      {
        continue;
      }
      FILE *file = fopen("diary", "r");
      FILE *temp = fopen("temp", "w");
      count = 1;
      while (fread(&entry, sizeof(diary_entry), 1, file))
      {
        if (count != entry_number)
        {
          fwrite(&entry, sizeof(diary_entry), 1, temp);
        }
        if (strncmp(entry.date, date, 10) == 0)
        {
          count++;
        }
      }
      fclose(file);
      fclose(temp);
      remove("diary");
      rename("temp", "diary");
      puts("Entry removed successfully!");
      continue;
    }
    if (strncmp(command, "4", 1) == 0 || strncmp(command, "help", 4) == 0)
    {
      menu();
      continue;
    }
    if (strncmp(command, "5", 1) == 0 || strncmp(command, "exit", 4) == 0 || strncmp(command, "quit", 4) == 0 || strncmp(command, "bye", 3) == 0)
    {
      puts("Goodbye!");
      return 0;
    }
  }
  return 0;
}
// Welcome user to the diary
void welcome()
{
  FILE *file = fopen("user", "r");
  if (file == NULL) // If the file does not exist
  {
    puts("Welcome to your diary!");
    puts("It seems like this is your first time.");
    fputs("Please enter your name: ", stdout);
    char name[100]; // Name of the user
    scanf("%s", name);
    file = fopen("user", "w");
    fprintf(file, "%s", name); // Write the name to the file
    fclose(file);
  }
  else
  {
    char name[100]; // Name of the user
    fscanf(file, "%s", name);
    printf("Welcome back, %s!\n", name); // Display the name of the user
    fclose(file);
  }
}
// Menu for the diary
void menu()
{
  puts("1. Add");
  puts("2. View");
  puts("3. Remove");
  puts("4. Help");
  puts("5. Exit");
}