import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day6 {
    String input;

    Day6() throws FileNotFoundException {
        File f = new File("inputs.txt");
        Scanner reader = new Scanner(f);
        this.input = reader.nextLine();
    }

    void easy() {
        for (int i = 0; i < this.input.length() - 4; i++) {
            if (magicFunction(this.input.substring(i, i + 4))) {
                System.out.println(i + 4);
                return;
            }
        }
    }

    void hard() {
        for (int i = 0; i < this.input.length() - 14; i++) {
            if (magicFunction(this.input.substring(i, i + 14))) {
                System.out.println(i + 14);
                return;
            }
        }
    }

    static boolean magicFunction(String str) {
        for (int i = 0; i<str.length(); i++) {
            for (int j = i+1; j<str.length(); j++) {
                if (str.substring(i, i+1).equals(str.substring(j, j+1))) {
                    return false;
                }
            }
        }
        return true;
    }
}
