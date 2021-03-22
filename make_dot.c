#include "make_dot.h"

bool make_dot (struct tree *root, char *dest, bool let_only_img) {
	FILE *dot=NULL;
	int i, j;
	char fname_dot[120], fname_png[120];
	char *temp;
	pid_t child;

	strcpy(fname_dot, dest);
	strcpy(fname_png, fname_dot);
	if (30-strlen(fname_dot)<5) {
		fprintf(stderr, "\nerror: Very long .dot filename. Aborting\n");
		return false;
	}
	if (30-strlen(fname_png)<5) {
		fprintf(stderr, "\nerror: Very long .png filename. Aborting\n");
		return false;
	}
	strcpy(&fname_dot[strlen(fname_dot)], ".dot");
	strcpy(&fname_png[strlen(fname_png)], ".png");
	dot = fopen(fname_dot, "wb");
	if (!dot) {
		for (i=strlen(fname_dot)-1;i>=0;i++) {
			if (fname_dot[i] == '/') {
				j = i;
				break;
			}
		}
		temp = calloc (j, sizeof(char));
		if (!temp) {
			return false;
		}
		strncpy(temp, fname_dot, j);
		if (mkdir(temp, 0777)) {
			fprintf(stderr, "error: %s folder could not be created!\n", temp);
			return false;
		}
		dot = fopen(fname_dot, "wb");
	}
	fprintf(dot, "digraph Tree {\n");
	write_dot (root, dot);
	fprintf(dot, "}\n");
	fclose(dot);
	child = fork();
	if (!child) {
		execl("/usr/bin/dot", "dot", "-T", "png", fname_dot, "-o", fname_png, NULL);
	}
	waitpid(child, NULL, 0);
	if (let_only_img) {
		if (remove (fname_dot)) {
			fprintf(stderr, "\nerror: %s not removed!\n", fname_dot);
		}
	}
	return true;
}

void write_dot (struct tree *root, FILE *dot) {
	if (!root) {
		return; 
	}
	fprintf(dot, "\t%d;\n", root->number);
	if (root->left) {
		fprintf(dot, "\t%d->%d;\n", root->number, root->left->number);
	}
	if (root->right) {
		fprintf(dot, "\t%d->%d;\n", root->number, root->right->number);
	}
	write_dot(root->left, dot);
	write_dot(root->right, dot);
}