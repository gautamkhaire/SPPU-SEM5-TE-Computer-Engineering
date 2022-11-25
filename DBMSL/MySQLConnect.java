//A8-group-A-Database Connectivity: 
//Write a program to implement MySQL database connectivity with any front end language to implement Database navigation operations (add, delete, edit etc.) 
//Java- JDBC connectivity-create,insert,update,delete
// need to use project database-any one
// connector-v-5 to 8-mysql-connector-java-5.1.49-bin-jar
//package jdbcnew;

import java.util.*;
import java.sql.*;//classes,interfaces and methods

public class Test
{
    public static void main(String args[])
    {  
		try
		{  
			Class.forName("com.mysql.jdbc.Driver");  // step-1-register the driver class
			//step2- establish connection
			Connection con=DriverManager.getConnection(  
			"jdbc:mysql://10.10.12.108:3306/t31367db","t31367","t31367");
			Statement stmt=con.createStatement();//step-3 create the statement object
			//step-4- to execute the queries-execute(string sql),executeUpdate(),executeQuery()
//			stmt.executeUpdate("create table studentDetails(id int,name varchar(50),marks int,city varchar(30),primary key(id))");
			
			int option;
			Scanner scn=new Scanner(System.in);
			do
			{
				System.out.println(" ------------------ Menu ------------------ ");
				System.out.println(" 1. Insert student details ");
				System.out.println(" 2. Delete student details ");
				System.out.println(" 3. Update student details ");
				System.out.println(" 4. Display student details records ");
				System.out.println(" 5. Exit ");
				System.out.println(" Enter option : ");
				option=scn.nextInt();
				
				int rollNo;
				String name;
				int marks;
				String city;
				
				switch(option) {
					case 1:
						System.out.print(" Enter RollNo of the Student : ");
						rollNo=scn.nextInt();
						System.out.print("\n Enter Name of the Student : ");
						name=scn.next();
						System.out.print("\n Enter Marks of the Student : ");
						marks=scn.nextInt();
						System.out.print("\n Enter Name of City of the Student : ");
						city=scn.next();
						
						PreparedStatement statement=con.prepareStatement("insert into studentDetails values(?,?,?,?)");
						statement.setInt(1,rollNo);
						statement.setString(2,name); 
						statement.setInt(3,marks);
						statement.setString(4,city);
						
						statement.executeUpdate();
						
						break;
					case 2:
						System.out.println("Enter RollNo of the Student whose details are to be Deleted : ");
						rollNo=scn.nextInt();
						
						statement=con.prepareStatement("delete from studentDetails where rollno=?");  
						statement.setInt(1,rollNo);
						
						statement.execute();
						
						break;
					case 3:
						System.out.print("Enter RollNo of the Student whose details are to be Updated : ");
						rollNo=scn.nextInt();
						System.out.print("\n Enter Marks of the Student : ");
						marks=scn.nextInt();
						
						statement=con.prepareStatement("update studentDetails set marks=? where rollno=?");
						statement.setInt(1, marks);
						statement.setInt(2, rollNo);
						
						statement.execute();
						
						break;
					case 4:
						System.out.println("Student Record Details are :- ");
						ResultSet rs=stmt.executeQuery("select * from studentDetails");  
						while(rs.next())
						{  
							System.out.println(rs.getInt(1)+" "+rs.getString(2)+"\t"+rs.getInt(3)+" "+rs.getString(4));  
						}  
						break;
					case 5:
						System.exit(0);
					default:
						System.out.println("Invalid option");	
				}
			}while(option>=1 && option<=4);
		}
		catch(ClassNotFoundException | SQLException e)
		{ 
			System.out.println(e);
		}
    }
}
