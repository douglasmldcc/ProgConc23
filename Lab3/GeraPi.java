/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 3 */
/* Codigo: Gerando aproximações de Pi */

import java.util.Scanner; 
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
        int sg = (int) Math.pow(-1, i);
        double cq = (2*i)+1;
        double res =sg*(1.0/(cq));
        ap += res;
      }
     // System.out.println("Thread = " + id + " Aprox = " + ap );
      GeraPi.Api += ap;
   }
}

//--classe do metodo main
class GeraPi {
   static double Api;

   public static void main (String[] args) {

      //--PASSO 2: receber as dimensoes a trabalhar
      Scanner Obj0 = new Scanner(System.in);  
      Scanner Obj1 = new Scanner(System.in);  
      System.out.println("Entre com N para aproximação");
      int N = Obj0.nextInt();
      System.out.println("Entre com o numero de threads");
      int Nt = Obj1.nextInt();

      //--Reserva espaço para um vetor de threads
      Thread[] threads = new Thread[Nt];
  
      //--PASSO 3: transformar o objeto Runnable em Thread
      for (int i=0; i<threads.length; i++) {
         int salto = threads.length;
         threads[i] = new Thread(new AproxPi(i,salto,N));
      }

      //--PASSO 4: iniciar a thread
      for (int i=0; i<threads.length; i++) {
         threads[i].start();
      }

      //--PASSO 5: esperar pelo termino das threads
      for (int i=0; i<threads.length; i++) {
            try { threads[i].join(); } 
            catch (InterruptedException e) { return; }
      }
      //--PASSO 6: comparar o valor da aproximação 
      double pi = 4*Api;
      System.out.println("N = "+ N +", Threads = "+ Nt);
      System.out.println("Pi = "+ Math.PI+", Aproximação = "+pi);
      System.out.println("Diferença absoluta = "+ Math.abs(Math.PI-pi));
      System.out.println("Terminou"); 
   }
}

