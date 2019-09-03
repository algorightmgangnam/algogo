import java.io.*;
import java.util.*;

public class Main {
  static int n,m;
  static char[][] map, copymap;
  static int result = Integer.MAX_VALUE;
  public static void solve() {
    // 8*8 체스판 선택
    for(int i=0; i<n-7; i++) {
      for(int j=0; j<m-7; j++) {
        int total=go(i,j);
        if(total<result) result=total;
      }
    }   
  }
  
  public static int go(int x, int y) {
    copymap = new char[8][8];
    for(int i=x; i<x+8; i++) {
      for(int j=y; j<y+8; j++) {
        copymap[i-x][j-y]=map[i][j];
      }
    }
    // 맨 왼쪽 위칸 = 흰색
    int totalA=0;
    for(int i=0; i<8; i=i+2) {
      for(int j=0; j<8; j=j+2) {
        if(copymap[i][j]=='B') {
          totalA++;
        }
      }
    }
    for(int i=0; i<8; i=i+2) {
      for(int j=1; j<8; j=j+2) {
        if(copymap[i][j]=='W') {
          totalA++;
        }
      }
    }
    for(int i=1; i<8; i=i+2) {
      for(int j=0; j<8; j=j+2) {
        if(copymap[i][j]=='W') {
          totalA++;
        }
      }
    }
    for(int i=1; i<8; i=i+2) {
      for(int j=1; j<8; j=j+2) {
        if(copymap[i][j]=='B') {
          totalA++;
        }
      }
    }
    
    // 맨 왼쪽 위칸 = 검은색
    int totalB=0;
    for(int i=0; i<8; i=i+2) {
      for(int j=0; j<8; j=j+2) {
        if(copymap[i][j]=='W') {
          totalB++;
        }
      }
    }
    for(int i=0; i<8; i=i+2) {
      for(int j=1; j<8; j=j+2) {
        if(copymap[i][j]=='B') {
          totalB++;
        }
      }
    }
    for(int i=1; i<8; i=i+2) {
      for(int j=0; j<8; j=j+2) {
        if(copymap[i][j]=='B') {
          totalB++;
        }
      }
    }
    for(int i=1; i<8; i=i+2) {
      for(int j=1; j<8; j=j+2) {
        if(copymap[i][j]=='W') {
          totalB++;
        }
      }
    }
    if(totalA<totalB) {
      return totalA;
    }else {
      return totalB;
    }
  }
  
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    n=Integer.parseInt(st.nextToken());
    m=Integer.parseInt(st.nextToken());
    map = new char[n][m];
    
    for(int i=0; i<n; i++) {
      String[] line = br.readLine().split("");
      for(int j=0; j<m; j++) {
        map[i][j]=line[j].charAt(0);
      }
    }
    solve();
    System.out.println(result);
  }
}
