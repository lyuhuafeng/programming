# 单例模式 singleton

to read
https://www.digitalocean.com/community/tutorials/thread-safety-in-java-singleton-classes

保证
- 该类在一个 JVM 中只有一个实例
- 提供一个全局访问点 global point of access to the Singleton object.

- 本质上，是个 global variable，且可能被更改 mutable。考虑：是否有更好的方式？
- 有点像 static variable。优点：静态变量在程序启动的时候JVM就会进行加载，如果不使用，会造成大量的资源浪费。singleton 可 lazy initialization，首次使用时再创建。

应用：
- 很多工具类都应用了单例模式，如：logging, driver objects, caching, thread pool
- 用于其他设计模式，如 Abstract Factory, Builder, Prototype, Facade, etc.
- java 核心类中，如 java.lang.Runtime, java.awt.Desktop

单例模式的实现需要三个必要的条件：
- private constructor: 这样才能将类的创建权控制在类的内部，从而使得类的外部不能创建类的实例。
- private static field: 存储其唯一实例。
- public static factory method: 供外界得到其唯一实例。

instance为什么一定要是static的？
- 通过静态的类方法 (getInstance) 获取instance，该方法是静态方法，instance由该方法返回（被该方法使用），如果instance非静态，无法被getInstance调用；
- instance需要在调用getInstance时候被初始化，只有static的成员才能在没有创建对象时进行初始化。且类的静态成员在类第一次被使用时初始化后就不会再被初始化，保证了单例；
- static类型的instance存在静态存储区，每次调用时，都指向的同一个对象。其实存放在静态区中的是引用，而不是对象。而对象是存放在堆中的。

构造方法为什么私有?
- 设置private以后，每次new对象的时候都要调用构造方法。而private的权限是当前类，那么其他类new对象的时候一定会失败。
- 设置成private是考虑封装性，防止在外部类中进行初始化，也就不是单例了。

# 饿汉式 eager initialization

在类加载时 (at the time of class loading)，静态实例 instance 就已创建并初始化好了。不会出现后面几个线程同时创建的情况。所以是线程安全的。

加载类本身（就是 ClassLoader 吧？）jvm是通过加锁保证线程安全的, 因此饿汉模式将实例作为类的静态变量, 就实现了线程安全的单例.

```java
    public class Singleton {
        private static final Singleton instance = new Singleton();
        private Singleton() { /* do something */ }
        public static Singleton getInstance() { return instance; }
    }

    // 使用
    Singleton si = Singleton.getInstance();
```

static block 法，可处理创建单例时发生的 exception

static block 中的语句，在类（被 Java ClassLoader）加载到内存时执行，而且只执行一次。<font color="green">在构造函数之前被执行。</font>通常用来创建静态资源。无法访问非静态变量。类中可以有多个 static block，但无意义。

```java
    public class Singleton {
        private static final Singleton instance;
        private Singleton() { /* do something */ }

        // static block initialization for exception handling。在 constructor 之前执行。
        static {
            try { instance = new Singleton(); }
            catch (Exception e) { throw new RuntimeException("exception occurred"); }
        }

        public static Singleton getInstance() { return instance; }
    }
```

饿汉式单例优缺点：

优点：
- 单例对象的创建是线程安全的；
- 获取单例对象时不需要加锁。
缺点：
- 单例对象的创建，不是延时加载。（一般认为延时加载可节省内存资源。但也要看实际应用场景，不一定所有场景都要延时加载。）

# 懒汉式 Lazy Initialization

与饿汉式对应的是懒汉式，懒汉式为了支持延时加载，将对象的创建延迟到了获取对象的时候，但为了线程安全，不得不为获取对象的操作加锁，这就导致了低性能。

并且这把锁只有在第一次创建对象时有用，而之后每次获取对象，这把锁都是一个累赘（双重检测对此进行了改进）。

代码如下：
```java
    public class Singleton {
        private static final Singleton instance;
        private Singleton() {}

        // 注意这里的 synchronized 关键字，它保证线程安全。若无它，则线程不安全。
        public static synchronized Singleton getInstance() {
            if (instance == null) { instance = new Singleton(); }
            return instance;
        }
    }
```

优点：
- 对象的创建是线程安全的。
- 支持延时加载。
缺点：
- 获取对象的操作，也被加上了锁，影响了并发度。（若需频繁使用单例对象，则此缺点无法接受；否则无伤大雅。）

# 双重检测

饿汉式和懒汉式的单例都有缺点，双重检测的实现方式解决了这两者的缺点。

双重检测将懒汉式中的 synchronized 方法改成了 synchronized 代码块。如下：

double-checked locking

利用 synchronized 关键字 + volatile 实现双重校验.

further reading: https://www.digitalocean.com/community/tutorials/thread-safety-in-java-singleton-classes

```java
    public class Singleton {
        private static Singleton instance = null; // 不实例化 (my question: default value 是啥)
        private Singleton() { /* do something */ }
    
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
    }
```

这种实现方式在 Java 1.4 及更早的版本中有些问题，就是指令重排序，可能会导致 Singleton 对象被 new 出来，并且赋值给 instance 之后，还没来得及初始化，就被另一个线程使用了。要解决这个问题，需给 instance 成员变量加上 volatile 关键字，以禁止指令重排序。高版本 Java 已在 JDK 内部解决了这个问题，不再需要关注。

双重检测单例优点：
- 对象的创建是线程安全的
- 支持延时加载
- 获取对象时不需要加锁

# 使用静态内部类 inner static helper class

Bill Pugh (William Pugh) 提出。Prior to Java 5, the Java memory model had a lot of issues, and the previous approaches used to fail in certain scenarios where too many threads tried to get the instance of the singleton class simultaneously.

https://www.digitalocean.com/community/tutorials/java-inner-class

instance 作为静态内部类的成员。

利用特性：Java 加载外部类的时候，不会创建内部类的实例，只有在外部类使用到内部类的时候才会创建内部类实例。这样也不用考虑线程安全问题。

不过，内部类的成员，是外部类的实例，直观感觉有点怪异。

```java
    public class Singleton {
        private Singleton() {}

        private static class SingletonInner {
            private static final Singleton instance = new Singleton();
        }

        public static Singleton getInstance() {
            return SingletonInner.instance;
        }
    }
```

Notice the private inner static class that contains the instance of the singleton class. When the singleton class is loaded, SingletonHelper class is not loaded into memory and only when someone calls the getInstance() method, this class gets loaded and creates the singleton class instance. This is the most widely used approach for the singleton class as it doesn't require synchronization.

SingletonInner 是一个静态内部类，当外部类 Singleton 被加载的时候，并不会创建 SingletonInner 实例对象。

只有当调用 getInstance() 方法时，SingletonInner 才会被加载，这个时候才会创建 instance。instance 的唯一性、创建过程的线程安全性，都由 JVM 来保证。

静态内部类单例优点：
- 对象的创建是线程安全的
- 支持延时加载
- 获取对象时不需要加锁

# 反射攻击

<font color="red">以上各种方法，都不能抵抗「反射攻击」using reflection to destroy the Singleton pattern.</font>

根据 java 反射，获取类 class 对象后，可用其构造函数创建新的实例。即使其构造函数是私有的，也可以调用。

攻击代码，来自[这里](https://www.digitalocean.com/community/tutorials/java-singleton-design-pattern-best-practices-examples)。

```java
    import java.lang.reflect.Constructor;

    // public class Singleton 代码略，用上面任何一种实现都可以

    class single_test {
        public static void main(String[] args) {
            Singleton inst1 = Singleton.getInstance(); // 正常生成
            Singleton inst2 = null, inst3 = null; // 下面根据反射生成
            try {
                Constructor[] constructors = Singleton.class.getDeclaredConstructors();
                Constructor c = constructors[0];
                c.setAccessible(true);
                inst2 = (Singleton) c.newInstance();
                inst3 = (Singleton) c.newInstance();
            } catch (Exception e) {
                e.printStackTrace();
            }
            System.out.println(inst1);
            System.out.println(inst2);
            System.out.println(inst3); // 以上三个不同
            System.out.println(inst1.hashCode());
            System.out.println(inst2.hashCode());
            System.out.println(inst3.hashCode()); // 以上三个不同
        }
    }
```

对抗方法：在私有的构造函数中，判断属性是否 null，若不是，则有问题，直接抛出异常。两种实现的代码如下。新增的判断，见注释所在行。

但这种方法会显式抛出 exception，不够优雅。最好还是好像什么都没发生一样。

```java
    public class Singleton {
        private static Singleton instance = null;
        private Singleton () {
            if (instance != null) { throw new RuntimeException(); } // 新增此句，对抗「反射攻击」
        }
        public static Singleton getInstance() {
            if (instance == null) {
                synchronized(Singleton.class) { if (instance == null) { instance = new Singleton(); } }
            }
            return instance;
        }
    }
    
    public class Singleton {
        private Singleton() {}
        private static class SingletonInner { private static final Singleton instance = new Singleton(); }
    
        public static Singleton getInstance() {
            if (SingletonInner.instance != null) { throw new RuntimeException(); } // 新增此句，对抗「反射攻击」
            return SingletonInner.instance;
        }
    }
```

# 枚举法

Joshua Bloch, Effective Java 作者

Java ensures that any enum value is instantiated only once in a Java program. Since Java Enum values are globally accessible, so is the singleton. The drawback is that the enum type is somewhat inflexible (for example, it does not allow lazy initialization).

用枚举来实现单例，是最简单的方式。这种实现方式通过 Java 枚举类型本身的特性，保证了实例创建的线程安全性和实例的唯一性。

与其他方法的明显区别：`Singleton.INSTANCE.getInstance()` 而不是 `Singleton.getInstance()`。

枚举对抗攻击：
- 天然可以对抗「反射攻击」：反射在通过 newInstance 创建对象时，会检查该类是否 enum 修饰，若是则抛出异常 (java.lang.IllegalArgumentException: Cannot reflectively create enum objects)，反射失败。
- 天然可以对抗「反序列化攻击」：甚至不会抛出异常，很优雅，就像什么都没发生一样。

最简方法。只用一个 `INSTANCE` 成员，连构造函数和 `getInstance()` 都不要了。调用时用 `Singleton.INSTANCE`。

```java
    public enum Singleton {
        INSTANCE; // 或加一对括号：INSTANCE();
        public void doSomething() { /* 想通过单例做什么, 就放在这里 */ }
    }
    // 使用
    Singleton obj = Singleton.INSTANCE;
    obj.doSomething();
```

稍啰嗦版本，增加构造函数、`getInstance()`。简化版本，去掉了 info 字段，直接看地址是否一样。

```java
    public enum Singleton {
        INSTANCE();
        private Singleton() {};
        public Singleton getInstance() { return INSTANCE; }
    }

    Singleton obj1 = Singleton.INSTANCE.getInstance(); // 使用方法，与上面不同
    Singleton obj2 = Singleton.INSTANCE.getInstance();
    if (obj1 == obj2) {
        System.out.println("same object");
    } else {
        System.out.println("different objects");
    }
```

更啰嗦版本：

```java
    public enum Singleton {
        INSTANCE("initial class info");
        private String info;
        private Singleton(String info) { this.info = info; }
        public Singleton getInstance() { return INSTANCE; }

        // getters and setters
        public String getInfo() { return info; }
        public void setInfo(String info) { this.info = info; }
        public static void doSomething() { /* do something */ }
    }

    Singleton obj1 = Singleton.INSTANCE.getInstance();
    System.out.println(obj1.getInfo()); // Initial enum info
    Singleton obj2 = Singleton.INSTANCE.getInstance();
    obj2.setInfo("updated enum info");
    // 下面两句输出结果一样，说明两个对象其实是同一个
    System.out.println(obj1.getInfo()); // New enum info
    System.out.println(obj2.getInfo()); // New enum info

    // 下面试图用反射创建 inst2，失败并抛出异常
    Singleton inst2 = null;
    try {
        Constructor[] constructors = Singleton.class.getDeclaredConstructors();
        Constructor c = constructors[0];
        c.setAccessible(true);
        inst2 = (Singleton) c.newInstance();
    } catch (Exception e) {
        e.printStackTrace();
    }
```

最啰嗦版本，将枚举作为内部类。枚举类的构造函数，只会执行一次。用这个特点来保证单例。

```java
    public class Singleton {
        private Singleton() {}
    
        public static Singleton getInstance() {
            return SinletonHolder.INSTANCE.getInstance();
        }

        private enum SinletonHolder {
            INSTANCE;
            private Singleton instance;
            SinletonHolder() { instance = new Singleton(); } // 枚举类的构造函数，只被执行一次
            private Singleton getInstance() { return instance; } // 枚举类里的方法，要通过枚举值进行调用
        }
    }
```

https://juejin.cn/post/6955698964993671182

# 序列化攻击 serialization 

序列化一个单例类的对象，接下来复原多个那个对象，那你就会有多个单例类的实例。

任何一个readObject方法，不管是显式的还是默认的，它都会返回一个新建的实例，这个新建的实例不同于该类初始化时创建的实例。”

当然，这个问题也是可以解决的，可以通过对序列化机制进行定制, 主要就是readResolve方法

枚举类为啥没有反序列化的问题?
在序列化的时候Java仅仅是将枚举对象的name属性输出到结果中，反序列化的时候则是通过java.lang.Enum的valueOf方法来根据名字查找枚举对象。
同时，编译器是不允许任何对这种序列化机制的定制的，因此禁用了writeObject、readObject、readObjectNoData、writeReplace和readResolve等方法。


https://www.digitalocean.com/community/tutorials/java-singleton-design-pattern-best-practices-examples

```java
    public class Singleton implements Serializable {
        private Singleton() {}
        private static class SingletonHelper { private static final Singleton instance = new Singleton(); }
        public static Singleton getInstance() { return SingletonHelper.instance; }

        // 以下新增，用于对抗「反序列化攻击」
        private static final long serialVersionUID = -7604766932017737115L; // 这句似乎也可以不要
        protected Object readResolve() {
            return getInstance();
        }
    }

    // 以下为攻击方式
    final String filename = "singleton.serialized";
    Singleton inst1 = Singleton.getInstance(); // 正常创建 inst1
    ObjectOutput out = new ObjectOutputStream(new FileOutputStream(filename));
    out.writeObject(inst1);
    out.close();

    ObjectInput in = new ObjectInputStream(new FileInputStream(filename));
    Singleton inst2 = (Singleton) in.readObject(); // 通过反序列化创建 inst2
    in.close();

    System.out.println("inst1 hashCode=" + inst1.hashCode());
    System.out.println("inst2 hashCode=" + inst2.hashCode());
```

https://howtodoinjava.com/design-patterns/creational/singleton-design-pattern-in-java/
5. Best Practice: Add readResolve() to Singleton Instance
6. Best Practice: Add SerialVersionUId to Singleton Instance

# 利用 CAS

CAS: compare and swap。设计并发算法时常用的技术。

链接：https://juejin.cn/post/6955698964993671182

如果我不想使用synchronized关键字来实现单例模式呢? 即使是类加载保证的线程安全, 底层也是加了锁的, 那么就可以采用CAS实现.
CAS的好处在于不需要使用传统的锁机制来保证线程安全,CAS是一种基于忙等待的算法,依赖底层硬件的实现,相对于锁它没有线程切换和阻塞的额外消耗,可以支持较大的并行度。
```java
    public class Singleton {
        private static final AtomicReference<Singleton> INSTANCE = new AtomicReference<Singleton>(); 
    
        private Singleton() {}
    
        public static Singleton getInstance() {
            for (;;) {
                Singleton singleton = INSTANCE.get();
                if (null != singleton) {
                    return singleton;
                }
    
                // CAS 操作
                singleton = new Singleton();
                if (INSTANCE.compareAndSet(null, singleton)) {
                    return singleton;
                }
            }
        }
    }
```

缺点：
- 若忙等待一直执行不成功，一直死循环中，开销大。



# 多例模式

上面介绍了5 种单例模式的实现方式，下面作为对单例模式的扩展，再来介绍一下多例模式以及线程间唯一的单例模式。先来看下多例模式。

单例模式是指，一个类只能创建一个对象。那么多例模式就是，一个类可以创建多个对象，但是对象个数可以控制。

对于多例模式，我们可以将类的实例都编上号，然后将实例存放在一个 Map 中。

代码如下：

```java
    public class MultiInstance {
        private long instanceNum; // 实例编号
        private static final Map<Long, MultiInstance> ins = new HashMap<>(); // 用于存放实例
    
        static { // 存放 3 个实例
            ins.put(1L, new MultiInstance(1));
            ins.put(2L, new MultiInstance(2));
            ins.put(3L, new MultiInstance(3));
        }
    
        private MultiInstance(long n) {
            this.instanceNum = n;
        }
    
        public MultiInstance getInstance(long n) {
            return ins.get(n);
        }
    }
```

实际上，Java 中的枚举就是一个“天然”的多例模式，其中的每一项代表一个实例，如下：

```java
    public enum MultiInstance {
        ONE,
        TWO,
        THREE;
    }
```

# 线程唯一的单例

一般情况下，我们所说的单例的作用范围是进程唯一的，就是在一个进程范围内，一个类只允许创建一个对象，进程内的多个线程之间也是共享同一个实例。

实际上，在Java 中，每个类加载器都定义了一个命名空间。所以我们这里实现的单例是依赖类加载器的，也就是在同一个类加载器中，我们实现的单例就是真正的单例模式。否则如果有多个类加载器，就会有多个单例出现了。一个解决办法是：自行指定类加载器，并且指定同一个类加载器。

那么线程唯一的单例就是，一个实例只能被一个线程拥有，一个进程内的多个线程拥有不同的类实例。

我们同样可以用 Map 来实现，代码如下：

```java
    public class ThreadedSingleton {
        private static final ConcurrentHashMap<Long, ThreadSingleton> instances = new ConcurrentHashMap<>();
    
        private ThreadedSingleton() {}
    
        public static ThreadedSingleton getInstance() {
            Long id = Thread.currentThread().getId();
            instances.putIfAbsent(id, new ThreadedSingleton());
            return instances.get(id);
        }
    }
```

# private constructor

- 导致类对象只能从类内部创建
- 不能从此类派生
用途
- 被其他 constructor 调用，称为 constructor delegation
- 创建「不可实例化的」(uninstantiable) 类。例如，只有一些静态方法的工具类。（这个类其实就是个 singleton）
- Builder 模式。例：Employee 类有 private constructor，所以不能直接创建其对象；它有个 inner Builder 类，在其 `build()` 方法中调用 Employee 的 private constructor，以创建 Employee 对象。代码：[`builder-pattern-example.java`](code/builder-pattern-example.java)
- 防止派生 subclassing。（更好的方法是把类声明为 final）
- 防止从外部创建类对象。
- singleton
- factory method
- static-methods-only (utility) class
- constants-only class

注意：
- 因为单例类的构造函数是私有的，所以单例类不能被继承。

另外，实现单例类时，还需要考虑三个问题：
- 创建时，线程安全。
- 创建，是否延时加载。
- 获取时，是否需要加锁（锁会导致低性能）。


# 反对意见
https://www.michaelsafyan.com/tech/design/patterns/singleton
