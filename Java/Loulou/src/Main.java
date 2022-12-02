import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import java.util.Vector;

public class Main {
    public static void main(String[] args) throws IOException {
        Day1.hard(parseInput());
    }

    public static Vector<String> parseInput() throws IOException {
        File f = new File("inputs.txt");
        Scanner reader = new Scanner(f);
        Vector<String> res = new Vector<String>();
        while (reader.hasNextLine()) {
            res.add(reader.nextLine());
        }
        return res;
    }
}
