public class NumberPrinter {
    public static void main(String[] args) {
        Thread evenThread = new Thread(new EvenNumberPrinter(), "EvenThread");
        Thread oddThread = new Thread(new OddNumberPrinter(), "OddThread");
        Thread primeThread = new Thread(new PrimeNumberPrinter(), "PrimeThread");

        evenThread.start();
        oddThread.start();
        primeThread.start();

        try {
            Thread.sleep(15); 
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        evenThread.interrupt();
        oddThread.interrupt();
        primeThread.interrupt();
    }

    static class EvenNumberPrinter implements Runnable {
        @Override
        public void run() {
            for (int i = 0; !Thread.interrupted(); i++) {
                if (i % 2 == 0) {
                    System.out.println(Thread.currentThread().getName() + ": " + i);
                }
            }
        }
    }

    static class OddNumberPrinter implements Runnable {
        @Override
        public void run() {
            for (int i = 0; !Thread.interrupted(); i++) {
                if (i % 2 != 0) {
                    System.out.println(Thread.currentThread().getName() + ": " + i);
                }
            }
        }
    }

    static class PrimeNumberPrinter implements Runnable {
        @Override
        public void run() {
            for (int i = 2; !Thread.interrupted(); i++) {
                if (isPrime(i)) {
                    System.out.println(Thread.currentThread().getName() + ": " + i);
                }
            }
        }

        private boolean isPrime(int n) {
            if (n <= 1) {
                return false;
            }
            for (int i = 2; i <= Math.sqrt(n); i++) {
                if (n % i == 0) {
                    return false;
                }
            }
            return true;
        }
    }
}
