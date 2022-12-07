package Day7;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day7 {
    final private Tree filesystem;

    public Day7() throws FileNotFoundException {
        File f = new File("inputs.txt");
        Scanner reader = new Scanner(f);
        reader.nextLine(); //Première ligne : $ cd /
        filesystem = new Tree("/", null);
        Tree current = filesystem;
        while (reader.hasNextLine()) {
            String l = reader.nextLine();
            String[] line = l.split(" ");
            if (line[0].equals("$")) {
                //current.printPath();
                //System.out.println(" " + l);
                if (line[1].equals("cd")) {
                    if (line[2].equals("..")) {
                        current = current.parent;
                    } else {
                        current = current.getChildByName(line[2]);
                    }
                }
            } else {
                if (line[0].equals("dir")) {
                    current.addChild(new Tree(line[1], current));
                } else {
                    current.addChild(new Tree(line[1], current, Integer.parseInt(line[0])));
                }
            }
        }
        filesystem.getSize(); //Calcule aussi les tailles des dossiers intermédiaires
    }

    public void easy() {
        //Tree.printTree(filesystem, 0);
        System.out.println(magicFunction(filesystem));
    }

    public void hard() {
        System.out.println(magicFunction2(filesystem, filesystem.getSize() - 40000000));
    }

    static int magicFunction(Tree t) {
        //t.printPath();
        //System.out.println("\tsize : " + t.getSize());
        if (!t.isDir()) {
            return 0;
        } else {
            int res = 0;
            if (t.getSize() < 100000) {
                //System.out.println("oui");
                res += t.getSize();
            }
            for (Tree child : t.children) {
                res += magicFunction(child);
            }
            return res;
        }
    }

    static int magicFunction2(Tree t, int neededSpace) {
        if (!t.isDir()) {
            return 0;
        } else {
            int minSpace = t.getSize();
            if (minSpace < neededSpace) {
                return minSpace;
            } else {
                for (Tree child : t.children) {
                    int space = magicFunction2(child, neededSpace);
                    if (neededSpace < space && space < minSpace) {
                        minSpace = space;
                    }
                }
                return minSpace;
            }
        }
    }
}
