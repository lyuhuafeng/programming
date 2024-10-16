# 综述

把所有用到的依赖包下载到本地 java-lib 目录下：

```bash
    $ mvn -f pom.json.xml dependency:copy-dependencies -DoutputDirectory=./java-lib
```

编译运行：
```bash
    $ javac -classpath java-lib/*: json-jackson-demo.java
    $ java -classpath java-lib/*:. JacksonDemo
```

# Maven 下载依赖包

最简的 [`pom.json.xml` 文件](pom.json.xml)。其中，project、modelVersion、groupId、artifactId、version 字段都不可少。dependencies 里就是需要下载的包。

```xml
    <project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">

      <modelVersion>4.0.0</modelVersion>

      <groupId>com.myflink</groupId>
      <artifactId>flink-java</artifactId>
      <version>1.0-SNAPSHOT</version>

      <dependencies> <!-- 略 --></dependencies>

    </project>
```

所用命令如下。将所有包都下载到 `./java-lib` 目录下。(其实应该是先下载到 repository 目录，再拷到指定目录)

```bash
    mvn -f pom.json.xml dependency:copy-dependencies -DoutputDirectory=./java-lib
```

也可用下面命令，省去 pom 文件，单独下载某个包。麻烦，还是上面方法好。

```bash
    # 这个貌似只能下载到 ~/.m2/repository 目录下，后面 dest 参数没起作用
    mvn dependency:get -Dartifact=com.fasterxml.jackson.core:jackson-core:2.17.0 -Ddest=./jackson-core-2.17.0.jar

    # 这个下载完后还会从 repository 目录拷到 dest 来。但 dest 只能指定一个文件名，而不是目录。改用 -DoutputDirectory 也没用。
    mvn org.apache.maven.plugins:maven-dependency-plugin:2.4:get -Dartifact=com.fasterxml.jackson.core:jackson-core:2.17.0 -Ddest=./jackson-core-2.1111111117.0.jar
```

其他 dependencies:get 用法：

```bash
    mvn org.apache.maven.plugins:maven-dependency-plugin:2.1:get \
        -DrepoUrl=https://download.java.net/maven/2/ \
        -Dartifact=robo-guice:robo-guice:0.4-SNAPSHOT

    mvn org.apache.maven.plugins:maven-dependency-plugin:2.4:get \
        -DremoteRepositories=http://download.java.net/maven/2 \
        -Dartifact=robo-guice:robo-guice:0.4-SNAPSHOT \
        -Ddest=c:\temp\robo-guice.jar

    mvn dependency:get -DrepoUrl=something -Dartifact=group:artifact:version
```

把依赖包下载到本地 repo（而不是指定目录）

```bash
    mvn dependency:go-offline
```
