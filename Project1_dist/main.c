#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h>

#include "util.h"

void show_error_message(char * ExecName) {
  fprintf(stderr, "Usage: %s [options] [target] : only single target is allowed.\n", ExecName);
  fprintf(stderr, "-f FILE\t\tRead FILE as a makefile.\n");
  fprintf(stderr, "-h\t\tPrint this message and exit.\n");
  exit(0);
}

int main(int argc, char *argv[]) {
  target_t targets[MAX_NODES];
  int nTargetCount = 0;

  /* Variables you'll want to use */
  char Makefile[64] = "Makefile";
  char TargetName[64];

  /* Declarations for getopt */
  extern int optind;
  extern char * optarg;
  int ch;
  char * format = "f:h";

  while((ch = getopt(argc, argv, format)) != -1) {
    switch(ch) {
      case 'f':
        strcpy(Makefile, strdup(optarg));
        break;
      case 'h':
      default:
        show_error_message(argv[0]);
        exit(1);
    }
  }

  argc -= optind;
  if(argc > 1) {
    show_error_message(argv[0]);
    return -1;
  }

  /* Init Targets */
  memset(targets, 0, sizeof(targets));

  /* Parse graph file or die */
  if((nTargetCount = parse(Makefile, targets)) == -1) {
    return -1;
  }

  /* Comment out the following line before submission */
  show_targets(targets, nTargetCount);

  /*
   * Set Targetname
   * If target is not set, set it to default (first target from makefile)
   */
  if(argc == 1) {
    strcpy(TargetName, argv[optind]);
  } else {
    strcpy(TargetName, targets[0].TargetName);
  }

  /*
   * Now, the file has been parsed and the targets have been named.
   * You'll now want to check all dependencies (whether they are 
   * available targets or files) and then execute the target that 
   * was specified on the command line, along with their dependencies, 
   * etc. Else if no target is mentioned then build the first target 
   * found in Makefile.
   */

  /*
	we will be calling the command using --> execvp("Path",**build_argv(target.Command),(char *) NULL) .
	
	local variable TargetName holds the either a given target from the terminal or the first target
	name in the make file.
	
	// START OF OUR CODE:
	
	int target_index = find_target(TargetName, targets, nTargetCount);
	// check find_target success
	if (target_index == -1){
		return -2;  // should be -1, but for troubleshooting might be easier to see problem for now at -2
	}
	// else TargetName is in targets
	
	// loop through target dependencies, the body of this loop will likely use fork, wait, and maybe exec?
	
	for(int i = 0, i< targets[target_index].DependencyCount; i++){
		TargetName??? or new char pointer = targets[target_index].DependencyNames[i][];
	// might need two loops, not sure how to access the char string at index [i][0-64], is it just 0? or what...
	}
  
  
   * INSERT YOUR CODE HERE
   */

  return 0;
}
