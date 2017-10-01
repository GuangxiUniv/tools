#include<stdio.h>
#include"set.h"
#define INIT_LIST_SIZE 3000
#define RESIZE_STEP  500

typedef struct{
   set_t *elem;
   int length;
   int listsize;
}setlist_t;

void init_setlist(setlist_t *psl, int n);
void setlist_print(setlist_t sl);
void setlist_fprint(setlist_t sl);
void setlist_addset(setlist_t *psl, set_t sset);

int main()
{
    /*variables declaration:*/
    int set_size = 0, num;
    char ch;
    setlist_t sl; set_t refset, sset;
    /* open the input file */

    FILE *fp;

    /* open the input file */
    if (!(fp = fopen("list.txt", "r"))){
        printf("Error openning the file.\n");
        exit(-1);
    }

    /* read info. from file and init setlist */
    fscanf(fp, "%d\n", &set_size);   // read from the input file
    init_setlist(&sl, set_size);     // init setlist
    refset = set_new(set_size);      // init the reference set
    sset = set_new(set_size);
    setlist_print(sl);

    /* read file and handle looply */
    do {
   	fscanf(fp,"%d%c",&num,&ch);
	SET_ADD_ELEMENT(refset,num);
    }while(ch != ';');
    set_print(refset); 
    do {
   	fscanf(fp,"%d%c",&num,&ch);
//        printf("num=%d,c =%c\n",num, ch);
	SET_ADD_ELEMENT(sset,num);
	if (ch == ';' || ch == '.'){
	    if (is_intersectset_empty(sset,refset))
            	setlist_addset(&sl, sset);
            sset = set_new(set_size);		
        }
    }while(ch != '.');
    setlist_fprint(sl);
    //set_print(refset); 


    return 0;
}

void init_setlist(setlist_t *psl, int set_size)
{
    if (!psl)
        psl = (setlist_t *)malloc(sizeof(setlist_t));
    psl->length = 0;
    psl->listsize = INIT_LIST_SIZE;

    if (!(psl->elem = (set_t *)malloc(INIT_LIST_SIZE * sizeof(set_t)))){
        printf("Error allocating memory\n");
        exit(-2);
    }
}

void setlist_print(setlist_t sl)
{
    int i;
    printf("len:%d,list_size:%d. set list is :\n", sl.length, sl.listsize);

    for (i=0; i<sl.length; i++)
        set_print(sl.elem[i]);
}

void setlist_fprint(setlist_t sl)
{
    int i, j;
    FILE *fp;
    if (!(fp = fopen("out.txt","w")))
	printf("Error openning the file!\n");
    printf("len:%d,list_size:%d. set list is printed in the file \"out.txt\"\n", sl.length, sl.listsize);

    for (i=0; i<sl.length; i++){
	for (j=0; j<SET_MAX_SIZE(sl.elem[i]); j++)
		if (SET_CONTAINS(sl.elem[i],j))
		     fprintf(fp," %d",j);
	fprintf(fp,"\n");
    }
}

void setlist_addset(setlist_t *psl, set_t sset)
{
    if (psl->length >= psl->listsize)
	if (!(psl->elem=realloc(psl->elem,(INIT_LIST_SIZE+RESIZE_STEP)*sizeof(set_t)))){
	   printf("Error reallocating memory!\n");
 	   exit(-2);
        }
    psl->elem[psl->length] = sset;
    psl->length++;
}
