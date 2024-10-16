import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.JsonNode;

import java.io.Reader;
import java.io.File;
import java.io.StringReader;
import java.io.InputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;

import java.net.URL;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;

import lombok.Getter;
import lombok.Setter;

/*
  mvn -f pom.json.xml dependency:copy-dependencies -DoutputDirectory=./java-lib
  javac -classpath java-lib/*: json-jackson-demo.java
  java -classpath java-lib/*:. JacksonDemo
*/

@Setter
@Getter
class Car {
    private String brand = null;
    private String color;
    private int doors = 0;

    public String toString() {
        return String.format("brand:%s, color:%s, doors:%d", brand, color, doors);
    }
}

class JacksonDemo {
    private static void t1() {
        ObjectMapper objectMapper = new ObjectMapper();

        try {
            // string -> java object
            String str = "{ \"color\" : \"Black\", \"brand\" : \"BMW\", \"doors\" : 4 }";
            Car c1 = objectMapper.readValue(str, Car.class);
            System.out.println(c1);

            // string input stream -> java object
            Reader reader = new StringReader(str);
            Car c2 = objectMapper.readValue(reader, Car.class);
            System.out.println(c2);

            // string byte array -> java object
            byte[] bytes = str.getBytes("UTF-8");
            Car c2x = objectMapper.readValue(bytes, Car.class);
            System.out.println(c2x);

            // file -> java object
            File file = new File("data/car2.json");
            Car c3 = objectMapper.readValue(file, Car.class);
            System.out.println(c3);

            // url -> java object
            URL url = new URL("file:data/car2.json");
            Car c4 = objectMapper.readValue(url, Car.class);
            System.out.println(c4);

            // byte input stream -> java object
            InputStream input = new FileInputStream("data/car2.json");
            Car c5 = objectMapper.readValue(input, Car.class);
            System.out.println(c5);

            // string -> java array
            String strArray = "[{\"brand\":\"ford\", \"color\":\"red\"}, {\"brand\":\"Fiat\"}]";
            Car[] cars = objectMapper.readValue(strArray, Car[].class);
            for (Car c : cars) {
                System.out.println(c);
            }

            // string -> java list
            List<Car> cars2 = objectMapper.readValue(strArray, new TypeReference<List<Car>>(){});
            System.out.println(cars2);
            // 输出: [brand:ford, color:red, doors:0, brand:Fiat, color:null, doors:0]

            // string -> java map
            Map<String, Object> jm = objectMapper.readValue(str, new TypeReference<Map<String,Object>>(){});
            System.out.println(jm);
            // 输出: {color=Black, brand=BMW, doors=4}
            // 注意，strArray 不能用此法转成 map

            // todo: strng -> list of map

            // Map<String, Object> jm2 = objectMapper.readValue(strArray, new TypeReference<Map<String,Object>>(){});
            // System.out.println(jm2);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void t2() {
        ObjectMapper objectMapper = new ObjectMapper();

        Car car = new Car();
        car.setBrand("bmw");
        car.setColor("brown");
        car.setDoors(6);

        try {
            objectMapper.writeValue(new FileOutputStream("data/car-output.json"), car);
            String str = objectMapper.writeValueAsString(car);
            System.out.println(str);

            byte[] b = objectMapper.writeValueAsBytes(car);
            System.out.println(new String(b));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void t3() {
        ObjectMapper objectMapper = new ObjectMapper();

        String str =
                "{ \"brand\" : \"Mercedes\", \"doors\" : 5," +
                "  \"owners\" : [\"John\", \"Jack\", \"Jill\"]," +
                "  \"nestedObject\" : { \"field\" : \"value\" } }";

        try {
            // JsonNode jn = objectMapper.readValue(str, JsonNode.class);
            JsonNode jsonNode = objectMapper.readTree(str);

            JsonNode brandNode = jsonNode.get("brand");
            String brand = brandNode.asText();
            System.out.println("brand = " + brand);

            JsonNode doorsNode = jsonNode.get("doors");
            int doors = doorsNode.asInt();
            System.out.println("doors = " + doors);

            JsonNode array = jsonNode.get("owners");
            JsonNode jsonNode2 = array.get(0);
            String john = jsonNode2.asText();
            System.out.println("john  = " + john);

            JsonNode child = jsonNode.get("nestedObject");
            JsonNode childField = child.get("field");
            String field = childField.asText();
            System.out.println("field = " + field);
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
    public static void main(String[] args) {
        t1();
        t2();
        t3();
    }

}
