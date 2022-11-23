import java.util.*;
import java.io.*;
import java.net.*;

public class client 
{

	public static void main(String[] args) throws Exception
	{
		Socket sock=new Socket("127.0.0.1",3000);
		
		BufferedReader keyRead=new BufferedReader(new InputStreamReader(System.in));
		OutputStream ostream=sock.getOutputStream();
		PrintWriter pwrite=new PrintWriter(ostream,true);
		InputStream istream=sock.getInputStream();
		BufferedReader receiveRead=new BufferedReader(new InputStreamReader(istream));
		
		System.out.println("Client is Ready");
		String receiveMessage,sendMessage,temp;
		while(true)
		{
			System.out.println("Press any key to start RPC");
			temp=keyRead.readLine();
			sendMessage=temp.toLowerCase();
			pwrite.println(sendMessage);
			
			System.out.println("Enter first paramter : ");
			sendMessage=keyRead.readLine();
			pwrite.println(sendMessage);
			System.out.println("Enter second parameter : ");
			sendMessage=keyRead.readLine();
			pwrite.println(sendMessage);
			
			System.out.print("Marshalling parameters and sending message");
			
			System.out.flush();
			if((receiveMessage=receiveRead.readLine())!=null)
			{
				System.out.println(receiveMessage);
			}
		}
	}

}
