/*
  author: Meilian Liang 
  institution: Gxu
  Date: Oct. 1, 2017
  Goal: Select sets 
*/
#include<stdio.h>
#include"set.h"

void set_fprint(FILE *fp, set_t sset);

int main()
{
    /*variables declaration:*/
    int set_size = 0, num;
    char ch;
    set_t refset, sset;
    FILE *fin, *fout;

    /* open the input file */
    if (!(fin = fopen("list.txt", "r"))){
        printf("Error openning the input file.\n");
        exit(-1);
    }

    /* open the input file */
    if (!(fout = fopen("out.txt", "w"))){
        printf("Error openning the output file.\n");
        exit(-1);
    }

    /* read info. from file and init setlist */
    fscanf(fin, "%d\n", &set_size);   // read from the input file
    refset = set_new(set_size);      // init the reference set
    sset = set_new(set_size);        // init the input set

    /* read file and handle looply 
       read the reference set first: */
    do {
   	fscanf(fin,"%d%c",&num,&ch);
	SET_ADD_ELEMENT(refset,num);
    }while(ch != ';');
    set_print(refset);

    /* read sets looply */ 
    do {
   	fscanf(fin,"%d%c",&num,&ch);
	SET_ADD_ELEMENT(sset,num);
	if (ch == ';' || ch == '.'){
	    if (is_intersectset_empty(sset,refset))
            	set_fprint(fout, sset);
            sset = set_new(set_size);		
        }
    }while(ch != '.');
    fprintf(fout,".");
    fclose(fin);
    fclose(fout);
    return 0;
}

void set_fprint(FILE *fp, set_t sset)
{
    int i, j, cnt;

    for (i=0, cnt=0; i < SET_MAX_SIZE(sset)-1; i++){
		if (SET_CONTAINS(sset,i)){
		     cnt++;
                     if (cnt == set_size(sset))
                         fprintf(fp, "%d;\n",i);
		     else
		        fprintf(fp,"%d,",i);
                } 
    }
}
