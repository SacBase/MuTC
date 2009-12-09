#define SAC_DO_COMPILE_MODULE 1
#define SAC_MUTC_FUNAP_AS_CREATE  1
#define SAC_MUTC_THREAD_MALLOC 0
#define SAC_MUTC_DISABLE_THREAD_MEM 0
#define SAC_MUTC_BENCH 0
#define SAC_MUTC_MACROS  1

#define SAC_BACKEND MUTC

#include "sac.h"


struct bench {                                                   
  int                num; 
  struct s_interval *interval;                                            
};                                                                       
                                                                         
void benchStart( struct bench *interval)                                 
{                                                                        
  mtperf_start_interval( interval->interval, 0, interval->num, 0);
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
  (*interval)->interval = 
    (struct s_interval *)malloc(sizeof( 1024/*(*interval)->interval*/));
  (*interval)->num = num;                                                   
  return;                                                                
}                                                                        
                                                                         
void benchDestroyInterval( struct bench *interval)                        
{                                                                        
  mtperf_free_intervals(interval->interval);  
  free(interval);                                                        
  return;                                                                
}                                                                        
void benchCreate( int* a)                                                
{                                                                        
  *a=1;                                                                  
  return;                                                                
}     
