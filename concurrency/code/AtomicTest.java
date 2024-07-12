import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.IntBinaryOperator;

public class AtomicTest {
    public static void main(String[] args) {
        {
        AtomicInteger ai = new AtomicInteger(10);
        int result = ai.getAndUpdate(x -> x + 2);
        assert result == 10 && ai.get() == 12;
        }

        {
        AtomicInteger ai = new AtomicInteger(10);
        int result = ai.updateAndGet(x -> x + 3);
        assert result == 13 && ai.get() == 13;
        }

        // 函数式，用 IntBinaryOperator
        {
        AtomicInteger ai = new AtomicInteger(10);
        int result = ai.getAndAccumulate(5, new IntBinaryOperator() {
            @Override
            public int applyAsInt(int left, int right) {
                return left + right;
            }
        });
        assert result == 10 && ai.get() == 15;
        }

        // 对上面的优化，用 lambda 代替 IntBinaryOperator
        {
        AtomicInteger ai = new AtomicInteger(10);
        int result = ai.getAndAccumulate(5, Integer::sum);
        assert result == 10 && ai.get() == 15;
        result = ai.getAndAccumulate(7, (int x, int y) -> { return x + y; });
        assert result == 15 && ai.get() == 22;
        }

        {
        AtomicInteger ai = new AtomicInteger(10);
        int result = ai.accumulateAndGet(5, Integer::sum);
        assert result == 15 && ai.get() == 15;
        }

    }

}