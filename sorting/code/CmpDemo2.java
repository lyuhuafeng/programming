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

    public static int byNameThenAge(Human h1, Human h2) {
        if (h1.name.equals(h2.name)) {
            return Integer.compare(h1.age, h2.age);
        } else {
            return h1.name.compareTo(h2.name);
        }
    }
}

class CmpDemo2 {
    public static void main(String args[]) {
        List<Human> humans = new ArrayList<>();
        humans.add(new Human("Igor", 11));
        humans.add(new Human("Andy", 18));
        humans.add(new Human("Alex", 14));
        humans.add(new Human("Mark", 12));
        
        humans.sort(Human::byNameThenAge);
        System.out.println(humans);
    }
}

