# `.equals()`

`==` 比较两个对象的「内存位置」，是不是「同一个」对象。

`equals()` 语义上，比较两个对象的「内容」是否「一样」。

`equals()` 的默认行为其实也是 `==`。所以通常需重写 `equals()`。

重写 `equals()` 时，必须遵守的 contract：
- 自反 reflexive: an object must equal itself
- 对称 symmetric: `x.equals(y)` must return the same result as `y.equals(x)`
- 传递 transitive: 若 `x.equals(y)` 且 `y.equals(z)`，则一定有 `x.equals(z)`
- 一致 consistent: the value of `.equals()` should change only if a property that is contained in `.equals()` changes (no randomness allowed); 如果 `x.equals(y)` 返回 true，只要 x 和 y 内容一直不变，不管你重复`x.equals(y)` 多少次，返回都是 true。
- 非空性，`x.equals(null)`，永远返回 false；`x.equals(与 x 不同类型的对象)` 永远返回 false。

## 继承时，容易破坏对称性

如下所示：

```java
class Money {
    int amount;
    String code;

    @Override
    public boolean equals(Object o) {
        if (o == this) return true;
        if (!(o instanceof Money)) return false;
        Money other = (Money)o;
        boolean codeEquals = (this.code == null && other.code == null) || (this.code != null && this.code.equals(other.code));
        return this.amount == other.amount && codeEquals;
    }
}

class Voucher extends Money {
    private String store;

    @Override
    public boolean equals(Object o) {
        if (o == this) return true;
        if (!(o instanceof Voucher)) return false;
        Voucher other = (Voucher)o;
        boolean codeEquals = (this.code == null && other.code == null) || (this.code != null && this.code.equals(other.code));
        boolean storeEquals = (this.store == null && other.store == null) || (this.store != null && this.store.equals(other.store));
        return this.amount == other.amount && codeEquals && storeEquals;
    }
}

Money cash = new Money(42, "USD");
Voucher voucher = new Voucher(42, "USD", "Amazon");

voucher.equals(cash) => false // As expected.
cash.equals(voucher) => true // That's wrong.
```

用 composition 而不继承，可解决此问题。

```java
class Voucher {
    private Money value;
    private String store;

    Voucher(int amount, String code, String store) {
        this.value = new Money(amount, code);
        this.store = store;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this) return true;
        if (!(o instanceof Voucher)) return false;
        Voucher other = (Voucher) o;
        boolean valueEquals = (this.value == null && other.value == null) || (this.value != null && this.value.equals(other.value));
        boolean storeEquals = (this.store == null && other.store == null) || (this.store != null && this.store.equals(other.store));
        return valueEquals && storeEquals;
    }
}
```

# `.hashCode()`

返回一个 integer 值。

与 `.equals()` 关系很紧密。下面的 contract 里，所有三条，都涉及到了 `.equals()`。

All three criteria in the `.hashCode()` contract mention the `.equals()` method in some way:

- internal consistency: 只有在 `equals()` 里用到的某个属性变化时，`hashCode()` 的返回值才能变。
- equals consistency: 若 `x.equals(y) == true`，则 x、y 的 `.hashCode()` 返回值应该相同。
- collisions: 即使 `x.equals(y) != true`，x、y 的 hashCode 也有可能相同。unequal objects may have the same hashCode。（当然，若 hashcode 不相等则可能提高性能）

<font color=green>重要：如果重写了 `equals()`，就必须重写 `.hashCode()`，以免违反第二条。</font>

重要性：若对象用作 map 或 set 的 key ...
