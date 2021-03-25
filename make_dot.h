#ifndef _MAKE_DOT__H_
#define _MAKE_DOT__H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_FILENAME_NUM 30

struct tree {
	struct tree* left;
	struct tree* right;
	struct tree* parent;
	int number;
	bool passed;
};

bool make_dot (struct tree *root, char *dest, bool let_only_img);
/* 
   This function creates a visualisation of a tree using dot program. The user has to pass the root of the binary tree
   and a destination to where the .dot and .png files are going to be stored.  
*/
void write_dot (struct tree *root, FILE *dot);
/*
   This function writes to the .dot file recursively.
*/

#endif
