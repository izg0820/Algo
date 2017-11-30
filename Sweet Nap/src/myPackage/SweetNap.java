package myPackage;
import java.util.Scanner;
import java.io.*;

public class SweetNap {
	public static void main(String[] args) throws IOException{
		int lineCount=1;
		int a;
		String[] line = new String[20];//for saving file text
		for(int i=0; i<20; i++){
			line[i]="";			
		}

		try{
			File file = new File("nap.txt");
			FileReader fr =null;
			BufferedReader in = null;
			String s;

			fr=new FileReader(file);
			in = new BufferedReader(fr);

			//File read one sentence
			while((s=in.readLine())!=null){
				line[lineCount]=s;
				lineCount++;
			}
			
			//Save number of schedule each day
			int[] n =new int[20];
			int dayCount=1;
			int dayStartPoint=1;
			do{
				n[dayCount] = Integer.parseInt(line[dayStartPoint]);
				dayStartPoint=dayStartPoint+n[dayCount]+1;
				dayCount++;
			}
			while(dayStartPoint<lineCount);

			//Save time information of each sentence
			String[] temp = new String[20];
			int c=1;
			int d=1;
			int firstLinePoint=1;
			for(int i=1;i<lineCount;i++){
				if(i==firstLinePoint){
					firstLinePoint=firstLinePoint+n[c]+1;
					c++;
				}
				else {
					temp[d]=line[i].replaceAll("[^0-9]","");
					d++;			
				}
			}
			//Save time in seconds
			int[][] time = new int[dayCount][20];
			int e=1;
			int split=1;
			while(e<dayCount){
				for(int i=1;i<=n[e];i++){
					time[e][2*i-1]= (Integer.parseInt(temp[split].substring(0,2))*60*60) + (Integer.parseInt(temp[split].substring(2,4))*60);
					time[e][2*i]=(Integer.parseInt(temp[split].substring(4,6))*60*60) + (Integer.parseInt(temp[split].substring(6,8))*60);
					split++;
				}
				e++;
			}

			//calculation naptime
			int[][] naptime = new int[dayCount][10];
			int[][] start = new int[dayCount][100];
			int f=1;
			int g=1;
			for(f=1;f<dayCount;f++){
				if(time[f][1]>=36000){
					start[f][g]=36000;
					naptime[f][g++]=time[f][1]-36000;
				}
				for(int i=1;i<n[f];i++){
					if(time[f][2*i]<=time[f][2*i+1]){
						start[f][g]=time[f][2*i];
						naptime[f][g++]=time[f][2*i+1]-time[f][2*i];
					}			
				}
				if(time[f][2*n[f]]<64800){
					start[f][g]=time[f][2*n[f]];
					naptime[f][g++]=64800-time[f][2*n[f]];
				}
				g=1;
			}

			//find Max naptime
			int h=1;
			int max;
			while(h<dayCount){
				int stp=1;
				max=naptime[h][stp];
				for(int j=1;j<=n[h];j++){
					if(max<naptime[h][j+1]){	
						max=naptime[h][j+1];
						stp=j+1;
					}
				}
				String t="";
				t =String.format("%02d", (start[h][stp]/60)%60);
				System.out.print("Day # "+h+": the longest nap starts at "+start[h][stp]/60/60+":"+t);
				System.out.println(" and will last for "+max/60/60+" hours and "+(max/60)%60+" minutes.");
				h++;
			}			
		}
		catch (FileNotFoundException e){
			System.out.println("Error opening the file ");
			System.exit(0);
		}
	}
}
