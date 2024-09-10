class PrintCharacterSequenceBySync {
    private static final int CHARACTER_COUNT = 26;
    private static volatile int currentIndex = 0;
    private static final int THREAD_COUNT = 5;
    private static final Object LOCK = new Object();

    public static void main(String[] args) {
        for (int i = 0; i < THREAD_COUNT; i++) {
            new Thread(new PrintThread(i)).start();
        }
    }

    static class PrintThread implements Runnable {
        private final int threadNumber;

        public PrintThread(int threadNumber) {
            this.threadNumber = threadNumber;
        }

        @Override
        public void run() {
            while (currentIndex < CHARACTER_COUNT) {
                if (currentIndex % THREAD_COUNT == threadNumber) {
                    synchronized (LOCK) {
                        if (currentIndex < CHARACTER_COUNT) {
                            System.out.printf("%c %d%n", 'a' + currentIndex, currentIndex);
                            currentIndex++;
                        }
                    }
                }
            }
        }
    }
}
