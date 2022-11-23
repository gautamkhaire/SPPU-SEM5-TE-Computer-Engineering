import java.util.*;
import java.io.*;
import java.net.*;

public class server 
{
	public static void main(String[] args) throws Exception
	{
		ServerSocket sersock=new ServerSocket(3000);
		System.out.println("Server is Ready");
		Socket sock=sersock.accept();
		
		BufferedReader keyRead=new BufferedReader(new InputStreamReader(System.in));
		OutputStream ostream=sock.getOutputStream();
		PrintWriter pwrite=new PrintWriter(ostream,true);
		InputStream istream=sock.getInputStream();
		BufferedReader receiveRead=new BufferedReader(new InputStreamReader(istream));
		
		String fun;
		int a,b,c;
		while(true)
		{
			fun=receiveRead.readLine();
			if(fun!=null)
			{
				System.out.println("RPC Started");
			}
			
			a=Integer.parseInt(receiveRead.readLine());
			System.out.println("Parameter 1 : "+a);
			b=Integer.parseInt(receiveRead.readLine());
			System.out.println("Parameter 2 : "+b);
			c=a*b;
			
			System.out.println("Calculation Done. Sending result as Message!");
			pwrite.println("Result is : Multiplication = "+c);
			System.out.flush();
			
		}
		
	}

}
