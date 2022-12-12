import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Vector;

import static java.lang.Math.abs;
import static java.lang.Math.max;

public class Day9 {
    boolean[][] visitedPositions;
    Vector<String> moves;

    Day9() throws FileNotFoundException {
        File f = new File("inputs.txt");
        Scanner reader = new Scanner(f);
        visitedPositions = new boolean[1000][1000]; //Defaults to false
        moves = new Vector<>();
        while (reader.hasNextLine()) {
            String[] move = reader.nextLine().split(" ");
            for (int i = 0; i < Integer.parseInt(move[1]); i++) {
                moves.add(move[0]);
            }
        }
    }

    int[] getNewMove(int tx, int ty, int hx, int hy) {
        // Comment coder à la truelle
        // Search move that minimizes distance to head if tail is not adjacent
        int dtx = 0, dty = 0;
        int minDist = 10;
        for (int i = -1; i<2; i++) {
            for (int j = -1; j<2; j++) {
                int ntx = tx + i, nty = ty + j;
                int nd = (ntx - hx) * (ntx - hx) + (nty - hy) * (nty - hy); // Aled
                if (nd < minDist) {
                    dtx = i;
                    dty = j;
                    minDist = nd;
                }
            }
        }
        return new int[]{dtx, dty};
    }

    void easy() {
        int hx = 500, hy = 500, tx = 500, ty = 500;
        int res = 0;
        for (String move : moves) {
            if (!visitedPositions[ty][tx]) {
                visitedPositions[ty][tx] = true;
                res += 1;
            }
            int dx = 0, dy = 0;
            if (move.equals("U")) {dy = 1;}
            if (move.equals("D")) {dy = -1;}
            if (move.equals("L")) {dx = -1;}
            if (move.equals("R")) {dx = 1;}

            hx += dx;
            hy += dy;

            if (max(abs(hx-tx), abs(hy-ty)) <= 1) {
                continue;
            }
            int[] newMove = getNewMove(tx, ty, hx, hy);
            tx += newMove[0];
            ty += newMove[1];
        }
        System.out.println(res);
    }


    void hard() {
        int[][] rope = new int[10][2];
        for (int i = 0; i<10; i++) {
            rope[i] = new int[]{500,500};
        }
        int res = 0;
        for (String move : moves) {
            int x = rope[9][0], y = rope[9][1];
            if (!visitedPositions[y][x]) {
                visitedPositions[y][x] = true;
                res += 1;
            }
            int dx = 0, dy = 0;
            if (move.equals("U")) {dy = -1;}
            if (move.equals("D")) {dy = 1;}
            if (move.equals("L")) {dx = -1;}
            if (move.equals("R")) {dx = 1;}

            rope[0][0] += dx;
            rope[0][1] += dy;

            for (int i = 1; i<10; i++) {
                int hx = rope[i-1][0], hy = rope[i-1][1], tx = rope[i][0], ty = rope[i][1];
                if (max(abs(hx - tx), abs(hy - ty)) <= 1) {
                    break;
                }
                int[] newMove = getNewMove(tx, ty, hx, hy);
                rope[i][0] += newMove[0];
                rope[i][1] += newMove[1];
            }
        }
        int x = rope[9][0], y = rope[9][1];
        if (!visitedPositions[y][x]) {
            visitedPositions[y][x] = true;
            res += 1;
        }
        System.out.println(res);
    }

}
