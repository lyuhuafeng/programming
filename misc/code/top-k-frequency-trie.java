import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

class TrieNode {
    Map<Character, TrieNode> children;
    int count;

    public TrieNode() {
        children = new HashMap<>();
        count = 0;
    }
}

class Trie {
    private TrieNode root;

    public Trie() {
        root = new TrieNode();
    }

    public void insert(String name) {
        TrieNode node = root;
        for (char ch : name.toCharArray()) {
            node = node.children.computeIfAbsent(ch, k -> new TrieNode());
        }
        node.count++;
    }

    public void getAllNames(TrieNode node, StringBuilder prefix, PriorityQueue<NameCount> minHeap, int k) {
        if (node == null) return;
        if (node.count > 0) {
            if (minHeap.size() < k) {
                minHeap.offer(new NameCount(prefix.toString(), node.count));
            } else if (node.count > minHeap.peek().count) {
                minHeap.poll();
                minHeap.offer(new NameCount(prefix.toString(), node.count));
            }
        }
        for (Map.Entry<Character, TrieNode> entry : node.children.entrySet()) {
            prefix.append(entry.getKey());
            getAllNames(entry.getValue(), prefix, minHeap, k);
            prefix.deleteCharAt(prefix.length() - 1);
        }
    }

    public PriorityQueue<NameCount> getTopKNames(int k) {
        PriorityQueue<NameCount> minHeap = new PriorityQueue<>(k);
        getAllNames(root, new StringBuilder(), minHeap, k);
        return minHeap;
    }
}

class NameCount implements Comparable<NameCount> {
    String name;
    int count;

    public NameCount(String name, int count) {
        this.name = name;
        this.count = count;
    }

    @Override
    public int compareTo(NameCount other) {
        return Integer.compare(this.count, other.count);
    }

    @Override
    public String toString() {
        return name + ": " + count;
    }
}

public class Main {
    public static void main(String[] args) {
        String[] names = {"张伟", "王伟伟", "王芳", "李伟", "李娜"}; // 示例数据
        int k = 100; // 找到前100个重名人数最多的姓名

        Trie trie = new Trie();
        for (String name : names) {
            trie.insert(name);
        }

        PriorityQueue<NameCount> topKNames = trie.getTopKNames(k);
        while (!topKNames.isEmpty()) {
            System.out.println(topKNames.poll());
        }
    }
}