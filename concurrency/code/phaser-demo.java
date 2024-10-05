import java.util.concurrent.Phaser;

class LongRunningAction implements Runnable {
    private String threadName;
    private Phaser ph;

    LongRunningAction(String threadName, Phaser ph) {
        this.threadName = threadName;
        this.ph = ph;
        this.doWork();
        ph.register();
        System.out.println(threadName + " registered during phase " + ph.getPhase());
    }

    @Override
    public void run() {
        System.out.println(threadName + " before work during phase " + ph.getPhase());
        ph.arriveAndAwaitAdvance();
        doWork();
        System.out.println(threadName + " after work during phase " + ph.getPhase());
        ph.arriveAndDeregister();
    }

    // Simulating real work
    private void doWork() {
        try {
            Thread.sleep((long) (Math.random() * 100));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class phaser_demo {
    public static void main(String[] args) {
        Phaser ph = new Phaser(1); // 创建一个 Phaser 实例并传给所有线程；所有线程共用一个 Phaser 实例
        System.out.println("phase " + ph.getPhase());
        new Thread(new LongRunningAction("w1", ph)).start();
        new Thread(new LongRunningAction("w2", ph)).start();
        new Thread(new LongRunningAction("w3", ph)).start();
        ph.arriveAndAwaitAdvance(); // 所有线程都到达 barrier 后，要在主线程里也「到达」一下，才能继续
        System.out.println("phase " + ph.getPhase());
        new Thread(new LongRunningAction("w4", ph)).start();
        new Thread(new LongRunningAction("w5", ph)).start();
        ph.arriveAndAwaitAdvance();
        System.out.println("phase " + ph.getPhase());
        ph.arriveAndDeregister();
        System.out.println("phase " + ph.getPhase());
    }
}
