import java.io.*;
import java.util.*;

public class Solution {
  static int T,n;
  static int[][] map,dist;
  static int min;
  static boolean[][] visited;
  static int[] dx= {-1,1,0,0};
  static int[] dy= {0,0,-1,1};
  
  public static void bfs() {
    Queue<Pair> q = new LinkedList<>();
    q.add(new Pair(0, 0, 0));
    while(!q.isEmpty()) {
      Pair tmp = q.poll();
      int tx=tmp.x;
      int ty=tmp.y;
      int time=tmp.time;
      for(int i=0; i<4; i++) {
        int nx=tx+dx[i];
        int ny=ty+dy[i];
        if(nx<0||nx>n-1||ny<0||ny>n-1) continue;
        if(visited[nx][ny]==false||(dist[nx][ny]>time+map[nx][ny])) {
          dist[nx][ny]=time+map[nx][ny];
          q.add(new Pair(nx, ny, time+map[nx][ny]));
          visited[nx][ny]=true;
        }
      }
    }
  }
  public static class Pair{
    int x,y,time;
    public Pair(int x, int y, int time) {
      this.x=x;
      this.y=y;
      this.time=time;
    }
    
  }
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    T = Integer.parseInt(br.readLine());
    for(int c=1; c<=T; c++) {
      n=Integer.parseInt(br.readLine());
      map=new int[n][n];
      dist=new int[n][n];
      visited=new boolean[n][n];
      min = Integer.MAX_VALUE;
      for(int i=0; i<n; i++) {
        String[] str = br.readLine().split("");
        for(int j=0; j<n; j++) {
          map[i][j]=Integer.parseInt(str[j]);
        }
      }
      bfs();
      System.out.println("#"+c+" "+dist[n-1][n-1]);
      
    } // end testcase; 
  }
}
