# Jackson

- Spring MVC 框架默认用 Jackson 解析 Json
- 依赖的 jar 包较少
- 与 Gson 相比，Jackson 解析大 json 文件快
- 运行时占内存少，性能好
- API 灵活，易扩展、定制
- 社区较活跃，更新快

其他 json 库：fastjson by Alibaba，Gson by Google

三个核心模块：
- jackson-core，底层，"流模式"解析 API，包括 JsonPaser 和 JsonGenerator
- jackson-annotations，注解包
- jackson-databind，数据绑定包，"对象绑定" 解析的相关 API （ ObjectMapper ）和 "树模型" 解析的相关 API （JsonNode）

依赖关系见 [`pom` 文件](code/_json-demo/pom.json.xml)。`jackson-databind` 依赖另两个，所以 pom 文件中可以只显式添加 `jackson-databind` 依赖，另两个则会 transitively 加入。

```xml
    <dependency>
      <groupId>com.fasterxml.jackson.core</groupId>
      <artifactId>jackson-databind</artifactId>
      <version>2.18.0</version>
    </dependency>
```

常用 ObjectMapper。更底层的 JsonParser 一般用不到。

三个类型：
- json: 表示 json 字符串、文件、输入流、url、byte 数组等
- object: 表示 java class 的 object
- JsonNode: jackson tree model 里的 JsonNode

互相转换：
- json -> object: `readValue()`
- object -> json: `writeValue()`
- json -> JsonNode: `readTree()` 或 `readValue(..., JsonNode.class)`
- JsonNode -> json: `writeValue()`
- object -> JsonNode: `valueToTree()`
- JsonNode -> object: `treeToValue()`

[完整代码](code/_json-demo/json-jackson-demo.java)

用到的 java object 的 class：

```java
    @Setter
    @Getter
    class Car {
        private String brand = null;
        private String color;
        private int doors = 0;
        public String toString() { /* */ }
    }
```

## json (string, file，url，input stream 等) -> java object

默认情况下，json 字段名与 class 中 `getter()`、`setter()` 方法名字对应。若需其他方式，需自定义 serializer 和 deserializer，或用 Jackson annotation。

代码示例如下。注意，各 `readValue()` 方法都需 catch IOException，这里略。

```java
    ObjectMapper objectMapper = new ObjectMapper();

    // -> java object。以 String 为例，其他 src 见具体代码
    String str = "{ \"color\" : \"Black\", \"brand\" : \"BMW\", \"doors\" : 4 }";
    Car c1 = objectMapper.readValue(str, Car.class);

    // string -> java array 或 list
    String strArray = "[{\"brand\":\"ford\", \"color\":\"red\"}, {\"brand\":\"Fiat\"}]";
    Car[] cars = objectMapper.readValue(strArray, Car[].class);
    List<Car> cars2 = objectMapper.readValue(strArray, new TypeReference<List<Car>>(){});

    // string -> java map
    Map<String, Object> jm = objectMapper.readValue(str, new TypeReference<Map<String, Object>>(){});
```

忽略未知的 json 字段、不允许基本类型为 null

```java
    objectMapper.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
    objectMapper.configure(DeserializationFeature.FAIL_ON_NULL_FOR_PRIMITIVES, true);
```

自定义反序列化：to add later

## java object -> json (string, file, byte array 等)

三种方式
- `writeValue()` 写入文件
- `writeValueAs()` 写入 String
- `writeValueAsBytes()` 写入 byte array

```java
    ObjectMapper objectMapper = new ObjectMapper();
    Car car = new Car(...);

    objectMapper.writeValue(new FileOutputStream("data/car-output.json"), car); // 写到 file
    String str = objectMapper.writeValueAsString(car); // 写到 string
    byte[] b = objectMapper.writeValueAsBytes(car); // 写到 byte array
```

### jackson 日期转化

Date -> long
Date -> String

## jackson JSON tree model

## json -> Jackson JsonNode

直接 `readTree()` 方法

或 `readValue()` 但第二个参数是固定的 `JsonNode.class`，而不是各类的 class 如 `Car.class`。

```java
    String str = "{ \"color\" : \"Black\", \"type\" : \"FIAT\" }";
    JsonNode jsonNode = objectMapper.readTree(str);
    // JsonNode jn = objectMapper.readValue(str, JsonNode.class);
    String color = jsonNode.get("color").asText();
```

## Jackson JsonNode -> json

`writeValue()` 的各种形式

```java
    JsonNode jsonNode = ...;
    String json = objectMapper.writeValueAsString(jsonNode);
```

## java object -> Jackson JsonNode

`valueToTree()` 方法

```java
    ObjectMapper objectMapper = new ObjectMapper();
    Car car = new Car(...);
    JsonNode carJsonNode = objectMapper.valueToTree(car);
```

