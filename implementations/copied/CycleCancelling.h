// Source: https://community.topcoder.com/stat?c=problem_solution&rm=312044&rd=14730&pm=11217&cr=22840511

struct NetWork {
  static const int NVET_MAX = 60;
  static const int NEDGE_MAX = NVET_MAX * NVET_MAX * 2;

  int head[NVET_MAX], nvet, nedge;
  int dest[NEDGE_MAX], next[NEDGE_MAX], cost[NEDGE_MAX], cap[NEDGE_MAX];
  int originCap[NEDGE_MAX];

  void init() {
    memset(head, -1, sizeof head);
    nedge = 0;
    nvet = 0;
  }

  int addVertex() {
    return nvet++;
  }

  void makeEdge(int s, int t, int c, int f) //source,dest,cost,flow
      {
    next[nedge] = head[s];
    dest[nedge] = t;
    cost[nedge] = c;
    originCap[nedge] = cap[nedge] = f;
    head[s] = nedge++;
  }

  void addEdge(int s, int t, int c, int f) {
    makeEdge(s, t, c, f);
    makeEdge(t, s, -c, 0);
  }
};

#define FOREDGE(e,G,u) for(int e=G.head[u];e!=-1;e=G.next[e])
struct MaxCostFlow {
  static const int NVET_MAX = 60;
  int maxCost;
  int n;
  NetWork&network;

  MaxCostFlow(NetWork&_network) :
      network(_network) {
    n = network.nvet;
    calcMaxCostFlow();
  }

  int dist[NVET_MAX];
  int prev[NVET_MAX]; // edge-id
  bool inStack[NVET_MAX];
  int start;

  bool dfsSpfa(int u) {
    inStack[u] = true;
    FOREDGE(e,network,u)
      if (network.cap[e]) {
        int v = network.dest[e];
        int nc = dist[u] + network.cost[e];
        if (nc > dist[v]) {
          dist[v] = nc;
          prev[v] = e;
          if (inStack[v]) {
            start = v;
            return true;
          } else if (dfsSpfa(v)) {
            return true;
          }
        }
      }

    inStack[u] = false;
    return false;
  }

  bool findPositiveCycle() {
    memset(dist, 0, sizeof(int) * n);
    memset(prev, -1, sizeof(int) * n);
    memset(inStack, 0, sizeof(bool) * n);

    for (int u = 0; u < n; u++)
      if (dfsSpfa(u))
        return true;

    return false;
  }

#define prevNode(it) (it==-1?it:network.dest[prev[it]^1])
  void cancelCycle() {
    //cout<<"Start Cancel:"<<endl;
    int at = start;
    while (true) {
      int edge = prev[at];
      network.cap[edge]--;
      network.cap[edge ^ 1]++;
      maxCost += network.cost[edge];
      at = prevNode(at);
      if (at == start)
        break;
    }
  }

  void calcMaxCostFlow() {
    maxCost = 0;
    while (findPositiveCycle()) {
      cancelCycle();
    }
  }
};
