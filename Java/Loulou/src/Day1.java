import java.util.Collections;
import java.util.Vector;

public class Day1 {
    public static void easy(Vector<String> inputs) {
        Vector<Integer> numbers = getIntegerVector(inputs);
        System.out.println(Collections.max(numbers));
    }


    public static void hard(Vector<String> inputs) {
        Vector<Integer> numbers = getIntegerVector(inputs);
        System.out.println(sum3Max(numbers));
    }

    private static Vector<Integer> getIntegerVector(Vector<String> inputs) {
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
            System.out.println(max1 + " " + max2 + " " + max3);
        }
        return max1 + max2 + max3;
    }
}
