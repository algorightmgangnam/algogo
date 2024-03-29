import java.io.*;
import java.util.*;

public class Main {
  static int r,c;
  static char[][] map;
  static int[] dx= {-1,1,0,0};
  static int[] dy= {0,0,-1,1};
  static boolean[][] visited,swvisited; 
  static Queue<Pair> q = new LinkedList<>();
  static Queue<Pair> nq = new LinkedList<>();
  static Queue<Pair> swan = new LinkedList<>();
  static Queue<Pair> nswan = new LinkedList<>();
  static ArrayList<Pair> list = new ArrayList<>();
  static int time;
  public static void solve() {
    while(true) {
      while(!q.isEmpty()) {    // 빙판을 녹인다.
        Pair tmp = q.poll();
        int tx=tmp.x;
        int ty=tmp.y;
        map[tx][ty]='.';
        for(int i=0; i<4; i++) {
          int nx=tx+dx[i];
          int ny=ty+dy[i];
          if(nx<0||nx>r-1||ny<0||ny>c-1) continue;
          if(visited[nx][ny]) continue;
          if(map[nx][ny]=='.') {
            q.add(new Pair(nx, ny));
            visited[nx][ny]=true;
          }else {
            nq.add(new Pair(nx, ny));
            visited[nx][ny]=true;
          }
        }
      }
      while(!swan.isEmpty()) {      // 백조 이동
        Pair tmp = swan.poll();
        int tx=tmp.x;
        int ty=tmp.y;
        for(int i=0; i<4; i++) {
          int nx=tx+dx[i];
          int ny=ty+dy[i];
          if(nx<0||nx>r-1||ny<0||ny>c-1) continue;
          if(swvisited[nx][ny]) continue;
          if(map[nx][ny]=='.') {
            swan.add(new Pair(nx, ny));
            swvisited[nx][ny]=true;
          }else {
            nswan.add(new Pair(nx, ny));
            swvisited[nx][ny]=true;
          }
        }
      }
      if(swvisited[list.get(1).x][list.get(1).y]) {
        System.out.println(time);
        return;
      }
      time++;
      q=nq;
      swan=nswan;
      nq=new LinkedList<>();
      nswan=new LinkedList<>();
    }
  }
  public static class Pair{
    int x,y;
    public Pair(int x, int y) {
      this.x=x;
      this.y=y;
    }
  }
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    r=Integer.parseInt(st.nextToken());
    c=Integer.parseInt(st.nextToken());
    map=new char[r][c];
    visited=new boolean[r][c];
    swvisited=new boolean[r][c];
    for(int i=0; i<r; i++) {
      String line=br.readLine();
      for(int j=0; j<c; j++) {
        map[i][j]=line.charAt(j);
        if(map[i][j]=='L') {
          list.add(new Pair(i, j));
          map[i][j]='.';
        }
        if(map[i][j]=='.') {
          q.add(new Pair(i, j));
          visited[i][j]=true;
        }
      }
    }
    swan.add(list.get(0));
    swvisited[list.get(0).x][list.get(0).y]=true;
    solve();
  }
}
