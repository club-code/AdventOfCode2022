import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Vector;

public class Day3 {
    Vector<String> lines;
    Vector<String> firstHalves;
    Vector<String> secondHalves;

    Day3() throws FileNotFoundException {
        File f = new File("inputs.txt");
        Scanner reader = new Scanner(f);
        this.lines = new Vector<String>();
        this.firstHalves = new Vector<String>();
        this.secondHalves = new Vector<String>();
        while (reader.hasNextLine()) {
            String line = reader.nextLine();
            int l = line.length();
            this.lines.add(line);
            this.firstHalves.add(line.substring(0, l/2));
            this.secondHalves.add(line.substring(l/2));
        }
    }

    static int getPriority(char c) {
        if (96 < (int) c && (int) c < 123) {
            return (int) c - 96;
        } else {
            return (int) c - 38;
        }
    }

    public void easy() {
        int res = 0;
        for (int i = 0; i < this.firstHalves.size(); i++) {
            for (char cf : this.firstHalves.get(i).toCharArray()) {
                boolean shouldBreak = false;
                for (char cs : this.secondHalves.get(i).toCharArray()) {
                    if (cf == cs) {
                        res += getPriority(cf);
                        shouldBreak = true;
                        break;
                    }
                }
                if (shouldBreak) {
                    break;
                }
            }
        }
        System.out.println(res);
    }

    public void hard() {
        int res = 0;
        for (int i = 0; i < this.lines.size(); i+=3) {
            for (char c : this.lines.get(i).toCharArray()) {
                if (this.lines.get(i+1).contains(String.valueOf(c)) && this.lines.get(i+2).contains(String.valueOf(c))) {
                    System.out.println("lines : " + i + " : " + c);
                    res += getPriority(c);
                    break;
                }
            }
        }
        System.out.println(res);
    }
}
