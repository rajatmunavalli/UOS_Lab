import java.util.concurrent.Semaphore;

class PrintNumbers {
    Semaphore semaphore;

    PrintNumbers() {
        semaphore = new Semaphore(1);
    }

    public void printEven() {
        for (int i = 0; i <= 10; i += 2) {
            try {
                semaphore.acquire();
                System.out.println(Thread.currentThread().getName() + " - " + i);
                semaphore.release();
                Thread.sleep(1000); // Sleep for 1 second
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void printOdd() {
        for (int i = 1; i <= 9; i += 2) {
            try {
                semaphore.acquire();
                System.out.println(Thread.currentThread().getName() + " - " + i);
                semaphore.release();
                Thread.sleep(1000); // Sleep for 1 second
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

public class Main {
    public static void main(String[] args) {
        PrintNumbers printNumbers = new PrintNumbers();

        Thread evenThread = new Thread(() -> printNumbers.printEven(), "EvenThread");
        Thread oddThread = new Thread(() -> printNumbers.printOdd(), "OddThread");

        evenThread.start();
        oddThread.start();
    }
}
