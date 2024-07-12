import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.TimeUnit;
import java.util.stream.IntStream;
import static java.util.concurrent.ThreadLocalRandom.current;
import static java.util.stream.Collectors.toList;

public class CyclicBarrierEx1 {
     public static void main(String[] args) throws InterruptedException {
        final int[] products = getProductsByCategoryId(); // 获取商品编号列表
        // 通过stream的map运算将商品编号转换为ProductPrice 
        List<ProductPrice> list = Arrays.stream(products)
                .mapToObj(ProductPrice::new)
                .collect(toList());
        final CyclicBarrier barrier = new CyclicBarrier(list.size()); // 1. CyclicBarrier，parties 就是子任务的数量

        final List<Thread> threadList = new ArrayList<>(); // 2. 用于存放线程任务的 list

        list.forEach(pp -> {
            Thread t = new Thread(() -> {
                System.out.println(pp.getProdID() + "-> start calculate price.");
                try {
                    TimeUnit.SECONDS.sleep(current().nextInt(10)); // 计算商品价格
                    pp.setPrice(pp.prodID * (pp.prodID % 2 == 0 ? 0.9D : 0.71D));
                    System.out.println(pp.getProdID() + "-> price calculate completed.");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } finally {
                    try {
                        barrier.await(); // 3. 在此等待其他工作线程到达 barrier point
                    } catch (InterruptedException | BrokenBarrierException e) {
                    }
                }                
            });
            threadList.add(t);
            t.start();
        });

        // 4. 等待所有工作线程结束
        threadList.forEach(t -> {
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        System.out.println("all of prices calculate finished.");
        list.forEach(System.out::println);
    }

    // 根据品类ID获取商品列表
    private static int[] getProductsByCategoryId() {
        return IntStream.rangeClosed(1, 10).toArray(); // 商品列表编号为从1~10的数字
    }

    private static class ProductPrice {
        private final int prodID;
        private double price;
        private ProductPrice(int prodID) {
            this(prodID, -1);
        }
        private ProductPrice(int prodID, double price) {
            this.prodID = prodID;
            this.price = price;
        }
        int getProdID() {
            return prodID;
        }
        void setPrice(double price) {
            this.price = price;
        }
        @Override
        public String toString() {
            return "ProductPrice{" + "prodID=" + prodID + ", price=" + price + '}';
        }
    }
};
