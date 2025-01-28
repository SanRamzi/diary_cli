#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void welcome(); // Welcome user to the diary
void menu(); // Menu for the diary

int main()
{
  welcome(); // Display welcome message
  char command[100]; // Command entered by the user
  menu(); // Display the menu
  while (1)
  {
    printf("Menu> ");
    fgets(command, 100, stdin); // Get the command from the user
    if (strncmp(command, " ", 1) == 0 || strncmp(command, "\n", 1) == 0)
    {
      continue;
    }
    if (strncmp(command, "1", 1) == 0)
    {
      printf("adding\n");
    }
    if (strncmp(command, "2", 1) == 0)
    {
      printf("viewing\n");
    }
    if (strncmp(command, "help", 4) == 0)
    {
      menu();
      continue;
    }
    if (strncmp(command, "3", 1) == 0 || strncmp(command, "exit", 4) == 0 || strncmp(command, "quit", 4) == 0 || strncmp(command, "bye", 3) == 0)
    {
      puts("Goodbye!");
      return 0;
    }
    puts(command); // Display the command entered by the user
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
    printf("Please enter your name: ");
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
  puts("3. Exit");
}