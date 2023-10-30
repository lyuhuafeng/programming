import java.util.*;
 
public class StringCmp {
    public static void main(String[] args) {
        Comparator<String> customComparator = new Comparator<String>() {
            @Override
            public int compare(String s1, String s2) {
                return s1.length() - s2.length();
            }
        };
        // Create a Priority Queue with a custom Comparator
        PriorityQueue<String> q = new PriorityQueue<>(customComparator);
        q.add("Red");
        q.add("Green");
        q.add("Blue");
        q.add("Cyan");
        q.add("Magenta");
        q.add("Yellow");

        while (!q.isEmpty()) {
            String s = q.poll();
            System.out.println(s);
        }
    }
}
