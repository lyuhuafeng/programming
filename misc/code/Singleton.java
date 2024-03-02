import java.lang.reflect.Constructor;

import java.io.Serializable;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectInputStream;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;

public class Singleton implements Serializable {
    private static Singleton instance = null; // 不实例化

    private Singleton () {
        if (instance != null) {
            throw new RuntimeException(); // 对抗「反射攻击」
        }
        /* do something */
    }

    public static Singleton getInstance() {
        if (instance == null) { // 第一次判断
            synchronized(Singleton.class) { // 类级别的锁
                if (instance == null) {     // 第二次判断，避免多线程并发时多次创建对象
                    instance = new Singleton();
                }
            }
        }
        return instance;
    }

    // 以下用于对抗「反序列化攻击」
    private static final long serialVersionUID = -7604766932017737115L;
    protected Object readResolve() {
        return getInstance();
    }
}

class single_test {
    public static void main(String[] args) {
        Singleton inst0 = Singleton.getInstance();
        Singleton inst1 = Singleton.getInstance();
        Singleton inst2 = null, inst3 = null;
        try {
            Constructor[] constructors = Singleton.class.getDeclaredConstructors();
            Constructor c = constructors[0];
            c.setAccessible(true);
            inst2 = (Singleton) c.newInstance();
            inst3 = (Singleton) c.newInstance();
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println(inst0);
        System.out.println(inst1);
        System.out.println(inst2);
        System.out.println(inst3);
        System.out.println(inst0.hashCode());
        System.out.println(inst1.hashCode());
        if (inst2 != null) {
            System.out.println(inst2.hashCode());
        }
        if (inst3 != null) {
            System.out.println(inst3.hashCode());
        }

        System.out.println("______\n");
        try {
            final String filename = "singleton.serialized";
            // Singleton inst1 = Singleton.INSTANCE.getInstance(); // 正常创建 inst1
            ObjectOutput out = new ObjectOutputStream(new FileOutputStream(filename));
            out.writeObject(inst1);
            out.close();

            ObjectInput in = new ObjectInputStream(new FileInputStream(filename));
            Singleton inst_deserialized = (Singleton) in.readObject(); // 通过反序列化创建 inst2
            in.close();

            System.out.println("inst1 hashCode=" + inst1.hashCode());
            System.out.println("inst2 hashCode=" + inst_deserialized.hashCode());
            if (inst1 == inst_deserialized) {
                System.out.println("deserialized: same object");
            } else {
                System.out.println("deserialized: different objects");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
