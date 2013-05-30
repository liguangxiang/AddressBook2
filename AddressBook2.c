/****************************AddressBook designed by Li Guangxiang*******************/
/***************************************************************2013.5.29************/
/***************************** Include Header Files *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AddressBook2.h"

/************************** Global Variable Definition *****************************/
struct contact *front, *rear;       /* front & tail pointer of the address linklist */
int addr_num = 0;                   /* number of address entries */
struct contact *addr_info[20];      /* search result */
char file_name[100];                /* file name record */
char command[30];
int flag=0;                         /* check whether enter the document*/
int cd_num=0;
/***********************************************************
Function name  :   main(int argc, char **argv)
Function       :   all the act 
***********************************************************/
int main(int argc, char **argv)
{
    FILE *cf_ptr;
    validate_arg(argc, argv);
    if (argc == 3)
	{
        if ((strcmp(&argv[2][0], "-new")) == 0)
		{
        	if ((cf_ptr = fopen(&argv[1][3], "w+")) == NULL)
			{
        		printf("Could not open file! First create Failed! \n");
        		return 1;
            }
            printf("First create OK!\n");
            strcpy(file_name, &argv[1][3]);
        }
    printf("The file path and name is: %s\n", &argv[1][3]);
    }
    if (argc == 2)
	{
    	if ((cf_ptr = fopen(&argv[1][3], "r+")) == NULL)
		{
			printf("Could not open file! \n");
			printf("The file which you assigned may be NOT exist.\n");
			return 1;	
                }
            printf("Open file: %s successfully!\n", &argv[1][3]);            
            strcpy(file_name, &argv[1][3]);
    }
    printf("****************************************************\n");
    printf("************** Welcome to AddressBook **************\n");
    printf("****************************************************\n");
    printf("\n");
    while (1)
	{
        switch (addr_command())
		{
		case 1:    addr_list(front); 
                           break;
	        case 2:    addr_cd();
		           flag=1;
		           cd_num=1;
		           break;
		case 3:    addr_cat(); 
                           break;
                case 4:    if (1==flag)
			       addr_add();
			   else
		              printf("Sorry,You have to go to a directory first !\n"); 
                           break;
                case 5:    if (1==flag)
			      addr_remove(); 
			   else
			      printf("Sorry,You have to go to a directory first !\n"); 
                           break; 
	        case 6:    addr_save(argc); 
			   flag=0;
                           break;
                case 7:    addr_load();
			   flag=0;
                           break;
	        case 8:    addr_help(); 
                           break;
	        case 9:    return(0);
                           break;
		default :
			printf("Invalid command\n");
                  }
   }
}
/***********************************************************
Function name  :   addr_command()
Function       :   receive the command and then act
***********************************************************/
int addr_command()
{
    int choice=10;
    printf("ab>");  
    fgets(command, sizeof(command), stdin);  
    command[strlen(command) - 1] = '\0';
    while (strcmp(command, "ls") && strncmp(command, "cd",2) && strncmp(command, "cat",3) && strcmp(command, "add") 
		&& strcmp(command, "remove") && strcmp(command, "save")  && strcmp(command,"load") 
		&& strcmp(command, "!help") && strcmp(command, "!quit"))
	{
        printf("%s: COMMAND NOT FOUND !\n", command);
        printf("Please type '!help' to get more help.\n");
        printf("ab>");
        fgets(command, sizeof(command), stdin);  
        command[strlen(command) - 1] = '\0';
        }
    if (!strcmp(command, "ls"))     choice = 1;
    if (!strncmp(command, "cd",2))  choice = 2;
    if (!strncmp(command, "cat",3)) choice = 3;
    if (!strcmp(command, "add"))    choice = 4;
    if (!strcmp(command, "remove")) choice = 5;
    if (!strcmp(command, "save"))   choice = 6;
    if (!strcmp(command, "load"))   choice = 7;
    if (!strcmp(command, "!help"))  choice = 8;
    if (!strcmp(command, "!quit"))  choice = 9;	
    return(choice);
}
/*******************************************************************
Function name  :   addr_list(struct contact *front)
Function       :   list all the entries by name in the addressbook
*********************************************************************/
void addr_list(struct contact *front)
{
    struct contact *p;
    p = front;
    if(front != NULL)
    {
        do
	{
            printf("%s\n", p->name);
            p = p->next;
        }while (p != NULL);
    }
	else  
	{
		if (cd_num==1)
		{
			printf("There is no entry in the addressbook\n");
			printf("You can type commond \"add\" to create an entry\n");
		}
		else
			printf("ab>entries\n");
	}
}
/*******************************************************************
Function name  :   addr_cd()
Function       :   enter a document
*********************************************************************/
void addr_cd()
{
	if(strstr(command , "entries") == NULL)
		printf("NO Such document\n");
}
/*****************************************************************
Function name  :   addr_cat()
Function       :   display a detail information of a entry
******************************************************************/
void addr_cat()
{
    int result;
    int i=0;
    if (!(result = addr_search(1)))
	{
        printf("NAME TO BE CAT NOT FOUND!\n\n");
        }
    else
	{
		 for (i = 0; i < result; i++)
		 {
			 printf(" \"%s\", {\"age\": %s, \"mobile\": \"%s\", \"address\": \"%s\" }\n",(*addr_info)->name,(*addr_info)->age, (*addr_info)->mobile,(*addr_info)->address);
			 (*addr_info)++;
		 }
	 }    
}
/*************************************************************
Function name  :   addr_add()
Function       :   add a new entry to the addressbook
*************************************************************/
void addr_add()
{
    struct contact *info;
    info = (struct contact *)malloc(sizeof(struct contact));
    if (info == NULL)
	{ 
        printf("\nOut of memory!\n");
        return;
        }
    inputs("key:", info->name, 15);
    iskeydul(info,front);                      
    inputs("age:", info->age, 3);
    inputs("mobile:", info->mobile, 12);
    inputs("address:", info->address, 40);    
    info = node_add(info);
    if (addr_num == 0) front = info; 
    addr_num++;
    printf("value: { \"age\": %s, \"mobile\" : \"%s\", \"address\" : \"%s\" }\n",info->age,info->mobile,info->address);
    printf("Address entry added.\n");
}
/***********************************************************
Function name  :   node_add(struct contact *info)
Function       :   add a new node(entry) to the linklist
***********************************************************/
struct contact *node_add(struct contact *info)
{
    if (rear) 
        rear->next = info;
    info->next = NULL;
    rear = info;
    return(info);
}
/*****************************************************************
Function name  :   addr_remove()
Function       :   delete the address entry by name
******************************************************************/
void addr_remove()
{
    int result;
    struct contact *p1, *p2;
    struct contact **info_ptr = addr_info;
    if ((result  = addr_search(2)))
	{ 
    	while (result--)
		{
                    if (addr_num == 1)                    /* if just only one item*/
	         	{                                    
                          front = rear = NULL;
                          free(*info_ptr);
                          *info_ptr = NULL;
                        }
                  else
			{
                          if (*info_ptr == rear)            
				{                               
                                     p2 = front;
                                     p1 = front->next;
                                     while(p1->next != NULL)
					{ 
                                           p2 = p1;
                                           p1 = p1->next;
                                         }
                                     p2->next = NULL;
                                     rear = p2;
                                     free(*info_ptr);
                                     *info_ptr = NULL;
                                     info_ptr++;
                                }
                          if (front == *info_ptr)                 
				{                             
                                     front = (*info_ptr)->next;
                                     free(*info_ptr); 
                                     *info_ptr = NULL;
                                     info_ptr++;
                                }
                          else if ((*info_ptr != front) && (*info_ptr != rear))
				{    
                                     p2 = front; 
                                     p1 = front->next; 
                                     while (*info_ptr != p1)
					{
                                            p2 = p1;
                                            p1 = p1->next;
                                         }
                                     p2->next = p1->next;
                                     free(*info_ptr);
                                     *info_ptr = NULL;
                                     info_ptr++;
                
                                }
                          }
            addr_num--;
        }
    }
    else
        printf("Address entry not found!\n");
}
/*******************************************************************
Function name  :   addr_save(int argc)
Function       :   save the addressbook to a file
*********************************************************************/
int addr_save(int argc)
{
    FILE *cf_ptr; 
    struct contact *node_ptr;
    if (argc == 1)
	{
        printf("file path: ");
        fgets(file_name, sizeof(file_name), stdin);  
        file_name[strlen(file_name) - 1] = '\0';
        cf_ptr = fopen(file_name, "w+");
        }
    cf_ptr = fopen(file_name, "w+");
    if (cf_ptr == NULL)
       {
        printf("Could not open file! \n");
        printf("The file which you assigned may be NOT exist.\n");
        return 1;
        }
    printf("Now saving...\n");
    fwrite(&addr_num, sizeof(int), 1, cf_ptr);
    for (node_ptr = front; node_ptr != NULL; node_ptr = node_ptr->next)
	{
        fwrite(node_ptr, sizeof(struct contact), 1, cf_ptr);
        }
    printf("Successfully saved!\n");
    fclose(cf_ptr);
    return 0;
}
/*******************************************************************
Function name  :   addr_load()
Function       :   load the file to the addressbook linklist
*********************************************************************/
int addr_load()
{
	FILE *cf_ptr; 
    struct contact *node_ptr;
    int n = 0;
    printf("file path: ");
    fgets(file_name, sizeof(file_name), stdin);  
    file_name[strlen(file_name) - 1] = '\0';
    printf("Now loading...\n");
    if ((cf_ptr = fopen(file_name, "r+")) == NULL)
	{
        printf("Could not open file! \n");
        printf("The file which you assigned may be NOT exist.\n");
        return 1;
        }
    fread(&addr_num, sizeof(int), 1, cf_ptr);
    while (n < addr_num)
	{                                                          
    	node_ptr = (struct contact *)malloc(sizeof(struct contact));
    	if (node_ptr == NULL)
		{ 
                    printf("\nOut of memory!\n");
                    return 1;
                }  
        fread(node_ptr, sizeof(struct contact), 1, cf_ptr);
        node_ptr = node_add(node_ptr);
        if (n == 0) front = node_ptr; 
        n++;
    }
    printf("Successfully loaded!\n");
    fclose(cf_ptr);
    return 0;
}
/*******************************************************************
Function name  :   addr_help()
Function       :   give helpful information to the user
*********************************************************************/
void addr_help()
{
    printf("***************  Help Information  *******************\n");
    printf("*******  The commands are defined internally. *******\n\n");
    printf("-------------- to save or load file -------------\n");
    printf(" 'save'   to save the built addressbook\n");
    printf(" 'load'   to load the saved addressbook\n");
    printf("------------ Address entries operation ----------\n");
    printf(" 'ls'     to list all the items in current position. \n");
    printf(" 'cd'     to enter to a document \n");
    printf(" 'cat'    to search the name in ab. \n");
    printf(" 'add'    to add new address entry.\n");
    printf(" 'remove' to remove one or more address entries.\n");
    printf(" '!help'  to get help.\n");
    printf(" '!quit'  to quit from the application.\n");
}   
/*****************************************************************
Function name  :   inputs(char *prompt, char *valueAddr, int max)
Function       :   input the information of the new entry
******************************************************************/
void inputs(char *prompt, char *valueAddr, int max)
{
    char valueStr[40];
    do
	{
        printf("%s", prompt);
        fgets(valueStr, sizeof(valueStr), stdin);  
        valueStr[strlen(valueStr) - 1] = '\0';
        if (strlen(valueStr) >= max) printf("Too long!\n\n");
    }while (strlen(valueStr) >= max);
    strcpy(valueAddr, valueStr);
}
/*******************************************************************
Function name  :   addr_search(int choice)
Function       :   search the given entry
*********************************************************************/
int addr_search(int choice)
{
    struct contact *info;
    info = front;
    char entry[30]; 
    int i;
    int result = 0;
    int n;
    switch (choice)
	{
    case 1:  n=strlen(command);
    	     for(i=4;i<=n;i++)
            {
		        entry[i-4] = command[i];
             } 

             if ((entry[n - 2] == '.') && (entry[n - 1] == '*'))
		{           
                 entry[n - 2] = '\0';
                 while (info)
                 {
                     if (!strcmp(entry, info->name))
                   {
                         addr_info[result++] = info;
                         info = info->next;
                     }
                     else info = info->next;
                 }
                 break;	
             }
      	     while (info)
                {
                 if (!strcmp(entry, info->name))
                   {
                     addr_info[result++] = info;
                     info = info->next;
                    }
                 else info = info->next;
             } break;
    case 2:  printf("please give the key:");
	     fgets(entry, sizeof(entry), stdin); 
	     entry[strlen(entry) - 1] = '\0';
	     n = strlen(entry);
	     printf("%s was deleted from JSON\n",entry);
	     if ((entry[n - 2] == '.') && (entry[n - 1] == '*'))   
	     {
		 entry[n - 2] = '\0';
		 while (info)
		    {
			if (!strcmp(entry, info->name))
			 {
			    addr_info[result++] = info;
			    info = info->next;
			 }
			 else
		            info = info->next;
		    }
		  break;
	      }
      	     while (info)
		  {
	              if (!strcmp(entry, info->name))
			  {
			     addr_info[result++] = info;
			     info = info->next;
			  }
		     else
			     info = info->next;
		  }
                  break;	 
    }       
    return(result);
}
/*******************************************************************
Function name  :   validate_arg(int argc, char **argv)
Function       :   validate command line arguments
*********************************************************************/
void validate_arg(int argc, char **argv)
{
    if ((argc != 1) && (argc != 2) && (argc != 3))
	{
    	printf("Invalid Arguments!\n");
    	printf("Please type '!help' to get more help.\n\n");
    	exit(1);
        }
    if (argc==3)
	{ 
        if ((strcmp(&argv[2][0], "-new")) != 0)
	     {
                printf("If you want creat new file ,use '-new'.\n");
                printf("Please type '!help' to get more help.\n\n");
                exit(1);
             }
        else
            printf("Creat new file for the first use of this software.\n");
        }
    if (argc == 2)
	{
        if ((argv[1][0] != '/') && (argv[1][0] != '-'))
	   { 
        	printf("Invalid Arguments!\n");
        	printf("Argument must start with character '/' or '-'.\n");
        	printf("Please type '!help' to get more help.\n\n");
        	exit(1);
            }
        if (argv[1][1] != 'f')
	   {
        	printf("Invalid Arguments!\n");
        	printf("the character assigned file path and name must be 'f'.\n");
        	printf("Please type '!help' to get more help.\n\n");
        	exit(1);
           }
        if (argv[1][2] != ':')
	   {
        	printf("Invalid Arguments!\n");
        	printf("Between '-f' and [path][filename] must be ':'.\n");
        	printf("Please type '!help' to get more help.\n\n");
        	exit(1);
           }
    }
}
/*******************************************************************
Function name  :   iskeydul(struct contact *info, struct contact *front)
Function       :   check to sure the identical key
*********************************************************************/
void iskeydul(struct contact *info, struct contact *front)
{
	struct contact *p;
	p=front;
	while(p)
	{
		if (!strcmp(p->name,info->name))
		{
			printf("Error! You are trying add the duplicated key\n");
			printf("Please input a different key\n");
			inputs("key:", info->name, 15);
			p=front;
		}
		else
			p=p->next;
	}
}
