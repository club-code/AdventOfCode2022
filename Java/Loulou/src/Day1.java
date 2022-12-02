import java.io.File;
import java.io.IOException;
import java.util.Collections;
import java.util.Scanner;
import java.util.Vector;

public class Day1 {
    Vector<String> inputs;
    Day1() throws IOException {
        File f = new File("inputs.txt");
        Scanner reader = new Scanner(f);
        this.inputs = new Vector<String>();
        while (reader.hasNextLine()) {
            this.inputs.add(reader.nextLine());
        }
    }

    public void easy() {
        Vector<Integer> numbers = getIntegerVector(this.inputs);
        System.out.println(Collections.max(numbers));
    }


    public void hard() {
        Vector<Integer> numbers = getIntegerVector(this.inputs);
        System.out.println(sum3Max(numbers));
    }

    private Vector<Integer> getIntegerVector(Vector<String> inputs) {
        Vector<Integer> numbers = new Vector<Integer>();
        int sum = 0;
        for (String line: inputs) {
            if (line.equals("")) {
                numbers.add(sum);
                sum = 0;
            } else {
                sum += Integer.parseInt(line);
            }
        }
        numbers.add(sum);
        return numbers;
    }

    static int sum3Max(Vector<Integer> vec) {
        int max1 = 0;
        int max2 = 0;
        int max3 = 0;
        for (int e: vec) {
            if (e > max3) {
                if (e > max2) {
                    max3 = max2;
                    if (e > max1) {
                        max2 = max1;
                        max1 = e;
                    } else {
                        max2 = e;
                    }
                } else {
                    max3 = e;
                }
            }
        }
        return max1 + max2 + max3;
    }
}
