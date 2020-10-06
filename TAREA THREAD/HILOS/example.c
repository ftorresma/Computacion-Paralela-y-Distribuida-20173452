 #include <stdio.h>
 #include <pthread.h>
 #include <unistd.h>
 
 volatile int i; /* i es global, por lo que es visible para todas las funciones.
                    También está marcada como volatile, porque cambiará
                    de forma que no es predecible por el compilador
                    (en este caso: por un hilo diferente.) */
 
 /* t1 usa un [[spinlock]] para esperar hasta que i deje de valer 0 */
 static void *f1()
 {
     while (i==0)
     {
          
     } 
     printf("i's value has changed to %d.\n", i);
   
     return;
 }
 
 static void *f2()
 {
     sleep(10); /* dormir 60 segundos. */
     i = 99;
     printf("t2 changing the value of i to %d.\n", i);
 
     return;
 }
 
 int main()
 {
     int x;
     pthread_t t1, t2;
     i = 0; /* set global int i to 0. */
  
     x = pthread_create(&t1, NULL, f1, NULL);
     if (x != 0)
     {
         printf("pthread foo failed.\n");
     }
  
     x = pthread_create(&t2, NULL, f2, NULL);
     if (x != 0)
     {
         printf("pthread bar failed.\n");
     }
  
     pthread_join(t1, NULL);
     pthread_join(t2, NULL);
     printf("all pthreads finished.\n");
     return 0;
 }