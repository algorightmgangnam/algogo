import java.io.*;
import java.util.*;

public class Main{
  static int n,m,d;
  static int[][] initmap,map,copymap;
  static boolean[] arr;
  static ArrayList<Integer> archer;
  static int[] dx= {0,-1,0};
  static int[] dy= {-1,0,1};
  static PriorityQueue<Pair> q;
  static int result=Integer.MIN_VALUE;

  public static void solve(int cnt, int index) {
    if(cnt==3) {
      init();
      go();
      return;
    }
    else {
      for(int i=index; i<m; i++) {
        arr[i]=true;
        solve(cnt+1,i+1);
        arr[i]=false;
      }
    }
  }
  
  public static void go() {
    archer=new ArrayList<>();
    for(int i=0; i<m; i++) { // 궁수 배치.
      if(arr[i]) archer.add(i);
    }
    int total=0;
    while(isPossible()) {
      // copy map;
      for(int i=0; i<n; i++) { 
        for(int j=0; j<m; j++) {
          copymap[i][j]=map[i][j];
        }
      }
      // 궁수3명이 적을 공격
      for(int t=0; t<3; t++) {
        int tx=n;
        int ty=archer.get(t);
        q=new PriorityQueue<>();
        for(int i=n-1; i>=0; i--) { // d이하의 거리에 있는 모든 적을 우선순위 큐에 add.
          for(int j=0; j<m; j++) {
            int dist=Math.abs(tx-i)+Math.abs(ty-j);
            if(dist>d) continue;
            if(map[i][j]==1) q.add(new Pair(i, j, dist));
          }
        }
        if(q.size()!=0) { // 적을 한명이라도 죽였으면, 
          Pair tmp=q.poll();
          if(copymap[tmp.x][tmp.y]!=0) {
            copymap[tmp.x][tmp.y]=0;
            total++;
          }
          
        }
      }
      
      // update map;
      for(int i=0; i<n; i++) { 
        for(int j=0; j<m; j++) {
          map[i][j]=copymap[i][j];
        }
      }
      
      // move map;
      for(int i=n-2; i>=0; i--) { 
        for(int j=0; j<m; j++) {
          map[i+1][j]=map[i][j];
        }
      }
      for(int j=0; j<m; j++) { 
        map[0][j]=0;
      }

      /*for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
          System.out.print(map[i][j]+" ");
        }
        System.out.println();
      }*/
    }
    if(result<total) result=total;
  }
  
  public static boolean isPossible() {
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        if(map[i][j]==1) return true;
      }
    }
    return false;
  }
  public static void init() {
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        map[i][j]=initmap[i][j];
      }
    }
  }
  public static class Pair implements Comparable<Pair>{
    int x,y,dist;
    public Pair(int x, int y, int dist) {
      this.x=x;
      this.y=y;
      this.dist=dist;
    }
    @Override
    public int compareTo(Pair o) {
      if(dist==o.dist) {
        return Integer.compare(y,o.y);
      }
      return Integer.compare(dist, o.dist);
    }
  }
  
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    n=Integer.parseInt(st.nextToken());
    m=Integer.parseInt(st.nextToken());
    d=Integer.parseInt(st.nextToken());
    initmap=new int[n][m];
    map=new int[n][m];
    copymap=new int[n][m];
    arr=new boolean[m];
    for(int i=0; i<n; i++) {
      st=new StringTokenizer(br.readLine());
      for(int j=0; j<m; j++) {
        initmap[i][j]=Integer.parseInt(st.nextToken());
      }
    }
    solve(0,0);
    System.out.println(result);
  }
}
