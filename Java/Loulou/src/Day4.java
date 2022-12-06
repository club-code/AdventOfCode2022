import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Vector;

public class Day4 {
    Vector<String> firstElfAssignment;
    Vector<String> secondElfAssignment;

    Day4() throws FileNotFoundException {
        File f = new File("inputs.txt");
        Scanner reader = new Scanner(f);
        this.firstElfAssignment = new Vector<String>();
        this.secondElfAssignment = new Vector<String>();
        while (reader.hasNextLine()) {
            String line = reader.nextLine();
            String[] assignments = line.split(",");
            this.firstElfAssignment.add(assignments[0]);
            this.secondElfAssignment.add(assignments[1]);
        }
    }

    public void easy() {
        int res = 0;
        for (int i = 0; i < this.firstElfAssignment.size(); i++) {
            String[] assignment1 = this.firstElfAssignment.get(i).split("-");
            String[] assignment2 = this.secondElfAssignment.get(i).split("-");
            if ((Integer.parseInt(assignment1[0]) <= Integer.parseInt(assignment2[0]) && Integer.parseInt(assignment1[1]) >= Integer.parseInt(assignment2[1]) ||
                    Integer.parseInt(assignment1[0]) >= Integer.parseInt(assignment2[0]) && Integer.parseInt(assignment1[1]) <= Integer.parseInt(assignment2[1]))) {
                res += 1;
            }
        }
        System.out.println(res);
    }

    public void hard() {
        int res = 0;
        for (int i = 0; i < this.firstElfAssignment.size(); i++) {
            String[] assignment1 = this.firstElfAssignment.get(i).split("-");
            String[] assignment2 = this.secondElfAssignment.get(i).split("-");
            if ((Integer.parseInt(assignment1[0]) <= Integer.parseInt(assignment2[0]) && Integer.parseInt(assignment2[0]) <= Integer.parseInt(assignment1[1])) ||
                    (Integer.parseInt(assignment2[0]) <= Integer.parseInt(assignment1[0]) && Integer.parseInt(assignment1[0]) <= Integer.parseInt(assignment2[1]))) {
                res += 1;
            }
        }
        System.out.println(res);
    }
}