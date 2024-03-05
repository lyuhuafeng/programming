import java.util.*;

class Human {
    private String name;
    private int age;

    public Human(String name, int age) {
        this.name = name;
        this.age = age;
    }
    public String getName() {
        return name;
    }
    public int getAge() {
        return age;
    }
    @Override
    public String toString() {
        return name + "/" + age;
    }
}

class CmpDemo3 {
    public static int byNameThenAge(Human h1, Human h2) {
        if (h1.getName().equals(h2.getName())) {
            return Integer.compare(h1.getAge(), h2.getAge());
        } else {
            return h1.getName().compareTo(h2.getName());
        }
    }
    public static void main(String args[]) {
        List<Human> humans = new ArrayList<>();
        humans.add(new Human("Igor", 11));
        humans.add(new Human("Andy", 18));
        humans.add(new Human("Alex", 14));
        humans.add(new Human("Mark", 12));

        humans.sort(CmpDemo3::byNameThenAge);
        System.out.println(humans);
    }
}

