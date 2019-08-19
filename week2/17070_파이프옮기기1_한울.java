import java.io.*;
import java.util.*;

public class Main {
  static int n;
  static int[][] map;
  static boolean[][] visited;
  static int[] dx= {0,1,1}; // 0:가로 , 1:대각선, 2:세로
  static int[] dy= {1,1,0};
  static int result=0;
  static boolean flag;
  public static void solve(int x, int y, int d) {
    if(x==n-1&&y==n-1) {
      result++;
      return;
    }
    if(d==0) {   // 가로
      for(int i=0; i<2; i++) {
        if(i==1) { // 대각선으로 이동 가능한지 확인
          diagonal(x,y);
        }
        else {
          int nx=x+dx[i];
          int ny=y+dy[i];
          if(nx<0||nx>n-1||ny<0||ny>n-1) continue;
          if(map[nx][ny]==1) continue;
          solve(nx,ny,i);
        }
      }
    }
    else if(d==2) {  // 세로
      for(int i=1; i<3; i++) {
        if(i==1) {
          diagonal(x,y);
        }
        else {
          int nx=x+dx[i];
          int ny=y+dy[i];
          if(nx<0||nx>n-1||ny<0||ny>n-1) continue;
          if(map[nx][ny]==1) continue;
          solve(nx,ny,i);
        }
      }
    }
    else {      // 대각선
      for(int i=0; i<3; i++) {
        if(i==1) {
          diagonal(x,y);
        }
        else {
          int nx=x+dx[i];
          int ny=y+dy[i];
          if(nx<0||nx>n-1||ny<0||ny>n-1) continue;
          if(map[nx][ny]==1) continue;
          solve(nx,ny,i);
        }
      }
    } 
  }
  public static void diagonal(int x, int y) {   // 대각선으로 이동 가능한지 확인
    flag=true;
    for(int j=0; j<3; j++) {
      int nx=x+dx[j];
      int ny=y+dy[j];
      if(nx<0||nx>n-1||ny<0||ny>n-1) {
        flag=false;
        break;
      }
      if(map[nx][ny]==1) {
        flag=false;
        break;
      }
    }
    if(flag) {
      solve(x+dx[1],y+dy[1],1);
    }
  }
  public static void main(String[] args) throws Exception{
    BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
    n=Integer.parseInt(br.readLine());
    map=new int[n][n];
    for(int i=0; i<n; i++) {
      StringTokenizer st = new StringTokenizer(br.readLine());
      for(int j=0; j<n; j++) {
        map[i][j]=Integer.parseInt(st.nextToken());
      }
    }
    solve(0,1,0);
    System.out.println(result);
  }
}
