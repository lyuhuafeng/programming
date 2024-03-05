import java.util.*;
import java.lang.String;

class MyOrder implements Comparable<MyOrder> {
    private int orderId;
    private double orderAmount;
    private String customerName;

    public MyOrder(int orderId, double orderAmount, String customerName) {
        this.orderId = orderId;
        this.orderAmount = orderAmount;
        this.customerName = customerName;
    }

    @Override
    public int compareTo(MyOrder o) {
        return o.orderId > this.orderId ? 1 : -1;
    }

    @Override
    public String toString() {
        return "orderId:" + this.orderId + ", orderAmount:" + this.orderAmount + ", customerName:" + customerName;
    }

    public double getOrderAmount() {
        return orderAmount;
    }
}

class MyOrderCmpByAmount implements Comparator<MyOrder> {
    @Override
    public int compare(MyOrder o1, MyOrder o2) {
        return o1.getOrderAmount() < o2.getOrderAmount() ? 1 : -1;
    }
}

class MyOrderDemo {
    public static void main(String args[]) {
        PriorityQueue<MyOrder> q = new PriorityQueue<MyOrder>();
        q.add(new MyOrder(1, 100.0, "customer1"));
        q.add(new MyOrder(3, 50.0, "customer3"));
        q.add(new MyOrder(2, 300.0, "customer2"));
        while (!q.isEmpty()) {
            System.out.println(q.poll());
        }

        PriorityQueue<MyOrder> q2 = new PriorityQueue<MyOrder>(new MyOrderCmpByAmount());
        q2.add(new MyOrder(1, 100.0, "customer1"));
        q2.add(new MyOrder(3, 50.0, "customer3"));
        q2.add(new MyOrder(2, 300.0, "customer2"));
        while (!q2.isEmpty()) {
            System.out.println(q2.poll());
        }
    }
}