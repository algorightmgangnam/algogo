import java.io.*;
import java.util.*;

public class Main {
  static int n,m,k;
  static int[][] map, copymap,arrtmp;
  static int[] arr;
  static ArrayList<Pair> list = new ArrayList<>();
  static Queue<Pair> q = new LinkedList<>();
  static int[] dx= {-1,1,0,0};
  static int[] dy= {0,0,-1,1};
  static int min=Integer.MAX_VALUE;

  public static void solve() {
    copymap=new int[n][m];
    arrtmp = new int[n][m];
    for(int i=0; i<n; i++) { // copy map
      for(int j=0; j<m; j++) {
        copymap[i][j]=map[i][j];
        arrtmp[i][j]=map[i][j];
      }
    }
    while(!q.isEmpty()) { // 회전 연산을 모두 수행할 때 까지.
      Pair tmp=q.poll();
      int sx=tmp.r-tmp.s;
      int sy=tmp.c-tmp.s;
      int ex=tmp.r+tmp.s;
      int ey=tmp.c+tmp.s;
      while(true) {
        if(ex==sx||ey==sy) break;
        for(int p=sy; p<ey; p++) {     // 우
          arrtmp[sx][p+1]=copymap[sx][p];
        }
        for(int p=sx; p<ex; p++) {     // 하
          arrtmp[p+1][ey]=copymap[p][ey];
        }
        for(int p=ey; p>sy; p--) {     // 좌
          arrtmp[ex][p-1]=copymap[ex][p];
        }
        for(int p=ex; p>sx; p--) {     // 상
          arrtmp[p-1][sy]=copymap[p][sy];
        }
        sx++; sy++;
        ex--; ey--;
      }
      for(int i=0; i<n; i++) { // update
        for(int j=0; j<m; j++) {
          copymap[i][j]=arrtmp[i][j];
        }
      }
    }
    cal();
  }
  
  public static void cal() {
    int tmp;
    for(int i=0; i<n; i++) {
      tmp=0;
      for(int j=0; j<m; j++) {
        tmp+=copymap[i][j];
      }
      if(tmp<min) min=tmp;
    }
  }
  
  public static boolean next_permutation() {
    int i = arr.length-1; int j = arr.length-1;
    while(i>0&&arr[i]<=arr[i-1]) {
      i -=1;
    }
    if(i<=0) return false;
    
    while(arr[i-1]>=arr[j]) {
      j-=1;
    }
    
    //swap
    int temp = arr[j];
    arr[j] = arr[i-1];
    arr[i-1] = temp;
    
    // i번째 뒤쪽을 오름차순으로 정렬.
    j=arr.length-1;
    while(i<j) {
      int tmp = arr[j];
      arr[j] = arr[i];
      arr[i] = tmp;
      i+=1; j-=1;
    }
    return true;
  }
  
  public static class Pair{
    int r,c,s;
    public Pair(int r, int c, int s) {
      this.r=r;
      this.c=c;
      this.s=s;
    }
  }
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    n=Integer.parseInt(st.nextToken());
    m=Integer.parseInt(st.nextToken());
    k=Integer.parseInt(st.nextToken());
    map=new int[n][m];
    for(int i=0; i<n; i++) {
      st=new StringTokenizer(br.readLine());
      for(int j=0; j<m; j++) {
        map[i][j]=Integer.parseInt(st.nextToken());
      }
    }
    arr=new int[k]; // 연산의 수행 순서를 저장.
    for(int i=0; i<k; i++) {
      arr[i]=i;
    }
    for(int i=0; i<k; i++) {
      st=new StringTokenizer(br.readLine());
      int r=Integer.parseInt(st.nextToken())-1;
      int c=Integer.parseInt(st.nextToken())-1;
      int s=Integer.parseInt(st.nextToken());
      list.add(new Pair(r, c, s));
    }
    
    do { // 모든 연산 순서를 수행해야한다.
      for(int i=0; i<k; i++) {
        q.add(list.get(arr[i]));
      }
      solve();
    }while(next_permutation());
    
    System.out.println(min);
  }
}
