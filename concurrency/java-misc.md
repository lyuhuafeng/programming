# 反射 reflection

是指：程序在运行期，即使对某对象一无所知（甚至连是什么 class 都不知道），也可以拿到该对象的所有信息，并可调用其方法。


JVM 加载 class，每加载一种 class，就创建一个「Class 类型的实例」或「Class 对象」。

这里的「Class 类型」是一个名叫 `Class` 的 class，大概长这样。注意其私有 ctor，所以我们无法创建其实例，只有 jvm 才可以。jvm 就是在加载 class 时创建。

```java
    public final class Class {
        private Class() {} // 
    }
```

三种方法获取某 class 对应的 Class 对象：

1. 通过类的 `class` 静态成员变量：`Class cls = String.class;`
2. 通过对象的 `getClass()` 方法：`String s = "Hello"; Class cls = s.getClass();`
3. 通过完整类名：`Class cls = Class.forName("java.lang.String");`

注意，Class 对象是唯一的，但 instanceof 不是唯一的。

```java
String getFullName(Object obj) {
    // 若知道类名，则可强制转换，不用反射
    Person p = (Person) obj;
    return p.getFirstName() + " " + p.getLastName();

    // 若不知道类名，则用反射
    Class cls = obj.getClass();
    return (String) cls.getField("firstName").get(obj) + " " + (String) cls.getField("lastName").get(obj);
}
```

动态加载

JVM 在执行 Java 程序时，并不是一次性把所有用到的 class 全部加载到内存，而是第一次需要用到 class 时才加载。

# 注解 annotation

三类：

1. SOURCE 类型，由编译器使用。编译器用过就扔了，注解信息不进入 .class 文件。
2. CLASS 类型，由工具处理 .class 文件时使用。如：加载 class 时动态修改。注解信息只存在 class 文件中，不会被加载进 jvm。
3. RUNTIME 类型。注解信息会被加载到 jvm 中，程序运行期能读取。

## 预定义的：

`@override`：告诉编译器，该方法是 override 了父类的同名方法。不写也可以。但如果写了，编译器就会检查是否 override 正确了。最好用上。

`@Deprecated`：告诉编译器，该方法已过时。调用该方法会警告。

`@SuppressWarnings`：告诉编译器，忽略指定的警告。

`@FunctionalInterface`：告诉编译器，该接口是函数式接口。

还有一些定义在 `java.lang.annotation` 里的，称为 meta-annotation，是「注解的注解」：`@Retention`、`@Documented`、`@Target`、`@Inherited`、`@Repeatable`

## 使用场景

junit 工具，运行所有 `@Test` 注解的方法。

代码分析，代码生成，文档生成，test case 生成，etc

运行时：加载 class 时动态修改；依赖注入框架（dependency injection frameworks）等。

使用场景：自定义一个 `@Range` 注解，用于检查某个字段的长度是否在 min 和 max 之间。

```java
    // 自定义
    @Retention(RetentionPolicy.RUNTIME)
    @Target(ElementType.FIELD)
    public @interface Range {
        int min() default 0;
        int max() default 255;
    }

    // 代码中使用
    public class Person {
        @Range(min=1, max=20)
        public String name;

        @Range(max=10)
        public String city;
    }

    // 运行时检查
    void check(Person person) throws IllegalArgumentException, ReflectiveOperationException {
        for (Field field : person.getClass().getFields()) { // 遍历所有字段
            Range range = field.getAnnotation(Range.class); // 获取该字段上定义的 range 值
            if (range != null) {
                Object value = field.get(person); // 获取字段的值
                if (value instanceof String s) { // 若值是 string 类型，则检查是否满足 range 限制
                    if (s.length() < range.min() || s.length() > range.max()) {
                        throw new IllegalArgumentException("Invalid field: " + field.getName());
                    }
                }
            }
        }
    }
```

# ref
- https://liaoxuefeng.com/books/java/reflection/index.html
- https://liaoxuefeng.com/books/java/annotation/index.html