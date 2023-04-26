/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 3 */
/* Codigo: AproxPi aproximações de Pi */

import java.util.Scanner;  // Import the Scanner class
import java.util.Arrays;
import java.lang.Math;

//--PASSO 1: criar uma classe que implementa a interface Runnable 
class AproxPi implements Runnable {
   private int id;
   private int salto;
   private int N;
   
   //--construtor
   public AproxPi(int id, int salto, int N) {        
      this.id = id;
      this.salto = salto;   
      this.N = N;
   }

   //--metodo executado pela thread
   public void run() { 
      double ap =0;
      // Calculando os valores de N 
      for (int i=N-id; i>=0; i-= salto) {
        ap += ((int) Math.pow(-1.0, i))*(1.0/((2.0*i)+1.0));
      }
     // System.out.println("Thread = " + id + " Aprox = " + ap );
      GeraPi.Api += ap;
   }
}

//--classe do metodo main
class GeraPi {
   static double Api;

   public static void main (String[] args) {

      //--PASSO 1: receber as dimensoes a trabalhar
      Scanner Obj0 = new Scanner(System.in);  
      Scanner Obj1 = new Scanner(System.in);  
      System.out.println("Entre o com N para aproximação");
      int N = Obj0.nextInt();
      System.out.println("Entre com o numero de threads");
      int Nt = Obj1.nextInt();

      //--Reserva espaço para um vetor de threads
      Thread[] threads = new Thread[Nt];
  
      //--PASSO 2: transformar o objeto Runnable em Thread
      for (int i=0; i<threads.length; i++) {
         int salto = threads.length;
         threads[i] = new Thread(new AproxPi(i,salto,N));
      }

      //--PASSO 3: iniciar a thread
      for (int i=0; i<threads.length; i++) {
         threads[i].start();
      }

      //--PASSO 4: esperar pelo termino das threads
      for (int i=0; i<threads.length; i++) {
            try { threads[i].join(); } 
            catch (InterruptedException e) { return; }
      }
      //--PASSO 5: comparar o valor da aproximação 
      double pi = 4*Api;
      System.out.println("N = "+ N +", Threads = "+ Nt);
      System.out.println("Pi = "+ Math.PI+", Aproximação = "+pi);
      System.out.println("Diferença absoluta = "+ Math.abs((Math.PI-pi)/Math.PI));
      System.out.println("Terminou"); 
   }
}
