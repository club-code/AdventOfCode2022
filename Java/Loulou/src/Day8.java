import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Vector;

public class Day8 {
    Vector<Vector<Integer>> forest;

    Day8() throws FileNotFoundException {
        File f = new File("inputs.txt");
        Scanner reader = new Scanner(f);
        forest = new Vector<>();
        while (reader.hasNextLine()) {
            char[] line = reader.nextLine().toCharArray();
            Vector<Integer> treeLine = new Vector<>();
            for (char c : line) {
                treeLine.add(Integer.parseInt(String.valueOf(c)));
            }
            forest.add(treeLine);
        }
    }

    void easy() {
        int res = 0;
        for (int y = 0; y < forest.size(); y++) {
            for (int x = 0; x < forest.get(y).size(); x++) {
                int[] pos = new int[]{x, y};
                if (isVisibleFrom(pos, new int[]{1, 0}) || isVisibleFrom(pos, new int[]{0, 1}) || isVisibleFrom(pos, new int[]{-1, 0}) || isVisibleFrom(pos, new int[]{0, -1})) {
                    res += 1;
                }
            }
        }
        System.out.println(res);
    }

    void hard() {
        int res = 0;
        for (int y = 0; y < forest.size(); y++) {
            for (int x = 0; x < forest.get(y).size(); x++) {
                int[] pos = new int[]{x, y};
                int scenicScore = getScenicScoreFromSide(pos, new int[]{1, 0}) * getScenicScoreFromSide(pos, new int[]{0, 1}) *
                        getScenicScoreFromSide(pos, new int[]{-1, 0}) * getScenicScoreFromSide(pos, new int[]{0, -1});
                if (scenicScore > res) {
                    res = scenicScore;
                }
            }
        }
        System.out.println(res);
    }

    int getValue(int[] pos) {
        return forest.get(pos[1]).get(pos[0]);
    }

    boolean isVisibleFrom(int[] initialPosition, int[] direction) {
        int treeSize = getValue(initialPosition);
        int x = initialPosition[0] + direction[0];
        int y = initialPosition[1] + direction[1];
        while (0 <= x && x < forest.get(0).size() && 0 <= y && y < forest.size()) {
            if (getValue(new int[]{x, y}) >= treeSize) {
                return false;
            }
            x += direction[0];
            y += direction[1];
        }
        return true;
    }

    int getScenicScoreFromSide(int[] initialPosition, int[] direction) {
        int treeSize = getValue(initialPosition);
        int x = initialPosition[0] + direction[0];
        int y = initialPosition[1] + direction[1];
        int res = 0;
        while (0 <= x && x < forest.get(0).size() && 0 <= y && y < forest.size()) {
            res += 1;
            if (getValue(new int[]{x, y}) >= treeSize) {
                break;
            }
            x += direction[0];
            y += direction[1];
        }
        return res;
    }
}
