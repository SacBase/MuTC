#define SAC_DO_COMPILE_MODULE 1
#define SAC_MUTC_FUNAP_AS_CREATE  1
#define SAC_MUTC_MACROS  1
#define SAC_BACKEND MUTC

#include "sac.h"


struct bench {                                                   
  int                num; 
  char *             name;
  struct s_interval *interval;                                            
};                                                                       

/*
int len( char *string){
  int i=0;

  while ( string[i] != '\0'){
    i++;
  }

  return( i);
}

char *cpy( char *string){
  int i=0;
  char *res;
  res = malloc( sizeof(char) * len(string));

  while ( string[i] != '\0'){
    res[i] = string[i];
    i++;
  }

  return( res);
}
*/
                                                                         
void benchStart( struct bench *interval)                                 
{                                                                        
  mtperf_start_interval( interval->interval, 0, interval->num, 
                         (const char *) interval->name);
  return;                                                                
}                                                                        
                                                                         
void benchEnd( struct bench* interval)                                   
{                                                                        
  mtperf_finish_interval( interval->interval, 0);
  return;                                                                
}                         
                                               
/* noop*/
void benchThis( )                                                        
{                                                                        
  return;                                                                
}                                                                        
                                                                         
void benchPrint( struct bench* interval)                                 
{                                                                        
  mtperf_report_intervals( interval->interval, 1, REPORT_FIBRE);
  return;                                                                
}                                                                        
                                                                         
void benchGetInterval_i( struct bench** interval, int num)               
{                                                                        
  (*interval) = (struct bench*)malloc( sizeof( (*interval)));
  (*interval)->interval = mtperf_alloc_intervals(1);
  (*interval)->num = num;
  (*interval)->name = (char *)malloc(sizeof(char));
  (*interval)->name[0] = '\0';
  return;                                                                
}                                                                        

void benchGetInterval_s( struct bench** interval, char *name) 
{                                                                        
  (*interval) = (struct bench*)malloc( sizeof( (*interval)));
  (*interval)->interval = mtperf_alloc_intervals(1);
  (*interval)->num = -1;                                                   
  (*interval)->name = name;
  return;                                                                
}                                                                        

void benchGetInterval_si( struct bench** interval, char * name, int num)
{                                                                        
  (*interval) = (struct bench*)malloc( sizeof( (*interval)));
  (*interval)->interval = mtperf_alloc_intervals(1);
  (*interval)->num = num;                                    
  (*interval)->name = name;
  return;                                                                
}                                                                        
                                                                         
void benchDestroyInterval( struct bench *interval)                        
{                                                                        
  mtperf_free_intervals(interval->interval);  
  free(interval->name);
  free(interval);                                                        
  return;                                                                
}                            
                                            
void benchCreate( int* a)                                                
{                                                                        
  *a=1;                                                                  
  return;                                                                
}     
