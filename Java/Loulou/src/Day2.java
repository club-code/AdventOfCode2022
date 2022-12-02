import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import java.util.Vector;

public class Day2 {
    Vector<String> firstColumn;
    Vector<String> secondColumn;

    Day2() throws IOException {
        File f = new File("inputs.txt");
        Scanner reader = new Scanner(f);
        this.firstColumn = new Vector<String>();
        this.secondColumn = new Vector<String>();
        while (reader.hasNextLine()) {
            String[] thisLine = reader.nextLine().split(" ");
            this.firstColumn.add(thisLine[0]);
            this.secondColumn.add(thisLine[1]);
        }
    }

    public void easy() {
        int score = 0;
        for (int i = 0; i<this.firstColumn.size(); i++) {
            int enemyPlay = getPlayScore(this.firstColumn.get(i));
            int yourPlay = getPlayScore(this.secondColumn.get(i));
            score += yourPlay + 1;
            if (yourPlay == enemyPlay) {
                score += 3;
            } else if (yourPlay == (enemyPlay + 1) % 3) {
                score += 6;
            }
        }
        System.out.println(score);
    }

    public void hard() {
        int score = 0;
        for (int i = 0; i<this.firstColumn.size(); i++) {
            int enemyPlay = getPlayScore(this.firstColumn.get(i));
            int outcome = getPlayScore(this.secondColumn.get(i));
            score += outcome*3 + (3 + enemyPlay + outcome - 1)%3 + 1;
        }
        System.out.println(score);
    }

    private static int getPlayScore(String play) {
        switch (play) {
            case "A":
            case "X":
                return 0;
            case "B":
            case "Y":
                return 1;
            case "C":
            case "Z":
                return 2;
        }
        System.out.println("Erreur");
        return -1;
    }
}
