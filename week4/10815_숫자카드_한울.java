import java.io.*;
import java.util.*;

public class Main{
  static int n,m;
  static boolean[] card=new boolean[20000001];
  static int[] result;
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;
    n=Integer.parseInt(br.readLine());
    st=new StringTokenizer(br.readLine());
    for(int i=0; i<n; i++) {
      int tmp = Integer.parseInt(st.nextToken())+10000000;
      card[tmp] = true; 
    }
    m=Integer.parseInt(br.readLine());
    result = new int[m];
    st=new StringTokenizer(br.readLine());
    for(int i=0; i<m; i++) {
      int tmp = Integer.parseInt(st.nextToken())+10000000;
      if(card[tmp]==true) {
        result[i]=1;
      }else {
        result[i]=0;
      }
    }
    
    for(int i=0; i<m; i++) {
      System.out.print(result[i]+ " ");
    }
  }
}
