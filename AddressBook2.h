/*****************  Addressbook Entry Data Structure   **************/
struct contact
{
    char name[30];
    char age[3];                                               /* name of the contact */  
    char mobile[12];                                           /* mobile number of the contact */
    char address[40];                                          /* home address of the contact */
    struct contact *next;                                      /* pointer to next entry */
 };
/********************  Sub-fuction Declaration   ******************/
int  addr_command();                                           /* Command line */
void addr_list(struct contact *front);                         /* Display all the address entries */
void addr_cd();                                                /* enter a document*/
void addr_cat();     					       /* display address entries by name */	
void inputs(char *prompt, char *valueAddr, int max);           /* Input function */        
void addr_add();                                               /* Add an address entry */
struct contact *node_add(struct contact *info);                /* Add a node to linklist */  
void addr_remove();                                            /* Delete address entry by name */
void addr_help();                                              /* Help information */
int  addr_save(int argc);                                      /* Save to an ab file */
int  addr_load();                                              /* Reload an ab file */
void iskeydul(struct contact *info, struct contact *front);    /* judge the identical key*/
int  addr_search(int choice);                                  /* search the given entry by the name*/
void validate_arg(int argc, char **argv);                      /* Validate command line arguments */
