#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  /*
  if(!geteuid() == 0){
    printf("Sudo is required\n");
    return 2;
  }
  */
  if(argc <= 1 || strcmp(argv[1], "--help") == 0){
    printf("Useage\n  %s [Flag(s)] [Program Name]\nFlags:\n -S Install a program from the aur\n -R Delete a program\n -Q Search a installed program.\n", argv[0]);
    return 1;
  }

  if(strcmp(argv[2], "") == 0 || strcmp(argv[2], " ") == 0 || !argv[2]){
    printf("Specify a program\n");
    return 2;
  }

  char flags[8];
  strcpy(flags, argv[1]);
  char cmd[126];
  char cdcmd[50];
  char rmcmd[50];
  char srchcmd[50];

  sprintf(cmd, "git clone https://aur.archlinux.org/%s.git $HOME/.npactemp ", argv[2]);
  sprintf(cdcmd, "cd %s", argv[2]);
  sprintf(rmcmd, "pacman -R %s --noconfirm", argv[2]);
  sprintf(srchcmd, "pacman -Q %s", argv[2]);

  for(int i = 0; i < strlen(flags); i++){
    if(flags[i] == 'S' || flags[i] == 's'){
      system(cmd);
      //chdir("/home/$USER/.npactemp");
      system("cd ~/.npactemp && makepkg -si");
      system("rm -rf $HOME/.npactemp");

    } else if (flags[i] == 'R' || flags[i] == 'r'){
      system(rmcmd);
    } else if (flags[i] == 'Q' || flags[i] == 'q'){
      system(srchcmd);
    }
  }

  return 0;
}
