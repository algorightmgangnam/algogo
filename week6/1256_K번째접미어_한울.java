import java.io.*;
import java.util.*;

public class Solution {
  static int C,k,len;
  static String str;
  static String[] word;
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    C=Integer.parseInt(br.readLine());
    for(int c=1; c<=C; c++) {
      k=Integer.parseInt(br.readLine())-1;
      str=br.readLine();
      len=str.length();
      word = new String[len];
      for(int i=0; i<len; i++) {
        word[i]=str.substring(i, len);
      }
      Arrays.sort(word);
      System.out.println("#"+c+" "+word[k]);
    }
  }
}
