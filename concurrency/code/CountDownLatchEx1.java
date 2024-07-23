import java.util.Arrays;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.stream.IntStream;
import static java.util.concurrent.ThreadLocalRandom.current;
import static java.util.stream.Collectors.toList;

public class CountDownLatchEx1 {
     public static void main(String[] args) throws InterruptedException {
        final int[] products = getProductsByCategoryId(); // 获取商品编号列表
        // 通过 stream 的 map 运算将商品编号转换为 ProductPrice 
        List<ProductPrice> list = Arrays.stream(products)
                .mapToObj(ProductPrice::new)
                .collect(toList());
        final CountDownLatch latch = new CountDownLatch(products.length); // 1. CountDownLatch，计数器数量就是子任务的数量

        // 2. 为每一件商品的计算都开辟对应的线程
        list.forEach(pp -> new Thread(() -> {
                    System.out.println(pp.getProdID() + "-> start calculating price.");
                    try {
                        TimeUnit.SECONDS.sleep(current().nextInt(10)); // 计算商品价格
                        pp.setPrice(pp.prodID * (pp.prodID % 2 == 0 ? 0.9D : 0.71D));
                        System.out.println(pp.getProdID() + "-> price calculation completed.");
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } finally {
                        latch.countDown(); // 3. 子任务执行完成, 计数器 count down
                    }
        }).start());
        latch.await(); // 4. 主线程阻塞等待所有子任务结束
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
