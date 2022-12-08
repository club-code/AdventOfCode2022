package Day7;

import java.util.Vector;

class Tree {
    final String name;
    Vector<Tree> children;
    final Tree parent;
    int size;

    Tree(String name, Tree parent, int size) {
        this.name = name;
        this.parent = parent;
        this.size = size;
        //System.out.println("Creating file : " + name);
    }

    Tree(String name, Tree parent) {
        this.name = name;
        this.parent = parent;
        this.size = 0;
        this.children = new Vector<Tree>();
        //System.out.println("Creating dir : " + name);
    }

    Tree getChildByName(String name) {
        for (Tree child : children) {
            if (child.name.equals(name)) {
                return child;
            }
        }
        return null;
    }

    void addChild(Tree child) {
        children.add(child);
    }

    int getSize() {
        if (size == 0) {
            for (Tree child : children) {
                size += child.getSize();
            }
        }
        return size;
    }

    boolean isDir() {
        return children != null;
    }

    void printPath() {
        if (parent == null) {
            System.out.print("");
        } else {
            parent.printPath();
            System.out.print("/" + name);
        }
    }

    static void printTree(Tree t, int depth) {
        for (int i = 0; i<depth; i++) {
            System.out.print("\t");
        }
        System.out.println(t.name + " (" + t.getSize() + ")");
        if (t.isDir()) {
            for (Tree child : t.children) {
                printTree(child, depth+1);
            }
        }
    }
}
