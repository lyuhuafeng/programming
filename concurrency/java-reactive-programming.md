
ref:
- https://medium.com/globant/reactive-programming-project-reactor-rx-java-java-9-reactive-flow-881f5070f7df
- https://www.baeldung.com/java-9-reactive-streams
- https://www.baeldung.com/cs/reactive-programming
- https://www.baeldung.com/reactor-core

Reactive Streams is a specification for asynchronous stream processing.

non-blocking, asynchronous and event driven processing to data streams. It facilitates automatic propagation of changed data flow.

多种实现
- Project Reactor
- Rx-Java
- Java 9 Reactive Flow

reactive programming 的四根支柱（四个 interface）
- `Publisher`
  - `subscribe(Subscriber<? super T> subscriber)`
- `Subscriber`
  - `onSubscribe(Subscription subscription)`
  - `onNext(T item)`
  - `onError(Throwable throwable)`
  - `onComplete()`
- `Subscription`
  - `request(Long n)`
  - `cancel()`
- `Processor extends Subscriber<T> , Publisher<T>`

事件

- subscriber 调用 publisher 的 `subscribe()` 方法，以 subscribe
- publisher 返回一个 subscription 对象给 subscriber
- subscriber 调用自己的 `onRequest()` 方法，向 publisher 请求数据
- publisher 发出（emits）events 1 to N times via `onNext`；最终发出 onComplete event。

## Project Reactor

提供了 Spring-WebFlux，在 spring boot 程序中

两种数据类型：
- Flux : Publisher that can publish 0 or N elements.
- Mono : Publisher that can publish 0 or 1 elements.

```java
    Flux<Stock> publisher = Flux.just(
                    new Stock("TCS", "3000"),
                    new Stock("infosys", "1800"),
                    new Stock("toyota", "2500"),
                    new Stock("hcl", "1500")).log();
    publisher.subscribe(stock -> log.debug("processing stock {} with price {}",
                    stock.getName(), stock.getPrice()));
```

## Rx-Java

是 ReactiveX 的 Java 实现。（ReactiveX 想给不同语言提供同样的 reactive programming 概念）

主要是 Android 在用。

主要组件
- Observable：基本就是 publisher
- Observer：基本就是 subscriber

创建 Observable 的若干方式：Observable, Flowable, Completable, Single, Maybe

## Java 9 Reactive Flow

在 java.util.concurrent.Flow 中，引入了 reactive streams。

在 java.util.concurrent.Flow 中，定义了核心接口 `Publisher`、`Subscriber`、`Subscription`、`Processor`，与上年提到的四大支柱完全一致。

# vs. Java 8 streams

java 8 streams: pull model
reactive stream: push model: events are pushed to the subscribers as they come in.

Backpressure: 下游让上游少发点数据，以免下游被 overwhelm。