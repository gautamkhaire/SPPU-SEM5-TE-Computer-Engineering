import java.io.*;
import java.util.*;

public class MacroPass2 {
    public static void main(String[] args) throws Exception {
        BufferedReader mntb = new BufferedReader(new FileReader("mnt.txt")); // Macro Name Table
        BufferedReader mdtb = new BufferedReader(new FileReader("mdt.txt")); // Macro Definition Table
        BufferedReader kpdtb = new BufferedReader(new FileReader("kpdt.txt")); // Keyword Parameter Default Table
        BufferedReader irb = new BufferedReader(new FileReader("intermediate.txt")); // Intermediate Code

        FileWriter fr = new FileWriter("pass2.txt"); // Pass2 Output

        HashMap<String, MNTEntry> mnt = new HashMap<>(); // {MacroName , MNT-Parameter}
        HashMap<Integer, String> aptab = new HashMap<>();
        HashMap<String, Integer> aptabInverse = new HashMap<>();

        Vector<String> mdt = new Vector<String>(); // Storing all the Macro Definition Table Statements line-by-line
        Vector<String> kpdt = new Vector<String>(); // Storing all the Keyword Parameter Default Statements
                                                    // line-by-line

        int pp, kp, mdtp, kpdtp, paramNo;
        String line;
        while ((line = mdtb.readLine()) != null) { // Filling the mdt Vector
            mdt.addElement(line);
        }
        while ((line = kpdtb.readLine()) != null) { // Filling the kpdt Vector
            kpdt.addElement(line);
        }
        while ((line = mntb.readLine()) != null) { // Filling the mnt HashMap
            String parts[] = line.split("\\s+"); // regex:"\\s+" means break on spaces, be it multiple spaces also it
                                                 // will break
            mnt.put(parts[0], new MNTEntry(parts[0], Integer.parseInt(parts[1]), Integer.parseInt(parts[2]),
                    Integer.parseInt(parts[3]), Integer.parseInt(parts[4])));

        }

        while ((line = irb.readLine()) != null) { // Processing the Intermediate Code line-by-line
            String[] parts = line.split("\\s+");
            if (mnt.containsKey(parts[0])) // If a MarcoName is there in MNT HashMap
            {
                pp = mnt.get(parts[0]).getPp(); // Getting the Position Parameters
                kp = mnt.get(parts[0]).getKp(); // Getting the Keyword Parameters
                mdtp = mnt.get(parts[0]).getMdtp(); // Getting the mdt Pointer
                kpdtp = mnt.get(parts[0]).getKpdtp(); // Getting the kpdt Pointer
                paramNo = 1;

                for (int i = 0; i < pp; i++) { // Processing the Positional Parameters
                    parts[paramNo] = parts[paramNo].replace(",", "");
                    aptab.put(paramNo, parts[paramNo]);
                    aptabInverse.put(parts[paramNo], paramNo);
                    paramNo++;
                }

                int j = kpdtp - 1;
                for (int i = 0; i < kp; i++) {
                    String temp[] = kpdt.get(j).split("\t");
                    aptab.put(paramNo, temp[1]);
                    aptabInverse.put(temp[0], paramNo);
                    j++;
                    paramNo++;
                }

                for (int i = pp + 1; i < parts.length; i++) {// Processing the Keyword Parameters
                    parts[i] = parts[i].replace(",", "");
                    String splits[] = parts[i].split("=");
                    String name = splits[0].replaceAll("&", "");
                    aptab.put(aptabInverse.get(name), splits[1]);
                }

                int i = mdtp - 1;
                while (!mdt.get(i).equalsIgnoreCase("MEND")) {
                    String splits[] = mdt.get(i).split("\\s+");
                    fr.write("+");
                    for (int k = 0; k < splits.length; k++) {
                        if (splits[k].contains("(P,")) {
                            splits[k] = splits[k].replaceAll("[^0-9]", "");// Will Contain Only Number
                            String value = aptab.get(Integer.parseInt(splits[k]));
                            fr.write(value + "\t");
                        } else {
                            fr.write(splits[k] + "\t");
                        }
                    }
                    fr.write("\n");
                    i++;
                }

                aptab.clear();
                aptabInverse.clear();
            } else // If it's Not a Marco Instruction then we need to just append it in Pass2
                   // Output File
            {
                fr.write(line + "\n");
            }

        }

        fr.close();
        mntb.close();
        mdtb.close();
        kpdtb.close();
        irb.close();
    }
}

class MNTEntry {
    String name;
    int pp, kp, mdtp, kpdtp;

    public MNTEntry(String name, int pp, int kp, int mdtp, int kpdtp) {
        super();
        this.name = name;
        this.pp = pp;
        this.kp = kp;
        this.mdtp = mdtp;
        this.kpdtp = kpdtp;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getPp() {
        return pp;
    }

    public void setPp(int pp) {
        this.pp = pp;
    }

    public int getKp() {
        return kp;
    }

    public void setKp(int kp) {
        this.kp = kp;
    }

    public int getMdtp() {
        return mdtp;
    }

    public void setMdtp(int mdtp) {
        this.mdtp = mdtp;
    }

    public int getKpdtp() {
        return kpdtp;
    }

    public void setKpdtp(int kpdtp) {
        this.kpdtp = kpdtp;
    }

}