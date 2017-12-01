package myPackage;
import java.io.*;
import java.util.*;

public class Pancake {
	public static void main(String[] args) throws IOException{
		try{
			int lineCount=0;
			String[] numOfText = new String[90];
			int totalTime=0;

			File file = new File("input.txt");
			FileReader fr =null;
			BufferedReader in = null;
			String s;

			fr=new FileReader(file);
			in = new BufferedReader(fr);

			//File read one sentence
			while((s=in.readLine())!=null){
				numOfText[lineCount]=s;
				lineCount++;
			}

		
			while(totalTime<lineCount)
			{
				int[][] temp = new int[lineCount][30];
				int size=0;
				for(int j=0;j<numOfText[totalTime].length();j=j+2){
					temp[totalTime][size++]= Integer.parseInt(numOfText[totalTime].substring(j,j+1));		
				}
				ArrayList<Integer> number = new ArrayList<Integer>();

				for(int j=0;j<temp[totalTime].length;j++){
					if(temp[totalTime][j]>0)
						number.add(temp[totalTime][j]);
				}
				int[] num = new int[number.size()];
				for(int i=0;i<number.size();i++){
					num[i]=number.get(i);
				}

				for(int curr_size=number.size();curr_size>1;--curr_size)
				{
					int index= findMax(num,curr_size);
					if(index != curr_size-1){
						flip(num,index);
						Print(num,num.length-index);
						flip(num,curr_size-1);
						Print(num,1);
						}
				}
				System.out.println(" ");
				totalTime++;
			}
		}
		catch (FileNotFoundException e){
			System.out.println("Error opening the file ");
			System.exit(0);{

			}
		}
	}
	/*
	 * purpose: find Max
	 * input: num array , array size 
	 * output: index of max value 
	*/
	public static int findMax(int[] num,int curr_size)
	{	
		int index=0;
		for(int i=0;i<curr_size;i++)
			if(num[index]<=num[i]){
				index=i;
				
			}
		return index;
	}
	/*purpose: flip array
	 *input: num array, index of max
	 *output: none */
	public static void flip(int[] num, int max)
	{
		int temp,start=0;
		while(start<max){
			temp=num[start];
			num[start]=num[max];
			num[max]=temp;
			start++;
			max--;
		}
	}

	/*purpose: flip array
	 *input: num array, array size
	 *output: none */
	public static void reverse (int[] num,int curr_size)
	{
		int revTime=0;
		int temp,start=0;
		while(start<curr_size){
			temp=num[start];
			num[start]=num[curr_size-1];
			num[curr_size-1]=temp;
			start++;
			curr_size--;
		}
		Print(num,++revTime);
	}
	/*purpose: Print array
	 * input: num array, flip point
	 * output: none
	 */
	public static void Print(int[] num,int flipPoint)
	{
		System.out.print("Flip("+(flipPoint)+") ");
		for(int i=0;i<num.length;i++)
		{
			System.out.print(num[i]+" ");
		}
		
		System.out.println(" ");
	}


}