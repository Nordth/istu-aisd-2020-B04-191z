package den23208;

import den23208.files.FilesWorker;
import den23208.indexer.Indexer;
import den23208.obj.Place;
import den23208.obj.Word;
import den23208.text.TextHelper;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Main m = new Main();
        m.start();
    }

    public void start() {
        FilesWorker fw = new FilesWorker();
        Indexer indexer = new Indexer();
        ArrayList<Path> files = new ArrayList<>();
        Scanner sc = new Scanner(System.in);

        while (true) {
            hint();
            int action = sc.nextInt();
            if (action == 1) {
                System.out.print("Path: ");
                String path = sc.next();
                files.clear();
                files.addAll(fw.loadFilesFromPath(path));
                for (Path p : files) {
                    try {
                        indexer.addWords(fw.getAllWords(p));
                    }
                    catch (IOException e) {
                        System.err.println("Can't load file: "+p.toString());
                    }
                }
            }
            else if (action == 2) {
                try {
                    indexer.saveState();
                    System.out.println("State saved.");
                }
                catch (Exception e) {
                    System.err.println("Can't save state.");
                }

            }
            else if (action == 3) {
                System.out.print("Print word: ");
                Word w = indexer.findWord(sc.next());
                if (w==null) {
                    System.out.println("Word not found!");
                }
                else {
                    if (indexer.checkPlaces(w)) {
                        System.out.println(w);
                        ArrayList<String> lines = new ArrayList<>();
                        for (Place p : w.getPlaces()) {
                            System.out.println(p);
                            try {
                                lines.clear();
                                lines.addAll(Files.readAllLines(Paths.get(p.getFile())));
                                for (Integer i : p.getRows()) {
                                    System.out.println("\t\tRow " + i + " : " + lines.get(i));
                                }
                            } catch (IOException e) {

                            }
                        }
                    }
                    else {
                        System.out.println("Word not found!");
                    }
                }
            }
            else if (action == 4) {
                System.out.print("Path: ");
                String path = sc.next();
                files.clear();
                files.addAll(fw.loadFilesFromPath(path));
                indexer.deletePlaces(files);
            }
            else break;
        }
    }

    public void hint(){
        System.out.println("1. Add files to indexing");
        System.out.println("2. Save state");
        System.out.println("3. Find word");
        System.out.println("4. Delete files from indexing");
    }
}
