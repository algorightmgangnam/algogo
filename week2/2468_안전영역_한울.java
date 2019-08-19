import java.io.*;
import java.util.*;

public class Main {
  static int n;
  static int[][] map,copymap;
  static boolean[][] visited;
  static Set<Integer> list=new HashSet<>(); // 수의 중복방지를 위해서 set을 사용.
  static int[] dx= {-1,1,0,0};
  static int[] dy= {0,0,-1,1};
  static int result=Integer.MIN_VALUE;
  public static void solve() {
    for(int t:list) {  // 모든 비 높이의 경우를 구한다.
      copy(); // copymap.
      rain(t); // t높이 이하인 지점은 물에 잠김.
      int total=0;
      for(int i=0; i<n; i++) {  // 안전영역 구하기.
        for(int j=0; j<n; j++) {
          if(!visited[i][j]&&map[i][j]!=-1) {
            bfs(i,j);
            total++;
          }
        }
      }
      if(result<total) result=total;
      init(); // map, visited 초기화.
    }
  }
  public static void bfs(int x, int y) {
    Queue<Pair> q = new LinkedList<>();
    q.add(new Pair(x,y));
    visited[x][y]=true;
    while(!q.isEmpty()) {
      Pair tmp = q.poll();
      int tx=tmp.x;
      int ty=tmp.y;
      for(int i=0; i<4; i++) {
        int nx=tx+dx[i];
        int ny=ty+dy[i];
        if(nx<0||nx>n-1||ny<0||ny>n-1) continue;
        if(visited[nx][ny]) continue;
        if(map[nx][ny]==-1) continue;
        q.add(new Pair(nx, ny));
        visited[nx][ny]=true;
      }
    }
  }
  public static void init() {
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        map[i][j]=copymap[i][j];
        visited[i][j]=false;
      }
    }
  }
  public static void copy() {
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        copymap[i][j]=map[i][j];
      }
    }
  }
  public static void rain(int t) {
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        if(map[i][j]<=t) {
          map[i][j]=-1;
        }
      }
    }
  }
  public static class Pair{
    int x, y;
    public Pair(int x, int y) {
      this.x=x;
      this.y=y;
    }
  }
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    n=Integer.parseInt(br.readLine());
    map=new int[n][n];
    copymap=new int[n][n];
    visited=new boolean[n][n];
    list.add(0);  // *** 아무 지역도 물에 잠기지 않을 수도 있다.***
    for(int i=0; i<n; i++) {
      String[] line=br.readLine().split(" ");
      for(int j=0; j<n; j++) {
        map[i][j]=Integer.parseInt(line[j]);
        list.add(map[i][j]);
      }
    }
    solve();
    System.out.println(result);
  }
}
