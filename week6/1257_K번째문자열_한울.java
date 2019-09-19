import java.io.*;
import java.util.*;

public class Solution {
  static int C,k,len;
  static String str;
  static Set<String> word; 
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    C=Integer.parseInt(br.readLine());
    for(int c=1; c<=C; c++) {
      k=Integer.parseInt(br.readLine())-1;
      str=br.readLine();
      len=str.length();
      word=new HashSet<>();
      for(int t=1; t<=len; t++) { // t개 선택
        for(int i=0; i<=len-t; i++) { // i번째
          word.add(str.substring(i,i+t));
        }
      }
      List list = new ArrayList(word);
      Collections.sort(list);
      if(list.size()<=k) {
        System.out.println("#"+c+"none");
        continue;
      }
      System.out.println("#"+c+" "+list.get(k));
    }
  }
}
