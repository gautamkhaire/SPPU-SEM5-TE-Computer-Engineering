import java.io.*;
import java.util.*;

public class MacroPass1 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("macro_input.asm"));

        FileWriter mnt = new FileWriter("mnt.txt"); // Macro Name Table
        FileWriter mdt = new FileWriter("mdt.txt"); // Macro Definition Table
        FileWriter kpdt = new FileWriter("kpdt.txt");// Keyword Parameter Default Table
        FileWriter pnt = new FileWriter("pntab.txt"); // Parameter Name Table
        FileWriter ir = new FileWriter("intermediate.txt"); // Intermediate Code

        LinkedHashMap<String, Integer> pntab = new LinkedHashMap<>();
        String line;
        String Macroname = null;
        int mdtp = 1, kpdtp = 0, paramNo = 1, pp = 0, kp = 0, flag = 0; // flag=1 indicates some marco is been
                                                                        // processing

        while ((line = br.readLine()) != null) {
            String parts[] = line.split("\\s+");

            if (parts[0].equalsIgnoreCase("MACRO")) // MarcoName and it's parameters are processed here
            {
                flag = 1; // A Marco has Started so set flag to 1
                line = br.readLine();
                parts = line.split("\\s+");
                Macroname = parts[0];
                if (parts.length <= 1) {
                    mnt.write(parts[0] + "\t" + pp + "\t" + kp + "\t" + mdtp + "\t" + (kp == 0 ? kpdtp : (kpdtp + 1))
                            + "\n");
                    continue;
                }
                for (int i = 1; i < parts.length; i++) // Processing of Parameters
                {
                    parts[i] = parts[i].replaceAll("[&,]", "");
                    if (parts[i].contains("=")) { // Keyword parameters
                        kp++;
                        String keywordParam[] = parts[i].split("=");
                        pntab.put(keywordParam[0], paramNo++);
                        if (keywordParam.length == 2) {
                            kpdt.write(keywordParam[0] + "\t" + keywordParam[1] + "\n");
                        } else {
                            kpdt.write(keywordParam[0] + "\t - \n");
                        }
                    } else { // Positional parameters
                        pp++;
                        pntab.put(parts[i], paramNo++);
                    }
                }

                mnt.write(
                        parts[0] + "\t" + pp + "\t" + kp + "\t" + mdtp + "\t" + (kp == 0 ? kpdtp : (kpdtp + 1)) + "\n");
                kpdtp = kpdtp + kp;
            } else if (parts[0].equalsIgnoreCase("MEND")) // MEND is processed here
            {
                mdt.write(line + "\n");
                flag = kp = pp = 0; // Reinitializing everything for another Macro
                paramNo = 1;
                mdtp++;
                // Filling the Parameter Table using the LinkedHashMap pntab
                pnt.write(Macroname + ":\t");
                Iterator<String> itr = pntab.keySet().iterator();
                while (itr.hasNext()) {
                    pnt.write(itr.next() + "\t");
                }
                pnt.write("\n");
                pntab.clear();
            } else if (flag == 1) // MacroBody (Leaving the MarcoName & it's parameters) is processed here
            {
                for (int i = 0; i < parts.length; i++) {
                    if (parts[i].contains("&")) { // Any Parameter is there then it's PNTAB value is placed in MDT
                        parts[i] = parts[i].replaceAll("[&,]", "");
                        mdt.write("(P," + pntab.get(parts[i]) + ")\t");
                    } else {
                        mdt.write(parts[i] + "\t");
                    }
                }
                mdt.write("\n");
                mdtp++;
            } else {
                ir.write(line + "\n");
            }
        }

        br.close();
        mdt.close();
        mnt.close();
        ir.close();
        pnt.close();
        kpdt.close();

        System.out.println("Macro Pass1 Processing done.");
    }

}