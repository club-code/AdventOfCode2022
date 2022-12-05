import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Stack;
import java.util.Vector;

public class Day5 {
    Stack<String>[] stacks;
    Vector<int[]> operations = new Vector<int[]>();

    Day5() throws FileNotFoundException {
        // Welcome to parsing spaghetti

        File f = new File("inputs.txt");
        Scanner reader = new Scanner(f);
        this.stacks = new Stack[9];
        for (int i = 0; i<9; i++) {
            this.stacks[i] = new Stack<String>();
        }
        String[] stackLines = new String[8];
        for (int i = 0; i<8; i++) {
            stackLines[i] = reader.nextLine();
        }
        for (int i = 7; i>=0; i--) {
            for (int j = 0; j<9; j++) {
                String chr = stackLines[i].substring(1 + 4*j, 4*j + 2);
                if (!chr.equals(" ")) {
                    this.stacks[j].push(chr);
                }
            }
        }

        reader.nextLine(); // Numbers
        reader.nextLine(); // Empty line

        while (reader.hasNextLine()) {
            String[] line = reader.nextLine().split(" ");
            int[] movement = new int[3];
            movement[0] = Integer.parseInt(line[1]);
            movement[1] = Integer.parseInt(line[3]);
            movement[2] = Integer.parseInt(line[5]);
            this.operations.add(movement);
        }
    }

    void easy() {
        for (int[] move : this.operations) {
            for (int i = 0; i<move[0]; i++) {
                this.stacks[move[2] - 1].push(this.stacks[move[1] - 1].pop());
            }
        }

        for (int i = 0; i<9; i++) {
            System.out.print(this.stacks[i].peek());
        }
    }

    void hard() {
        for (int[] move : this.operations) {
            Stack<String> tempStack = new Stack<String>(); // Oui, je suis un connard
            for (int i = 0; i<move[0]; i++) {
                tempStack.push(this.stacks[move[1] - 1].pop());
            }
            for (int i = 0; i<move[0]; i++) {
                this.stacks[move[2] - 1].push(tempStack.pop());
            }
        }

        for (int i = 0; i<9; i++) {
            System.out.print(this.stacks[i].peek());
        }
    }
}
