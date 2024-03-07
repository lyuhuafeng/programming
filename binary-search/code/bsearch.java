import java.util.Arrays;

class bsearch_demo {
    static int lower_bound(int a[], int k) {
        int i = Arrays.binarySearch(a, k);
        System.out.printf("raw index: %d%n", i);

        if (i < 0) { // 没找到
            return -i - 1;
        } else { // 找到，不确定是哪个，需左移找到第一个
            while (i > 0) {
                if (a[i - 1] == k) {
                    i--;
                } else {
                    return i;
                }
            }
            return i; // 此时 i=0
        }
    }
    static int upper_bound(int a[], int k) {
        int i = Arrays.binarySearch(a, k);
        System.out.printf("raw index: %d%n", i);

        if (i < 0) { // 没找到
            return -i - 1;
        } else { // 找到，不确定是哪个，需右移找到最后一个
            while (i < a.length) {
                if (a[i] == k) {
                    i++;
                } else {
                    return i;
                }
            }
            return i; // 此时 i=a.length
        }
    }
    public static void main(String[] args) {
        int a[] = { 4, 6, 10, 12, 18, 18, 18, 20, 20, 30, 45 };
        Arrays.sort(a);

        int k = 3;
        int li = lower_bound(a, k);
        System.out.printf("lower bound: %d%n", li);
        int ui = upper_bound(a, k);
        System.out.printf("upper bound: %d%n", ui);
    }
}
