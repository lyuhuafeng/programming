import java.util.concurrent.Exchanger;
import java.lang.String;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ExchangerTest {

    private static final Exchanger<String> exchanger = new Exchanger<>();
    private static ExecutorService threadPool = Executors.newFixedThreadPool(2);

    public static void main(String[] args) {

        threadPool.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    String A = "12345";
                    String B = exchanger.exchange(A);
                    System.out.println("thread 1 got: " + B);
                } catch (InterruptedException e) {
                }
            }
        });

        threadPool.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    String B = "abcde";
                    String A = exchanger.exchange(B);
                    System.out.println("thread 2 got: " + A);
                    // System.out.println("A和B数据是否一致：" + A.equals(B));
                    // System.out.println("A= "+A);
                    // System.out.println("B= "+B);
                } catch (InterruptedException e) {
                }
            }
        });

        threadPool.shutdown();

    }
}
