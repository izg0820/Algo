import java.io.*;
import java.util.*;

import com.sun.management.GarbageCollectionNotificationInfo;
public class SmartElephant {
	public static int[] result = new int[10];
	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		int count=0;
		String info;

		System.out.print("Push the number of elephant: ");
		count=sc.nextInt();
		String garbage= sc.nextLine();// for enter input 
		int[][] elephant = new int[count][2];

		System.out.println("Push elephant weight and IQ: "); //input format is an elephant weight and an IQ
		for(int i=0;i<count;i++){
			info= sc.nextLine();
			String[] s= info.split(("\\s"));// divide the sentence according to the spacing between words.
			elephant[i][0]=Integer.parseInt(s[0]);
			elephant[i][1]=Integer.parseInt(s[1]);
		}	
		sort(elephant);
		System.out.println(" ");
		DP(count,elephant);
		Print(elephant,result);
	}
	
	/*purpose: sort 
	 * input: elephant information 
	 * output: sorted elephant array
	 * */
	public static int[][] sort(int[][] info)
	{
		int temp1=0,temp2;
		for(int j=0;j<info.length-1;j++){
			for(int i=0;i<info.length-1;i++){
				if(info[i][0]>info[i+1][0]){
					temp1=info[i][0];
					info[i][0]=info[i+1][0];
					info[i+1][0]=temp1;
					temp2=info[i][1];
					info[i][1]=info[i+1][1];
					info[i+1][1]=temp2;
				}
			}
		}
		return info;
	}
	
	/*purpose: write table to find the maximum sequence
	 * input: elephant info array and the number of elephant value
	 * output: none*/
	public static void DP(int count,int[][] elephant){
		int[][] table = new int[count][count];
		int compareTime=0;
		int criteriaIQ,criteriaWeight;
		do{
			table[compareTime][compareTime]=1;
			criteriaIQ=elephant[compareTime][1];
			criteriaWeight=elephant[compareTime][0];
			for(int j=compareTime;j<=elephant.length-1;j++){
				if(j==elephant.length-1)
					break;
				if((criteriaIQ>elephant[j+1][1])&&(criteriaWeight!=elephant[j+1][0])){
					//If you gain weight, you add 1 to the previous value if you have less IQ.
					criteriaIQ=elephant[j+1][1];
					criteriaWeight=elephant[j+1][0];
					table[compareTime][j+1]=table[compareTime][j]+1;
				}
				else 
					table[compareTime][j+1]=table[compareTime][j];
			}
			compareTime++;
		}while(compareTime<=elephant.length-1);
		findIndex(table,count);
	}
	
	/*purpose: print result
	 * input: table array and position of maximum value index
	 * out[put: none;
	 * */
	public static void Print(int[][] arr,int[] index){
		int max= index[0];
		System.out.println(max);
		for(int i=1;i<index.length;i++){
			System.out.println(arr[index[i]][0]+" "+arr[index[i]][1]);
		}
	}
	
	/*purpose: find the maximum value in table 
	 * input : table array and the number of elephant value 
	 * output: result array 
	 * */
	public static int[] findIndex(int[][] table,int count){
		int max=table[0][count-1];
		int maxIndex=0;
		for(int i=0;i<table.length-1;i++){
			if(max<table[i+1][count-1]){
				max=table[i+1][count-1];
				maxIndex=i+1;
			}
		}
		result = new int[max+1];
		int k=2;
		result[0]=max;
		result[1]=table[maxIndex][maxIndex];
		for(int i=maxIndex;i<table[maxIndex].length-1;i++){
			if(table[maxIndex][i]!=table[maxIndex][i+1]){
				result[k]=i+1;
				k++;
			}
			else{
				continue;
			}		
		}
		return result;
	}
}
