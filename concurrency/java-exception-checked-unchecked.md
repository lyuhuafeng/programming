

Java exceptions 分两类：checked exceptions 和 unchecked exceptions。

## checked exception

表示程序控制之外的问题，外界问题。如：file not found, io, sql, parse 等。

Java 在编译时 verify 之。故，代码中需显式 throw 或 try-catch。

```java
    private static void funcThrow() throws FileNotFoundException {
        File file = new File("not_existing_file.txt");
        FileInputStream stream = new FileInputStream(file);
    }

    private static void funcCatch() {
        File file = new File("not_existing_file.txt");
        try {
            FileInputStream stream = new FileInputStream(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
```

父类：Exception。可如下创建自己的 checked exception。

```java
    public class IncorrectFileNameException extends Exception {
        // 只要在 ctor 中调用父类的 ctor 即可：super(msg)
        public IncorrectFileNameException(String errorMessage) {
            super(errorMessage);
        }
    }
```

## unchecked exception

表示程序自己的内部逻辑问题。如：arithmetic (例如：被零除), null pointer, array index out of bounds, illegal argument 等。

Java 在编译时不会 verify 之。故，代码中无需显式 throw 或 try-catch。

父类：RuntimeException。可如下创建自己的 unchecked exception。

```java
    public class NullOrEmptyException extends RuntimeException {
        // 只要在 ctor 中调用父类的 ctor 即可：super(msg)
        public NullOrEmptyException(String errorMessage) {
            super(errorMessage);
        }
    }
```