#define SAC_DO_COMPILE_MODULE 1
#define SAC_MUTC_FUNAP_AS_CREATE  1
#define SAC_MUTC_MACROS  1
#define SAC_BACKEND MUTC

#include "stdarg.h"
#include "cmalloc.h"
#include "sac.h"

struct bench {                                                   
  int                num; 
  char *             name;
  struct s_interval *interval;                                            
};                                                                       
                                                                         
void benchStart( struct bench *interval)                                 
{                                                                        
  mtperf_start_interval( interval->interval, 0, interval->num, 
                         (const char *) interval->name);
  return;                                                                
}

sl_def(bench_start_rc_threadfun, void, sl_shparm(struct bench*, interval))
{
   struct bench *local = sl_getp( interval);
   benchStart( local);
   sl_setp( interval, local);
}
sl_enddef

void benchStartRC( struct bench *interval)                                 
{                                                                        
  sl_create(,SAC_mutc_rc_place,0,1,1,,,bench_start_rc_threadfun,sl_sharg(struct bench*, , interval)); 
  sl_sync();
  return;                                                                
}     
                                                                         
void benchEnd( struct bench* interval)                                   
{                                                                        
  mtperf_finish_interval( interval->interval, 0);
  return;                                                                
}  

sl_def(bench_end_rc_threadfun, void, sl_shparm(struct bench*, interval))
{
   struct bench *local = sl_getp( interval);
   benchEnd( local);
   sl_setp( interval, local);
}
sl_enddef

void benchEndRC( struct bench* interval)                                   
{                                                                        
  sl_create(,SAC_mutc_rc_place,0,1,1,,,bench_end_rc_threadfun,sl_sharg(struct bench*, , interval)); 
  sl_sync(); 
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

void benchmemcpy( void* toarg, void* fromarg, size_t n){
  int i;
  char *to=toarg;
  char *from=fromarg;

  for (i=0; i<n; i++){
    to[i] = from[i];
  }
}

void benchPrintVector( int n, ...)
{
  va_list dots;
  int i=0;
  struct s_interval intervals[n];

  va_start( dots, n);
  for (i=0;i<n;i++){
    intervals[i] =  *(va_arg( dots, struct bench*)->interval);
  }
  va_end( dots);

  mtperf_report_intervals( intervals, n, REPORT_FIBRE);
}

void benchPrint2( struct bench *a,
                  struct bench *b){
  benchPrintVector( 2, a, b);
}
void benchPrint3( struct bench *a,
                  struct bench *b,
                  struct bench *c){
  benchPrintVector( 3, a, b, c);
}
void benchPrint4( struct bench *a,
                  struct bench *b,
                  struct bench *c,
                  struct bench *d){
  benchPrintVector( 4, a, b, c, d);
}
void benchPrint5( struct bench *a,
                  struct bench *b,
                  struct bench *c,
                  struct bench *d,
                  struct bench *e){
  benchPrintVector( 5, a, b, c, d, e);
}
void benchPrint6( struct bench *a,
                  struct bench *b,
                  struct bench *c,
                  struct bench *d,
                  struct bench *e,
                  struct bench *f){
  benchPrintVector( 6, a, b, c, d, e, f);
}
void benchPrint7( struct bench *a,
                  struct bench *b,
                  struct bench *c,
                  struct bench *d,
                  struct bench *e,
                  struct bench *f,
                  struct bench *g){
  benchPrintVector( 7, a, b, c, d, e, f, g);
}
void benchPrint8( struct bench *a,
                  struct bench *b,
                  struct bench *c,
                  struct bench *d,
                  struct bench *e,
                  struct bench *f,
                  struct bench *g,
                  struct bench *h){
  benchPrintVector( 8, a, b, c, d, e, f, g, h);
}
void benchPrint9( struct bench *a,
                  struct bench *b,
                  struct bench *c,
                  struct bench *d,
                  struct bench *e,
                  struct bench *f,
                  struct bench *g,
                  struct bench *h,
                  struct bench *i){
  benchPrintVector( 9, a, b, c, d, e, f, g, h, i);
}
void benchPrint10( struct bench *a,
                   struct bench *b,
                   struct bench *c,
                   struct bench *d,
                   struct bench *e,
                   struct bench *f,
                   struct bench *g,
                   struct bench *h,
                   struct bench *i,
                   struct bench *j){
  benchPrintVector( 10, a, b, c, d, e, f, g, h, i, j);
}
                                                                         
void benchGetInterval_i( struct bench** interval, int num)               
{                                                                        
  (*interval) = (struct bench*)malloc( sizeof( struct bench));
  (*interval)->interval = mtperf_alloc_intervals(1);
  (*interval)->num = num;
  (*interval)->name = (char *)malloc(sizeof(char));
  (*interval)->name[0] = '\0';
  return;                                                                
}                                                                        

void benchGetInterval_s( struct bench** interval, char *name) 
{                                                                        
  (*interval) = (struct bench*)malloc( sizeof( struct bench));
  (*interval)->interval = mtperf_alloc_intervals(1);
  (*interval)->num = -1;                                                   
  (*interval)->name = name;
  return;                                                                
}                                                                        

void benchGetInterval_si( struct bench** interval, char * name, int num)
{                                                                        
  (*interval) = (struct bench*)malloc( sizeof( struct bench));
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
