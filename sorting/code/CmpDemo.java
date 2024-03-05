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

class CmpDemo {
    public static void main(String args[]) {
        List<Human> humans = new ArrayList<>();
        humans.add(new Human("Igor", 11));
        humans.add(new Human("Andy", 18));
        humans.add(new Human("Alex", 14));
        humans.add(new Human("Mark", 12));
        
        // 1. basic sorting, 未使用 lambda
        // 在 sort() 参数中直接定义 comparator 对象
        Collections.sort(humans, new Comparator<Human>() {
            @Override
            public int compare(Human h1, Human h2) {
                return h1.getName().compareTo(h2.getName());
            }
        });
        System.out.println(humans);

        // 1.a. basic sorting, 未使用 lambda
        // 先定义好 comparator 对象，再在 sort() 中引用
        Comparator<Human> cmpByAge = new Comparator<>() {
            @Override
            public int compare(Human h1, Human h2) {
                return h1.getAge() <= h2.getAge() ? -1 : 1;
            }
        };
        Collections.sort(humans, cmpByAge);
        System.out.println(humans);
        
        // 2a. lambda，参数带类型
        humans.sort((Human h1, Human h2) -> h1.getName().compareTo(h2.getName()));
        System.out.println(humans);

        // 2b. lambda，参数不带类型。
        humans.sort((h1, h2) -> h1.getAge() <= h2.getAge() ? -1 : 1);
        System.out.println(humans);

        // 2c. lambda 当做变量
        Comparator<Human> byAge = ((h1, h2) -> h1.getAge() <= h2.getAge() ? -1 : 1);
        humans.sort(byAge);
        System.out.println(humans);
    }
}

