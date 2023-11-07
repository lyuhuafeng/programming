import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Vector;

class VertexWeight {
    public int vertex;
    public int weight;

    public VertexWeight(int v, int w) {
        this.vertex = v;
        this.weight = w;
    }

    @Override
    public String toString() {
        return String.format("v:%d,w:%d", vertex, weight);
    }
}

class VertexDist {
    public int vertex;
    public int dist;

    public VertexDist(int v, int d) {
        this.vertex = v;
        this.dist = d;
    }
}

class VertexDistComparator implements Comparator<VertexDist> {
    public int compare(VertexDist v1, VertexDist v2) {
        if (v1.dist < v2.dist) {
            return -1;
        } else if (v1.dist > v2.dist) {
            return 1;
        } else {
            return 0;
        }
    }
};

// class VertexDist implements Comparator<VertexDist> {
//     public int vertex;
//     public int dist;

//     public VertexDist(int v, int d) {
//         this.vertex = v;
//         this.dist = d;
//     }
   
//     @Override
//     public int compare(VertexDist v1, VertexDist v2) {
//         if (v1.dist < v2.dist) {
//             return -1;
//         } else if (v1.dist > v2.dist) {
//             return 1;
//         } else {
//             return 0;
//         }
//     }
// };

class Solution {

    public static void addEdge(Vector<Vector<VertexWeight>> adj, int u, int v, int wt) {
        adj.get(u).add(new VertexWeight(v, wt));
        adj.get(v).add(new VertexWeight(u, wt));
    }

    public static void shortestPath(Vector<Vector<VertexWeight>> adj, int V, int src) {
        PriorityQueue<VertexDist> pq = new PriorityQueue<>(new VertexDistComparator());

        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        boolean[] visited = new boolean[V];
        Arrays.fill(visited, false);
        int[] prevs = new int[V];
        Arrays.fill(prevs, -1);

        pq.add(new VertexDist(src, 0));
        dist[src] = 0;
        prevs[src] = src;
        System.out.printf("push: vertex:%d, dist:%d, prev:%d\n", src, 0, src);

        while (pq.size() > 0) {
            int u = pq.poll().vertex;
            if (visited[u]) {
                System.out.printf("min:%d. dist:%d. already visited. skip.\n", u, dist[u]);
                continue;
            }
            visited[u] = true;
            System.out.printf("min:%d. dist:%d. set visited.\n", u, dist[u]);
            for (VertexWeight t : adj.get(u)) {
                int v = t.vertex;
                int weight = t.weight;
                System.out.printf("  calc %d -> %d (w:%d)\n", u, v, weight);
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    prevs[v] = u;
                    pq.add(new VertexDist(v, dist[v]));
                    System.out.printf("  push: vertex:%d, dist:%d, prev:%d\n", v, dist[v], prevs[v]);
                }
            }
        }

        System.out.printf("vertex distance from source\n");
        for (int i = 0; i < V; ++i) {
            System.out.printf("%d: %d\t\t", i, dist[i]);
            for (int j = i; j != src; j = prevs[j]) {
                System.out.printf((j == i ? "%d" : " <- %d"), j);
            }
            System.out.printf(" <- %d\n", src);
        }
    }


    public static void main(String[] args) {
        int V = 9; // 共9个顶点，编号从0开始

        Vector<Vector<VertexWeight>> adj = new Vector<>();
        for (int i = 0; i < V; i++) {
            adj.add(new Vector<VertexWeight>());
        }

        addEdge(adj, 0, 1, 4);
        addEdge(adj, 0, 7, 8);
        addEdge(adj, 1, 2, 8);
        addEdge(adj, 1, 7, 11);
        addEdge(adj, 2, 3, 7);
        addEdge(adj, 2, 8, 2);
        addEdge(adj, 2, 5, 4);
        addEdge(adj, 3, 4, 9);
        addEdge(adj, 3, 5, 14);
        addEdge(adj, 4, 5, 10);
        addEdge(adj, 5, 6, 2);
        addEdge(adj, 6, 7, 1);
        addEdge(adj, 6, 8, 6);
        addEdge(adj, 7, 8, 7);

        for (int i = 0; i < V; i++) {
            System.out.printf("vertex:%d, adjacent:%s\n", i, adj.get(i).toString());
        }

        shortestPath(adj, V, 0);
    }
}
